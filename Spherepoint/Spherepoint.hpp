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
	float getDistanceTo(const Spherepoint* point); 
	Spherepoint(float PHI = 0, float THETA = 0) : phi(PHI), theta(THETA) {
		this->setCoord();
	} 
};

void Spherepoint::setCoord () {
	this->x = cos(theta) * cos(phi);
	this->y = cos(theta) * sin(phi);
	this->z = sin(theta);
}

float Spherepoint::getDistanceTo(const Spherepoint* point) {
	return sqrt( pow(this->x - point->x,2) 
		+ pow(this->x - point->x,2) 
		+ pow(this->z - point->z,2));
}
