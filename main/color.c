#include "color.h"
#include "macros.h"

color color_lerp(color a, color b, float v) {
    return (color){LERP(a.r, b.r, v), LERP(a.g, b.g, v), LERP(a.b, b.b, v)};
}

color color_mult(color c, float v) {
    return (color){c.r * v, c.g * v, c.b * v};
}
