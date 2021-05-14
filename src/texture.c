#include "texture.h"
#include "scene.h"
#include <SOIL/SOIL.h>
GLuint load_texture(char* filename)
{
    GLuint texture_name;
    glGenTextures(1, &texture_name);

    int width;
    int height;

    Pixel* image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture_name;
}
void draw_ground(GLuint* texture_id) {
    
    glMatrixMode(GL_MODELVIEW);
    glBindTexture(GL_TEXTURE_2D, texture_id[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -100.0f, -100, -9.0f );
        glTexCoord2f(0, 1); glVertex3f( -100.0f, 100,  -9.0f );
        glTexCoord2f(1, 1); glVertex3f(  100.0f, 100,  -9.0f );
        glTexCoord2f(1, 0); glVertex3f(  100.0f, -100, -9.0f );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture_id[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -100.0f, -100.0f, -100.0f );
        glTexCoord2f(1, 1); glVertex3f( 100.0f, -100.0f, -100.0f );
        glTexCoord2f(1, 0); glVertex3f( 100.0f,  -100.0f, 100.0f );
        glTexCoord2f(0, 0); glVertex3f(  -100.0f,  -100.0f, 100.0f );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture_id[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 1); glVertex3f(  -100.0f, 100.0f,  -100.0f );
        glTexCoord2f(0, 1); glVertex3f(  100.0f,  100.0f, -100.0f );
        glTexCoord2f(0, 0); glVertex3f(  100.0f,  100.0f, 100.0f );
        glTexCoord2f(1, 0); glVertex3f(  -100.0f, 100.0f, 100.0f );
        
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(1, 0); glVertex3f( -100.0f, 100.0f,  -100.0f );
        glTexCoord2f(1, 1); glVertex3f(  -100.0f, 100.0f,  100.0f );
        glTexCoord2f(0, 1); glVertex3f(  -100.0f,  -100.0f,  100.0f );
        glTexCoord2f(0, 0); glVertex3f( -100.0f,  -100.0f,  -100.0f );
 
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -100.0f, -100, 100.0f );
        glTexCoord2f(0, 1); glVertex3f( -100.0f, 100,  100.0f );
        glTexCoord2f(1, 1); glVertex3f(  100.0f, 100,  100.0f );
        glTexCoord2f(1, 0); glVertex3f(  100.0f, -100, 100.0f );
    glEnd();
    glBindTexture(GL_TEXTURE_2D, texture_id[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( 100.0f,  100.0f, 100.0f );
        glTexCoord2f(0, 0); glVertex3f( 100.0f,  100.0f,  -100.0f );
        glTexCoord2f(1, 0); glVertex3f(  100.0f,  -100.0f,  -100.0f );
        glTexCoord2f(1, 1); glVertex3f(  100.0f,  -100.0f, 100.0f );
    glEnd();
   
   } 
   
