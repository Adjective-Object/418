#include "scene.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "scenegraph.hpp"
#include "scene.hpp"
#include <functional>

SceneNode * leftThigh;
SceneNode * leftShin;
SceneNode * rightThigh;
SceneNode * rightShin;
SceneNode * body;
SceneNode * leftArm;
SceneNode * rightArm;
SceneNode * head;
SceneNode * eyeWhite;
SceneNode * eyePupil;
SceneNode * beakTop;
SceneNode * beakBottom;

SceneNode * scene;

extern int draw_joints;

void createPenguin() {
    glMatrixMode(GL_MODELVIEW);
   
    SceneNode * joint = new SceneNode(
        1.0f,
        flatValue(0),
        doNothing,
        conditionalRender(drawNgon({1, 1, 1}, 6, 2), &draw_joints),
        {0, 0, 10, 0, 1, 1},
        {}
    );

    std::function<void ()> drawShin = 
        drawRect({1.0f, 0.0f, 0.0f},
                 -2, 0, 2, -10);
   

    std::function<void ()> drawThigh = 
        drawRect({1.0f, 0.0f, 0.0f},
                 -2, 0, 2, -20);

    leftShin = new SceneNode(
        2.0f,
        normSin,
        rotateAbout(0, 0, 20),
        drawShin,
        {0, -18, 0, -90, 1, 1},
        {joint} 
    );

    leftThigh = new SceneNode(
        1.0f,    // number of seconds per animation loop
        normSin, // animate rotation in a sinusoidal pattern
        rotateAbout(0, 0, -20), // animate by rotating about some point
        drawThigh,
        {6, -14, 2, 0, 1, 1},
        {leftShin, joint}
    );

    rightShin = new SceneNode(
        2.0f,
        normSin,
        rotateAbout(0,0,20),
        drawShin,
        {0, -18, 0, -90, 1, 1},
        {joint}
    );

     rightThigh = new SceneNode(
        1.0f,    // number of seconds per animation loop
        normSin, // animate rotation in a sinusoidal pattern
        rotateAbout(0, 0, 20), // animate by rotating about some point
        drawThigh,
        {-6, -12, -2, 0, 1, 1},
        {rightShin, joint}
    );

     std::function<void ()> drawArm = drawPolygon(
        {0, 0, 1.0f}, 
        {{-5, -8},
         {-5,  2},
         {5,   2},
         {5,  -8},
         {0, -20}});

     leftArm = new SceneNode(
        1.2f,
        normSin,
        rotateAbout(0,0,60),
        drawArm,
        {5, 13, 1, 0, 1, 1},
        {joint}
    );


    rightArm = new SceneNode(
        1.2f,
        normSin,
        rotateAbout(0,0,-60),
        drawArm,
        {-5, 13, -1, 0, 1, 1},
        {joint}
    );

    beakBottom = new SceneNode(
        0.5f,
        normSin,
        scaledTranslate(0, 2),
        drawPolygon(
            {184.0f/255, 73.0f/255, 38.0f/255},
            {{0,   5},
             {-10, 5},
             {-10, 3},
             {0,   0}}),
        {-8, 3, -2, 0, 1, 1},
        {joint}
    );

    beakTop = new SceneNode(
        1.2f,
        flatValue(0),
        doNothing,
        drawPolygon(
            {184.0f/255, 73.0f/255, 38.0f/255},
            {{0,   5},
             {-10, 4},
             {-10, 0},
             {0,   0}}),
        {-8, 10, -2, 0, 1, 1},
        {}
    );

    eyePupil = new SceneNode(
        1.0f,
        normSin,
        scaledTranslate(1, 0),
        drawNgon({0, 0, 0}, 10, 2),
        {0, 0, 2, 0, 1, 1},
        {}
    );

    eyeWhite = new SceneNode(
        1.0f,
        flatValue(0),
        doNothing,
        drawNgon({1, 1, 1}, 8, 4),
        {2, 10, 2, 0, 1, 1},
        {eyePupil}
    );

    head = new SceneNode(
        3.0f,
        normSin,
        rotateAbout(0,0,3),
        drawPolygon(
            {0, 0, 0},
            {{-10, 0},
             {-8, 20},
             {8,  20},
             {10, 0}}),
        {0, 20, 1, 0, 1, 1},
        {beakTop, beakBottom, eyeWhite, joint}
    );

    
    body = new SceneNode(
        1.0f, // number of seconds per animation loop
        flatValue(0),
        doNothing,
        drawPolygon(
            {0, 1.0f, 0},
            {{-10,  20},
             { 10,  20},
             { 13, -16},
             {  0, -20},
             {-13, -16}}),
        {0, 0, 0, 0, 1, 1},
        {leftThigh, rightThigh, leftArm, rightArm, head}
    );

    scene = body;

    printf("scene initialized\n");
}


