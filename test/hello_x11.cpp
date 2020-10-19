#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/utsname.h>

int main(int argc, char** argv)
{
    Display* dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
		fprintf(stderr, "Cannot open display\n");
		exit(1);
    }

    int s = DefaultScreen(dpy);
    Window win = XCreateSimpleWindow(dpy, RootWindow(dpy, s), 10, 10, 660, 200, 1,
	BlackPixel(dpy, s), WhitePixel(dpy, s));
    XSelectInput(dpy, win, ExposureMask | KeyPressMask);
    XMapWindow(dpy, win);

    //XStoreName(dpy, win, "Geeks3D.com - X11 window under Linux (Mint 10)");

    Atom WM_DELETE_WINDOW = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(dpy, win, &WM_DELETE_WINDOW, 1);
	GC gc = XCreateGC(dpy, win, 0, NULL);
	XEvent e;
	int i = 100;
  	while (1) 
  	{
    XNextEvent(dpy, &e);
	XDrawPoint(dpy, win, gc, i, i);
    if (e.type == KeyPress)
    {
     	 char buf[128] = {0};
     	 KeySym keysym;
     	 int len = XLookupString(&e.xkey, buf, sizeof buf, &keysym, NULL);
     	 if (keysym == XK_Escape)
        break;
    }
 
    if ((e.type == ClientMessage) && 
        (static_cast<unsigned int>(e.xclient.data.l[0]) == WM_DELETE_WINDOW))
    {
      break;
    }
	i++;
  }
    XDestroyWindow(dpy, win);
    XCloseDisplay(dpy);
    return 0;
}
