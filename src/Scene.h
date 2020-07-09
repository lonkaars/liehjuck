#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <exception>

// Position does not contain any significant behavior, thus making
// It sensible for x, y and z to be public
struct Position
{
    float x;
    float y;
    float z;

    Position(float X, float Y, float Z);
};

// Orientation does contains some behavior, mainly that an orientation
// can only be between 0 and 360
class Orientation
{
    float x;
    float y;
    float z;

    public:
        static float toDegrees(float degrees);

        Orientation(float X, float Y, float Z);

        // I'm not sure if it makes sense for these to be defined in 
        // the header or the normal file
        float getX();
        float getY();
        float getZ();
        void setX();
        void setY();
        void setZ();

};

// Each color must be between 0 and 255
class Color
{
    int red;
    int green;
    int blue;

    public:
        Color(int Red, int Green, int Blue);

        float getX();
        float getY();
        float getZ();
        void setX();
        void setY();
        void setZ();
};

class Camera
{

};

class Light
{
    
};

class Objects
{

};

class Scene
{

};

#endif