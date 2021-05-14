#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/glut.h>
#include <obj/model.h>

typedef GLubyte Pixel[3];

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename);
void draw_ground(GLuint* texture_id);
void initialize_texture(GLuint texture_id[6],float y);
#endif /* TEXTURE_H */

