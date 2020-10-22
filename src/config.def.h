namespace config {

/* static int controlforward = 25; */
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
	float framerate = 30.0f;
	const char *title = "[floating] cool window";
};

keymap keys;
renderSettings render;

}

