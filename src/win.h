#include "scene.h"

#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/utsname.h>

namespace win
{

class Win
{
	public:
	Window window;
	Display *display;
	int screen;
	
	Win()
	{
		display = XOpenDisplay(NULL);
		if (display == NULL) {
			fprintf(stderr, "Cannot open display\n");
			exit(1);
		}

		int screen = DefaultScreen(display);
		window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 660, 200, 1,
										 BlackPixel(display, screen), WhitePixel(display, screen));
		XSelectInput(display, window, ExposureMask | KeyPressMask);
		XMapWindow(display, window);

		Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False);
		XSetWMProtocols(display, window, &WM_DELETE_WINDOW, 1);

		XEvent e;
		while (1) {
			XNextEvent(display, &e);

			if ((e.type == ClientMessage) &&
				(static_cast<unsigned int>(e.xclient.data.l[0]) == WM_DELETE_WINDOW)) {
				break;
			}
		}

		XDestroyWindow(display, window);
		XCloseDisplay(display);
	}

	void Drawpixel(jdscn::Position2D pos)
	{
		XDrawPoint(display, window, DefaultGC(display, screen), pos[0], pos[1]);
	}
};
} // namespace win
