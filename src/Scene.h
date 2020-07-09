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

    Position(float px, float py, float pz);
    Position(); // This is only needed because it has to have a default constructor
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

        Orientation(float ox, float oy, float oz);
        Orientation(); // This is only needed because it has to have a default constructor

        float getX() {return x;}
        float getY() {return y;}
        float getZ() {return z;}
        void setX(float degrees) {x = toDegrees(degrees);}
        void setY(float degrees) {y = toDegrees(degrees);}
        void setZ(float degrees) {z = toDegrees(degrees);}

};

// Each color must be between 0 and 255
// Used an unsigned char to have a number between 0 and 255
// I'm not sure if this is beautiful or really, really bad
// This class might be replacable by something in X11
class Color
{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

    public:
        Color(unsigned char cRed, unsigned char cGreen, unsigned char cBlue);

        unsigned char getRed();
        unsigned char getGreen();
        unsigned char getBlue();
        void setRed(unsigned char Red);
        void setGreen(unsigned char Green);
        void setBlue(unsigned char Blue);
};

class Camera
{
    Position position;
    Orientation orientation;
    float focalLength;

    public:
        Camera(Position pos, Orientation orent, float focalLen);
        Camera(Position pos, Orientation orent);
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