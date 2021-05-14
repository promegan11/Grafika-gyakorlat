#include "callbacks.h"
#include "utils.h"
#include <obj/draw.h>
#include <math.h>
#include <gl\glut.h>
#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0
bool help_on=FALSE;
struct {
    int x;
    int y;
} mouse_position;
int z=0,k=0;
float lastX,lastY;
bool firstMouse=TRUE,fut=FALSE;
void display()
{
     if(help_on==1)
    {
        glPushMatrix();
        draw_help(&ground);
        glPopMatrix();
    }else
    {
    glBindTexture(GL_TEXTURE_2D, scene.texture_id);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    set_view(&camera);
    if(fut==1)
    {
        if(z <10)
        {
            z++;   
        }else
        {
            z = 0;
        }
    }else
    {
        z=0;
    }
    if(k <10)
    {
            k++;   
    }else
    {
            k = 0;
    }
    draw_scene(&scene,&camera,&ground,z,k);
    glPopMatrix();
    glPushMatrix();

    glPopMatrix();
    glutSwapBuffers();

    }
   
   
}

void reshape(GLsizei width, GLsizei height)
{
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    if (!help_on)
    {
        gluPerspective( 45.0f, (GLdouble) width/height, 0.1f, 500.0f );
    }
    else
    {
        gluOrtho2D(0, width, height, 0);
    }
   
}

void mouse(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
       camera.position.z -= 1;
    }
    else
    {
        camera.position.z += 1;
        
    }
   
}

void motion(int x, int y)
{
   
    if (firstMouse)
    {
        lastX = x;
        lastY = y;
        firstMouse = FALSE;
    }
    float xoffset = x - lastX;
    float yoffset = y - lastY ; 
    lastX = x;
    lastY = y;
  
    camera.rotation.z -= (float) xoffset/3;
    camera.rotation.x -= (float) yoffset/3;
    if( camera.rotation.x < -30.0f )
        camera.rotation.x = -30.0f;
    if( camera.rotation.x > 30.0f )
        camera.rotation.x = 30.0f;
   

    
}
void keyboard(unsigned char key, int x, int y)
{
    const float cameraSpeed = 10.0f;
    float xrotrad,yrotrad, zrotrad;
    switch (key) {
    case 'w':
    {
        fut=TRUE;
        if(camera.position.x<91.0f)
            {
                zrotrad = degree_to_radian(camera.rotation.z);
                xrotrad =degree_to_radian(camera.rotation.x ); 
                camera.position.x += (float)(cos(zrotrad));
                //camera.position.z += (float)(sin(xrotrad));
                camera.position.y += (float)(sin(zrotrad));
                glutPostRedisplay();
            }else
            {
                camera.position.x = 91;
            }
        break;
    }
    case 's':
        { 
            fut=TRUE;
            if(camera.position.y<91.0f)
            {
                zrotrad = degree_to_radian(camera.rotation.z);
                xrotrad =degree_to_radian(camera.rotation.x ); 
                camera.position.x -= (float)(cos(zrotrad));
                //camera.position.z -= (float)(sin(xrotrad));
                camera.position.y -= (float)(sin(zrotrad));
                glutPostRedisplay();
            }else
            {
                camera.position.x = -91;
            }
        break;
    }
      
    case 'a':
        {
            fut=TRUE;
            if(camera.position.y<91.0f)
            {
                zrotrad = degree_to_radian(camera.rotation.z);
                xrotrad =degree_to_radian(camera.rotation.x );
                camera.position.x -= (float)(sin(zrotrad)) * 0.5f;
                camera.position.y += (float)(cos(zrotrad))* 0.5f;
                glutPostRedisplay();
            }else
            {
                camera.position.y = 91;
            }
        break;
    }
     case '+':
     {
     if (ambient_light[0] < 1)
            ambient_light[0] = ambient_light[1] = ambient_light[2] += 0.1;
        
        set_lighting();
        break;
    }
    case '-':
     {
     if (ambient_light[0] > -0.51)
            ambient_light[0] = ambient_light[1] = ambient_light[2] -= 0.1;
        set_lighting();
        break;
    }
    case 'd':
        {
            fut=TRUE;
            if(camera.position.y>-91.0f)
            {
                zrotrad = degree_to_radian(camera.rotation.z);
                xrotrad =degree_to_radian(camera.rotation.x );
                camera.position.x += (float)(sin(zrotrad)) * 0.5f;
                camera.position.y -= (float)(cos(zrotrad))* 0.5f;
                glutPostRedisplay();
            }else
            {
                camera.position.y = -91;
            }
        break;
    }
    case 27:
        exit(0);
  
    }

    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int x, int y)
{
    switch (key) {
    case 'w':
    case 's':
        fut=FALSE;
        break;
    case 'a':
    case 'd':
        fut=FALSE;
        break;
    
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

   //update_camera(&camera, elapsed_time);

    glutPostRedisplay();
}

void specialFunc(int key, int x, int y) {
	
	switch (key) {
	case GLUT_KEY_F1:
		if (help_on) {
			help_on = 0;

			reshape(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
		}
		else {
			help_on = 1;
			
		}
		break;
        case GLUT_KEY_LEFT:
        {

            camera.rotation.z+=1.0f;
            glutPostRedisplay();
        }
        break;
        case GLUT_KEY_RIGHT:
            camera.rotation.z-=1.0f;
            glutPostRedisplay();
        break;
        case GLUT_KEY_UP:
            camera.rotation.x+=1.0f;
            glutPostRedisplay();
        break;
        case GLUT_KEY_DOWN:
            camera.rotation.x-=1.0f;
            glutPostRedisplay();
        break;
    
	}

}


