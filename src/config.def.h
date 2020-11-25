#pragma once
#include "jdscn_types.h"

/** @file config.def.h */

/** @brief Default config file */
namespace config
{

/** @brief Keycode mapping */
struct keymap {
	int forward = 25;  // w
	int backward = 39; // s
	int left = 38;	   // a
	int right = 40;	   // d
	int up = 65;	   // space
	int down = 37;	   // control

	int exit = 24; // q
};

/** @brief Render window settings */
struct renderSettings {
	int width = 1280;
	int height = 720;
	float framerate = 30.0f;
	const char *title = "[floating] cool window";
};

/** @brief Camera movement settings */
struct camera_controls {
	float speed = 5;
	/** @brief Easing amount, higher means more time to reach cursor */
	float easing = 8;
	/** @brief Sensitivity, higher is slower */
	float sensitivity_x = 500;
	float sensitivity_y = sensitivity_x;
};

/** @brief Debug "minecraft" cursor settings */
struct debug_cursor {
	/** @brief enables the cursor */
	bool on = true;
	/** @brief maximum axis length */
	int length = 30;

	jdscn::Color x_axis = {255, 0, 0};
	jdscn::Color y_axis = {0, 255, 0};
	jdscn::Color z_axis = {0, 0, 255};
};

} // namespace config
