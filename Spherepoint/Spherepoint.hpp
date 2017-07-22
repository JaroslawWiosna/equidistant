/**
 * \class Spherepoint
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

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
    void rotate(float thetaMovement);
    void setPhi(float PHI);
    void setTheta(float THETA);
    Spherepoint(float PHI, float THETA); 
    Spherepoint& operator=(const Spherepoint&);
};

#endif // SPHEREPOINT_HPP

