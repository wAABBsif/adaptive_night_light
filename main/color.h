#pragma once

typedef struct color {
    float r;
    float g;
    float b;
} color;

#define RED     ((color){1.0, 0.0, 0.0})
#define GREEN   ((color){0.0, 1.0, 0.0})
#define BLUE    ((color){0.0, 0.0, 1.0})
#define BLACK   ((color){0.0, 0.0, 0.0})
#define WHITE   ((color){1.0, 1.0, 1.0})
