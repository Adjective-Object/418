#ifndef SCENEGRAPH
#define SCENEGRAPH

#include <functional>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glui.h>

typedef struct Color {
    float red;
    float green;
    float blue;
} Color;

typedef struct Transform {
    float translateX;
    float translateY;
    float translateZ;
    float rotation;
    float scaleX;
    float scaleY;
} Transform;

class SceneNode {
    Color color;

    protected:
        std::vector<SceneNode *> children;

    public:

        float internalTime;
        float internalTimeMax;
        
        SceneNode(float internalTimeMax,
                  std::function<float (float)> easingfn,
                  std::function<void (float)> applyParameter,
                  std::function<void ()> draw,
                  Transform baseTransform,
                  std::vector<SceneNode *> children);
        ~SceneNode();

        void update(float tDelta);
        void render();

        float param;
        
        // base transform of this matrix relative to the parent
        // (16 element float array)
        Transform  baseTransform;
    
        // apply the current value of the matrix as a transformation
        std::function<void (float param)> applyParameter;

        // animation function to generate the current value of the matrix 
        // based on loop time, tdelta, and current value of the parameter
        std::function<float (float time)> 
            generateParameter;

        // draw the actual model of the 2d object
        std::function<void ()> draw; 
};


// easing functions
float _normSin(float t);
extern std::function<float (float)> normSin;
std::function<float (float)> flatValue(float value);

// automation functions & their higher order counterparts
std::function<void (float)> rotateAbout(
        float xOff, float yOff, float thetaScale);
std::function<void (float)> scaledTranslate(float xOff, float yOff);
extern std::function<void (float)> doNothing;

// rendering functions & their higher order counterparts
void _drawRect(Color c, float x1, float y1, float x2, float y2);
std::function<void ()> drawRect(
        Color c, float x1, float y1, float x2, float y2);

void _drawPolygon(Color c, std::vector<std::pair<float, float>> verts);
std::function<void ()> drawPolygon(
        Color c, std::vector<std::pair<float, float>> verts);

void _drawNgon(Color c, int n, float radius);
std::function<void ()> drawNgon(Color c, int n, float radius);
std::function<void ()> conditionalRender(std::function<void ()> drawfn, int * control);

#endif
