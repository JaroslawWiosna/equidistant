cmake_minimum_required (VERSION 2.8)
SET(CMAKE_CXX_STANDARD 14)
SET(COMPILE_FLAGS "-std=c++14 -std=gnu++14 -Wall")
SET(LINK_FLAGS "-lgtest -lpthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINK_EXECUTABLE} ${LINK_FLAGS}" )
include_directories(${GTEST_INCLUDE_DIRS})

project (equidistant)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
find_package(Gtest)
add_executable(equidistant MACOSX_BUNDLE equidistant.cpp) 
target_link_libraries(equidistant gtest pthread)
 
if(VTK_LIBRARIES)
  target_link_libraries(equidistant ${VTK_LIBRARIES})
else()
  target_link_libraries(equidistant vtkHybrid vtkWidgets)
endif()
#######
PROJECT(Sphere)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Sphere MACOSX_BUNDLE Sphere.cxx)
 
if(VTK_LIBRARIES)
  target_link_libraries(Sphere ${VTK_LIBRARIES})
else()
  target_link_libraries(Sphere vtkHybrid vtkWidgets)
endif()
