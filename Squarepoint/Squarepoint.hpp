#ifndef SQUAREPOINT_HPP
#define SQUAREPOINT_HPP

#include<iostream>
#include<list>
#include<cfloat> // FLT_MIN
#include<cmath> // abs
#include<algorithm>

class Squarepoint{
	public:
	float x,y;
	float getDistanceTo(Squarepoint* point); 
	float getDistanceTo(Squarepoint& point); 
	Squarepoint(float X = 0.5, float Y = 0.5) : x(X), y(Y) {}
};

float Squarepoint::getDistanceTo(Squarepoint* point) {
	return sqrt( pow(this->x - point->x,2) 
		+ pow(this->y - point->y,2)); 
}

float Squarepoint::getDistanceTo(Squarepoint& point) {
	return sqrt( pow(this->x - point.x,2) 
		+ pow(this->y - point.y,2)); 
}

#endif // SPHEREPOINT_HPP

