#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

GLfloat ambient_light[4];
typedef struct Scene
{
    Model raptor[11];
    Material material;
    GLuint texture_id;
} Scene;
typedef struct {
    int front, back, left, right, top;
}Skybox;
typedef struct Ground
{
    Material material;
    GLuint texture_id[7];
} Ground;
/**
 * Initialize the ground by loading models.
 */
void init_ground(Ground* ground);
/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene,const Camera* camera,const Ground* ground,int z,int k);

/**
 * Draw the origin of the world coordinate system.
 */

void draw_help();
void raptor_move(const Scene* scene,int k);
#endif /* SCENE_H */
