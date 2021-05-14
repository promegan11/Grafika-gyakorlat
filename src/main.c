

#include <stdio.h>
#include "callbacks.h"
#include "init.h"
#include "texture.h"
#include <gl\glut.h>



void set_callbacks()
{
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseWheelFunc(mouse);
    glutPassiveMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutSpecialFunc(specialFunc);
    glutIdleFunc(idle);
}





int main( int argc, char* argv[] )
{	int z=0;
	int window;
	glutInit( &argc, argv );
	glutInitWindowSize( 1024, 768 );
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    window = glutCreateWindow( "Beadando Grafika" );
    glutSetWindow(window);
	init_opengl();
	init_ground(&ground);
	
    init_scene(&scene);
    
    init_camera(&camera);
    set_callbacks();

    glutMainLoop();

	return 0;
}