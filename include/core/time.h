#ifndef TIME_H
#define TIME_H

#include <cstdint>

namespace fdse{
    struct Time {
        double last_time = 0;
        float delta_seconds = 0.0f;

        void update();

        float delta() const { return delta_seconds; }
    };
}

#endif