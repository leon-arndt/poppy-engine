cmake_minimum_required(VERSION 3.10)
project(poppy-engine)

project(${PROJECT_NAME} VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(SOURCES 
    ${SRC_DIR})

add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp vendor/entt.h src/transform.h src/transform.cpp)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME}
    PRIVATE ${SRC_DIR})

find_package(glfw3 3.2 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
