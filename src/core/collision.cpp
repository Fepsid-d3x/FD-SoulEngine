#include "../../include/core/collision.h"

bool fdse::is_collision_box(const fdse::Rect &a, const fdse::Rect &b){
    float dx = std::abs(a.x - b.x);
    float dy = std::abs(a.y - b.y);
    return dx < (a.w + b.w) / 2.0f && dy < (a.h + b.h) / 2.0f;
}
bool fdse::is_collision_circle(const fdse::Rect &a, const fdse::Rect &b){
    int ax = a.x + a.w / 2;
    int ay = a.y + a.h / 2;
    int bx = a.x + a.w / 2;
    int by = a.y + a.h / 2;
    int ar = a.w / 2;
    int br = b.w / 2;
    int dx = ax - bx;
    int dy = ay - by;
    
    return (dx * dx + dy * dy) <= ((ar + br) * (ar + br));
}
bool fdse::is_collision_pixel(const fdse::Rect &a, const PixelMask &maskA, const fdse::Rect &b, const PixelMask &maskB){
    if (maskA.empty() || maskB.empty()) return false;

    int left = std::max(a.x, b.x);
    int right = std::min(a.x + a.w, b.x + b.w);
    int top = std::max(a.y, b.y);
    int bottom = std::min(a.y + a.h, b.y + b.h);

    if (right <= left || bottom <= top)
        return false;

    float scaleXA = maskA[0].size() / a.w;
    float scaleYA = maskA.size() / a.h;
    float scaleXB = maskB[0].size() / b.w;
    float scaleYB = maskB.size() / b.h;

    for (int y = top; y < bottom; ++y){
        for (int x = left; x < right; ++x){
            int ax = static_cast<int>((x - a.x) * scaleXA);
            int ay = static_cast<int>((y - a.y) * scaleYA);
            int bx = static_cast<int>((x - b.x) * scaleXB);
            int by = static_cast<int>((y - b.y) * scaleYB);

            if (
                ay >= 0 && ay < static_cast<int>(maskA.size()) &&
                ax >= 0 && ax < static_cast<int>(maskA[0].size()) &&
                by >= 0 && by < static_cast<int>(maskB.size()) &&
                bx >= 0 && bx < static_cast<int>(maskB[0].size())
            ){
                if (maskA[ay][ax] && maskB[by][bx]){
                    return true;
                }
            }
        }
    }
    return false;
}