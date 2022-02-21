cmake_minimum_required(VERSION 3.10)
project(poppy-engine)

set(CMAKE_CPP_COMPILER clang)
set(CMAKE_CXX_STANDARD 17)

project(${PROJECT_NAME} VERSION 1.0)

file(GLOB IMGUI_SOURCES
${CMAKE_SOURCE_DIR}/imgui/*.h
${CMAKE_SOURCE_DIR}/imgui/*.cpp
${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.h
${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.h
${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/glad/*.c
)

file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/src/*.h
    ${CMAKE_SOURCE_DIR}/glad/*.h
)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${IMGUI_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/renderer
        ${CMAKE_SOURCE_DIR}/src/entt
        ${CMAKE_SOURCE_DIR}/src/entt/components
        ${CMAKE_SOURCE_DIR}/src/util
        imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/glew
        imgui/glad
        )

link_directories(${OPENGL_gl_LIBRARY})
link_directories(${GLFW_LIBRARY})
set(LIBS glfw dl ${OPENGL_gl_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${LIBS})