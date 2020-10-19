#include "scene.h"
#include "win.h"
namespace draw
{

class Drawloop
{
	public:
	Win::Canvas canvas;
	jdscn::Scene scene;
	float interval;

	Drawloop(Win::Canvas &, jdscn::Scene &, float framerate);
	void startLoop();
};

}; // namespace draw
