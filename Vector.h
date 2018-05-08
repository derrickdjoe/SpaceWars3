#pragma once
#ifndef VEC_H
#define VEC_H

class Vec{

private:

	float x;
	float y;

public:

	inline Vec();
	inline Vec(float x, float y);
	inline void setX(float x);
	inline void setY(float y);
	inline float getX();
	inline float getY();
	inline void add(Vec vector);

};

Vec::Vec() : x(0.1), y(0.2){

}

Vec::Vec(float x, float y) {
	
	setX(x);
	setY(y);

}

void Vec::add(Vec vector) {

	this->x += vector.x;
	this->y += vector.y;

}

void Vec::setX(float x){

	this->x = x;

}
void Vec::setY(float y){

	this->y = y;

}
float Vec::getX(){

	return x;

}
float Vec::getY(){

	return y;

}
#endif 
