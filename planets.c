/**
 * @file planets.c
 * @author Andrea Bocchese
 * @date 31 Mar 2014
 * @brief draw planets and other stuff
 *
 * In this file there are the function the print planet orbit and axis and the menu
 */

#include "planets.h"
#include <SDL.h>
#include <SDL_image.h>

#define PI 3.141592653589793238462643383
int AXIS=0;
int ORBIT=0;
int TARDIS=0;

SDL_Surface* sdlimage;

static GLuint texName1;
static GLuint texName2;
static GLuint texName3;
static GLuint texName4;
static GLuint texName5;

void drawAxis(double radius, GLfloat color[3]);

/**
 * @brief Print Generic Planet.
 * This function print a generic planet.
 * @param main_animation_angle this angle is used to animate the planet.
 * @param radius the radisu of the sphere that represent the planet.
 * @param po_x x position of the planet.
 * @param po_y y position of the planet.
 * @param po_z z position of the planet.
 * @param year_length the lenght of the year expressed in earth day.
 * @param day_length the lenght of the day expressed in earth hours.
 * @param orbital_angle inclination of the orbit.
 * @param orb_x direction of orbital inclination.
 * @param orb_y direction of orbital inclination.
 * @param orb_z direction of orbital inclination.
 * @param axis_angle inclination of the axis of the planet.
 * @param axis_x direction of axis inclination.
 * @param axis_y direction of axis inclination.
 * @param axis_z direction of axis inclination.
 * @param text_name texture indices.
 */
void drawPlanet(double main_animation_angle, double radius, double pos_x, double pos_y, double pos_z,
				double year_legth, double day_length, 
				double orbital_angle, double orb_x, double orb_y, double orb_z,
				double axis_angle, double axis_x, double axis_y, double axis_z,
				GLuint text_name){

	glPushMatrix();
		GLfloat col[] = {0.5, 0.5, 0.5};
		glRotatef(orbital_angle, orb_x, orb_y, orb_z);//ORBITAL ORIENTATION
		if(ORBIT){
			drawOrbit(sqrt(pos_x*pos_x+pos_y*pos_y+pos_z*pos_z),col);
		}
		if(year_legth)//to prevent division by zero
			glRotatef(main_animation_angle*(365./year_legth), 0, 0, 1);//REVOLUTION
		glPushMatrix();
			glTranslatef(pos_x,pos_y,pos_z);
			glRotatef(axis_angle, axis_x, axis_y, axis_z);//AXIS ORIENTATION
			glRotatef(main_animation_angle*365*(24./day_length), 0, 0, 1);//ROTATION
			GLUquadric *qobj = gluNewQuadric();
			gluQuadricTexture(qobj,GL_TRUE); 
			
			glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D,text_name);
				gluSphere(qobj,radius,50,50); 
				gluDeleteQuadric(qobj); 
			glDisable(GL_TEXTURE_2D);
			
			if(AXIS){
				drawAxis(radius,col);
			}

		glPopMatrix();
	glPopMatrix();
}

/**
 * @brief Print Sun.
 * This function print Sun.
 * @param angle change this value to move the sun in the next position.
 */
void drawSun(double angle){
	glPushAttrib(GL_LIGHTING_BIT);
		GLfloat material_col[] = {1.0, 1.0, 1.0};
		glMaterialfv(GL_FRONT, GL_EMISSION, material_col);
		drawPlanet(1000*angle, 2.0, 0.0, 0.0, 0.0,
					0.0, 25*24,
					0.0, 0.0, 0.0, 0.0,
					0.0, 0.0, 0.0, 0.0,
					texName1);
	glPopAttrib();
}

/**
 * @brief Print Earth.
 * This function print Earth.
 * @param angle change this value to move the Earth in the next position.
 */
void drawEarth(double angle){
	drawPlanet(1000*angle, 1.5, 7.0, 0.0, 0.0,
				365.0, 24.0,
				10, 1.0, 0.0, 0.0,
				35.0, 0.0, 1.0, 0.0,
				texName2);
}

/**
 * @brief Print Mars.
 * This function print Mars.
 * @param angle change this value to move the Mars in the next position.
 */
void drawMars(double angle){
	drawPlanet(1000*angle, 0.9, 14.0, 0.0, 0.0,
				687, 24.0,
				6.0, 0.0, 1.0, 1.0,
				10.0, 0.0, 1.0, 0.0,
				texName3);
}

/**
 * @brief Create a texture.
 * This function build the texture from a path of an image.
 * @param text_name this is the address of a GLuint texture index.
 * @param file_path the path of the image file.
 */
void createTexture(GLuint* text_name, char* file_path){
	sdlimage = IMG_Load(file_path);
   	glGenTextures(1, text_name);
   	glBindTexture(GL_TEXTURE_2D, *text_name);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, sdlimage->w, sdlimage->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, sdlimage->pixels );
}

/**
 * @brief create all texture needed.
 * This function build all the texture.
 */
void loadTexture(){
	createTexture(&texName1,"./texture/sun.png");
	createTexture(&texName2,"./texture/earth.png");
	createTexture(&texName3,"./texture/mars.jpg");
	createTexture(&texName4,"./texture/stars.png");
	createTexture(&texName5,"./texture/Tardis.png");
}











//*****************************************************************
//*****************************************************************
//                           INUTILITY :)
//*****************************************************************
//*****************************************************************

/**
 * The follow function are not commented cause are just random stuff
 * added to the original request of the assignment.
 */


int enableOrbit(){
	if(ORBIT){
		ORBIT=1;
		return 0;
	}
	ORBIT=1;
	return 1;
}

void disableOrbit(){ORBIT=0;};
int enableAxis(){
	if(AXIS){
		AXIS=1;
		return 0;
	}
	AXIS=1;
	return 1;
}
void disableAxis(){AXIS=0;};

void drawCarth();
int enableTardis(){
	if(TARDIS){
		TARDIS=1;
		return 0;
	}
	TARDIS=1;
	return 1;
}
void disableTardis(){TARDIS=0;};

void drawStars(double angle){
	//sta cosa solo perchè ho voluto fare void disableAxis
	//per l'orbita non mi faccio problemi in quanto non si vede negli elementi centrati in 0
	int statoassi=enableAxis();
	if(statoassi==0)//se erano abilitati
		disableAxis();//li spengo
	disableAxis();//se per caso li ho accesi li spegno di nuovo 
	//disegno
	glPushAttrib(GL_LIGHTING_BIT);
		GLfloat material_col[] = {1.0, 1.0, 1.0};
		glMaterialfv(GL_FRONT, GL_EMISSION, material_col);
		drawPlanet(1000*angle, 50, 0.0, 0.0, 0.0,
					0, 1000000.0,
					0.0, 0.0, 0.0, 0.0,
					0.0, 0.0, 0.0, 0.0,
					texName4);
	glPopAttrib();
	if(statoassi==0)
		enableAxis();
}

void drawOrbit(double radius, GLfloat color[3]){
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f (color[0], color[1], color[2]);
	glBegin(GL_LINES);
		double i;
		for(i = 0; i < 2 * PI; i += PI / 100)
 			glVertex3f(cos(i) * radius, sin(i) * radius, 0.0);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawAxis(double radius, GLfloat color[3]){
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glColor3f (color[0], color[1], color[2]);
	glBegin( GL_LINES );
		glVertex3f(0.0, 0.0, -2*radius);
		glVertex3f(0.0, 0.0, +2*radius);
	glEnd();
	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void drawString (void * font, char *s, float x, float y, float z){
     unsigned int i;
     glRasterPos3f(x, y, z);
     glColor3f( 1, 1, 1 );
     for (i = 0; i < strlen (s); i++)
          glutBitmapCharacter (font, s[i]);
}

void menu()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

 	glColor3f( 1.0, 0.8, 0.5 );
  	drawString(GLUT_BITMAP_HELVETICA_12, "Show Axis: 1       Show Orbit: 2         Enable Tardis: 3", -5, 5.3, -10);
  	glColor3f( 1.0, 1.0, 1.0 );
  	drawString(GLUT_BITMAP_HELVETICA_12, "Zoom: W/A          Horizontal: A/D       Vertical: C/V", -5, 4.9, -10);
  	drawString(GLUT_BITMAP_HELVETICA_12, "Speed: Arrow Up/down", -5, 4.5, -10);
  	glEnable(GL_TEXTURE_2D);

  	glEnable(GL_LIGHTING);
}

// Just a simple joke
void WHO(double angle){
	if(TARDIS){
		glPushAttrib(GL_LIGHTING_BIT);
			GLfloat material_col[] = {1.0, 1.0, 1.0, 0.0};
			glMaterialfv(GL_FRONT, GL_EMISSION, material_col);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texName5);
			glPushMatrix();
				glRotatef(10*angle*0.9, 0, 0, 1);
				glRotatef(10*angle*0.8, 0, 1, 0);
				glRotatef(10*angle*0.5, 1, 0, 0);
				glTranslatef(15,15,0);
				glRotatef(135, 0, 0, 1);
				glRotatef(-90, 1, 0, 0);
				glBegin(GL_QUADS);
					glTexCoord2f(0.0, 0.0); 
					glVertex3f(-2.0, -1.0, 0.0);
					glTexCoord2f(0.0, 1.0); 
					glVertex3f(-2.0, 1.0, 0.0);
					glTexCoord2f(1.0, 1.0); 
					glVertex3f(0.0, 1.0, 0.0);
					glTexCoord2f(1.0, 0.0); 
					glVertex3f(0.0, -1.0, 0.0);
				glEnd();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		glPopAttrib();
	}
}
