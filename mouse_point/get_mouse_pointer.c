/*================================================================
*   Copyright (C) 2019 Ltd. All rights reserved.
*   
*   File Name ：get_mouse_pointer.c
*   Author    ：hptsf
*   Date      ：2019-06-27
*   Descriptor： gcc -o get_mouse_pointer get_mouse_pointer.c -lX11
*
================================================================*/

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <X11/Xlib.h>

static int run_flag = 0;
static void sig_handler(int key)
{
    fprintf(stdout, "get a key: %d\n", key);
    run_flag = 0;
}

char *key_name[] = {
    "left",
    "second (or middle)",
    "right",
    "pull_up",
    "pull_down"
};
 
int main(int argc, char **argv)
{
    Display *display;
    XEvent xevent;
    Window window;
 
    if( (display = XOpenDisplay(NULL)) == NULL )
        return -1;
 
    window = DefaultRootWindow(display);
    XAllowEvents(display, AsyncBoth, CurrentTime);
 
    XGrabPointer(display,
                 window,
                 1,
                 PointerMotionMask | ButtonPressMask | ButtonReleaseMask ,
                 GrabModeAsync,
                 GrabModeAsync,
                 None,
                 None,
                 CurrentTime);

    run_flag = 1;
    signal(SIGINT, sig_handler); 
    while(run_flag){
        XNextEvent(display, &xevent);
 
        switch (xevent.type) {
        case MotionNotify:
            printf("Mouse move      : [%d, %d]\n", xevent.xmotion.x_root, xevent.xmotion.y_root);
            break;

        case ButtonPress:
            printf("Button pressed  : %s\n", key_name[xevent.xbutton.button - 1]);
            break;

        case ButtonRelease:
            printf("Button released : %s\n", key_name[xevent.xbutton.button - 1]);
            break;

        default:
            break;
        }
    }

    fprintf(stdout, "program will exit\n");

    return 0;
}
