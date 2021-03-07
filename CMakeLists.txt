cmake_minimum_required(VERSION 3.10)
set(CMAKE_CPP_COMPILER clang)
set(CMAKE_CXX_STANDARD 17)
project(poppy-engine)

project(${PROJECT_NAME} VERSION 1.0)



set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SOURCES 
    ${SRC_DIR})

file(GLOB sources
src/main.cpp
vendor/entt.h
src/transform.h
src/transform.cpp
src/renderer/model.cpp
src/renderer/hardware_resources.cpp
src/renderer/resource_manager.cpp
glad/glad.h
glad/glad.c)

add_executable(${PROJECT_NAME} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${SRC_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/glm
    )

find_package(glfw3 3.2 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
set(LIBS glfw dl ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
