#include "Easing.h"

float Easing::EaseIn(float t)
{
    return t*t*t*t*t;
}

float Easing::EaseOut(float t)
{
    return 1.0f - (1-t) * (1-t) * (1-t) * (1-t);
}
