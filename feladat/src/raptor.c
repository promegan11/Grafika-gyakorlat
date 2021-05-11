#ifdef WIN32
#include <windows.h>
#endif

#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "model.h"
#include "draw.h"

typedef int bool;
#define true 1
#define false 0

#include <gl\glut.h>
#include <gl\glext.h>

static float ang;

typedef GLubyte Pixel[3];

Pixel* images[8];
GLuint texture_names[8];

int z,k, help_on = 0;
bool fut = false;

struct Vector3
{
	float x, y, z;
};
struct Model model[11];

struct ThirdPersonCamera_t
{
	struct Vector3 vecPos;
	struct Vector3 vecRot;
	float fRadius;
	float fLastX;
	float fLastY;
};


			
#define respawn_time 500		

struct ThirdPersonCamera_t camera;
GLuint floor_tex = 0;
GLint hits = 0;


void glEnable2D( void )
{
	GLint iViewport[4];

	glGetIntegerv( GL_VIEWPORT, iViewport );

	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();

	glOrtho( iViewport[0], iViewport[0]+iViewport[2],
			 iViewport[1]+iViewport[3], iViewport[1], -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();

	glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
}


void glDisable2D( void )
{
	glPopAttrib();
	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
	glPopMatrix();
}


void glPrintf( int x, int y, void* font, char* string, ... )
{
	char *c;
	char temp[256];
	va_list ap;

	va_start( ap, string );
	vsprintf( temp, string, ap );
	va_end( ap );

	glEnable2D();

	glRasterPos2i(x,y);

	for (c=temp; *c != '\0'; c++) 
	{
		glutBitmapCharacter(font, *c);
	}

	glDisable2D();
}

float distance( const struct Vector3* v1, const struct Vector3* v2 )
{
	float d = 0.0f;
	float x = v2->x - v1->x;
	float y = v2->y - v1->y;
	float z = v2->z - v1->z;

	x *= x;
	y *= y;
	z *= z;

	d = sqrt(x+y+z);

	return d;
}

void calculate_distances( void )
{
	int i;
	struct Vector3 neg_camera;

	neg_camera.x = camera.vecPos.x * -1.0f;
	neg_camera.y = 0.0f;
	neg_camera.z = camera.vecPos.z * -1.0f;

	
}
GLuint load_texture(char* filename, Pixel* image)
{
    GLuint texture_name;
    glGenTextures(1, &texture_name);

    int width;
    int height;

    image = (Pixel*)SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (Pixel*)image);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    return texture_name;
}

void initialize_texture()
{
    unsigned int i;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
    texture_names[0] = load_texture("skin/raptor.png", images[0]);
    texture_names[1] = load_texture("back/arrakisday_bk.png", images[1]);
    texture_names[2] = load_texture("back/arrakisday_dn.png", images[2]);
	texture_names[3] = load_texture("back/arrakisday_lf.png", images[3]);
	texture_names[4] = load_texture("back/arrakisday_ft.png", images[4]);
	texture_names[5] = load_texture("back/arrakisday_up.png", images[5]);
	texture_names[6] = load_texture("back/arrakisday_rt.png", images[6]);
	texture_names[7] = load_texture("back/help.png", images[7]);

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

	glEnable(GL_TEXTURE_2D);
}

void floor_render( float size, float y )
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glTranslatef( 0.0f, 0.7f, 0.0f );

    glBindTexture(GL_TEXTURE_2D, texture_names[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  100.0f, -100.0f, -100.0f );
        glTexCoord2f(1, 0); glVertex3f( -100.0f, -100.0f, -100.0f );
        glTexCoord2f(1, 1); glVertex3f( -100.0f,  100.0f, -100.0f );
        glTexCoord2f(0, 1); glVertex3f(  100.0f,  100.0f, -100.0f );
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture_names[1]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(  100.0f, -100.0f,  100.0f );
        glTexCoord2f(1, 0); glVertex3f(  100.0f, -100.0f, -100.0f );
        glTexCoord2f(1, 1); glVertex3f(  100.0f,  100.0f, -100.0f );
        glTexCoord2f(0, 1); glVertex3f(  100.0f,  100.0f,  100.0f );
    glEnd();
 
    glBindTexture(GL_TEXTURE_2D, texture_names[6]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -100.0f, -100.0f,  100.0f );
        glTexCoord2f(1, 0); glVertex3f(  100.0f, -100.0f,  100.0f );
        glTexCoord2f(1, 1); glVertex3f(  100.0f,  100.0f,  100.0f );
        glTexCoord2f(0, 1); glVertex3f( -100.0f,  100.0f,  100.0f );
 
    glEnd();
 
    glBindTexture(GL_TEXTURE_2D, texture_names[4]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -100.0f, -100.0f, -100.0f );
        glTexCoord2f(1, 0); glVertex3f( -100.0f, -100.0f,  100.0f );
        glTexCoord2f(1, 1); glVertex3f( -100.0f,  100.0f,  100.0f );
        glTexCoord2f(0, 1); glVertex3f( -100.0f,  100.0f, -100.0f );
    glEnd();
 
    glBindTexture(GL_TEXTURE_2D, texture_names[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 1); glVertex3f( -100.0f,  100.0f, -100.0f );
        glTexCoord2f(0, 0); glVertex3f( -100.0f,  100.0f,  100.0f );
        glTexCoord2f(1, 0); glVertex3f(  100.0f,  100.0f,  100.0f );
        glTexCoord2f(1, 1); glVertex3f(  100.0f,  100.0f, -100.0f );
    glEnd();
 
    glBindTexture(GL_TEXTURE_2D, texture_names[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f( -100.0f, y, -100.0f );
        glTexCoord2f(0, 1); glVertex3f( -100.0f, y,  100.0f );
        glTexCoord2f(1, 1); glVertex3f(  100.0f, y,  100.0f );
        glTexCoord2f(1, 0); glVertex3f(  100.0f, y, -100.0f );
    glEnd();
	glPopMatrix();

}
void set_lightings()
{
    GLfloat light_position[] = { 50.0, 50.0, -50.0, 0.0 };
    GLfloat light_ambient[] = { 1, 1, 1, 0 };
    GLfloat light_diffuse[] = { 0.5, 0.5, 0, 0 };
    GLfloat light_specular[] = { 1, 1, 1, 0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
}

void draw_crosshair( void )
{
	float fViewport[4];
	float w = 32.0f, h = 32.0f;

	glGetFloatv( GL_VIEWPORT, fViewport ); 

	glEnable2D();

	glBegin( GL_LINES );
		glColor3f( 1.0f, 1.0f, 0.0f );
		glVertex2f( (fViewport[2]/2.0f)-(w/2.0f), fViewport[3]/2.0f );
		glVertex2f( (fViewport[2]/2.0f)+(w/2.0f), fViewport[3]/2.0f );
		glVertex2f( fViewport[2]/2.0f, (fViewport[3]/2.0f)-(h/2.0f) );
		glVertex2f( fViewport[2]/2.0f, (fViewport[3]/2.0f)+(h/2.0f) );
	glEnd();

	glDisable2D();
}


int InitScene( void )
{
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glClearDepth( 1.0f );

	set_lightings();
	
	glEnable( GL_COLOR_MATERIAL );

	glDisable( GL_TEXTURE_2D );

	glDisable( GL_BLEND );

	glDisable( GL_DITHER );

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );

	k=0;
	z=0;
	initialize_texture();

	int i;
	char mod[11][25]={"model/raptor.obj","model/raptor_000001.obj","model/raptor_000002.obj","model/raptor_000003.obj","model/raptor_000004.obj","model/raptor_000005.obj","model/raptor_000006.obj",
	"model/raptor_000007.obj","model/raptor_000008.obj","model/raptor_000009.obj","model/raptor_000010.obj"};
	for(i=0;i<11;++i)
	{
		load_model(mod[i],&model[i]);
	}

	 
	memset( &camera, 0, sizeof( struct ThirdPersonCamera_t ) );
	camera.fRadius = 25.0f;

	srand( time( NULL ) );

	return GL_TRUE;
}
void raptor_move(int leptek,float pozx,float pozy, float rotx)
{
	glTranslatef( pozx, 0.0f, pozy-(k*leptek) );
	glRotatef( rotx, 0.0f, 1.0f, 0.0f );
	
	
	if (k<11)
	{
		
		draw_model(&model[k]);
		Sleep(100);
		k+=1;
		
	}
	if(k==11)
	{
		
		k=0;
	}
	glRotatef( 0, 0.0f, 1.0f, 0.0f );
	glTranslatef( 100, 0.0f, -100);
}
void DisplayFunction( void )
{
	if (!help_on) {
	int iViewport[4];
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	glLoadIdentity();
	
	glTranslatef( 0.0f, -7.0f, -camera.fRadius );
	glRotatef( camera.vecRot.x, 1.0f, 0.0f, 0.0f );
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		
	glPushMatrix();	

	glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	
	if(fut==false)
	{
	draw_model(&model[0]);
	}
	if(fut==true)
	{
	draw_model(&model[z]);
	
	Sleep(150);
	z+=1;
	
	}
	
	glGetIntegerv( GL_VIEWPORT, iViewport );
	glPopMatrix();
	}
	glPopAttrib();
	glRotatef( camera.vecRot.y, 0.0f, 1.0f, 0.0f );
	glTranslatef( -camera.vecPos.x, 0.0f, -camera.vecPos.z );
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	{
		glEnable(GL_LIGHTING);
		
	    GLfloat light_ambient[] = { 0, 0, 0, 0 };
    GLfloat light_diffuse[] = { 0.0, 0.0, 0, 0 };
    GLfloat light_specular[] = { 0, 0, 0, 0 };
    
	    glMaterialfv(GL_COLOR_MATERIAL, GL_AMBIENT, light_ambient);
	    glMaterialfv(GL_COLOR_MATERIAL, GL_DIFFUSE, light_diffuse);
	    glMaterialfv(GL_COLOR_MATERIAL, GL_SPECULAR, light_specular);
	    glMaterialf(GL_COLOR_MATERIAL, GL_SHININESS, 90.0f);


	    glBindTexture(GL_TEXTURE_2D, texture_names[0]);
		glPushMatrix();	
		
		raptor_move(3,20,-10,0);
		glGetIntegerv( GL_VIEWPORT, iViewport );
		glPopMatrix();
		
	}
	glPopAttrib();
	glPushMatrix();	
	glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	raptor_move(5,40,-30,50);
	glGetIntegerv( GL_VIEWPORT, iViewport );
	glPopMatrix();
	glPushMatrix();	
	glBindTexture(GL_TEXTURE_2D, texture_names[0]);
	raptor_move(-2,-40,60,-180);
	glGetIntegerv( GL_VIEWPORT, iViewport );
	glPopMatrix();

	floor_render( 50.0f, -0.75f );


	glBindTexture(GL_TEXTURE_2D, 0);

	

	glutSwapBuffers();
	ang++;
	if(ang>=360.0f)
	{
		ang=0.0f;
	}
	if(z==11)
	{
		z=0;
	}

	
}else
{
	
	draw_help();

}
	

}
void specialFunc(int key, int x, int y) {
	
	switch (key) {
	case GLUT_KEY_F1:
		if (help_on) {
			help_on = 0;

			ReshapeFunction(1024,768);
		}
		else {
			help_on = 1;

			
		}
	}

}
void draw_help() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glBindTexture(GL_TEXTURE_2D, texture_names[7]);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(0, 0, 0);

	glTexCoord2f(1, 0);
	glVertex3f(1024, 0, 0);

	glTexCoord2f(1, 1);
	glVertex3f(1024, 768, 0);
	
	glTexCoord2f(0, 1);
	glVertex3f(0, 768, 0);
	glEnd();
	ReshapeFunction(1024,768);
	

	glutSwapBuffers();
}

void IdleFunction( void )
{

	glutPostRedisplay();
}

void KeyboardFunction( GLubyte k, int x, int y )
{
	static float fRotSpeed = 1.0f;
	if (k=='q')
    {
    	
		camera.vecRot.x += fRotSpeed;
		if (camera.vecRot.x > 360) camera.vecRot.x -= 360;
    }
    else if (k=='z')
    {
    	
		camera.vecRot.x -= 1;
		if (camera.vecRot.x < -360) camera.vecRot.x += 360;
    }
    else if (k=='w')
    {
		fut=true;
		float xrotrad, yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		xrotrad = (camera.vecRot.x / 180.0f * 3.141592654f); 
		camera.vecPos.x += (float)(sin(yrotrad));
		camera.vecPos.z -= (float)(cos(yrotrad));
		camera.vecPos.y -= (float)(sin(xrotrad));
					
    }
    else if (k=='s')
    {
    	fut=true;
		float xrotrad, yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		xrotrad = (camera.vecRot.x / 180.0f * 3.141592654f); 
		camera.vecPos.x -= (float)(sin(yrotrad));
		camera.vecPos.z += (float)(cos(yrotrad));
		camera.vecPos.y += (float)(sin(xrotrad));
		
    }
    else if (k=='d')
    {
    	fut=true;
		float yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		camera.vecPos.x += (float)(cos(yrotrad)) * 0.5f;
		camera.vecPos.z += (float)(sin(yrotrad)) * 0.5f;
		

    }
    else if (k =='a')
    {
    	fut=true;
		float yrotrad;
		yrotrad = (camera.vecRot.y / 180.0f * 3.141592654f);
		camera.vecPos.x -= (float)(cos(yrotrad)) * 0.5f;
		camera.vecPos.z -= (float)(sin(yrotrad)) * 0.5f;
		

    }
	else if( k == 27 )
	{
		exit(0);
	}
	
	glutPostRedisplay();
	
}
void keyUp (unsigned char k, int x, int y)
{
   fut=false;
}
void MouseFunction(int x, int y )
{
	int diffx = x - camera.fLastX;
	int diffy = y - camera.fLastY;

	camera.fLastX = x;
	camera.fLastY = y;

	camera.vecRot.x += (float) diffy;
	camera.vecRot.y += (float) diffx;

	if( camera.vecRot.x < -30.0f )
		camera.vecRot.x = -30.0f;
	if( camera.vecRot.x > 90.0f )
		camera.vecRot.x = 90.0f;

}

void ReshapeFunction( GLsizei width, GLsizei height )
{
	if( !height ) height = 1;

	glViewport( 0, 0, width, height );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	if (!help_on)
		gluPerspective( 45.0f, (GLdouble) width/height, 0.1f, 500.0f );
	else
		gluOrtho2D(0, width, height, 0);
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	
	
		
}


void mouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0)
    {
       camera.fRadius -= 1;
    }
    else
    {
        camera.fRadius += 1;
    }
    
    
}
int main( int argc, char* argv[] )
{

	glutInit( &argc, argv );
	glutInitWindowSize( 1024, 768 );
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow( "Beadando Grafika" );
	InitScene();
	glutIdleFunc( IdleFunction );
	glutDisplayFunc( DisplayFunction );
	glutKeyboardFunc( KeyboardFunction );
	glutKeyboardUpFunc(keyUp);
	glutMouseWheelFunc(mouseWheel);
	glutReshapeFunc( ReshapeFunction );
	glutPassiveMotionFunc( MouseFunction );
	glutSpecialFunc(specialFunc);
	glutMainLoop();

	return 0;
}