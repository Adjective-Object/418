#include <tgmath.h>
#include "scenegraph.hpp"

#include <functional>
#include <vector>

SceneNode::SceneNode(
          float internalTimeMax,
          std::function<float (float)> easingfn,
          std::function<void (float)> applyParameter,
          std::function<void ()> draw,
          Transform baseTransform,
          std::vector<SceneNode *> children)
            : generateParameter(easingfn),
              applyParameter(applyParameter),
              draw(draw),
              internalTime(0.0f),
              internalTimeMax(internalTimeMax),
              baseTransform(baseTransform),
              children(children) {
}

SceneNode::~SceneNode() {
}
    
void SceneNode::update(float tDelta) {
    // update the internal animation timer by incrementing it by tDelta,
    // and do the same to all children of this scene node
    for(std::vector<SceneNode *>::size_type i = 0;
            i < this->children.size(); i++) {
        this->children[i]->update(tDelta);
    }

    this->internalTime = (float) fmod(this->internalTime + tDelta,
                                      this->internalTimeMax); 
}


void SceneNode::render() {
    // generate the animation parameter based on the internal time counter
    // and the timing function of the SceneNode
    this->param = this->generateParameter(
                this->internalTime / this->internalTimeMax);
    
    glPushMatrix();
    
    // apply the specified base transformation
    glTranslatef(this->baseTransform.translateX,
                 this->baseTransform.translateY,
                 this->baseTransform.translateZ);
    glRotatef(this->baseTransform.rotation, 0, 0, 1);
    glScalef(this->baseTransform.scaleX, this->baseTransform.scaleY, 1);

    // apply the animation parameter before drawing and draw the element
    this->applyParameter(this->param);
    this->draw();

    for(std::vector<SceneNode *>::size_type i = 0;
            i < this->children.size(); i++) {
        this->children[i]->render();
    }

    glPopMatrix();
}


//////////////////////
// Easing Functions //
//////////////////////

// normalized sinusoid (period of 1)
const float PI = 3.14159f;
float _normSin(float t) {return sin(t * 2 * PI);}
std::function<float (float)> normSin = std::function<float (float)>(_normSin);

// holding a flat value
std::function<float (float)> flatValue(float value){
    return [=] (float time) {return value;};
}

// triangle wave (UNTESTED)
float triangleWave (float t) {
    if (t<0.25f) {
        return 0.5 + t*2;
    } else if (t<0.75f) {
        return 1.0f - (t - 0.25f) *2;
    } else {
        return -1 - (1.0f - t) * 2;
    } 
}

/////////////////////////////////////
// Paramater Application Functions //
/////////////////////////////////////

// rotate about an x,y point in the local coordinate space of the object
// in range (-thetaScale, thetaScale)
std::function<void (float)> rotateAbout( 
        float xOff, float yOff, float thetaScale) {
    return [=] (float param) { 
        glTranslatef(-xOff, -yOff, 0);
        glRotatef(param * thetaScale, 0.0f, 0.0f, 1.0f);
        glTranslatef(xOff,yOff, 0);
    };
}

// translate between (-xOff, -yOff) -> (xOff, yOff)
std::function<void (float)> scaledTranslate( 
        float xOff, float yOff) {
    return [=] (float param) { 
        glTranslatef(xOff * param, yOff * param, 0);
    };
}

// do no animation
std::function<void (float)> doNothing = [] (float time) {};


///////////////////////
// Drawing functions //
///////////////////////

// draw a rectange
std::function<void ()> drawRect(
        Color c, float x1, float y1, float x2, float y2) {
    return [=] () { _drawRect(c, x1, y1, x2, y2); };
}
void _drawRect(Color color, float x1, float y1, float x2, float y2) {    
    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POLYGON);
    glVertex2d(x1,y1);
    glVertex2d(x2,y1);
    glVertex2d(x2,y2);
    glVertex2d(x1,y2);
    glEnd();
}


// draw an arbitrary polygon
std::function<void ()> drawPolygon(
        Color color, std::vector<std::pair<float, float>> points) {
    return [=] () {_drawPolygon(color, points);};
}
void _drawPolygon(Color color, std::vector<std::pair<float, float>> points) {
    glColor3f(color. red, color.green, color.blue);
    glBegin(GL_POLYGON);
    for (int i=0; i<points.size(); i++) {
        glVertex3d(points[i].first, points[i].second, 0);
    }
    glEnd();
}

// draw an nGon
std::function<void ()> drawNgon(Color color, int n, float radius) {
    return [=] () {_drawNgon(color, n, radius);};
}

void _drawNgon(Color color, int n, float radius) {
    glColor3f(color. red, color.green, color.blue);
    glPushMatrix();
    float rStep = 2 * PI / n;
    float angle = 0;
    
    glBegin(GL_POLYGON);
    for (int i=0; i<n; i++) {
        glVertex3d(cos(angle) * radius, sin(angle) * radius, 0);
        angle += rStep;
    }
    
    glEnd();
    glPopMatrix();
}

// control the use of anothe rendering function based on a boolean switch
// (actually an int switch because of the types required by glui)
std::function<void ()> conditionalRender(
        std::function<void ()> renderFn, int * control) {
    return [=] () {
        if (* control) {
            renderFn();
        }
    };
}
