#pragma once

namespace config
{

struct keymap {
	int forward = 25;
	int backward = 39;
	int left = 38;
	int right = 40;
	int up = 65;
	int down = 37;
};

struct renderSettings {
	int width = 1280;
	int height = 720;
	float framerate = 60.0f;
	const char *title = "[floating] cool window";
};

struct camera_controls {
	float speed = 5;
};

} // namespace config
