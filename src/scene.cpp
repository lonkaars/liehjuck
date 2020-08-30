#include <math.h>

// For position class
Position::Position(float px, float py, float pz)
{
    x = px;
    y = py;
    z = pz;
}


// For orientation class
float Orientation::toDegrees(float degrees)
{
    float result = fmod(degrees, 360);
    return result;
}

Orientation::Orientation(float ox, float oy, float oz)
{
    x = toDegrees(ox);
    y = toDegrees(oy);
    z = toDegrees(oz);
}


// For color class 

// In case of a color being bigger than 255 or smaller than 0, it should either:
// 1. Throw an exception
// 2. Default to a value of 0, which will result in a black
Color::Color(unsigned char cRed, unsigned char cGreen, unsigned char cBlue)
{
    red = cRed;
    green = cGreen;
    blue = cBlue;
}


// For camera class

Camera::Camera(Position pos, Orientation orent, float focalLen)
{
    position = pos;
    orientation = orent;
    focalLength = focalLen;
}

Camera::Camera(Position pos, Orientation orent)
{
    position = pos;
    orientation = orent;
    focalLength = 35;
}


// For scale class

float Scale::toScaleFactor(float scale)
{
    if(scale < 0)
    {
        return scale * -1;
    }
    else
    {
        return scale;
    }
    
}

Scale::Scale(float sx, float sy, float sz)
{
    x = sx;
    y = sy;
    z = sz;
}
