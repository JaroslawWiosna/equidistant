#include<iostream>
#include<list>
#include<cfloat> // FLT_MIN
#include<cmath> // abs
#include<algorithm>
#include"Spherepoint/Spherepoint.hpp"

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
 
void fun4 (std::list<Spherepoint*>& points) {
	std::list<Spherepoint*>::iterator closest0, closest1, closest2, closest3;
	std::size_t size = points.size();

	std::vector < std::pair<std::size_t , float>> distance;
	std::pair<std::size_t , float> tmp_pair;
	float meanTheta{}, meanPhi;
	std::size_t min[4];
	std::list<Spherepoint*>::iterator it, jt;
	constexpr float eps = 0.1;

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

		Spherepoint * itLeft  = new Spherepoint((*it)->phi - 0.001 , (*it)->theta);
		Spherepoint * itRight = new Spherepoint((*it)->phi + 0.001 , (*it)->theta);
		// the following two lines will be needed! but now, let's try move only phi...
		Spherepoint * itUp    = new Spherepoint((*it)->phi           , (*it)->theta + 0.001);
		Spherepoint * itDown  = new Spherepoint((*it)->phi           , (*it)->theta - 0.001);

		if (((*it)->getDistanceTo(*closest3)
			- (*it)->getDistanceTo(*closest2)
			< eps) 
			&&
			((*it)->getDistanceTo(*closest2)
			 - (*it)->getDistanceTo(*closest1)
			< eps)
		) {
			if (itLeft->getDistanceTo(*closest1)
				+ itLeft->getDistanceTo(*closest2)
				+ itLeft->getDistanceTo(*closest3)
				 > 
				(*it)->getDistanceTo(*closest1)
				+ (*it)->getDistanceTo(*closest2)
				+ (*it)->getDistanceTo(*closest3)
				) {
					(*it)->phi -= 0.001;
					std::cout << " i=" << i << " new=LEFT" << std::endl;
			} else if (itRight->getDistanceTo(*closest1)
				+ itRight->getDistanceTo(*closest2)
				+ itRight->getDistanceTo(*closest3)
				 > 
				(*it)->getDistanceTo(*closest1)
				+ (*it)->getDistanceTo(*closest2)
				+ (*it)->getDistanceTo(*closest3)
				) {
					(*it)->phi += 0.001;
					std::cout << " i=" << i << " new=RIGHT" << std::endl;
			}
	
			//The following if-else-clause is for theta movement 
			if (itUp->getDistanceTo(*closest1)
				+ itUp->getDistanceTo(*closest2)
				+ itUp->getDistanceTo(*closest3)
				 > 
				(*it)->getDistanceTo(*closest1)
				+ (*it)->getDistanceTo(*closest2)
				+ (*it)->getDistanceTo(*closest3)
				) {
					(*it)->theta += 0.001;
					std::cout << " i=" << i << " new=UP" << std::endl;
			} else if (itDown->getDistanceTo(*closest1)
				+ itDown->getDistanceTo(*closest2)
				+ itDown->getDistanceTo(*closest3)
				 > 
				(*it)->getDistanceTo(*closest1)
				+ (*it)->getDistanceTo(*closest2)
				+ (*it)->getDistanceTo(*closest3)
				) {
					(*it)->theta -= 0.001;
					std::cout << " i=" << i << " new=DOWN" << std::endl;
			}
		}
		(*it)->setCoord();

		delete itLeft;
		delete itRight;
		delete itUp;
		delete itDown;
	}
}

void Sphereprint (std::list<Spherepoint*>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 0; i < size; ++i) {
		std::list<Spherepoint*>::iterator it = std::next(points.begin(), i);
		std::cout << i <<".--\t" << (*it)->x << " " << (*it)->y << " " << (*it)->z << " " << (*it)->theta    << " " << (*it)->phi << std::endl; 
	}
	std::cout << std::endl;
	
}



int main() {
	Spherepoint * test= new Spherepoint();
	Spherepoint * obj1= new Spherepoint(1,0.7);
	Spherepoint * obj2= new Spherepoint(2,0.4);
	Spherepoint * obj3= new Spherepoint(3,-0.3);
	Spherepoint * obj4= new Spherepoint(0.1,-0.7555);
	Spherepoint * obj5= new Spherepoint(0,0);
	Spherepoint * obj6= new Spherepoint(0,0);

	std::list<Spherepoint*> Spoints = {obj1, obj2, obj3, obj4 };

	std::list<Spherepoint*>::iterator it = std::next(Spoints.begin(), 0);

	Sphereprint(Spoints);
	for (std::size_t i = 1; i < 80000; ++i) {
		fun4(Spoints);
		std::cout << i/800.0 << " %       \r"; 
		std::cout.flush();
	}
	std::cout << std::endl;

	std::cout << "After moving...\n" ;
	Sphereprint(Spoints);
		
	it = std::next(Spoints.begin(), 0);

  // Sphere 1
  vtkSmartPointer<vtkSphereSource> sphereSource1 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->SetCenter(0.0, 0.0, 0.0);
  sphereSource1->SetRadius(1.0);
  sphereSource1->Update();
 
  vtkSmartPointer<vtkPolyDataMapper> mapper1 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper1->SetInputConnection(sphereSource1->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor1 = 
    vtkSmartPointer<vtkActor>::New();
  actor1->SetMapper(mapper1);
 
  // Sphere 2
  vtkSmartPointer<vtkSphereSource> sphereSource2 = 
    vtkSmartPointer<vtkSphereSource>::New();
  it = std::next(Spoints.begin(), 0);
  sphereSource2->SetCenter((*it)->x, (*it)->y, (*it)->z);
  sphereSource2->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper2 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper2->SetInputConnection(sphereSource2->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor2 = 
    vtkSmartPointer<vtkActor>::New();
  actor2->SetMapper(mapper2);
 
   // Sphere 3
  vtkSmartPointer<vtkSphereSource> sphereSource3 = 
    vtkSmartPointer<vtkSphereSource>::New();
  it = std::next(Spoints.begin(), 1);
  sphereSource3->SetCenter((*it)->x, (*it)->y, (*it)->z);
  sphereSource3->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper3 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper3->SetInputConnection(sphereSource3->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor3 = 
    vtkSmartPointer<vtkActor>::New();
  actor3->SetMapper(mapper3);

  // Sphere 4
  vtkSmartPointer<vtkSphereSource> sphereSource4 = 
    vtkSmartPointer<vtkSphereSource>::New();
  it = std::next(Spoints.begin(), 2);
  sphereSource4->SetCenter((*it)->x, (*it)->y, (*it)->z);
  sphereSource4->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper4 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper4->SetInputConnection(sphereSource4->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor4 = 
    vtkSmartPointer<vtkActor>::New();
  actor4->SetMapper(mapper4);
 
  // Sphere 5
  vtkSmartPointer<vtkSphereSource> sphereSource5 = 
    vtkSmartPointer<vtkSphereSource>::New();
  it = std::next(Spoints.begin(), 3);
  sphereSource5->SetCenter((*it)->x, (*it)->y, (*it)->z);
  sphereSource5->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper5 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper5->SetInputConnection(sphereSource5->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor5 = 
    vtkSmartPointer<vtkActor>::New();
  actor5->SetMapper(mapper5);
 /* 
   // Sphere 6
  vtkSmartPointer<vtkSphereSource> sphereSource6 = 
    vtkSmartPointer<vtkSphereSource>::New();
  it = std::next(Spoints.begin(), 4);
  sphereSource6->SetCenter((*it)->x, (*it)->y, (*it)->z);
  sphereSource6->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper6 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper6->SetInputConnection(sphereSource6->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor6 = 
    vtkSmartPointer<vtkActor>::New();
  actor6->SetMapper(mapper6);
  
 
  // Sphere 7
  vtkSmartPointer<vtkSphereSource> sphereSource7 = 
    vtkSmartPointer<vtkSphereSource>::New();
  it = std::next(Spoints.begin(), 5);
  sphereSource7->SetCenter((*it)->x, (*it)->y, (*it)->z);
  sphereSource7->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper7 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper7->SetInputConnection(sphereSource7->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor7 = 
    vtkSmartPointer<vtkActor>::New();
  actor7->SetMapper(mapper7);
*/  
  // A renderer and render window
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
 
  // An interactor
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  // Add the actors to the scene
  renderer->AddActor(actor1);
  renderer->AddActor(actor2);
  renderer->AddActor(actor3);
  renderer->AddActor(actor4);
  renderer->AddActor(actor5);
//  renderer->AddActor(actor6);
//  renderer->AddActor(actor7);
  renderer->SetBackground(1,1,0); // Background color yellow
 
  // Render
  renderWindow->Render();
 
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); //like paraview
 
  renderWindowInteractor->SetInteractorStyle( style );
 
  // Begin mouse interaction
  renderWindowInteractor->Start();
 
  vtkSmartPointer<vtkSTLWriter> stlWriter =
    vtkSmartPointer<vtkSTLWriter>::New();
  stlWriter->SetFileName("object_test.stl");
  stlWriter->SetInputConnection(sphereSource5->GetOutputPort());
  stlWriter->Write();

	delete obj1;
	delete obj2;
	delete obj3;
	delete obj4;
	delete obj5;
	delete obj6;


  return EXIT_SUCCESS;


}
