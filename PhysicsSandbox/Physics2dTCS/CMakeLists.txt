# get our parent directory
get_filename_component(ParentDirectory ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
set(CurrentDirectory ${CMAKE_CURRENT_LIST_DIR})

add_library(Physics2dTCS "") 

target_include_directories(Physics2dTCS
    PUBLIC 
        ${ParentDirectory}
        ${CurrentDirectory}
)

include(${CMAKE_CURRENT_LIST_DIR}/CMakeFiles.cmake)

target_link_libraries(Physics2dTCS
                      PUBLIC
                      Common
                      Meta
                      Serialization
                      Engine
                      Physics2dCore
)

zero_set_all_common_project_settings(
  Target Physics2dTCS 
  Filter PhysicsSandbox 
  PrecompiledHeader "Precompiled.hpp"
  PrecompiledSource "Precompiled.cpp"
)
