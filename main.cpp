/**
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include<iostream>
#include<list>
#include<cfloat> // FLT_MIN
#include<cmath> // abs
#include<algorithm>
#include<memory>
#include<list>
#include"Spherepoint.hpp"
#include"SphereVisualization.hpp"
#include"FlagParser.hpp"

void funRand(std::list<Spherepoint*>& points) {
    std::list<Spherepoint*>::iterator closest0, closest1, closest2, closest3;
    std::size_t size = points.size();
    std::vector < std::pair<std::size_t , float>> distance;
    std::pair<std::size_t , float> tmp_pair;
    std::list<Spherepoint*>::iterator it, jt;
    float PI = M_PI;

    std::size_t i = rand()%size;
        it = std::next(points.begin(), i);
        for (std::size_t j = 0; j < size; ++j) {
            jt = std::next(points.begin(), j);
            // distance[j] is distance between it and 'j'
            distance.push_back(std::make_pair(j,(*it)->getDistanceTo(*jt))); // think about emplace_back
	}
		// let's find 3 the closest points to it
		auto cmp = [](std::pair<std::size_t,float> const & a, std::pair<std::size_t,float> const & b) 
		{ 
			     return a.second != b.second?  a.second < b.second : a.first < b.first;
		};
		std::sort( distance.begin(), distance.end(), cmp);
		closest0 = std::next(points.begin(), distance[0].first ); // should be the same as *it
		closest1 = std::next(points.begin(), distance[1].first );
		closest2 = std::next(points.begin(), distance[2].first );
		closest3 = std::next(points.begin(), distance[3].first );
		std::cout << "indexes:::::" << distance[0].first  << distance[1].first  << distance[2].first << distance[3].first << std::endl;
		//now we know what are the 3 closest points
		//lets make one step left, one right and check which is better

//		float thetaMovement = (*it)->theta;
//		if( std::abs(thetaMovement) > ((PI / 2.0) - 0.1 ))
//		for (std::size_t j = 0; j < size; ++j) {
//			jt = std::next(points.begin(), j);
//			(*jt)->rotate((-1)*thetaMovement);
//		}

            float tmpa{}, tmpb{}, tmpdist{};
            for (float a = 0 ; a < 2 * PI ; a+=0.01) {
                for (float b =( -0.5 * PI)-0.001 ; b < (0.5*PI-0.001) ; b +=0.01) {
		    Spherepoint * newSp  = new Spherepoint(a,b);
                    if (newSp->getDistanceTo(*closest1) > tmpdist)
                        tmpa = a;
                        tmpb = b;
                }
            }
            (*it)->phi = tmpa;          
            (*it)->theta = tmpb;          
		(*it)->setCoord();
}

void funOnGridRand(std::list<Spherepoint*>& points, std::list<Spherepoint*>& grid) {
    auto gridSize = grid.size();
    std::list<Spherepoint*>::iterator closest0, closest1, closest2, closest3;
    std::list<Spherepoint*>::iterator it, jt;
    std::size_t i = rand()%(points.size());
    it = std::next(points.begin(), i);
    std::vector < std::pair<std::size_t , float>> distance;
    for (std::size_t j = 0; j < points.size(); ++j) {
        jt = std::next(points.begin(), j);
        // distance[j] is distance between it and 'j'
        if (it != jt)
        distance.push_back(std::make_pair(j,(*it)->getDistanceTo(*jt))); // think about emplace_back
    }
		// let's find 3 the closest points to it
    auto cmp = [](std::pair<std::size_t,float> const & a, std::pair<std::size_t,float> const & b) { 
       return a.second != b.second?  a.second < b.second : a.first < b.first;
    };
    std::sort( distance.begin(), distance.end(), cmp);
    closest0 = std::next(points.begin(), distance[0].first ); 
    float distanceToClosest = distance[0].second;

    auto newPoint = rand()%gridSize;
    std::list<Spherepoint*>::iterator itNewPoint = std::next(grid.begin(), newPoint);
    float newPhi = (*itNewPoint)->phi;
    float newTheta = (*itNewPoint)->theta;
    std::vector < std::pair<std::size_t , float>> distanceFromNewPoint;
    for (std::size_t j = 0; j < points.size(); ++j) {
        if (it != jt) {
            jt = std::next(points.begin(), j);
            distanceFromNewPoint.push_back(std::make_pair(j,(*itNewPoint)->getDistanceTo(*jt)));
        }
    }
    std::sort( distanceFromNewPoint.begin(), distanceFromNewPoint.end(), cmp);
    if (distanceFromNewPoint.size() > 0) {
        float distanceToClosestFromNewPoint = distanceFromNewPoint[0].second;
        if (distanceToClosestFromNewPoint > distanceToClosest + 0.6)
            {
            std::cout << "CHANGE\n\n";
            std::cout << "phi=" << (*it)->phi << "\t->" << newPhi << "\n"; 
            std::cout << "theta=" << (*it)->theta << "\t->" << newTheta << "\n"; 
            std::cout << "dTCFNP" << distanceToClosestFromNewPoint << "\n"; 
            std::cout << "dTC" << distanceToClosest << "\n"; 
            (*it)->phi = newPhi;
            (*it)->theta = newTheta;
            (*it)->setCoord();
        }	
    }
}

void funOnGrid(std::list<Spherepoint*>& points, std::list<Spherepoint*>& grid) {
    auto gridSize = grid.size();
    std::list<Spherepoint*>::iterator closest0, closest1, closest2, closest3;
    std::list<Spherepoint*>::iterator it, jt;
    std::size_t i = rand()%(points.size());
    it = std::next(points.begin(), i);
    std::vector < std::pair<std::size_t , float>> distance;
    for (std::size_t j = 0; j < points.size(); ++j) {
        jt = std::next(points.begin(), j);
        // distance[j] is distance between it and 'j'
        if (it != jt)
        distance.push_back(std::make_pair(j,(*it)->getDistanceTo(*jt))); // think about emplace_back
    }
		// let's find 3 the closest points to it
		auto cmp = [](std::pair<std::size_t,float> const & a, std::pair<std::size_t,float> const & b) 
		{ 
			     return a.second != b.second?  a.second < b.second : a.first < b.first;
		};
		std::sort( distance.begin(), distance.end(), cmp);
		closest0 = std::next(points.begin(), distance[0].first ); 
                float distanceToClosest = distance[0].second;

    for (std::size_t newPoint=0 ; newPoint < gridSize ; ++newPoint) {
        std::list<Spherepoint*>::iterator itNewPoint = std::next(grid.begin(), newPoint);
        if (itNewPoint == it) {
            continue;
        }
        float newPhi = (*itNewPoint)->phi;
        float newTheta = (*itNewPoint)->theta;
        std::vector < std::pair<std::size_t , float>> distanceFromNewPoint;
        for (std::size_t j = 0; j < points.size(); ++j) {
            if (it != jt) {
                jt = std::next(points.begin(), j);
                distanceFromNewPoint.push_back(std::make_pair(j,(*itNewPoint)->getDistanceTo(*jt))); 
            }
        }
        std::sort( distanceFromNewPoint.begin(), distanceFromNewPoint.end(), cmp);
        if (distanceFromNewPoint.size() > 0) {
            float distanceToClosestFromNewPoint = distanceFromNewPoint[0].second;
            if (distanceToClosestFromNewPoint > distanceToClosest + 0.7) {
                distanceToClosest = distanceToClosestFromNewPoint;
                (*it)->phi = newPhi;
                (*it)->theta = newTheta;
                (*it)->setCoord();
            }	
        }
    }
}


int main(int argc, char** argv ) {
    FlagParser parser(argc, argv);
    auto flags = parser.getFlags();
//    parser.printFlags();

    srand(time(NULL));

//    std::size_t numberOfPoints = 4;
    std::unique_ptr<Spherepoint> point01{new Spherepoint{0, 0.1}};
    std::unique_ptr<Spherepoint> point02{new Spherepoint{0, 0.2}};
    std::unique_ptr<Spherepoint> point03{new Spherepoint{0, 0.3}};
    std::unique_ptr<Spherepoint> point04{new Spherepoint{0, 0.4}};

    std::list<Spherepoint*> Spoints{}; 
    Spoints.push_back(point01.get());
    Spoints.push_back(point02.get());
    Spoints.push_back(point03.get());
    Spoints.push_back(point04.get());

    //---------------

    constexpr std::size_t numberOfGridPoints{10000};
    
    std::list<Spherepoint*> gridPointsList{};
    for (std::size_t i=0 ; i < numberOfGridPoints ; ++i) {
/*
        float uRandom = -1 + static_cast<float>(rand())
           /(static_cast<float>(RAND_MAX/2));
        float thetaRandom = static_cast<float>(rand())
           /(static_cast<float>(RAND_MAX/ (2*M_PI)));
        float x = sqrt(1 - pow(uRandom,2)) * cos(thetaRandom);
        float y = sqrt(1 - pow(uRandom,2)) * sin(thetaRandom);
        float z = uRandom;
        float phi = (0.5 * M_PI - std::atan2(y,x));
        float theta = std::asin(z/(sqrt(x*x + y*y + z*z)));
*/
        float x1 = -1 + static_cast<float>(rand())
           /(static_cast<float>(RAND_MAX/2));
        float x2 = -1 + static_cast<float>(rand())
           /(static_cast<float>(RAND_MAX/2));
        if ((pow(x1,2) + pow(x2,2)) < 1) {
           float x = 2*x1*sqrt(1 - pow(x1,2) - pow(x2,2));
           float y = 2*x2*sqrt(1 - pow(x1,2) - pow(x2,2));
           float z = 1 - 2*(pow(x1,2)+pow(x2,2));
           float phi = (0.5 * M_PI - std::atan2(y,x));
           float theta = std::asin(z/(sqrt(x*x + y*y + z*z)));
            float distanceToClosest = 100;
            Spherepoint tmp{phi,theta};
            for (auto& i : gridPointsList) {
                if (i->getDistanceTo(tmp) < distanceToClosest) {
                     distanceToClosest = i->getDistanceTo(tmp);
                }
            }
            if (distanceToClosest > 0.07) {
                gridPointsList.push_back(new Spherepoint{phi,theta});
                std::cout << "New point!\n";
            } else {
//                std::cout << "Already in the list!\n";
            }
        }
    }

    //---------------

//    SphereVisualization gridVis{gridPointsList};
//    gridVis.showAll();

    for (auto& i : gridPointsList) {
        i->setCoord();
    }

    //---------------

    for (int i=0 ; i < 70000 ; ++i) {
        funOnGridRand(Spoints,gridPointsList);      
    }

    //---------------
    gridPointsList.remove_if([](Spherepoint * elem){delete elem; return true;});

    std::list<Spherepoint*>::iterator it;
    for (int i=0 ; i < 4 ; ++i) {
        it = std::next(Spoints.begin(), i);
        std::cout << (*it)->phi <<"\t"<<(*it)->theta <<"\n";
    }
    SphereVisualization visFinal{Spoints};
    visFinal.showAll();

    return 0;
} 
