#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "file_size_calculator.h"

typedef struct {
    short x, y;
    char string[100]; 
} MyText;

typedef struct {
    short x, y;
    int width, height;
} Outline;

typedef struct {
    short x, y;
    int width, height;
    short angle1, angle2;
} Arc;


FILE *input_file;

int main(int argc, char *argv[]) {
    Display* MainDisplay = XOpenDisplay(0);
    if (!MainDisplay) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    Window RootWindow = XDefaultRootWindow(MainDisplay);
    
    Window MainWindow = XCreateSimpleWindow(MainDisplay, RootWindow, 0, 0, 800, 600, 0, 0, 0x007FFFD4);

    // selecting types of inputs needed for drawing the items and moving the text with arrow keys 
    XSelectInput(MainDisplay, MainWindow, ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask);

    XStoreName(MainDisplay, MainWindow, "This is an attempt at making the text 'Hello World!' move");


    XGCValues value1 ;
    value1.line_width = 3; // to change the line weight of the brush for drawing the rectangle and arc 
    value1.line_style = LineSolid;

    GC gc = XCreateGC(MainDisplay, MainWindow , GCLineWidth | GCLineStyle, &value1);

    XSetForeground(MainDisplay, gc, 0x00DC143C);

    XMapWindow(MainDisplay, MainWindow);

    // making an atom that will close the window cleanly when the "Esc" key is pressed
    Atom wmDeleteMessage = XInternAtom(MainDisplay, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(MainDisplay, MainWindow, &wmDeleteMessage, 1);
    

    MyText label = {};
    int size = sizeGiver("fisier_intrare.txt");
    input_file = fopen("fisier_intrare.txt", "r");
    fgets(label.string, size + 1, input_file);
    fclose(input_file);

    int x = 100, y = 100;
    Outline border = {};
    border.width =  110;
    border.height = 40;

    Arc arc = {};
    arc.width =  130;
    arc.height = 110;
    arc.angle1 = 0;
    arc.angle2 = 360;


    XEvent event;
    int WindowIsOpened = 1;
    int PixelSpeed = 10;

    while(WindowIsOpened){
        XEvent WindowEvent = {};

        XNextEvent(MainDisplay, &WindowEvent);

        switch(WindowEvent.type){
            case KeyPress:
            case KeyRelease:{
                XKeyPressedEvent *Event = (XKeyPressedEvent *)&WindowEvent;
                if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_Escape))
                {
                    WindowIsOpened = 0;
                }

                if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_Down))
                {
                    y += PixelSpeed;
                }
                else if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_Up))
                {
                    y -= PixelSpeed;
                }
                else if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_Right))
                {
                    x += PixelSpeed;
                }
                else if(Event->keycode == XKeysymToKeycode(MainDisplay, XK_Left))
                {
                    x -= PixelSpeed;
                }
            } break;
            case ClientMessage:{
                XClientMessageEvent *Event = (XClientMessageEvent *) &WindowEvent;
                if((Atom)WindowEvent.xclient.data.l[0] == wmDeleteMessage) {
                    XDestroyWindow(MainDisplay, MainWindow);
                    WindowIsOpened = 0;
                }
            } break;
        }

        // getting the screen resolution limits , to make the text teleport from one margin of the screen
        // to the other 
        int X = DisplayWidth(MainDisplay, DefaultScreen(MainDisplay));
        int Y = DisplayHeight(MainDisplay, DefaultScreen(MainDisplay));

        if (x > X) {
            x = 0;
        } else if (x < 0) {
            x = X-3;
        }
        if(y > Y) {
            y = 0;
        } else if (y < 0) {
            y = Y -3;
        }

        XClearWindow(MainDisplay, MainWindow);
        XDrawRectangle(MainDisplay, MainWindow, gc, x, y, border.width, border.height);
        XDrawString(MainDisplay, MainWindow, gc, x + border.width/5, y + border.height/2, label.string, strlen(label.string));
        XDrawArc(MainDisplay, MainWindow, gc, x - 8, y - 40, arc.width, arc.height, arc.angle1 * 64, arc.angle2 * 64);
    }
    
    return 0;
}