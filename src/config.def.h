#pragma once

/**
 * @file config.def.h
 *
 * Default config file
 */

/** @brief config namespace */
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
	float sensitivity_x = 500;
	float sensitivity_y = sensitivity_x;
};

} // namespace config
