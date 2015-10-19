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

SceneNode * body;
SceneNode * l_shoulder;
SceneNode * r_shoulder;
SceneNode * l_elbow;
SceneNode * r_elbow;
SceneNode * head;
SceneNode * l_leg;
SceneNode * r_leg;
SceneNode * l_foot;
SceneNode * r_foot;

SceneNode * scene;

extern Keyframe * joint_ui_data;
extern int renderPassMode;

Vector3 l_shoulder_offset,
        r_shoulder_offset,
        l_elbow_offset,
        l_elbow_rotation,
        r_elbow_offset,
        r_elbow_rotation,
        head_offset;

float nothing = 0.0f;

Vector3 invert_z_vec = {1,1,-1};
std::function<void (float)> invertZ = fixedScale(
        &invert_z_vec.x,
        &invert_z_vec.y,
        &invert_z_vec.z);

void initScene() { 

    l_elbow_offset = {0.01f, -1.0f, 0.0f};
    l_elbow_rotation = {0.0f, 0.0f, 0.0f};
    l_elbow = new SceneNode(
        1.0f,
        normSin,
        multiAnim({
            fixedTranslate(
                &l_elbow_offset.x,
                &l_elbow_offset.y,
                &l_elbow_offset.z),
            invertZ,
            fixedRotate({0, -0.5, 0},
                joint_ui_data->getDOFPtr(Keyframe::L_ELBOW),
                &l_elbow_rotation.y,
                &l_elbow_rotation.z),
            }),
        drawCube(&renderPassMode,
            {0.5f, 0.0f, 0.25f},
            0.2f, 0.5f, 0.2f),
        {});
    
    r_elbow_offset = {-0.01f, -1.0f, 0.0f};
    r_elbow_rotation = {0.0f, 0.0f, 0.0f};
    r_elbow = new SceneNode(
        1.0f,
        normSin,
        multiAnim({
            fixedTranslate(
                &r_elbow_offset.x,
                &r_elbow_offset.y,
                &r_elbow_offset.z),
            invertZ,
            fixedRotate({0, -0.5, 0},
                joint_ui_data->getDOFPtr(Keyframe::R_ELBOW),
                &r_elbow_rotation.y,
                &r_elbow_rotation.z),
            }),
        drawCube(&renderPassMode,
            {0.5f, 0.0f, 0.25f},
            0.2f, 0.5f, 0.2f),
        {});
    
    l_shoulder_offset = {1.0f, 0.5f, 0.0f};
    l_shoulder = new SceneNode(
        1.0f,
        normSin,
        multiAnim({
            fixedTranslate(
                &l_shoulder_offset.x, 
                &l_shoulder_offset.y, 
                &l_shoulder_offset.z),
            fixedRotate({0,-0.25,0}, 
                joint_ui_data->getDOFPtr(Keyframe::L_SHOULDER_PITCH), 
                joint_ui_data->getDOFPtr(Keyframe::L_SHOULDER_YAW), 
                joint_ui_data->getDOFPtr(Keyframe::L_SHOULDER_ROLL))}),
       drawCube(&renderPassMode,
                {1.0f, 0.0f, 0.5f}, //color
                0.2f, 0.5f, 0.2f), //dimensions
       {l_elbow});

    r_shoulder_offset = {-1.0f, 0.5f, 0.0f};
    r_shoulder = new SceneNode(
        1.0f,
        normSin,
        multiAnim({
            fixedTranslate(
                &r_shoulder_offset.x, 
                &r_shoulder_offset.y, 
                &r_shoulder_offset.z),
            fixedRotate({0,-0.25,0}, 
                joint_ui_data->getDOFPtr(Keyframe::R_SHOULDER_PITCH), 
                joint_ui_data->getDOFPtr(Keyframe::R_SHOULDER_YAW), 
                joint_ui_data->getDOFPtr(Keyframe::R_SHOULDER_ROLL))}),
       drawCube(&renderPassMode,
                {1.0f, 0.0f, 0.5f}, //color
                0.2f, 0.5f, 0.2f), //dimensions
       {r_elbow});

    head_offset = {0.0f, 2.0f, 0.0f};
    head = new SceneNode(
        1.0f,
        normSin,
        multiAnim({
            fixedTranslate(
                &head_offset.x,
                &head_offset.y,
                &head_offset.z),
            fixedRotate(
                {0, 0, 0},
                &nothing,
                joint_ui_data->getDOFPtr(Keyframe::HEAD),
                &nothing)}),
        drawCube(&renderPassMode,
                 {0.5f, 0.0f, 1.0f},
                 0.5f, 0.5f, 0.5),
        {}
    );

    body = new SceneNode(
        1.0f, // number of seconds per animation loop
        normSin,
        multiAnim({
            fixedTranslate(
                joint_ui_data->getDOFPtr(Keyframe::ROOT_TRANSLATE_X),
                joint_ui_data->getDOFPtr(Keyframe::ROOT_TRANSLATE_Y),
                joint_ui_data->getDOFPtr(Keyframe::ROOT_TRANSLATE_Z)),
            fixedRotate(
                {0,0,0},
                joint_ui_data->getDOFPtr(Keyframe::ROOT_ROTATE_X),
                joint_ui_data->getDOFPtr(Keyframe::ROOT_ROTATE_Y),
                joint_ui_data->getDOFPtr(Keyframe::ROOT_ROTATE_Z))}),
        drawCube(&renderPassMode,
                 {1.0f, 0.5f, 0.1f},
                 0.5f, 1.0f, 0.5f),
        {l_shoulder, r_shoulder, head}
    );

    scene = body;

    printf("scene initialized\n");
}


