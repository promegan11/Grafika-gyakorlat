#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>
GLfloat position[] = { 50.0, 50.0, -50.0, 0.0 };
GLfloat ambient_light[] = { 1, 1, 1, 0 };
GLfloat diffuse_light[] = { 0.5, 0.5, 0, 0 };
GLfloat specular_light[] = { 1, 1, 1, 0 };

void init_scene(Scene* scene)
{

    int i=0;
    char mod[11][35]={"model/raptor.obj","model/raptor_000001.obj","model/raptor_000002.obj",
    "model/raptor_000003.obj","model/raptor_000004.obj","model/raptor_000005.obj",
    "model/raptor_000006.obj","model/raptor_000007.obj","model/raptor_000008.obj",
    "model/raptor_000009.obj","model/raptor_000010.obj"};
    for(i;i<11;i++)
    {
         load_model(&(scene->raptor[i]),mod[i]);
    }
   
    scene->texture_id = load_texture("skin/raptor.png"); 
    
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);
    scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 0.5;
    scene->material.diffuse.green = 0.5;
    scene->material.diffuse.blue = 0.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 900.0;
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
    //draw_ground();

}

void init_ground(Ground* ground)
{
    
    ground->texture_id[0] = load_texture("back/arrakisday_bk.png");
    ground->texture_id[1] = load_texture("back/arrakisday_dn.png");
    ground->texture_id[2] = load_texture("back/arrakisday_lf.png");
    ground->texture_id[3] = load_texture("back/arrakisday_ft.png");
    ground->texture_id[4] = load_texture("back/arrakisday_up.png");
    ground->texture_id[5] = load_texture("back/arrakisday_rt.png");
    ground->texture_id[6] = load_texture("back/help.png");
    ground->material.ambient.red = 1.0;
    ground->material.ambient.green = 1.0;
    ground->material.ambient.blue = 1.0;

    ground->material.diffuse.red = 0.5;
    ground->material.diffuse.green = 0.5;
    ground->material.diffuse.blue = 0.0;

    ground->material.specular.red = 1.0;
    ground->material.specular.green = 1.0;
    ground->material.specular.blue = 1.0;

    ground->material.shininess = 10.0;
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
}
void set_lighting()
{


    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
    glEnable(GL_NORMALIZE);
    glFrontFace(GL_CCW);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene,const Camera* camera,const Ground* ground,int z,int k)
{
    set_material(&(scene->material));
    set_lighting();
    Sleep(100);
    glPushMatrix();
    glTranslatef( camera->position.x, camera->position.y, 0.0f);
    glRotatef(  camera->rotation.z,0.0f, 0.0f, 1.0f );
        
    draw_model(&(scene->raptor[z]));

   // glRotatef( camera->rotation.y, 0.0f, 1.0f, 0.0f );
    glTranslatef( -camera->position.x, 0, -camera->position.z );
    glPopMatrix();
    glPushMatrix();
        
        set_material(&(ground->material));
        draw_ground(&ground->texture_id);
    
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->texture_id);
        Material raptor1mat;
        raptor1mat.ambient.red = 0.0;
        raptor1mat.ambient.green = 1.0;
        raptor1mat.ambient.blue = 1.0;

        raptor1mat.diffuse.red = 0.5;
        raptor1mat.diffuse.green = 0.5;
        raptor1mat.diffuse.blue = 0.0;

        raptor1mat.specular.red = 1.0;
        raptor1mat.specular.green = 1.0;
        raptor1mat.specular.blue = 1.0;

        raptor1mat.shininess = 40.0;
        glEnable(GL_NORMALIZE);
        glFrontFace(GL_CCW);
        set_material(&(raptor1mat));
        glTranslatef( 10+(k*0.5f), 10.0f+(k*0.5f), 0 );
        glRotatef( 45, 0.0f, 0.0f, 1.0f );
        
        raptor_move(&scene->raptor,k);
    

    
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->texture_id);
        Material raptor2mat;
        raptor2mat.ambient.red = 0.7;
        raptor2mat.ambient.green = 0.9;
        raptor2mat.ambient.blue = 0.8;

        raptor2mat.diffuse.red = 0.2;
        raptor2mat.diffuse.green = 0.7;
        raptor2mat.diffuse.blue = 0.0;

        raptor2mat.specular.red = 1.0;
        raptor2mat.specular.green = 1.0;
        raptor2mat.specular.blue = 1.0;

        raptor2mat.shininess = 20.0;
        glEnable(GL_NORMALIZE);
        glFrontFace(GL_CCW);
        set_material(&(raptor2mat));
        glTranslatef( 40+(k*0.5f), -40.0f+(k*0.5f), 0 );
        glRotatef( 45, 0.0f, 0.0f, 1.0f );
        //Sleep(100);
        raptor_move(&scene->raptor,k);
    

    
    glPopMatrix();
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, scene->texture_id);
        Material raptor3mat;
        raptor3mat.ambient.red = 0.7;
        raptor3mat.ambient.green = 0.9;
        raptor3mat.ambient.blue = 0.8;

        raptor3mat.diffuse.red = 0.2;
        raptor3mat.diffuse.green = 0.7;
        raptor3mat.diffuse.blue = 0.0;

        raptor3mat.specular.red = 1.0;
        raptor3mat.specular.green = 1.0;
        raptor3mat.specular.blue = 1.0;

        raptor3mat.shininess = 20.0;
        glEnable(GL_NORMALIZE);
        glFrontFace(GL_CCW);
        set_material(&(raptor3mat));
        glTranslatef( -40+(k*0.5f), -40.0f+(k*1.5f), 0 );
        glRotatef( 90, 0.0f, 0.0f, 1.0f );
        //Sleep(100);
        raptor_move(&scene->raptor,k);
    glPopMatrix();
    

   
}


void draw_help(Ground* ground) {
    
    int width=glutGet(GLUT_WINDOW_WIDTH);
    int height=glutGet(GLUT_WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    set_material(&(ground->material));
    glBindTexture(GL_TEXTURE_2D, ground->texture_id[6]);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(0, 0, 0);

    glTexCoord2f(1, 0);
    glVertex3f(width, 0, 0);

    glTexCoord2f(1, 1);
    glVertex3f(width, height, 0);
    
    glTexCoord2f(0, 1);
    glVertex3f(0, height, 0);
    glEnd();
    reshape(width,height);
    glutSwapBuffers();
}
void raptor_move(const Scene* scene,int k)
{
   draw_model(&(scene->raptor[k]));
}