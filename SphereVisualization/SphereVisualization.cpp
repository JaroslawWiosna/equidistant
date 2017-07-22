/**
 * \class SphereVisualization
 *
 * @par Licence
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 */

#include"SphereVisualization.hpp"
SphereVisualization::SphereVisualization(std::list<Spherepoint*> Spoints) : Spoints(Spoints) {
  
}

void SphereVisualization::showAll() {
    std::list<Spherepoint*>::iterator it = std::next(Spoints.begin(), 0);
    std::size_t size = Spoints.size();
    vtkSmartPointer<vtkSphereSource>* sphereSources = new vtkSmartPointer<vtkSphereSource>[size]; 
    vtkSmartPointer<vtkPolyDataMapper>* mappers = new vtkSmartPointer<vtkPolyDataMapper>[size]; 
    vtkSmartPointer<vtkActor>* actors = new vtkSmartPointer<vtkActor>[size]; 
    for(std::size_t i=0 ; i<size ; ++i) {
        sphereSources[i] = vtkSmartPointer<vtkSphereSource>::New();
        it = std::next(Spoints.begin(), i);
        sphereSources[i]->SetCenter((*it)->x, (*it)->y, (*it)->z);
        sphereSources[i]->SetRadius(0.1);
        sphereSources[i]->Update();
 
        mappers[i] = vtkSmartPointer<vtkPolyDataMapper>::New();
        mappers[i]->SetInputConnection(sphereSources[i]->GetOutputPort());
        actors[i] = vtkSmartPointer<vtkActor>::New();
        actors[i]->SetMapper(mappers[i]);
  }

    vtkSmartPointer<vtkSphereSource> sphereSourceCentral = 
    vtkSmartPointer<vtkSphereSource>::New();
  sphereSourceCentral->SetCenter(0.0, 0.0, 0.0);
  sphereSourceCentral->SetRadius(1.0);
  sphereSourceCentral->Update();
  vtkSmartPointer<vtkPolyDataMapper> mapperCentral = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapperCentral->SetInputConnection(sphereSourceCentral->GetOutputPort());
  vtkSmartPointer<vtkActor> actorCentral = 
    vtkSmartPointer<vtkActor>::New();
  actorCentral->SetMapper(mapperCentral);

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
 
  for(std::size_t i=0 ; i<size ; ++i) {
    renderer->AddActor(actors[i]);
  }
  renderer->AddActor(actorCentral);
  renderer->SetBackground(0,0.5,1); // Background color yellow
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
  for(std::size_t i=0 ; i<size ; ++i) {
    stlWriter->SetInputConnection(sphereSources[i]->GetOutputPort());
  }
stlWriter->Write();
    delete [] sphereSources;
    delete [] mappers;
    delete [] actors;
}

// obsolete
void SphereVisualization::show() {
}
