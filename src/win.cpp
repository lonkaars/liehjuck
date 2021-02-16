#include "win.h"
#include "scene.h"
#include "calc.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <thread>
#include <xcb/xcb.h>
#include <xcb/xcb_image.h>

namespace win
{

Canvas::Canvas(int width, int height, const char *title)
{
	this->width = width;
	this->height = height;
	this->title = title;

	connection = xcb_connect(NULL, NULL);
	display = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

	window = xcb_generate_id(connection);

	uint32_t rgb = 0xff000000;

	mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	uint32_t values[2] = {display->black_pixel, XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS |
													XCB_EVENT_MASK_KEY_RELEASE |
													XCB_EVENT_MASK_POINTER_MOTION |
													XCB_EVENT_MASK_BUTTON_PRESS};

	gc = xcb_generate_id(connection);
	xcb_create_gc(connection, gc, display->root, XCB_GC_FOREGROUND, &rgb);

	xcb_create_window(connection, XCB_COPY_FROM_PARENT, window, display->root, 0, 0, width, height,
					  0, XCB_WINDOW_CLASS_INPUT_OUTPUT, display->root_visual, mask, values);

	xcb_change_property(connection, XCB_PROP_MODE_REPLACE, window, XCB_ATOM_WM_NAME,
						XCB_ATOM_STRING, 8, strlen(title), title);

	frame = xcb_image_create_native(connection, this->width, this->height,
			XCB_IMAGE_FORMAT_Z_PIXMAP, 24, NULL, this->width*this->height*4, NULL);

	xcb_map_window(connection, window);

	xcb_flush(connection);

	xcb_generic_event_t *event;
	while ((event = xcb_wait_for_event(connection))) {
		if (event->response_type == XCB_EXPOSE)
			break;
		free(event);
	}
}

void Canvas::drawAbsolute(int x, int y, jdscn::Color c) {
	if (x > this->width - 1 || x < 0 || y > this->height - 1 || y < 0)
		return;

	int32_t rgb =
		pow(0x100, 3) + c[0] * pow(0x100, 2) + c[1] * pow(0x100, 1) + c[2] * pow(0x100, 0);
	xcb_image_put_pixel(frame, x, y, rgb);
}

void Canvas::draw(int x, int y, jdscn::Color c)
{
	x = this->width / 2 - x;
	y = this->height / 2 + y;
	drawAbsolute(x, y, c);
}

void Canvas::flush()
{
	xcb_image_put(connection, window, gc, frame, 0, 0, 0);
	xcb_flush(connection);
}

void Canvas::clear()
{
	memset(frame->data, 0, frame->size);
}

void Canvas::line(jdscn::Position2D start, jdscn::Position2D end, jdscn::Color c)
{
	std::vector<jdscn::Position2D> points =
		calc::interpolateBetweenPoints( jdscn::Position2D({ int(start[0]), int(start[1]) }),
				jdscn::Position2D({ int(end[0]), int(end[1]) }));
	for(jdscn::Position2D p : points)
		draw(p[0], p[1], c);
}

void Canvas::drawTriangle(jdscn::TriXY tri,
				  jdscn::Color c)
{
	for(int i = 0; i < tri.size(); i++) {
		int i_1 = (i+1)%tri.size();
		line({int(tri[i][0]), int(tri[i][1])},
				 {int(tri[i_1][0]), int(tri[i_1][1])},
				 c);
	}
}

// le trash propriatary binary search
int binarySearch(std::vector<jdscn::Position2D> input, int searchValue, std::array<int, 2> range) {
	int midpoint = (range[0] + range[1]) / 2;
	// reverse == 1 => klein -> groot
	// reverse == 0 => groot -> klein
	bool reverse = input.front()[1] > input.back()[1];

	if(searchValue == input[midpoint][1]) return midpoint;
	if(range[0] + 1 == range[1]) return midpoint;
	/* if(range[0] + 1 == range[1]) return midpoint; */
	// searchValue < input[.....] == true als midpoint rechts van searchValue zit (bij reverse == 0)
	/* std::cout << "s = " << searchValue << */
	/* 	"   p = " << input[midpoint][1] << */
	/* 	"   r = [" << range[0] << ", " << range[1] << "]" << */
	/* 	"   rev = " << reverse << */
	/* 	"   searchValue < input[midpoint][1] = " << int(searchValue < input[midpoint][1]) << */
	/* 	"   range[" << int(searchValue < input[midpoint][1] != reverse) << "]" << */
	/* 	std::endl; */
	/* std::this_thread::sleep_for(std::chrono::seconds(1)); */
	range[int(searchValue < input[midpoint][1] != reverse)] = midpoint;

	return binarySearch(input, searchValue, range);
}
int binarySearch(std::vector<jdscn::Position2D> input, int searchValue) {
	return binarySearch(input, searchValue, {0, int(input.size()-1)});
}

void swap(jdscn::TriXY& tri, int a, int b)
{
	jdscn::FloatXY buffer = tri[a];
	tri[a] = tri[b];
	tri[b] = buffer;
}

void Canvas::filledTriangle(jdscn::TriXY tri, jdscn::Color c)
{
	//std::cout << "start, ";
	//std::cout << "Drawing triangle: " << tri[0][0] << ", " << tri[0][1] << "; " << tri[1][0] << ", " << tri[1][1] << "; " << tri[2][0] << ", " << tri[2][1] << "; " << "with color " << c[2] << std::endl;

	drawTriangle(tri, c);

	int largestYI = 0;

	for(int i = 0; i < 3; i++)
	{
		if(tri[i][1] >= tri[largestYI][1])
			largestYI = i;

	}
	
	swap(tri, largestYI, 2);
	
	if(tri[1][1] < tri[0][1])
		swap(tri, 0, 1);

	//std::cout << "sorted tri, ";

	//std::cout << "Sorted triangle: " << tri[0][0] << ", " << tri[0][1] << "; " << tri[1][0] << ", " << tri[1][1] << "; " << tri[2][0] << ", " << tri[2][1] << "; " << "with color " << c[2] << std::endl;
	// pak die driehoek (rasterizeer)
	std::array<std::vector<jdscn::Position2D>, 3> triangle;

	triangle[0] = calc::interpolateBetweenPoints(
			jdscn::Position2D({int(tri[0][0]), int(tri[0][1])}),
			jdscn::Position2D({int(tri[1][0]), int(tri[1][1])}));
	triangle[1] = calc::interpolateBetweenPoints(
			jdscn::Position2D({int(tri[0][0]), int(tri[0][1])}),
			jdscn::Position2D({int(tri[2][0]), int(tri[2][1])}));
	triangle[2] = calc::interpolateBetweenPoints(
			jdscn::Position2D({int(tri[1][0]), int(tri[1][1])}),
			jdscn::Position2D({int(tri[2][0]), int(tri[2][1])}));

	/*std::cout << "triangle[1]" << std::endl;
	for(jdscn::Position2D pos : triangle[2])
	{
		std::cout << pos[0] << ", " << pos[1] << std::endl;
	}
	std::cout << "made lines, ";*/
	std::array<std::vector<jdscn::Position2D>, 2> diangle;
	diangle[0] = triangle[1];
	diangle[1].insert(diangle[1].end(), triangle[0].begin(), triangle[0].end());
	diangle[1].pop_back();
	diangle[1].insert(diangle[1].end(), triangle[2].begin(), triangle[2].end());

	// std::cout << "made diangle, ";
	
	for(int i = 0; i < diangle[0].size(); i++) {
		prettyLine(diangle[0][i], diangle[1][i], c);
	}
}

void Canvas::prettyLine(jdscn::Position2D start, jdscn::Position2D end, jdscn::Color color)
{
	int diffX = abs(start[0] - end[0]);
	int diffY = abs(start[1] - end[1]);
	bool scan = diffX > diffY;

	std::vector<jdscn::Position2D> points =
		calc::interpolateBetweenPoints( jdscn::Position2D({ int(start[scan]), int(start[!scan]) }),
				jdscn::Position2D({ int(end[scan]), int(end[!scan]) }));
	for(jdscn::Position2D p : points)
		draw(p[scan], p[!scan], color);
}

}; // namespace win
