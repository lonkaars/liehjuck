#include "draw.h"
#include "jdscn_types.h"
#include <array>

/** @file camera.h */

/** @brief Mouse and keyboard input */
namespace controls
{

/** @brief Captures input and moves the scene camera */
class CameraController
{
	public:
	xcb_connection_t *connection;
	xcb_window_t window;

	CameraController(xcb_connection_t *c, xcb_window_t *w);

	/** @brief Array with keyboard state */
	std::array<bool, 255> keysPressed;
	/** @brief Target position of the camera, in the camera's local coordinate space */
	jdscn::Position cursor;
	/** @brief Mouse cursor position */
	jdscn::Position2D pointer;
	/** @brief Original camera rotation */
	jdscn::Orientation originalRotation;
	/** @brief Cursor capturing state */
	bool capturingCursor;
	/** @brief Frame width, used for cursor warping */
	int width;
	/** @brief Frame height, used for cursor warping */
	int height;

	/**
	 * @brief Start a thread that waits for an X event, and changes the
	 * keysPressed array accordingly
	 */
	void startInputLoop();
	/**
	 * @brief Moves the cursor accoring to the keys currently held
	 * @param float camera z rotation, used for relative coordinates with camera movement
	 */
	void moveCursor(float rotation);
	/** @brief Moves the cursor accoring to the keys currently held */
	jdscn::Orientation cameraRotation(int, int);
};

} // namespace controls
