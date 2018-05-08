#pragma once
#include "Rectangle.h"
#include "GlutApp.h"
#include "RgbImage.h"
#include "TexRect.hpp"

class Al : public Rectangle
{
public:

	GLuint al;
	TexRect* test;
	float x;
	float y;
	float h;
	float w;

	Al(float x, float y, float h, float w) {

		GLuint al = loadTexture("playership.bmp");
		this->x = x;
		this->y = y;
		this->h = h;
		this->w = w;
		test = new TexRect(x, y, h, w);

		
	}

	GLuint loadTexture(const char *filename) {

		GLuint texture_id;
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glShadeModel(GL_FLAT);
		glEnable(GL_DEPTH_TEST);

		RgbImage theTexMap(filename);

		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
			GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

		return texture_id;

	}

};
