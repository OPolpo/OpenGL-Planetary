#ifndef PLANET_H
	#define PLANET_H

	#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
	#else
	#include <GL/glut.h>
	#endif
	
	// extern static GLuint texName1;
	// extern static GLuint texName2;
	// extern static GLuint texName3;
	// extern static GLuint texName4;
	// extern static GLuint texName5;

	void drawSun(double angle);
	void drawEarth(double angle);
	void drawMars(double angle);
	void drawStars(double radius);
	void WHO(double angle);
	void drawOrbit(double radius, GLfloat color[3]);
	
	int enableOrbit();
	void disableOrbit();
	int enableAxis();
	void disableAxis();
	int enableTardis();
	void disableTardis();
	void menu();

#endif