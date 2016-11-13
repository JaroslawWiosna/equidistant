#include <iostream>
#include <list>
#include <cfloat> // FLT_MIN
#include <cmath> // abs
#include <algorithm>
#include "Squarepoint/Squarepoint.hpp"

#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkInteractorStyleTrackball.h>

#include <vtkPolyData.h>
#include <vtkSTLWriter.h>
#include <vtkSTLReader.h>
#include <vtkSphereSource.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

float PI = 3.14; // FIXME: http://stackoverflow.com/questions/1727881/how-to-use-the-pi-constant-in-c
 
void fun5 (std::list<Squarepoint*>& points) {
	std::list<Squarepoint*>::iterator closest0, closest1, closest2, closest3;
	std::size_t size = points.size();

	std::vector < std::pair<std::size_t , float>> distance;
	std::size_t min[4];
	std::list<Squarepoint*>::iterator it, jt;
	constexpr float eps = 0.01;

	for (std::size_t i = 0; i < size; ++i) {
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
//		std::cout << "indexes:::::" << distance[0].first  << distance[1].first  << distance[2].first << distance[3].first << std::endl;
		//now we know what are the 3 closest points
		//lets make one step left, one right and check which is better

		Squarepoint * itLeft  = new Squarepoint((*it)->x - 0.001 , (*it)->y);
		Squarepoint * itRight = new Squarepoint((*it)->x + 0.001 , (*it)->y);
		// the following two lines will be needed! but now, let's try move only phi...
		Squarepoint * itUp    = new Squarepoint((*it)->x           , (*it)->y + 0.001);
		Squarepoint * itDown  = new Squarepoint((*it)->x           , (*it)->y - 0.001);

			if (itLeft->getDistanceTo(*closest1)
				 > 
				(*it)->getDistanceTo(*closest1)
				) {
					(*it)->x -= 0.001;
					if ((*it)->x < 0) (*it)->x = 0;
					//std::cout << " i=" << i << " new=LEFT" << std::endl;
			} else if (itRight->getDistanceTo(*closest1)
				 > 
				(*it)->getDistanceTo(*closest1)
				) {
					(*it)->x += 0.001;
					if ((*it)->x > 1) (*it)->x = 1;
					//std::cout << " i=" << i << " new=RIGHT" << std::endl;
			}

			if (itUp->getDistanceTo(*closest1)
				 > 
				(*it)->getDistanceTo(*closest1)
				) {
					(*it)->y += 0.001;
					if ((*it)->y > 1) (*it)->y = 1;
					//std::cout << " i=" << i << " new=UP" << std::endl;
			} else if (itDown->getDistanceTo(*closest1)
				 > 
				(*it)->getDistanceTo(*closest1)
				) {
					(*it)->y -= 0.001;
					if ((*it)->y < 0) (*it)->y = 0;
					//std::cout << " i=" << i << " new=DOWN" << std::endl;
			}

		delete itLeft;
		delete itRight;
		delete itUp;
		delete itDown;
	}
}

void Squareprint (std::list<Squarepoint*>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 0; i < size; ++i) {
		std::list<Squarepoint*>::iterator it = std::next(points.begin(), i);
		std::cout << i <<".--\t(" << (*it)->x << ", " << (*it)->y << ") " << std::endl; 
	}
	std::cout << std::endl;
	
}



int main() {
	Squarepoint * obj1= new Squarepoint(0.11,0.14);
	Squarepoint * obj2= new Squarepoint(0.91,0.92);
	Squarepoint * obj3= new Squarepoint(0.12,0.93);
	Squarepoint * obj4= new Squarepoint(0.96,0.95);
	Squarepoint * obj5= new Squarepoint(0.5,0.5);
	Squarepoint * obj6= new Squarepoint(0.90,0.71);
	Squarepoint * obj7= new Squarepoint(0.86,0.67);

	std::list<Squarepoint*> Spoints = {obj1, obj2, obj3, obj4, obj5 };

	std::list<Squarepoint*>::iterator it = std::next(Spoints.begin(), 0);

	Squareprint(Spoints);
	std::size_t size = Spoints.size();
	for (std::size_t i = 1; i < 888884; ++i) {
		fun5(Spoints);
		//std::cout << i/80.0 << " %       \r"; 
		for (std::size_t i = 0; i < size; ++i) {
			std::list<Squarepoint*>::iterator it = std::next(Spoints.begin(), i);
			std::cout << "(" << (*it)->x << ", " << (*it)->y << ") "; 
			std::cout.flush();
		}
		std::cout << "                       \r";
		for(int ii = 0; i<100000000; ++i);
		std::cout.flush();
	
	//std::cout.flush();
	}
	std::cout << std::endl;

	std::cout << "After moving...\n" ;
	Squareprint(Spoints);
		
	delete obj1;
	delete obj2;
	delete obj3;
	delete obj4;
	delete obj5;
	delete obj6;
	delete obj7;

	return 0;
}
