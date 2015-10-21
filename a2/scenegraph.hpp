#ifndef SCENEGRAPH
#define SCENEGRAPH

#include <functional>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>

#include "keyframe.h"

enum {WIREFRAME, SOLID, OUTLINED, MATTE, METALLIC};

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
    protected:
        std::vector<SceneNode *> children;

    public:
        SceneNode(std::function<void (Keyframe & currentFrame)> applyDOF,
                  std::function<void ()> draw,
                  std::vector<SceneNode *> children);
        ~SceneNode();

        void update(float tDelta);
        void render(Keyframe & dof);

        // use the current keyframe to generate the transform of this object
        std::function<void (Keyframe &)> applyDOF;

        // render the model of the object
        std::function<void ()> draw; 
};


// keyframing helper functions
void rotateAbout(Vector3 offset, float x, float y, float z); 

// rendering functions & their higher order counterparts
void _cube(Color c, float w, float h, float d);
std::function<void ()> cube(float w, float h, float d);
std::function<void ()> drawModel(
        int * renderStyle, Color c, std::function<void ()> draw);

void _drawPolygon(Color c, std::vector<std::pair<float, float>> verts);
std::function<void ()> drawPolygon(
        Color c, std::vector<std::pair<float, float>> verts);

void _drawNgon(Color c, int n, float radius);
std::function<void ()> drawNgon(Color c, int n, float radius);
std::function<void ()> conditionalRender(std::function<void ()> drawfn, int * control);

#endif
