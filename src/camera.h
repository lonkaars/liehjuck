#include <array>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#include "draw.h"
#include "jdscn_types.h"

/** @brief Namespace handling mouse and keyboard input */
namespace controls {

class CameraController {
	public:
	std::array<bool, 255> keysPressed;
	Display *display;
	Window window;
	CameraController(Display *d, Window *w);
	void startInputLoop();
	jdscn::Position cursor;
	void moveCursor();
};

}
