// based on http://www.vtk.org/Wiki/VTK/Examples/Cxx/Visualization/MultipleActors

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
 
int main (int, char *[])
{
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
  sphereSource2->SetCenter(1.0, 0.0, 0.0);
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
  sphereSource3->SetCenter(0.0, 0.0, 1.0);
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
  sphereSource4->SetCenter(0.0, 1.0, 0.0);
  sphereSource4->SetRadius(0.1);
 
  // Create a mapper
  vtkSmartPointer<vtkPolyDataMapper> mapper4 = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper4->SetInputConnection(sphereSource4->GetOutputPort());
 
  // Create an actor
  vtkSmartPointer<vtkActor> actor4 = 
    vtkSmartPointer<vtkActor>::New();
  actor4->SetMapper(mapper4);
 
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
  renderer->SetBackground(1,1,0); // Background color white
 
  // Render
  renderWindow->Render();
 
  vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = 
    vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New(); //like paraview
 
  renderWindowInteractor->SetInteractorStyle( style );
 
  // Begin mouse interaction
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
