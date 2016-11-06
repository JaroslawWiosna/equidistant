// SOURCE: http://www.vtk.org/Wiki/VTK/Examples/Cxx/GeometricObjects/Sphere
// http://www.vtk.org/Wiki/VTK/Examples/Cxx/Visualization/MultipleActors
// http://www.vtk.org/Wiki/VTK/Examples/Cxx/GeometricObjects/Point
// http://www.vtk.org/Wiki/VTK/Examples/Cxx/PolyData/ColoredPoints
// http://www.vtk.org/Wiki/VTK/Examples/Cxx/Images/CombineImages
//
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
//#include <vtkPolyDataMapper.h>
//#include <vtkActor.h>
#include <vtkProperty.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderer.h>
//#include <vtkRenderWindowInteractor.h>

//#include <vtkVersion.h>
//#include <vtkSmartPointer.h>
//#include <vtkPoints.h>
//#include <vtkPolyData.h>
#include <vtkPointData.h>
//#include <vtkCellArray.h>
#include <vtkUnsignedCharArray.h>
//#include <vtkPolyDataMapper.h>
//#include <vtkActor.h>
//#include <vtkRenderWindow.h>
//#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkVertexGlyphFilter.h>
//#include <vtkProperty.h>

#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkJPEGReader.h>
#include <vtkImageData.h>
#include <vtkSmartPointer.h>
#include <vtkImageViewer2.h>
#include <vtkImageBlend.h>
#include <string>

// For compatibility with new VTK generic data arrays
 #ifdef vtkGenericDataArray_h
 #define InsertNextTupleValue InsertNextTypedTuple
 #endif

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
  points->InsertNextPoint (0.0, 0.0, 1.0);
  points->InsertNextPoint (1.0, 0.0, 0.0);
  points->InsertNextPoint (0.0, 1.0, 0.0);
 
  vtkSmartPointer<vtkPolyData> pointsPolydata =
    vtkSmartPointer<vtkPolyData>::New();
 
  pointsPolydata->SetPoints(points);
 
  vtkSmartPointer<vtkVertexGlyphFilter> vertexFilter =
    vtkSmartPointer<vtkVertexGlyphFilter>::New();
#if VTK_MAJOR_VERSION <= 5
  vertexFilter->SetInputConnection(pointsPolydata->GetProducerPort());
#else
  vertexFilter->SetInputData(pointsPolydata);
#endif
  vertexFilter->Update();
 
  vtkSmartPointer<vtkPolyData> polydata =
    vtkSmartPointer<vtkPolyData>::New();
  polydata->ShallowCopy(vertexFilter->GetOutput());
 
  // Setup colors
  unsigned char red[3] = {255, 0, 0};
  unsigned char green[3] = {0, 255, 0};
  unsigned char blue[3] = {0, 0, 255};
 
  vtkSmartPointer<vtkUnsignedCharArray> colors =
    vtkSmartPointer<vtkUnsignedCharArray>::New();
  colors->SetNumberOfComponents(3);
  colors->SetName ("Colors");
  colors->InsertNextTupleValue(red);
  colors->InsertNextTupleValue(green);
  colors->InsertNextTupleValue(blue);
 
  polydata->GetPointData()->SetScalars(colors);
 
  // Visualization
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
#if VTK_MAJOR_VERSION <= 5
  mapper->SetInputConnection(polydata->GetProducerPort());
#else
  mapper->SetInputData(polydata);
#endif
 
  vtkSmartPointer<vtkActor> actorPoints =
    vtkSmartPointer<vtkActor>::New();
  actorPoints->SetMapper(mapper);
  actorPoints->GetProperty()->SetPointSize(5);

  vtkSmartPointer<vtkImageBlend> blend =
    vtkSmartPointer<vtkImageBlend>::New();
  blend->AddInputConnection(sphereSource->GetOutputPort());
  //blend->AddInputConnection(points->GetPoint(1)->GetOutputPort());
  blend->AddInputConnection(points->GetData());

///////////////////////
//  vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//  mapper->SetInputConnection(sphereSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
//  renderer->AddActor(actor);
  renderer->AddActor(actorPoints);
  renderer->SetBackground(.3, .6, .3); // Background color green
 
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}
