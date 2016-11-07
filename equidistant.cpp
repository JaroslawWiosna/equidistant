#include<iostream>
#include<list>
#include<cfloat> // FLT_MIN
#include<cmath> // abs

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
 
template <typename T>
void print (std::list<T>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 1; i < size; ++i) {
		std::list<float>::iterator it = std::next(points.begin(), i);
		std::cout << *it << " \t";	
	}
	std::cout << std::endl;
	
}

template <typename T>
void fun (std::list<T>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 1; i < size; ++i) {
		std::list<float>::iterator it = std::next(points.begin(), i);
		std::list<float>::iterator prev = std::next(it, -1);
		std::list<float>::iterator next = std::next(it, 1);
		*it = (*prev + *next) / 2.0;

		if (i == size-1) {
			*it = (*prev + 1.0) / 2.0;
		}
	}
	
}


template <typename T>
void fun2 (std::list<T>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 1; i < size-1; ++i) {
		std::list<float>::iterator it = std::next(points.begin(), i);
		std::list<float>::iterator prev = std::next(it, -1);
		std::list<float>::iterator next = std::next(it, 1);
		*it = (*prev + *next) / 2.0;
		if (std::abs(*it - *prev) < std::abs(*it - *next)) {
			*it += FLT_MIN;
		} else {
			*it -= FLT_MIN;
		}
	}
/*
	std::list<float>::iterator it = std::next(points.end(), -1);
	std::list<float>::iterator prev = std::next(it, -1);
	//std::list<float>::iterator next = std::next(it, 1);

	if (std::abs(*it - *prev) < (1.0 - *it)) {
		*it += FLT_MIN;
	} else {
		*it -= FLT_MIN;
	}
*/
}

class Spherepoint{
	public:
	float phi, theta;
	float x,y,z;
	void setCoord();	
	Spherepoint(float PHI = 0, float THETA = 0) : phi(PHI), theta(THETA) {} 
};

void Spherepoint::setCoord () {
	this->x = cos(theta) * cos(phi);
	this->y = cos(theta) * sin(phi);
	this->z = sin(theta);
}



void fun3 (std::list<Spherepoint>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 1; i < size-1; ++i) {
		float tmp;
		std::list<Spherepoint>::iterator it = std::next(points.begin(), i);
		std::list<Spherepoint>::iterator prev = std::next(it, -1);
		std::list<Spherepoint>::iterator next = std::next(it, 1);
		it->phi = ((*prev).phi + (*next).phi) / 2.0;
/*		if (std::abs(it->phi - prev->phi) < std::abs(it->phi - next->phi)) {
			it->phi += FLT_MIN;
		} else {
			it->phi -= FLT_MIN;
		}
*/	}
}

void fun4 (std::list<Spherepoint>& points) {
	std::list<Spherepoint>::iterator closest0, closest1, closest2, closest3;
	std::size_t size = points.size();

	float * distance = new float[size];
	float meanTheta{}, meanPhi;
	std::size_t min[4];

	for (std::size_t i = 0; i < size; ++i) {
		std::list<Spherepoint>::iterator it = std::next(points.begin(), i);
		for (std::size_t j = 0; j < size; ++j) {
			std::list<Spherepoint>::iterator jt = std::next(points.begin(), j);
			// distance[j] is distance between it and 'j'
			distance[j] = sqrt( (it->x - jt->x)*(it->x - jt->x) + (it->x - jt->x)*(it->y - jt->y) + (it->z - jt->z)*(it->z - jt->z) );
		}
		// let's find 3 the closest points to it
		// TODO !!!
		// let's 'hardcode' it for a while. our points are j=2,j=3,j=4

		/* ????
		min[0] = 0; // because the closest point is itself, thus we need 4 the closest, then 'remove' the closest one(itself) from the list
		for (std::size_t k = 0; k < 4; ++k) {
			for (std::size_t i = 0; i < size; ++i) {
				if (distance[i] < min[0])
					min[k] = i;
			}
		}
		*/	
	
		closest0 = std::next(points.begin(), 0);
		closest1 = std::next(points.begin(), 1);
		closest2 = std::next(points.begin(), 2);
		closest3 = std::next(points.begin(), 3);

		// a huge hack :( <----- onlyfor 4 points
		// compute mean
		meanPhi = closest0->phi + closest1->phi + closest2->phi + closest3->phi - it->phi;
		meanPhi /= 3.0;
		// TODO remenber that sometimes you should add PI to phi,then modulo 2PI  
		if (abs(it->phi - meanPhi) < abs(it->phi - (meanPhi+PI))) {
			it->phi = meanPhi;
		} else {
			it->phi = meanPhi+PI;
		}
		meanTheta = closest0->theta + closest1->theta + closest2->theta + closest3->theta - it->theta;
		meanTheta /= 3.0;
		// TODO remenber that sometimes you should multiply theta by -1 
		if (abs(it->theta - meanTheta) < abs(it->theta - ( (-1) * meanTheta))) {
			it->theta = meanTheta;
		} else {
			it->theta = ( (-1) * meanTheta);
		}

		it->setCoord();
	}
}

void Sphereprint (std::list<Spherepoint>& points) {
	std::size_t size = points.size();
	for (std::size_t i = 0; i < size; ++i) {
		std::list<Spherepoint>::iterator it = std::next(points.begin(), i);
		std::cout << it->phi << " \t";	
	}
	std::cout << std::endl;
	
}



int main() {
	std::list<float> points = {0,0.11,0.14442,0.3,1.0};

	print(points);
	fun2(points);
	print(points);
	for (std::size_t i = 1; i < 30000; ++i) {
		fun2(points);
	//	print(points);
	}
	print(points);

	Spherepoint * test= new Spherepoint();
	Spherepoint * obj1= new Spherepoint(0.11,-1);
	Spherepoint * obj2= new Spherepoint(0.2,0.25);
	Spherepoint * obj3= new Spherepoint(1.3,0.26);
	Spherepoint * obj4= new Spherepoint(1.66,1.44);

	std::list<Spherepoint> Spoints = {*obj1, *obj2, *obj3, *obj4};
	
	Sphereprint(Spoints);
	for (std::size_t i = 1; i < 2002; ++i) {
		fun4(Spoints);
	}
	Sphereprint(Spoints);

	std::list<Spherepoint>::iterator it = std::next(Spoints.begin(), 0);
	for (std::size_t i = 0; i < 4; ++i) {
		it = std::next(Spoints.begin(), i);
		std::cout << i <<".--\t" << it->x << " " << it->y << " " << it->z << " " << it->theta    << " " << it->phi << std::endl; 
	}

	for (std::size_t i = 0; i < 4; ++i) {
		it = std::next(Spoints.begin(), i);
		it->setCoord();
	}

	for (std::size_t i = 0; i < 4; ++i) {
		it = std::next(Spoints.begin(), i);
		std::cout << i <<".--\t" << it->x << " " << it->y << " " << it->z << " " << it->theta    << " " << it->phi << std::endl; 
	}
		
	//std::list<Spherepoint>::iterator it = std::next(Spoints.begin(), 0);
	it = std::next(Spoints.begin(), 0);

  // Sphere 1
  vtkSmartPointer<vtkSphereSource> sphereSource1 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource1->SetCenter(0.0, 0.0, 0.0);
  sphereSource1->SetRadius(0.5);
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
  sphereSource2->SetCenter(it->x, it->y, it->z);
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
  sphereSource3->SetCenter(it->x, it->y, it->z);
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
  sphereSource4->SetCenter(it->x, it->y, it->z);
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
  sphereSource4->SetCenter(it->x, it->y, it->z);
  sphereSource5->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper5 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper5->SetInputConnection(sphereSource5->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor5 = 
    vtkSmartPointer<vtkActor>::New();
  actor5->SetMapper(mapper5);
  
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
//  renderer->AddActor(actor1);
  renderer->AddActor(actor2);
  renderer->AddActor(actor3);
  renderer->AddActor(actor4);
  renderer->AddActor(actor5);
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

  return EXIT_SUCCESS;


}
