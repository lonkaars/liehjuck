#include "Scene.h"

#include <math.h>

// For position class
Position::Position(float X, float Y, float Z)
{
    x = X;
    y = y;
    z = Z;
}


// For orientation class
float Orientation::toDegrees(float degrees)
{
    float result = fmod(degrees, 360);
    return result;
}

Orientation::Orientation(float X, float Y, float Z)
{
    x = toDegrees(x);
    y = toDegrees(y);
    z = toDegrees(z);
}

// For color class

// In case of a color being bigger than 255 or smaller than 0, it should either:
// 1. Throw an exception
// 2. Default to a value of 0, which will result in a black color
Color::Color(int Red, int Green, int Blue)
{
    red = Red;
    green = Green;
    blue = Blue;
}