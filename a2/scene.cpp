#include "scene.hpp"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <functional>

#include "keyframe.h"
#include "scenegraph.hpp"
#include "scene.hpp"

SceneNode *body,
          *l_shoulder,
          *r_shoulder,
          *l_elbow,
          *r_elbow,
          *head,
          *l_hip,
          *r_hip,
          *l_shin,
          *r_shin,
          *l_foot,
          *r_foot,
          *scene;

extern int renderPassMode;

Vector3 l_shoulder_offset,
        r_shoulder_offset,
        l_elbow_offset,
        l_elbow_rotation,
        r_elbow_offset,
        r_elbow_rotation,
        head_offset;

void invertZ(){
    glScalef(1, 1, -1);
}

void initScene() { 

    l_elbow = new SceneNode(
        [] (Keyframe & frame) {
            glTranslatef(0.01, -1.0f, 0.0f); // translate to the end of the arm
            invertZ(); //glScalef(1, 1, -1); // invert forward/back
            rotateAbout(
                {0, -0.5, 0}, // rotate about the top of the arm
                frame.getDOF(Keyframe::L_ELBOW),0,0); 
        },
        drawCube(&renderPassMode,
            {0.5f, 0.0f, 0.25f},
            0.2f, 0.5f, 0.2f),
        {});
    
    r_elbow = new SceneNode(
        [] (Keyframe & frame) {
            glTranslatef(-0.01f, -1.0f, 0.0f),
            invertZ();
            rotateAbout(
                {0, -0.5, 0},
                frame.getDOF(Keyframe::R_ELBOW),0,0);
        },
        drawCube(&renderPassMode,
            {0.5f, 0.0f, 0.25f},
            0.2f, 0.5f, 0.2f),
        {});
    
    l_shoulder = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(1.0f, 0.5f, 0.0f);
            rotateAbout({0,-0.25,0}, 
                frame.getDOF(Keyframe::L_SHOULDER_PITCH), 
                frame.getDOF(Keyframe::L_SHOULDER_YAW), 
                frame.getDOF(Keyframe::L_SHOULDER_ROLL));
        },
        drawCube(&renderPassMode,
                {1.0f, 0.0f, 0.5f}, //color
                0.2f, 0.5f, 0.2f), //dimensions
        {l_elbow});

    r_shoulder = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(-1.0f, 0.5f, 0.0f);
            rotateAbout({0,-0.25,0}, 
                frame.getDOF(Keyframe::R_SHOULDER_PITCH), 
                frame.getDOF(Keyframe::R_SHOULDER_YAW), 
                frame.getDOF(Keyframe::R_SHOULDER_ROLL));
        },
        drawCube(&renderPassMode,
                {1.0f, 0.0f, 0.5f}, //color
                0.2f, 0.5f, 0.2f), //dimensions
        {r_elbow});

    l_foot = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(0.0f, -0.4f, 0.3f);
        },
        drawCube(&renderPassMode,
            {1.0f, 0.0f, 0.5f}, //color
            0.15f, 0.05f, 0.35f),
        {}
    );

    l_shin = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(-0.01f, -0.6f, 0);
            rotateAbout({0, -0.3f, 0},
                frame.getDOF(Keyframe::L_KNEE), 0, 0);
        },
        drawCube(
            &renderPassMode,
            {1.0f, 0.4f, 0.4f},
            0.1f, 0.3f, 0.1f),
        {l_foot}
    );

    l_hip = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(-0.6f, -1.0f, 0.0f);
            rotateAbout({0.0f, -0.3f, 0.0f},
                frame.getDOF(Keyframe::L_HIP_PITCH),
                frame.getDOF(Keyframe::L_HIP_YAW),
                frame.getDOF(Keyframe::L_HIP_ROLL));
        },
        drawCube(
            &renderPassMode,
            {1.0f, 0.4f, 0.4f},
            0.1f, 0.3f, 0.1f),
        {l_shin}
    );

    r_foot = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(0.0f, -0.4f, 0.3f);
        },
        drawCube(&renderPassMode,
            {1.0f, 0.0f, 0.5f}, //color
            0.15f, 0.05f, 0.35f),
        {}
    );

    r_shin = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(0.01f, -0.6f, 0);
            rotateAbout({0, -0.3f, 0},
                frame.getDOF(Keyframe::R_KNEE), 0, 0);
        },
        drawCube(
            &renderPassMode,
            {1.0f, 0.4f, 0.4f},
            0.1f, 0.3f, 0.1f),
        {r_foot}
    );

    r_hip = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(0.6f, -1.0f, 0.0f);
            rotateAbout({0.0, -0.3f, 0.0f},
                frame.getDOF(Keyframe::R_HIP_PITCH),
                frame.getDOF(Keyframe::R_HIP_YAW),
                frame.getDOF(Keyframe::R_HIP_ROLL));
        },
        drawCube(
            &renderPassMode,
            {1.0f, 0.4f, 0.4f},
            0.1f, 0.3f, 0.1f),
        {r_shin}
    );

    head = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(0.0f, 2.0f, 0.0f),
            rotateAbout(
                {0, 0, 0},
                0,frame.getDOF(Keyframe::HEAD),0);
        },
        drawCube(&renderPassMode,
                 {0.5f, 0.0f, 1.0f},
                 0.5f, 0.5f, 0.5),
        {}
    );

    body = new SceneNode(
        [](Keyframe & frame) {
            glTranslatef(
                frame.getDOF(Keyframe::ROOT_TRANSLATE_X),
                frame.getDOF(Keyframe::ROOT_TRANSLATE_Y),
                frame.getDOF(Keyframe::ROOT_TRANSLATE_Z));
            rotateAbout(
                {0,0,0},
                frame.getDOF(Keyframe::ROOT_ROTATE_X),
                frame.getDOF(Keyframe::ROOT_ROTATE_Y),
                frame.getDOF(Keyframe::ROOT_ROTATE_Z));
            },
        drawCube(&renderPassMode,
                 {1.0f, 0.5f, 0.1f},
                 0.5f, 1.0f, 0.5f),
        {l_shoulder, r_shoulder, head, l_hip, r_hip}
    );

    scene = body;

    printf("scene initialized\n");
}


