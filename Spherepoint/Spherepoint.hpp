#ifndef SPHEREPOINT_HPP
#define SPHEREPOINT_HPP

#include<iostream>
#include<list>
#include<cfloat> // FLT_MIN
#include<cmath> // abs
#include<algorithm>

class Spherepoint{
	public:
	float phi, theta;
	float x,y,z;
	void setCoord();	
	float getDistanceTo(Spherepoint* point); 
	float getDistanceTo(Spherepoint& point); 
	Spherepoint(float PHI = 0, float THETA = 0) : phi(PHI), theta(THETA) {
		this->setCoord();
	} 
};

void Spherepoint::setCoord () {
	this->x = cos(theta) * cos(phi);
	this->y = cos(theta) * sin(phi);
	this->z = sin(theta);
}

float Spherepoint::getDistanceTo(Spherepoint* point) {
	return sqrt( pow(this->x - point->x,2) 
		+ pow(this->y - point->y,2) 
		+ pow(this->z - point->z,2));
}

float Spherepoint::getDistanceTo(Spherepoint& point) {
	return sqrt( pow(this->x - point.x,2) 
		+ pow(this->y - point.y,2) 
		+ pow(this->z - point.z,2));
}

#endif // SPHEREPOINT_HPP

