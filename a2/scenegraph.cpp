#include <tgmath.h>
#include "scenegraph.hpp"

#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;

SceneNode::SceneNode(
          float internalTimeMax,
          std::function<float (float)> easingfn,
          std::function<void (float)> applyParameter,
          std::function<void ()> draw,
          std::vector<SceneNode *> children)
            : generateParameter(easingfn),
              applyParameter(applyParameter),
              draw(draw),
              internalTime(0.0f),
              internalTimeMax(internalTimeMax),
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

    //printf("internalTime %f\n", this->internalTime);
}


void SceneNode::render() {
    this->param = this->generateParameter(
                this->internalTime / this->internalTimeMax);
    
    glPushMatrix(); 

    // printf("%f\n", this->param);

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

std::function<void (float)> scaledTranslate(float xOff, float yOff) {
    return [=] (float param) { 
        glTranslatef(xOff * param, yOff * param, 0);
    };
}

std::function<void (float)> doNothing = [] (float time) {};

std::function<void (float)> multiAnim(
        std::vector<std::function<void (float)>> anims) {
    return [anims] (float param) {
        cout << "anims: "<< anims.size() << endl;
        std::vector<std::function<void (float)>>::iterator it;
        for(int i=0; i<anims.size(); i++) {
            cout << "processing first..." << endl;
            anims[i](param);
        }
    };
}

std::function<void (float)> rotateAbout
        (Vector3 offset, Vector3 axis, float angle) {
    return [=](float param) {
        glTranslatef(-offset.x, -offset.y, -offset.z);
        glRotatef(angle * param, axis.x, axis.y, axis.z);
        glTranslatef(offset.x, offset.y, offset.z);
    };
}

std::function<void (float)> fixedRotate
        (Vector3 offset, float* x, float* y, float* z) {
    return [=](float param) {
        glTranslatef(-offset.x, -offset.y, -offset.z);
        glRotatef(*x, 1, 0, 0);
        glRotatef(*y, 0, 1, 0);
        glRotatef(*z, 0, 0, 1);
        glTranslatef(offset.x, offset.y, offset.z);
    };
}

std::function<void (float)> fixedScale
        (float* x, float* y, float* z) {
    return [=](float param) {
        glScalef(*x, *y, *z);
    };
}

std::function<void (float)> fixedTranslate
        (float* x, float* y, float* z) {
    return [=](float param) {glTranslatef(*x, *y, *z);};
}

// Drawing functions


// rectangle

// Draw a unit cube, centered at the current location
// README: Helper code for drawing a cube
void _drawCube(Color c, float w, float h, float d)
{
    glColor3f(c.red, c.green, c.blue);
	glBegin(GL_QUADS);
		// draw front face
		glVertex3f(-w, -h, d);
		glVertex3f( w, -h, d);
		glVertex3f( w,  h, d);
		glVertex3f(-w,  h, d);

		// draw back face
		glVertex3f( w, -h, -d);
		glVertex3f(-w, -h, -d);
		glVertex3f(-w,  h, -d);
		glVertex3f( w,  h, -d);

		// draw left face
		glVertex3f(-w, -h, -d);
		glVertex3f(-w, -h,  d);
		glVertex3f(-w,  h,  d);
		glVertex3f(-w,  h, -d);

		// draw right face
		glVertex3f( w, -h,  d);
		glVertex3f( w, -h, -d);
		glVertex3f( w,  h, -d);
		glVertex3f( w,  h,  d);

		// draw top
		glVertex3f(-w,  h,  d);
		glVertex3f( w,  h,  d);
		glVertex3f( w,  h, -d);
		glVertex3f(-w,  h, -d);

		// draw bottom
		glVertex3f(-w, -h, -d);
		glVertex3f( w, -h, -d);
		glVertex3f( w, -h,  d);
		glVertex3f(-w, -h,  d);
	glEnd();
}


std::function<void ()> drawCube(
        int * renderPassMode, Color c, float w, float h, float d) {
    return [=] ()  {
        if (*renderPassMode == SOLID) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            _drawCube(c, w, h, d);
        }

        if (*renderPassMode == WIREFRAME) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            _drawCube(c, w, h, d);
        }
        
        if (*renderPassMode == OUTLINED) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            _drawCube({0,0,0}, w, h, d);
        }
    };
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
    for (size_t i=0; i<points.size(); i++) {
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
