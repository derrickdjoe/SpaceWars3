#ifndef Rectangle_hpp
#define Rectangle_hpp
#include "Vector.h"
#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

class Rectangle {

	float x;
	float y;
	float w;
	float h;
	float r;
	float g;
	float b;

	public:

		bool missle1;
		bool missle2;
		bool missle3;

		Rectangle(float xx = 0, float yy = 0, float ww = 0.1, float hh = 0.1, float rr = 1, float gg = 0, float bb = 0) :
			x(xx), y(yy), w(ww), h(hh), r(rr), g(gg), b(bb) {

			missle1 = false;
		}


		void draw();
		void fire();
		void fire1();

		float getX() const { 

			return x; 

		}

		float getY() const { 

			return y; 

		}

		void setX(float xx) { 

			x = xx; 

		}

		void setY(float yy) { 

			y = yy; 

		}

		float getW() const { 

			return w; 

		}

		float getH() const { 

			return h; 

		}

		void setW(float ww){ 

			w = ww; 

		}

		void setH(float hh){ 

			h = hh; 

		}

		float getR() const { 

			return r; 

		}

		float getG() const { 

			return g;

		}

		float getB() const { 

			return b;
 
		}

		void setColor(float rr, float gg, float bb) { 

			r = rr; g = gg; b = bb; 

		}
		
};
#endif
