#ifndef SPHEREPOINT_HPP
#define SPHEREPOINT_HPP

#include<iostream>
#include<list>
#include<cfloat> // FLT_MIN
#include<cmath> // abs
#include<algorithm>
float PI = 3.14; // FIXME: http://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c

class Spherepoint{
	public:
	float phi, theta;
	float x,y,z;
	void setCoord();	
	float getDistanceTo(Spherepoint* point); 
	float getDistanceTo(Spherepoint& point); 
	void rotate(float thetaMovement);
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

void Spherepoint::rotate(float thetaMovement) {
	this->theta += thetaMovement;

	if (this->theta > PI / 2.0) {
		this->theta = PI - this->theta; // PI / 2.0 - (this->theta - PI / 2.0);
		this->phi += PI;
	}
	
	if (this->theta < (-1) * PI / 2.0) {
		this->theta = (-1) * PI - this->theta;
		this->phi += PI;
	}
	
	
}

#endif // SPHEREPOINT_HPP

