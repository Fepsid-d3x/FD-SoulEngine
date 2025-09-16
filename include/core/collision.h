#ifndef COLLISION_H
#define COLLISION_H

#include <cmath>
#include <vector>

#include "./rect.h"
#include "../../include/graphics/sprite2d.h"

namespace fdse{
    using PixelMask = std::vector<std::vector<bool>>;

    bool is_collision_box(const fdse::Rect &a, const fdse::Rect &b);
    bool is_collision_circle(const fdse::Rect &a, const fdse::Rect &b);
    bool is_collision_pixel(const fdse::Rect &a, const PixelMask &mask_a, const fdse::Rect &b, const PixelMask &mask_b);
}
#endif