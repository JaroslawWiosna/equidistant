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
	float theta, phi;
	float x,y,z;
	void setCoord();	
	Spherepoint(float THETA = 0, float PHI = 0) : theta(THETA), phi(PHI) {} 
};

void Spherepoint::setCoord () {
	x = cos(theta) * cos(phi);
	y = cos(theta) * sin(phi);
	z = sin(theta);
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
/*
	Spherepoint * test= new Spherepoint();
	Spherepoint * obj1= new Spherepoint(0,0.1);
	Spherepoint * obj2= new Spherepoint(0,0.25);
	Spherepoint * obj3= new Spherepoint(0,0.26);
	Spherepoint * obj4= new Spherepoint(0,0.44);
	Spherepoint * obj5= new Spherepoint(0,1.5);

//	std::list<Spherepoint> Spoints = {(0.1,0.1),(0.25,0.25),(0.26,0.26),(0.44,0.44),(0.5,0.5)};
	std::list<Spherepoint> Spoints = {*obj1, *obj2, *obj3, *obj4, *obj5};
*/	
	Spherepoint  test= Spherepoint();
	Spherepoint  obj1= Spherepoint(0,0.1);
	Spherepoint  obj2= Spherepoint(0,0.25);
	Spherepoint  obj3= Spherepoint(0,0.26);
	Spherepoint  obj4= Spherepoint(0,0.44);
	Spherepoint  obj5= Spherepoint(0,1.5);

//	std::list<Spherepoint> Spoints = {(0.1,0.1),(0.25,0.25),(0.26,0.26),(0.44,0.44),(0.5,0.5)};
	std::list<Spherepoint> Spoints = {obj1, obj2, obj3, obj4, obj5};
	
	Sphereprint(Spoints);
	for (std::size_t i = 1; i < 30000; ++i) {
		fun3(Spoints);
//		Sphereprint(Spoints);
	}
	Sphereprint(Spoints);

	obj1.setCoord();
	obj2.setCoord();
	obj3.setCoord();
	obj4.setCoord();
	obj5.setCoord();
/*	std::cout << obj1->x << " " << obj2->x << " " << obj3->x << " " << obj4->x    << " " << obj5->x << std::endl; 
	std::cout << obj1->y << " " << obj2->y << " " << obj3->y << " " << obj4->y    << " " << obj5->y << std::endl; 
	std::cout << obj1->z << " " << obj2->z << " " << obj3->z << " " << obj4->z    << " " << obj5->z << std::endl; 
	std::cout << obj1->theta << " " << obj2->theta << " " << obj3->theta << " " << obj4->theta    << " " << obj5->theta << std::endl; 
	std::cout << obj1->phi << " " << obj2->phi << " " << obj3->phi << " " << obj4->phi    << " " << obj5->phi << std::endl; 
*/
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
  sphereSource2->SetCenter(obj1.x, obj1.y, obj1.z);
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
  sphereSource3->SetCenter(obj2.x, obj2.y, obj2.z);
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
  sphereSource4->SetCenter(obj3.x, obj3.y, obj3.z);
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
  sphereSource5->SetCenter(obj4.x, obj4.y, obj4.z);
  sphereSource5->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper5 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper5->SetInputConnection(sphereSource5->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor5 = 
    vtkSmartPointer<vtkActor>::New();
  actor5->SetMapper(mapper5);
  
   // Sphere 6
  vtkSmartPointer<vtkSphereSource> sphereSource6 = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource6->SetCenter(obj5.x, obj5.y, obj5.z);
  sphereSource6->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper6 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper6->SetInputConnection(sphereSource6->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor6 = 
    vtkSmartPointer<vtkActor>::New();
  actor6->SetMapper(mapper6);
 
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
  renderer->AddActor(actor6);
  renderer->SetBackground(1,1,0); // Background color white
 
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
