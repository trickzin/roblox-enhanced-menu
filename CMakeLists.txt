cmake_minimum_required(VERSION 3.16)
project(RobloxEnhancedMenu VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
    set(IMGUI_SOURCES
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
    )
else()
    add_executable(RobloxConsoleMenu simple_menu.cpp)
    set_target_properties(RobloxConsoleMenu PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
    )
    return()
endif()
set(PROJECT_SOURCES
    src/main.cpp
    src/menu.cpp
    src/performance_monitor.cpp
    src/optimization.cpp
    src/themes.cpp
    src/imgui_setup.cpp
)

set(PROJECT_HEADERS
    src/menu.h
    src/performance_monitor.h
    src/optimization.h
    src/themes.h
    src/imgui_setup.h
)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${IMGUI_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    imgui/
    imgui/backends/
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE pdh psapi)
elseif(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl pthread)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)