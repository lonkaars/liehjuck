#pragma once
#include "scene.h"
#include "win.h"

/** @file draw.h */

/** @brief Draw loop */
namespace draw
{

/** @brief Saves references to the canvas and scene to draw, and starts a draw loop */
class Drawloop
{
	public:
	/** @brief The canvas to draw to */
	win::Canvas &canvas;
	/** @brief The scene to render */
	jdscn::Scene scene;

	jdscn::Scene startScene;
	/** @brief The framerate to render at */
	float interval;

	Drawloop(win::Canvas &canvas, jdscn::Scene scene, jdscn::Scene startscene, float framerate);
	/** @brief Start the drawloop */
	void startLoop();
};

}; // namespace draw
