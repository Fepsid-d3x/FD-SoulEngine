#ifndef RECT_H
#define RECT_H

namespace fdse {
    struct Rect {
        Rect() : x(0), y(0), w(0), h(0) {}
        Rect(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

        float x, y;
        float w, h;
    };
}

#endif