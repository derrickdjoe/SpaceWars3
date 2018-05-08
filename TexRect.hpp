//
//  TexRect.hpp
//  glutapp
//
//  Created by Angelo Kyrilov on 4/11/17.
//  Copyright © 2017 Angelo Kyrilov. All rights reserved.
//

#ifndef TexRect_hpp
#define TexRect_hpp
#include "Vector.h" 

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

class TexRect {
	float x;
	float y;
	float w;
	float h;

public:
	TexRect(float x = 0, float y = 0, float w = 0.5, float h = 0.5) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}


	void setX(float x)
	{
		this->x = x;
	}
	void setY(float y)
	{
		this->y = y;
	}

	float getX()
	{
		return this->x;
	}

	float getY()
	{
		return this->y;
	}
	void draw() {
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex2f(x, y - h);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(x, y);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(x + w, y);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(x + w, y - h);

		glEnd();

		glDisable(GL_TEXTURE_2D);
	}
	bool contains(float x, float y)
	{
		if ((x > this->x) &&
			(x < (this->x + this->w)) &&
			(y< this->y) &&
			(y > (this->y - this->h)))
		{
			return true;
		}
		else
			return false;
	}
};

#endif /* TexRect_hpp */
