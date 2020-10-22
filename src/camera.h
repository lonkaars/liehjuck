#include "draw.h"
#include "jdscn_types.h"
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <array>

/** @file camera.h */

/** @brief Namespace handling mouse and keyboard input */
namespace controls
{

/** @brief Captures input and moves the scene camera */
class CameraController
{
	public:
	/** @brief Array with keyboard state */
	std::array<bool, 255> keysPressed;
	Display *display;
	Window window;
	CameraController(Display *d, Window *w);
	/** @brief Start a thread that waits for an X event, and changes the keysPressed array
	 * accordingly */
	void startInputLoop();
	/** @brief Target position of the camera, in the camera's local coordinate space */
	jdscn::Position cursor;
	/** @brief Moves the cursor accoring to the keys currently held */
	void moveCursor();
};

} // namespace controls
