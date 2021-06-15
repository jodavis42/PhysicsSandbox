# get our parent directory
get_filename_component(ParentDirectory ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(SandboxSpatialPartitions "") 

target_include_directories(SandboxSpatialPartitions
    PUBLIC 
        ${ParentDirectory}
        ${CurrentDirectory}
)

include(${CMAKE_CURRENT_LIST_DIR}/CMakeFiles.cmake)

target_link_libraries(SandboxSpatialPartitions
                      PUBLIC
                      Common
                      SandboxGeometry

)

zero_set_all_common_project_settings(
  Target SandboxSpatialPartitions 
  Filter PhysicsSandbox 
  PrecompiledHeader "Precompiled.hpp"
  PrecompiledSource "Precompiled.cpp"
)
