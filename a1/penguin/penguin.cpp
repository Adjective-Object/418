/***********************************************************
             CSC418/2504, Fall 2009
  
                 penguin.cpp
                 
       Simple demo program using OpenGL and the glut/glui 
       libraries

  
    Instructions:
        Please read the assignment page to determine 
        exactly what needs to be implemented.  Then read 
        over this file and become acquainted with its 
        design.

        Add source code where it appears appropriate. In
        particular, see lines marked 'TODO'.

        You should not need to change the overall structure
        of the program. However it should be clear what
        your changes do, and you should use sufficient comments
        to explain your code.  While the point of the assignment
        is to draw and animate the character, you will
        also be marked based on your design.

***********************************************************/

#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <glui.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef _WIN32
#include <unistd.h>
#else
void usleep(unsigned int nanosec)
{
    Sleep(nanosec / 1000);
}
#endif

#include "scenegraph.hpp"
#include "scene.hpp"

// --------------- USER INTERFACE VARIABLES -----------------

// Window settings
int windowID;               // Glut window ID (for display)
GLUI *glui;                 // Glui window (for controls)
int Win[2];                 // window (x,y) size


// ---------------- ANIMATION VARIABLES ---------------------

// Animation settings
int animate_mode = 0;       // 0 = no anim, 1 = animate
int draw_joints = 0;
bool paused = true;

// Joint parameters

//////////////////////////////////////////////////////
// TODO: Add additional joint parameters here
//////////////////////////////////////////////////////

extern SceneNode * scene;

// ***********  FUNCTION HEADER DECLARATIONS ****************


// Initialization functions
void initGlut(char* winName);
void initGlui();
void initGl();


// Callbacks for handling events in glut
void myReshape(int w, int h);
void animate();
void display(void);

// Callback for handling events in glui
void GLUI_Control(int id);

// Return the current system clock (in seconds)
double getTime();

// ******************** FUNCTIONS ************************



// main() function
// Initializes the user interface (and any user variables)
// then hands over control to the event handler, which calls 
// display() whenever the GL window needs to be redrawn.
int main(int argc, char** argv)
{
    // Process program arguments
    if(argc != 3) {
        printf("Usage: demo [width] [height]\n");
        printf("Using 300x200 window by default...\n");
        Win[0] = 300;
        Win[1] = 200;
    } else {
        Win[0] = atoi(argv[1]);
        Win[1] = atoi(argv[2]);
    }

    // Initialize glut, glui, and opengl
    
    glutInit(&argc, argv);
    initGlut(argv[0]);
    initGl();
    createPenguin();
    initGlui();

    // Invoke the standard GLUT main event loop
    glutMainLoop();

    return 0;         // never reached
}


// Initialize glut and create a window with the specified caption 
void initGlut(char* winName)
{
    // Set video mode: double-buffered, color, depth-buffered
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Create window
    glutInitWindowPosition (0, 0);
    glutInitWindowSize(Win[0],Win[1]);
    windowID = glutCreateWindow(winName);

    // Setup callback functions to handle events
    glutReshapeFunc(myReshape); // Call myReshape whenever window resized
    glutDisplayFunc(display);   // Call display whenever new frame needed 
}


// Quit button handler.  Called when the "quit" button is pressed.
void quitButton(int)
{
  exit(0);
}

// Animate button handler.  Called when the "animate" checkbox is pressed.
void animateButton(int)
{
  // synchronize variables that GLUT uses
  glui->sync_live();

  if(animate_mode == 1) {
    // start animation
    GLUI_Master.set_glutIdleFunc(animate);
  } else {
    // stop animation
    GLUI_Master.set_glutIdleFunc(NULL);
    paused = true;
  }
}

void addNodePanel(GLUI * glui,
        GLUI_Panel * parent,
        const char * name, 
        SceneNode * node) {
    GLUI_Rollout * node_panel = glui->add_rollout_to_panel(parent, name, true);
    
    GLUI_Spinner * spinner = glui->add_spinner_to_panel(
            node_panel,
            "animation time",
            GLUI_SPINNER_FLOAT,
            &(node->internalTime));
    spinner->set_speed(1);
    spinner->set_float_limits(0, node->internalTimeMax, GLUI_LIMIT_WRAP);
    
    GLUI_Spinner * translatex = glui->add_spinner_to_panel(
            node_panel,
            "x translation",
            GLUI_SPINNER_FLOAT,
            &(node->baseTransform.translateX));
    translatex->set_speed(1);
    translatex->set_float_limits(-100, 100, GLUI_LIMIT_CLAMP);

    GLUI_Spinner * translatey = glui->add_spinner_to_panel(
            node_panel,
            "y translation",
            GLUI_SPINNER_FLOAT,
            &(node->baseTransform.translateY));
    translatey->set_speed(1);
    translatey->set_float_limits(-100, 100, GLUI_LIMIT_CLAMP);

    GLUI_Spinner * translatez = glui->add_spinner_to_panel(
            node_panel,
            "z translation",
            GLUI_SPINNER_FLOAT,
            &(node->baseTransform.translateZ));
    translatez->set_speed(1);
    translatez->set_float_limits(-100, 100, GLUI_LIMIT_CLAMP);

    glui->add_column_to_panel(
            node_panel,
            false);

    GLUI_Spinner * rotation = glui->add_spinner_to_panel(
            node_panel,
            "rotation",
            GLUI_SPINNER_FLOAT,
            &(node->baseTransform.rotation));
    rotation->set_speed(1);
    rotation->set_float_limits(-360, 360, GLUI_LIMIT_WRAP);
    
    GLUI_Spinner * scalex = glui->add_spinner_to_panel(
            node_panel,
            "x scale",
            GLUI_SPINNER_FLOAT,
            &(node->baseTransform.scaleX));
    scalex->set_speed(1);
    scalex->set_float_limits(0, 100, GLUI_LIMIT_WRAP);
    
    GLUI_Spinner * scaley = glui->add_spinner_to_panel(
            node_panel,
            "y scale",
            GLUI_SPINNER_FLOAT,
            &(node->baseTransform.scaleY));
    scaley->set_speed(1);
    scaley->set_float_limits(0, 100, GLUI_LIMIT_WRAP);

}

// Initialize GLUI and the user interface
void initGlui()
{
    GLUI_Master.set_glutIdleFunc(NULL);

    // Create GLUI window
    glui = GLUI_Master.create_glui("Penguin Control", 0, (Win[0]+10) * 2, 0);

    GLUI_Panel * node_section = glui->add_panel("", GLUI_PANEL_NONE);

    // Create a control to specify the rotation of the joint
    addNodePanel(glui, node_section, "body", body);
    addNodePanel(glui, node_section, "left thigh", leftThigh);
    addNodePanel(glui, node_section, "left shin", leftShin);
    addNodePanel(glui, node_section, "right thigh", rightThigh);
    addNodePanel(glui, node_section, "right shin", rightShin);
    glui->add_column_to_panel(node_section, false);
    addNodePanel(glui, node_section, "head", head);
    addNodePanel(glui, node_section, "beak bottom", beakBottom);
    addNodePanel(glui, node_section, "pupil", eyePupil);
    addNodePanel(glui, node_section, "right arm", rightArm);
    addNodePanel(glui, node_section, "left arm", leftArm);


    GLUI_Panel * control_section = glui->add_panel("", GLUI_PANEL_NONE);

    // Add button to specify animation mode 
    glui->add_checkbox_to_panel(
            control_section,
            "Animate", 
            &animate_mode, 0,
            animateButton);

    glui->add_column_to_panel(control_section, false);
    
    // Add button to control joint rendering
    glui->add_checkbox_to_panel(
            control_section,
            "draw joints", 
            &draw_joints);

    glui->add_column_to_panel(control_section, false);

    // Add "Quit" button
    glui->add_button_to_panel(
            control_section,
            "Quit", 0,
            quitButton);

    // Set the main window to be the "active" window
    glui->set_main_gfx_window(windowID);
}


// Performs most of the OpenGL intialization
void initGl(void)
{
    // glClearColor (red, green, blue, alpha)
    // Ignore the meaning of the 'alpha' value for now
    glClearColor(0.7f,0.7f,0.9f,1.0f);

    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_POLYGON_SMOOTH, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
}


int lastTime = 0;
// Callback idle function for animating the scene
void animate()
{
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    int timeDelta = currentTime - lastTime;
    lastTime = currentTime;

    // update the scene graph based on the elapsed time, unless resuming from paused frame
    if (paused) {
        scene->update(0.025f);
        paused = false;
    } else {
        scene->update(timeDelta/ 1000.0f);
    }
    
    // Update user interface
    glui->sync_live();

    // Tell glut window to update itself.  This will cause the display()
    // callback to be called, which renders the object (once you've written
    // the callback).
    glutSetWindow(windowID);
    glutPostRedisplay();


    // Wait 25 ms between frames (40 frames per second)
    usleep(25000);
}


// Handles the window being resized by updating the viewport
// and projection matrices
void myReshape(int w, int h)
{
    // Setup projection matrix for new window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w/2, w/2, -h/2, h/2, -100, 100);

    // Update OpenGL viewport and internal variables
    glViewport(0,0, w,h);
    Win[0] = w;
    Win[1] = h;
}

// display callback
//
// This gets called by the event handler to draw
// the scene, so this is where you need to build
// your scene -- make your changes and additions here.
// All rendering happens in this function.  For Assignment 1,
// updates to geometry should happen in the "animate" function.
void display(void)
{
    // glClearColor (red, green, blue, alpha)
    // Ignore the meaning of the 'alpha' value for now
    glClearColor(0.7f,0.7f,0.9f,1.0f);

    // OK, now clear the screen with the background colour
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

    // Setup the model-view transformation matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    ///////////////////////////////////////////////////////////
    // TODO:
    //   Modify this function draw the scene
    //   This should include function calls to pieces that
    //   apply the appropriate transformation matrice and
    //   render the individual body parts.
    ///////////////////////////////////////////////////////////
        
    // Draw the scene
    scene->render();

    // Execute any GL functions that are in the queue just to be safe
    glFlush();

    // Now, show the frame buffer that we just drew into.
    // (this prevents flickering).
    glutSwapBuffers();
}

