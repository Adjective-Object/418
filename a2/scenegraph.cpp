#include <tgmath.h>
#include "scenegraph.hpp"

#include <functional>
#include <algorithm>
#include <iostream>

using namespace std;

SceneNode::SceneNode(
          std::function<void (Keyframe &)> applyDOF,
          std::function<void ()> draw,
          std::vector<SceneNode *> children)
            : applyDOF(applyDOF),
              draw(draw),
              children(children) {
}

SceneNode::~SceneNode() {
}
    
void SceneNode::render(Keyframe & dof) {
    glPushMatrix(); 
    
    this->applyDOF(dof);
    this->draw();

    for(std::vector<SceneNode *>::size_type i = 0;
            i < this->children.size(); i++) {
        this->children[i]->render(dof);
    }

    glPopMatrix();
}

void rotateAbout (Vector3 offset, Vector3 axis, float angle) {
        glTranslatef(-offset.x, -offset.y, -offset.z);
        glRotatef(angle, axis.x, axis.y, axis.z);
        glTranslatef(offset.x, offset.y, offset.z);
}

void rotateAbout (Vector3 offset, float x, float y, float z) {
    glTranslatef(-offset.x, -offset.y, -offset.z);
    glRotatef(x, 1, 0, 0);
    glRotatef(y, 0, 1, 0);
    glRotatef(z, 0, 0, 1);
    glTranslatef(offset.x, offset.y, offset.z);
}

// Drawing functions

// Draw a rectangular prism cube, centered at the current location
void _cube(float w, float h, float d)
{
	glBegin(GL_QUADS);
		// draw front face
        glNormal3f(0, 0, 1);
		glVertex3f(-w, -h, d);
        glNormal3f(0, 0, 1);
		glVertex3f( w, -h, d);
        glNormal3f(0, 0, 1);
		glVertex3f( w,  h, d);
        glNormal3f(0, 0, 1);
		glVertex3f(-w,  h, d);

		// draw back face
        glNormal3f(0, 0, -1);
		glVertex3f( w, -h, -d);
        glNormal3f(0, 0, -1);
		glVertex3f(-w, -h, -d);
        glNormal3f(0, 0, -1);
		glVertex3f(-w,  h, -d);
        glNormal3f(0, 0, -1);
		glVertex3f( w,  h, -d);

		// draw left face
        glNormal3f(-1, 0, 0);
		glVertex3f(-w, -h, -d);
        glNormal3f(-1, 0, 0);
		glVertex3f(-w, -h,  d);
        glNormal3f(-1, 0, 0);
		glVertex3f(-w,  h,  d);
        glNormal3f(-1, 0, 0);
		glVertex3f(-w,  h, -d);

		// draw right face
        glNormal3f(1, 0, 0);
		glVertex3f( w, -h,  d);
        glNormal3f(1, 0, 0);
		glVertex3f( w, -h, -d);
        glNormal3f(1, 0, 0);
		glVertex3f( w,  h, -d);
        glNormal3f(1, 0, 0);
		glVertex3f( w,  h,  d);

		// draw top
        glNormal3f(0, 1, 0);
		glVertex3f(-w,  h,  d);
        glNormal3f(0, 1, 0);
		glVertex3f( w,  h,  d);
        glNormal3f(0, 1, 0);
		glVertex3f( w,  h, -d);
        glNormal3f(0, 1, 0);
		glVertex3f(-w,  h, -d);

		// draw bottom
        glNormal3f(0, -1, 0);
		glVertex3f(-w, -h, -d);
		glVertex3f( w, -h, -d);
		glVertex3f( w, -h,  d);
		glVertex3f(-w, -h,  d);
	glEnd();
}

std::function<void ()> cube(float w, float h, float d) {
    return [=] () {_cube(w, h, d);};
}


std::function<void ()> drawModel(
        int * renderPassMode, Color c, 
        std::function<void ()> draw) {
    return [=] ()  {
        if (*renderPassMode == SOLID || 
            *renderPassMode == MATTE || 
            *renderPassMode == METALLIC) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glColor3f(c.red, c.green, c.blue);
            draw();
        }

        if (*renderPassMode == WIREFRAME) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(c.red, c.green, c.blue);
            draw();
        }
        
        if (*renderPassMode == OUTLINED) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glColor3f(0,0,0);
            draw();
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

// ngon
const float PI = 3.14159;

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
