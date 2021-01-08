
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

using std::vector;

void move(XPoint *points, int npoints, short rx, short ry) {
    for (int i = 0; i < npoints; i++) {
        points[i].x += rx;
        points[i].y += ry;
    }
}

void moveArc(XArc *krzywe, int nkrzywe, int rx, int ry) {
    for (int i = 0; i < nkrzywe; i++) {
        krzywe[i].x += rx;
        krzywe[i].y += ry;
    }
}

void rotate(XPoint *points, int npoints, int rx, int ry, float angle) {
    for (int i = 0; i < npoints; i++) {
        int x, y;
        float cos = cosf(angle);
        float sin = sinf(angle);
        x = points[i].x - rx;
        y = points[i].y - ry;
        points[i].x = rx + x * cos - y * sin;
        points[i].y = ry + x * sin + y * cos;
    }
}

void rotateArc(XArc *krzywe, int nkrzywe, int rx, int ry, float angle) {
    auto degree = angle * 57.2957795;
    while (degree >= 360) {
        degree -= 360;

    }
    for (int i = 0; i < nkrzywe; i++) {
        int x, y;
        float cos = cosf(angle);
        float sin = sinf(angle);
        x = krzywe[i].x - rx;
        y = krzywe[i].y - ry;
//        krzywe[i].x = rx + x * cos - y * sin;
//        krzywe[i].y = ry + x * sin + y * cos;
        krzywe[i].angle1 -= degree * 64;

//krzywe[i].angle2 += degree;



        std::cout << std::endl;


//        std::cout << degree << std::endl;
//
//        std::cout << "cos = " << cos << std::endl;
//        std::cout << "cos = " << cos << std::endl;
//        std::cout << "sin = " << sin << std::endl;

        auto d = (cos + 1);
        auto p = 1;

        krzywe[i].angle2 += degree;
//        krzywe[i].x -= 100 * abs(cos-1);

    }
}

//-90 * 64, 90 * 64
struct literka {
    vector<XPoint> punkty;
    vector<XArc> krzywe;
};

int main(int argc, char *argv[]) {
    char icon_name[] = "Icon";
    char title[] = "\U0001F64F";
    Display *display;
    Window window;
    GC gc;
    XEvent event;
    KeySym key;
    XSizeHints info;
    int screen_no;
    unsigned long foreground;
    unsigned long background;
    char buffer[8];
    int hm_keys;

    int to_end;
    XPoint current_point, previous_point;
    int i;
    //kolorki
    Colormap colormap;

    display = XOpenDisplay(0);
    screen_no = DefaultScreen(display);

    int blackColor = BlackPixel(display, DefaultScreen(display));
    int whiteColor = WhitePixel(display, DefaultScreen(display));

    colormap = DefaultColormap(display, screen_no);


    // kolory w trybie 24-bitowym:
    unsigned int blue = 255;
    unsigned int orange = 256 * 256 * 255 + 256 * 140 + 20;   // 256*256*Red + 256*Green + Blue

    info.x = 200;
    info.y = 250;
    info.width = 640;
    info.height = 480;
    info.flags = PPosition | PSize;


    window = XCreateSimpleWindow(display, DefaultRootWindow(display), 500, 200,
                                 800, 800, 0, blackColor, blackColor);
    XSetStandardProperties(display, window, title, icon_name, None,
                           argv, argc, &info);
    gc = XCreateGC(display, window, 0, 0);
    XMapWindow(display, window);

    XSetBackground(display, gc, background);
    XSetForeground(display, gc, foreground);

    int input_mask = KeyPressMask | ExposureMask | ButtonPressMask | PointerMotionMask | StructureNotifyMask |
                     //ResizeRedirectMask |
                     ButtonReleaseMask | Button1MotionMask | FocusChangeMask | EnterWindowMask | LeaveWindowMask;

    XSelectInput(display, window, (input_mask));
    XMapRaised(display, window);

    auto AllocNamedColor = [&](char *name) {  //funkcja do zwracania kolorkow
        XColor col;
        XParseColor(display, colormap, name, &col);
        XAllocColor(display, colormap, &col);
        return col;
    };

    auto red = AllocNamedColor("red");
    auto green = AllocNamedColor("green");

    int button_pressed = 0;   // czy klawisz myszy jest nacisniety

    long liczbapetli = 0;
    to_end = FALSE;

    for (;;) {
        XEvent e;
        XNextEvent(display, &e);
        if (e.type == MapNotify)
            break;
    }

//    std::cout << "LOL" << std::endl;

    while (to_end == FALSE) {

        while (XPending(display) == 0)  // dopoki liczba komunikatow w kolejce == 0
        {


            event.type = Expose;
            event.xexpose.count = 0;
            XSendEvent(display, window, 0, ExposureMask, &event);
        }
//        XCheckWindowEvent(display, window, input_mask, &event);
        XNextEvent(display, &event);         // pobranie z bufora kolejnego komunikatu
        switch (event.type) {
            case KeyPress:                   // wcisniecie klawisza na klawiaturze
                hm_keys = XLookupString(&event.xkey, buffer, 8, &key, 0);

                if ((hm_keys == 1) && (buffer[0] == 'q'))
                    to_end = TRUE;
                if ((hm_keys == 1) && (buffer[0] == '1')) {

                }

            case Expose: {
                literka a;
                a.punkty.push_back({0, 0});
                a.punkty.push_back({50, 0});
                a.punkty.push_back({120, 100});
                a.punkty.push_back({280, 100});
                a.punkty.push_back({350, 0});
                a.punkty.push_back({400, 0});
                a.punkty.push_back({200, 300});
                a.punkty.push_back({200, 230});
                a.punkty.push_back({250, 150});
                a.punkty.push_back({150, 150});
                a.punkty.push_back({200, 230});
                a.punkty.push_back({200, 300});
                a.punkty.push_back({0, 0});
                literka b;
                b.punkty.push_back({0, 0});
                b.punkty.push_back({200, 0});
                b.punkty.push_back({200, 50});
                b.punkty.push_back({200, 100});
                b.punkty.push_back({150, 150});
                b.punkty.push_back({150, 250});
                b.punkty.push_back({100, 300});
                b.punkty.push_back({0, 300});
                b.punkty.push_back({50, 250});
                b.punkty.push_back({100, 250});
                b.punkty.push_back({100, 200});
                b.punkty.push_back({50, 200});
                b.punkty.push_back({50, 250});
                b.punkty.push_back({0, 300});
                b.punkty.push_back({0, 0});
                b.punkty.push_back({50, 50});
                b.punkty.push_back({50, 100});
                b.punkty.push_back({150, 100});
                b.punkty.push_back({150, 50});
                b.punkty.push_back({50, 50});
                b.punkty.push_back({0, 0});
                b.krzywe.push_back({50, 200, 100, 100, 0, -90 * 64});
                liczbapetli += 1;


                XSetLineAttributes(display, gc, 4, LineSolid, CapRound, JoinRound);


//                std::cout << liczbapetli << std::endl;


                rotate(b.punkty.data(), b.punkty.size(), 100, 250, liczbapetli / 100.0);
                rotateArc(b.krzywe.data(), b.krzywe.size(), 50, 50, liczbapetli / 100.0);

                rotate(a.punkty.data(), a.punkty.size(), 200, 100, liczbapetli / 100.0);
                moveArc(b.krzywe.data(), b.krzywe.size(), 400, 350);
                move(b.punkty.data(), b.punkty.size(), 400, 350);
                move(a.punkty.data(), a.punkty.size(), 200, 100);


                XClearWindow(display, window);
                XSetForeground(display, gc, red.pixel);
                XDrawArcs(display, window, gc, b.krzywe.data(), b.krzywe.size());

                XDrawLines(display, window, gc, b.punkty.data(), b.punkty.size(), CoordModeOrigin);
                XSetForeground(display, gc, green.pixel);
                XFillArcs(display, window, gc, b.krzywe.data(), b.krzywe.size());
                XFillPolygon(display, window, gc, b.punkty.data(), b.punkty.size(), Complex, CoordModeOrigin);



                XSetForeground(display, gc, red.pixel);
                XDrawLines(display, window, gc, a.punkty.data(), a.punkty.size(), CoordModeOrigin);
                XSetForeground(display, gc, green.pixel);
                XFillPolygon(display, window, gc, a.punkty.data(), a.punkty.size(), Complex, CoordModeOrigin);

                XFlush(display);
                struct timespec tim, time2;
                tim.tv_sec = 0;
                tim.tv_nsec = 5 * 1000 * 10000;
                nanosleep(&tim, &time2);
                break;
            }
            case LeaveNotify:                        // kursor myszki znalazl sie poza obszarem okna
                break;
            case MotionNotify:                        // ruch myszy
            {
                if (button_pressed) {
                    current_point.x = event.xbutton.x;
                    current_point.y = event.xbutton.y;

                }
                break;
            }
            case ButtonPress:               // nacisniecie klawisza myszki
                button_pressed = 1;
                break;
            case ButtonRelease:               // puszczenie klawisza myszki
                button_pressed = 0;
                break;

            default:
                break;
        } // switch event

    }

    XFreeGC(display, gc
    );
    XDestroyWindow(display, window
    );
    XCloseDisplay(display);

    return 0;
}


