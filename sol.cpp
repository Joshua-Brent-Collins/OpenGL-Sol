#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include "imageloader.h" //HELPER CLASS TO LAOD BMP DATA
#include <math.h>



using namespace std;

float rotation = 0;
int rtime = 0;

//from shader stuff
//GLuint f,p;

   

   GLfloat mat_specular[] = { 0, 0, 0, 1.0 };
   GLfloat mat_diffuse[] = { 0, 0, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 75 };
   //GLfloat mat_emissive[] = { 0.0, 0.0, 1.0, 1 };


   GLfloat mat_shininess_sun[] = { 100 };
   GLfloat mat_emissive_sun[] = { .25, .25, .25, .25 };

   float star_coordx[1000];
   float star_coordy[1000];

//planet texture ids and object pointers
GLuint tId;
GLuint tIde;
GLuint tIdj;
GLuint tIdm;
GLuint tIdv;
GLuint tIdn;

GLUquadricObj *sn = NULL;
GLUquadricObj *earth = NULL;
GLUquadricObj *jup = NULL;
GLUquadricObj *merc = NULL;
GLUquadricObj *ven = NULL;
GLUquadricObj *nep = NULL;

//*******************HELPER FUNCTION FOUND ONLINE*****************************************


GLuint loadTexture(Image* image) {

  GLuint textureId;

  glGenTextures(1, &textureId); //Make room for our texture

  glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit

  //Map the image to the texture
/*
  glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D

         0,                            //0 for now

         GL_RGB,                       //Format OpenGL uses for image

         image->width, image->height,  //Width and height

         0,                            //The border of the image

         GL_RGB, //GL_RGB, because pixels are stored in RGB format

         GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored

                           //as unsigned numbers

         image->pixels);               //The actual pixel data
*/
 gluBuild2DMipmaps( GL_TEXTURE_2D, 3, image->width, image->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels );
  return textureId; //Returns the id of the texture

}
//**********************************************

void img(int id){

if(id == 1){
Image *image = loadBMP("maps/sun.bmp");

tId = loadTexture(image);

delete image;
}


if(id == 2){
Image *imagee = loadBMP("maps/earth.bmp");

tIde = loadTexture(imagee);

delete imagee;
}

if(id == 3){
Image *imagej = loadBMP("maps/jupiter.bmp");

tIdj = loadTexture(imagej);

delete imagej;
}

if(id == 4){
Image *imagem = loadBMP("maps/mercury.bmp");

tIdm = loadTexture(imagem);

delete imagem;
}

if(id == 5){
Image* imagen = loadBMP("maps/neptune.bmp");

tIdn = loadTexture(imagen);

delete imagen;
}

if(id == 6){
Image *imagev = loadBMP("maps/venus.bmp");

tIdv = loadTexture(imagev);

delete imagev;
}


//glEnable(GL_NORMALIZE);

//setup of filtering and use of mipmaps
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );

}


void qsetup(){

sn = gluNewQuadric();
earth = gluNewQuadric();
jup = gluNewQuadric();
merc = gluNewQuadric();
ven = gluNewQuadric();

}








void imgsun(){



  
img(1);


    gluQuadricDrawStyle(sn, GLU_FILL);
    gluQuadricTexture(sn, GL_TRUE);
    gluQuadricNormals(sn, GLU_SMOOTH);  

glPushMatrix();

//   glBindTexture(GL_TEXTURE_2D, tId);
   gluSphere(sn,.15,25,25);



glPopMatrix();

glDeleteTextures(1,&tId);

//gluDeleteQuadric(sn);
//glDisable(GL_TEXTURE_2D);
}



void gen_stars(){

for(int k=0;k<1000;k++){
star_coordx[k]=((float)(rand()%100))/100;
star_coordy[k]=((float)(rand()%100))/100;
}
}

/*
//old sun function
void sun(){

glPushMatrix();

   
 
   glColor3f(1,1,.1);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_EMISSION, mat_emissive_sun);


glutSolidSphere (.15, 57, 57);
glTranslatef(0 ,0, 0);

//glDeleteShader(f);
//glDeleteProgram(p);
//glDetachShader(p,f);
glPopMatrix();
}
*/
void new_planet(float diam,float x,float y,float z,float offset,int id){

glPushMatrix();

   
/*
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
*/

glRotatef((rotation+=.05)+offset,0,0,1);
glTranslatef(x ,y, z);

   

if(id == 2){
img(2);

gluQuadricDrawStyle(earth, GLU_FILL);
gluQuadricTexture(earth, GL_TRUE);
gluQuadricNormals(earth, GLU_SMOOTH);
//glBindTexture(GL_TEXTURE_2D, tIde);
gluSphere(earth,diam,15,15);
//gluDeleteQuadric(earth);
glDeleteTextures(1,&tIde);

}
if(id == 3){
img(3);

gluQuadricDrawStyle(jup, GLU_FILL);
gluQuadricTexture(jup, GL_TRUE);
gluQuadricNormals(jup, GLU_SMOOTH);
//glBindTexture(GL_TEXTURE_2D, tIdj);
gluSphere(jup,diam,15,15);
//gluDeleteQuadric(jup);
glDeleteTextures(1,&tIdj);

}
if(id == 4){
img(4);

gluQuadricDrawStyle(merc, GLU_FILL);
gluQuadricTexture(merc, GL_TRUE);
gluQuadricNormals(merc, GLU_SMOOTH);
//glBindTexture(GL_TEXTURE_2D, tIdm);
gluSphere(merc,diam,15,15);
//gluDeleteQuadric(merc);
glDeleteTextures(1,&tIdm);

}
if(id == 5){
img(5);
nep = gluNewQuadric();
gluQuadricDrawStyle(nep, GLU_FILL);
gluQuadricTexture(nep, GL_TRUE);
gluQuadricNormals(nep, GLU_SMOOTH);
//glBindTexture(GL_TEXTURE_2D, tIdn);
gluSphere(nep,diam,15,15);
//gluDeleteQuadric(nep);
glDeleteTextures(1,&tIdn);

}
if(id == 6){
img(6);

gluQuadricDrawStyle(ven, GLU_FILL);
gluQuadricTexture(ven, GL_TRUE);
gluQuadricNormals(ven, GLU_SMOOTH);
//glBindTexture(GL_TEXTURE_2D, tIdv);
gluSphere(ven,diam,15,15);
//gluDeleteQuadric(ven);
glDeleteTextures(1,&tIdv);

}




glPopMatrix();

}


void stars(){


glPushMatrix();




glBegin(GL_POINTS);
glColor3f(1,1,1);
for (int k = 0; k<250; k++)
{
glVertex3f(star_coordx[k],star_coordy[k],.99);

}

for (int k = 250; k<500; k++)
{
glVertex3f(-1 * star_coordx[k],star_coordy[k],.99);
}

for (int k = 500; k<750; k++)
{
glVertex3f(star_coordx[k],-1 * star_coordy[k],.99);
}

for (int k = 750; k<1000; k++)
{
glVertex3f(-1 * star_coordx[k],-1 * star_coordy[k],.99);
}


glEnd();
glPopMatrix();







}



void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     

   glPushMatrix();

	//correct the rotated view to allow for proper star coordinates
 	glPushMatrix();
         glRotatef(-70, 1, 0, 0);
	 stars();
	glPopMatrix();  


  glScalef(.50,.50,.50);

  glPushMatrix();
   glRotatef(rotation, 1, 1, 0);
   imgsun();
glPopMatrix();

   //glColor3f(.8,.2,.5);
   
   new_planet(.03,.5,0,0,0,4);
  
   //glColor3f(0,0,1);
   new_planet(.05,.8,0,0,20,6);
   
   //glColor3f(.1,.42,.2);
   new_planet(.08,1.8,0,0,70,3);
   
   //glColor3f(1,.2,0);
   new_planet(.057,1,0,0,140,5);

   //glColor3f(.80,.82,.8);
   new_planet(.09,2,0,0,240,2); 
   

   
   glPopMatrix();

	

//usleep(rtime);

if(rotation >= 360 )
{
rotation == 0;
}

//one.move();

glFlush();

glutPostRedisplay();

}





void init(void) 
{

//setup for lighting and textures;

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_LIGHT0);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);



   GLfloat light_position[] = { 0, 0, 0, 1}; // x,y,z,w w is directional or nondirectional light
   GLfloat light_positions[] = { 0, 0, -.75, 1};
   glClearColor (0.0, 0.0, 0.0, 0.0);
   //glShadeModel (GL_SMOOTH);



   GLfloat light_specular[] = { 1, 1, 1, 1.0 };
   GLfloat light_diffuse[] = { 1, 1, 1, 1.0 };

	//lighting on all objects reguardless of location
  GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);



  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT1, GL_POSITION, light_positions);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);




  // glEnable(GL_LIGHT1);





//AA being enabled

   glEnable(GL_POINT_SMOOTH);
   glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);
   glEnable(GL_LINE_SMOOTH);
   glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
   glEnable(GL_POLYGON_SMOOTH);
   glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);


  
  GLfloat la;
  glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &la);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, la);



glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

  glRotatef(70, 1, 0, 0);
	

}


int main(int argc, char** argv)
{
   srand(time(0));
   gen_stars();
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

   glutInitWindowSize (1200, 1000); 
   glutInitWindowPosition (250, 0);
   glutCreateWindow ("Orbits");
   init ();
   qsetup();
   //img();
   glutDisplayFunc(display); 
   glutMainLoop();
   return 0;


}
