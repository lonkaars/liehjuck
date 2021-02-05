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

// le trash propriatary binary search (propriatary in dat het alleen voor Canvas::filledTriangles wordt gebruikt en geen generic binary search implementatie is)
int binarySearch(std::vector<jdscn::Position2D> input, int searchValue, std::array<int, 2> range) {
	int midpoint = (range[0] + range[1]) / 2;
	bool reverse = input.front()[1] > input.back()[1];

	if(searchValue == input[midpoint][1]) return midpoint;
	if(range[0] + 1 == range[1]) return midpoint;

	range[int(searchValue < input[midpoint][1] != reverse)] = midpoint;

	return binarySearch(input, searchValue, range);
}
int binarySearch(std::vector<jdscn::Position2D> input, int searchValue) {
	return binarySearch(input, searchValue, {0, int(input.size()-1)});
}

void Canvas::filledTriangle(jdscn::TriXY tri, jdscn::Color c)
{
	drawTriangle(tri, c); // tri is alleen de eindpunten van de 3 hoeken van de driehoek

	// pak die driehoek (rasterizeer)
	std::array<std::vector<jdscn::Position2D>, 3> triangle; // triangle (goed gekozen naam :^)) is een std::array van gerasterizeerde lijnen (std::vector van jdscn::Position2D (int, int))
	for(int i = 0; i < 3; i++){
		int i_1 = (i+1)%3; // Dit tekent de driehoek met lijnen van i = [0, 1], [1, 2] en [2, 0]
		std::vector<jdscn::Position2D> points = calc::interpolateBetweenPoints(
				jdscn::Position2D({ int(tri[i][0]), int(tri[i][1]) }),
				jdscn::Position2D({ int(tri[i_1][0]), int(tri[i_1][1]) }));
		triangle[i] = points;
	}

	// bepaal langste zijde
	int largestY = tri[0][1], smallestY = largestY, // hier initializeer ik met een waarde uit de tri zodat ik niet een smallestY of largestY instel die niet bestaat
		resolvedSide = 0;

	for (int i = 0; i < 3; i++) { // deze zoekt voor elk eindpunt voor de hoogste Y en de laagste Y coordinaat
		largestY = std::max(largestY, int(tri[i][1]));
		smallestY = std::min(smallestY, int(tri[i][1]));
	}

	for (int i = 0; i < 3; i++) { // deze geeft de index van triangle waarin de zijde staat met zowel de hoogste als de laagste Y
		if ((triangle[i].front()[1] == largestY && triangle[i].back()[1] == smallestY) ||
			(triangle[i].front()[1] == smallestY && triangle[i].back()[1] == largestY)) {
			resolvedSide = i;
		}
	}

	/**
	 * diangle = triangle - 1 zijde (stom woordgrapje) dit voegt de overige
	 * zijdes (niet triangle[resolvedSide]) toe aan een nieuwe variabele die
	 * het zelfde is als triangle maar met twee zijdes
	 * */
	std::array<std::vector<jdscn::Position2D>, 2> diangle;
	diangle[0] = triangle[resolvedSide];
	diangle[1].insert(diangle[1].end(), triangle[(resolvedSide+1)%3].begin(), triangle[(resolvedSide+1)%3].end());
	diangle[1].insert(diangle[1].end(), triangle[(resolvedSide+2)%3].begin(), triangle[(resolvedSide+2)%3].end());

	/**
	 * loopt over diangle[0] (hoogste en laagste Y zijde) en tekent een lijn
	 * van elke x-coordinaat van diangle[0] naar de x-coordinaat van diangle[1]
	 * met binary search (is onnodig want beide arrays hebben dezelfde "step",
	 * begin en einde, maar binarySearch moet hier want het begin en einde van
	 * de lijnen die samengevoegd zijn in de 'alinea' hierboven zitten twee
	 * keer in diangle[1]) (verbetering mogelijk?)
	 * */
	for(jdscn::Position2D end : diangle[0]) {
		jdscn::Position2D begin = diangle[1][binarySearch(diangle[1], end[1])];
		prettyLine(begin, end, c); //FIXME: maak expliciet horizontale en verticale lijn ipv prettyLine die eerst kijkt of de lijn steiler dan 45 graden is (je weet hier dat het altijd een horizontale lijn zal zijn)
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
