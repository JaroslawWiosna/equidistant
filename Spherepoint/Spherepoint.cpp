/**
 * \class Spherepoint
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include "Spherepoint.hpp"
float PI = M_PI; // FIXME: http://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c

Spherepoint::Spherepoint(float PHI = 0, float THETA = 0) : phi(PHI), theta(THETA) {
    this->setCoord();
} 

Spherepoint& Spherepoint::operator=( const Spherepoint& tmp){
    if (&tmp != this) {
       this->phi   = tmp.phi;
       this->theta = tmp.theta;
    }
    this->setCoord();
    return *this;
}
 
void Spherepoint::setPhi(float PHI) {
    phi = PHI;
}

void Spherepoint::setTheta(float THETA) {
    this->theta = THETA;
}

void Spherepoint::setCoord () {
    this->x = cos(theta) * cos(phi);
    this->y = cos(theta) * sin(phi);
    this->z = sin(theta);
}

float Spherepoint::getDistanceTo(Spherepoint* point) {
    return acos(( (sin(phi) * sin(point->phi) ) + ( cos(phi) * cos(point->phi) * cos(theta-point->theta)) ));
}

float Spherepoint::getDistanceTo(Spherepoint& point) {
    return acos(( (sin(phi) * sin(point.phi) ) + ( cos(phi) * cos(point.phi) * cos(theta-point.theta)) ));
}

void Spherepoint::rotate(float thetaMovement) {
	this->theta += thetaMovement;

	if (this->theta > PI / 2.0) {
		this->theta = PI - this->theta; // PI / 2.0 - (this->theta - PI / 2.0);
		this->phi += PI;
		if (this->phi > 2.0*PI) {
			this->phi -= 2.0*PI;
		}
	}
	
	if (this->theta < (-1) * PI / 2.0) {
		this->theta = (-1) * PI - this->theta;
		this->phi += PI;
		if (this->phi < 0) {
			this->phi += 2.0*PI;
		}
	}
	
	this->setCoord();
	
}


