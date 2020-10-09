#include "scene.h"
#include "win.h"
namespace draw
{

class Drawloop
{
	public:
	Win::Canvas c; 
	jdscn::Scene s;
	float interval;

	Drawloop(Win::Canvas& c, jdscn::Scene s, float framerate);
	void startLoop();
};

}; // draw

