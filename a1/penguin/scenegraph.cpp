#include <tgmath.h>
#include "scenegraph.hpp"

#include <functional>

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
    for(std::vector<SceneNode *>::size_type i = 0;
            i < this->children.size(); i++) {
        this->children[i]->update(tDelta);
    }

    this->internalTime = (float) fmod(this->internalTime + tDelta,
                                      this->internalTimeMax); 
}


void SceneNode::render() {
    this->param = this->generateParameter(
                this->internalTime / this->internalTimeMax);
    
    glPushMatrix();
    
    // apply the specified base transformation
    glTranslatef(this->baseTransform.translateX,
                 this->baseTransform.translateY,
                 this->baseTransform.translateZ);
    glRotatef(this->baseTransform.rotation, 0, 0, 1);
    glScalef(this->baseTransform.scaleX, this->baseTransform.scaleY, 1);

    this->applyParameter(this->param);
    this->draw();

    for(std::vector<SceneNode *>::size_type i = 0;
            i < this->children.size(); i++) {
        this->children[i]->render();
    }

    glPopMatrix();
}



// Easing Functions
const float PI = 3.14159f;
float _normSin(float t) {
    return sin(t * 2 * PI);
}

std::function<float (float)> normSin = std::function<float (float)>(_normSin);

std::function<float (float)> flatValue(float value){
    return [=] (float time) {return value;};
}

float triangleWave (float t) {
    if (t<0.25f) {
        return 0.5 + t*2;
    } else if (t<0.75f) {
        return 1.0f - (t - 0.25f) *2;
    } else {
        return -1 - (1.0f - t) * 2;
    } 
}

// Paramater Application Functions

std::function<void (float)> rotateAbout( 
        float xOff, float yOff, float thetaScale) {
    return [=] (float param) { 
        glTranslatef(-xOff, -yOff, 0);
        glRotatef(param * thetaScale, 0.0f, 0.0f, 1.0f);
        glTranslatef(xOff,yOff, 0);
    };
}

std::function<void (float)> scaledTranslate( 
        float xOff, float yOff) {
    return [=] (float param) { 
        glTranslatef(xOff * param, yOff * param, 0);
    };
}

std::function<void (float)> doNothing = [] (float time) {};


// Drawing functions


// rectangle

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


// arbitrary polygon
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

// arbitrary polygon
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

//  control rendering on a switch

std::function<void ()> conditionalRender(std::function<void ()> renderFn, int * control) {
    return [=] () {
        if (* control) {
            renderFn();
        }
    };
}
