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
	int forward = 25;
	int backward = 39;
	int left = 38;
	int right = 40;
	int up = 65;
	int down = 37;
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
	float easing = 8;
};

} // namespace config
