#include <math.h>

#include "jdscn_types.h"
#include "scene.h"
#include "win.h"

namespace debug {

void line(jdscn::Position2D start, jdscn::Position2D end, jdscn::Color color, win::Canvas& canvas)
{
	//FIXME: This is duplicated code, there should be a 2D interpolation function in calc.cpp which can be extended as a line function
	int diffX = abs(start[0] - end[0]);
	int diffY = abs(start[1] - end[1]);
	bool scan = diffY > diffX;
	/* bool scan = 1; */

	int step = start[scan] > end[scan] ? -1 : 1;
	float change = float(end[!scan] - start[!scan]) / float(end[scan] - start[scan]);
	for(int y = start[scan]; y != end[scan] + step; y += step){
		int a = start[scan] + (y - start[scan]) * change;
		int b = start[scan] + (y - start[scan]);
		canvas.draw((scan ? a : b) + canvas.width / 2, (scan ? b : a) + canvas.height / 2, color);
	}
}

void draw_debug_axes(jdscn::Camera camera, win::Canvas& canvas)
{
	int length = 30;
	float updown = camera.orientation[0] - M_PI / 2;
	
	jdscn::Position2D z = {0, int(cos(updown) * -length)};
	jdscn::Position2D y = {int(cos(camera.orientation[2]) * length),
		int(-sin(camera.orientation[2]) * length * (updown / (M_PI / 2)))};
	jdscn::Position2D x = {int(sin(camera.orientation[2]) * length),
		int(cos(camera.orientation[2]) * length * (updown / (M_PI / 2)))};

	line({0, 0}, z, {0, 0, 255}, canvas);
	line({0, 0}, y, {0, 255, 0}, canvas);
	line({0, 0}, x, {255, 0, 0}, canvas);
}

};

