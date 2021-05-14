#ifndef CAMERA_H
#define CAMERA_H


#include "utils.h"
/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
} Camera;

/**
 * Is the texture preview visible?
 */


/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Update the position of the camera.
 */

void set_view(const Camera* camera);


#endif /* CAMERA_H */
