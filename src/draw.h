#include "scene.h"
#include "win.h"

/** @file draw.h */

/**
 * @namespace draw
 *
 * @brief namespace handling the draw loop
 */
namespace draw
{

/**
 * @class Drawloop
 */
class Drawloop
{
	public:
	/** @brief The canvas to draw to */
	Win::Canvas& canvas;
	/** @brief The scene to render */
	jdscn::Scene& scene;
	/** @brief The framerate to render at */
	float interval;

	Drawloop(Win::Canvas &canvas, jdscn::Scene &scene, float framerate);
	/**
	 * @brief Start the drawloop
	 */
	void startLoop();
};

}; // namespace draw
