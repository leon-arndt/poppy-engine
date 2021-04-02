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
set(ImGuiSources
        main.cpp
        imgui/imconfig.h
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_impl_glfw.cpp
        imgui/imgui_impl_glfw.h
        imgui/imgui_impl_opengl3.cpp
        imgui/imgui_impl_opengl3.h
        imgui/imgui_internal.h
        imgui/imgui_widgets.cpp
        imgui/imgui.cpp
        imgui/imgui.h
        imgui/imstb_rectpack.h
        imgui/imstb_textedit.h
        imgui/imstb_truetype.h
        )

file(
    GLOB sources
    src/main.cpp
    vendor/entt.h
    imgui/examples/imgui_impl_opengl3.cpp
    imgui/examples/imgui_impl_glfw.cpp
    src/transform.h
    src/transform.cpp
    src/entt/entt_manager.cpp
    src/entt/components/comp_mesh_render.cpp
    src/entt/components/comp_mesh_render.h
    src/renderer/model.cpp
    src/renderer/hardware_resources.cpp
    src/renderer/resource_manager.cpp
        imgui/glad/glad.h
        imgui/glad/glad.c
    ${ImGuiSources}
        )

add_executable(${PROJECT_NAME} ${sources})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${SRC_DIR}
        imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/glm
        ${CMAKE_CURRENT_SOURCE_DIR}/glew
        imgui/glad
        )

find_package(glfw3 3.2 REQUIRED)
target_link_libraries(${PROJECT_NAME} glfw)
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
link_directories(${OPENGL_LIBRARY_DIRS})
set(LIBS glfw dl ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBS})
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)
