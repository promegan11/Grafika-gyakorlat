#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "camera.h"
#include "scene.h"

#include <GL/glut.h>

/**
 * Scene
 */
Scene scene;
/**
 * Ground
 */
Ground ground;

/**
 * Camera
 */
Camera camera;

/**
 * Call when need to display the graphical content.
 */
void display();

/**
 * Call after windows resizing.
 */
void reshape(GLsizei width, GLsizei height);

/**
 * Call after mouse button event.
 */
void mouse(int button, int state, int x, int y);

/**
 * Call after mouse event.
 */
void motion(int x, int y);

/**
 * Call after keyboard event.
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Call after keyboard release event.
 */
void keyboard_up(unsigned char key, int x, int y);

/**
 * Call when there is no other event.
 */
void idle();
/**
*Special key functions
*/
void specialFunc(int key, int x, int y);

#endif /* CALLBACKS_H */