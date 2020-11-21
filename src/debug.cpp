#include <math.h>

#include "jdscn_types.h"
#include "scene.h"
#include "win.h"
#include "config.h"
#include "calc.h"

namespace debug {


void draw_debug_axes(jdscn::Camera camera, win::Canvas& canvas)
{
	config::debug_cursor settings;
	int length = settings.length;
	float updown = camera.orientation[0] - M_PI / 2;
	float leftright = -camera.orientation[2] - M_PI / 2;
	
	jdscn::Position2D z = {0, int(cos(updown) * -length)};
	jdscn::Position2D y = {int(cos(leftright) * length),
		int(-sin(leftright) * length * (updown / (M_PI / 2)))};
	jdscn::Position2D x = {int(sin(leftright) * length),
		int(cos(leftright) * length * (updown / (M_PI / 2)))};

	canvas.prettyLine({0, 0}, z, settings.z_axis);
	canvas.prettyLine({0, 0}, y, settings.y_axis);
	canvas.prettyLine({0, 0}, x, settings.x_axis);
}

};

