#include "CitizenBalance.h"
#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;


CitizenBalance * cb;


unsigned int ignored_mask = LockMask | Mod1Mask | Mod2Mask | Mod3Mask | Mod4Mask | Mod5Mask;


void grab_key(Display* dpy, int keycode, int modifiers, Window win, Bool owner_events, int pointer_mode, int keyboard_mode){
	unsigned int imask = 0;
	for(unsigned int imask = 0; imask <= ignored_mask; imask++){
		if (imask & ~(ignored_mask))
        	{
			
         		continue;
        	}
        	
        	XGrabKey (dpy, keycode, modifiers | imask, win, True, GrabModeAsync, GrabModeSync);
        	
        	
	}
}

void ungrab_key(Display* dpy, int keycode, int modifiers, Window win){
	unsigned int imask = 0;
	for(unsigned int imask = 0; imask <= ignored_mask; imask++){
		if (imask & ~(ignored_mask))
        	{
			
         		continue;
        	}
        	
        	XUngrabKey(dpy,keycode,modifiers,win);
        	
        	
	}
}


void swallow_keystroke(Display * dpy, XEvent * ev){
	XAllowEvents(dpy, AsyncKeyboard, ev->xkey.time);
}

void passthru_keystroke(Display * dpy, XEvent * ev)
{
    XAllowEvents(dpy, ReplayKeyboard, ev->xkey.time);
    XFlush(dpy);
}

static const string s = "xdotool type --clearmodifiers ";

void keypress_callback(){

	double d = cb->get_mass();

	string cmd = s + "\"" + to_string(d) + "\"";
	cout << "Sent command: " << cmd << endl;


	std::system(cmd.c_str());

}

#define TEST


#ifdef TEST
int main()
{

	cb = new CitizenBalance("/dev/ttyS0");
	cb->tare();
	cout << cb->get_mass_string() << endl;
	cout << cb->get_mass() << endl;
//cout << cb->get_mass_string() << endl;

//cout << cb->get_mass_string() << endl;

    //cb->testcommand();
	
    //cb->get_mass();


	return 0;
}



#endif




#ifndef TEST
int main()
{

    cb = new CitizenBalance("/dev/ttyS0");

    cb->get_mass();


    Display*    dpy     = XOpenDisplay(0);
    Window      root    = DefaultRootWindow(dpy);
    XEvent      ev;

    unsigned int    modifiers       = ControlMask | ShiftMask;
    int             keycode         = XKeysymToKeycode(dpy,XK_space);
    Window          grab_window     =  root;
    Bool            owner_events    = False;
    int             pointer_mode    = GrabModeAsync;
    int             keyboard_mode   = GrabModeAsync;

    grab_key(dpy, keycode, modifiers, grab_window, owner_events, pointer_mode, keyboard_mode);

	

	int keysyms_per_keycode;
	KeySym *keysym = XGetKeyboardMapping (dpy, keycode, 1, &keysyms_per_keycode);

	//cout << XKeysymToString (keysym[0]) << endl;
	
    XSelectInput(dpy, root, KeyPressMask );
    while(true)
    {
        bool shouldQuit = false;
        XNextEvent(dpy, &ev);
        if(ev.type == KeyRelease){
        
                keypress_callback();
                swallow_keystroke(dpy, &ev);

        }else if(ev.type == KeyPress){
       		swallow_keystroke(dpy, &ev);
        }else{
        	passthru_keystroke(dpy, &ev);
        }
        if(shouldQuit)
            break;
    }

    ungrab_key(dpy,keycode,modifiers,grab_window);
    XCloseDisplay(dpy);
    return 0;
}

#endif

