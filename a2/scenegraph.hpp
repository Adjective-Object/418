#ifndef SCENEGRAPH
#define SCENEGRAPH

#include <functional>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>

enum {WIREFRAME, SOLID, OUTLINED};

typedef struct Color {
    float red;
    float green;
    float blue;
} Color;

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

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
                  std::vector<SceneNode *> children);
        ~SceneNode();

        void update(float tDelta);
        void render();

        float param;
        
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
std::function<void (float)> rotateAbout
        (Vector3 offset, Vector3 axis, float angle);
std::function<void (float)> scaledTranslate(float xOff, float yOff);
extern std::function<void (float)> doNothing;


std::function<void (float)> fixedScale(float* x, float* y, float* z);
std::function<void (float)> fixedTranslate(float * x, float * y, float * z);
std::function<void (float)> fixedRotate(Vector3 offset, float * x, float * y, float * z);

std::function<void (float)> multiAnim(
        std::vector<std::function<void (float)>> anims);
 

// rendering functions & their higher order counterparts
void _drawCube(Color c, float w, float h, float d);
std::function<void ()> drawCube(
        int * renderStyle, Color c, float w, float h, float d);

void _drawPolygon(Color c, std::vector<std::pair<float, float>> verts);
std::function<void ()> drawPolygon(
        Color c, std::vector<std::pair<float, float>> verts);

void _drawNgon(Color c, int n, float radius);
std::function<void ()> drawNgon(Color c, int n, float radius);
std::function<void ()> conditionalRender(std::function<void ()> drawfn, int * control);

#endif
