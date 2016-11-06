// SOURCE: http://www.vtk.org/Wiki/VTK/Examples/Cxx/GeometricObjects/Sphere
// http://www.vtk.org/Wiki/VTK/Examples/Cxx/Visualization/MultipleActors
// http://www.vtk.org/Wiki/VTK/Examples/Cxx/GeometricObjects/Point
// http://www.vtk.org/Wiki/VTK/Examples/Cxx/PolyData/ColoredPoints

#include <vtkSphereSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkVersion.h>
//#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
//#include <vtkPolyData.h>
#//include <vtkPolyDataMapper.h>
//#include <vtkActor.h>
#include <vtkProperty.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindowInteractor.h>
 
int main(int, char *[])
{
  // Create a sphere
  vtkSmartPointer<vtkSphereSource> sphereSource = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSource->SetCenter(0.0, 0.0, 0.0);
  sphereSource->SetRadius(1.0);
/////////////// 
  vtkSmartPointer<vtkPoints> points =
    vtkSmartPointer<vtkPoints>::New();
  const float p[3] = {1.0, 0.0, 0.0};

  // Create the topology of the point (a vertex)
  vtkSmartPointer<vtkCellArray> vertices =
    vtkSmartPointer<vtkCellArray>::New();
  vtkIdType pid[1];
  pid[0] = points->InsertNextPoint(p);
  vertices->InsertNextCell(1,pid);
 
  // Create a polydata object
  vtkSmartPointer<vtkPolyData> point =
    vtkSmartPointer<vtkPolyData>::New();
 
  // Set the points and vertices we created as the geometry and topology of the polydata
  point->SetPoints(points);
  point->SetVerts(vertices);


///////////////////////
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

   vtkSmartPointer<vtkActor> actorPoint =
	       vtkSmartPointer<vtkActor>::New();
     actor->SetMapper(mapper);
       actor->GetProperty()->SetPointSize(2000);
 
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
//  renderer->AddActor(actor);
  renderer->AddActor(actorPoint);
  renderer->SetBackground(.3, .6, .3); // Background color green
 
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
