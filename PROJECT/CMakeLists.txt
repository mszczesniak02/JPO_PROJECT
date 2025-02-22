cmake_minimum_required(VERSION 3.16)

project(JPO_PROJECT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define DirectX SDK Include and Lib Paths (Assuming DXSDK is installed)
# UPDATE/FIND DX9
set(DIRECTX_SDK_INCLUDE "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include")
set(DIRECTX_SDK_LIB "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Lib/x86")

# ImGui ADD TO PATH 
include_directories(${CMAKE_SOURCE_DIR}/ImGui ${DIRECTX_SDK_INCLUDE})

# SRC FILES
file(GLOB IMGUI_SOURCES
    ${CMAKE_SOURCE_DIR}/ImGui/*.cpp
    ${CMAKE_SOURCE_DIR}/ImGui/*.h
    ${CMAKE_SOURCE_DIR}/ImGui/*.hpp
)

# EXECS
add_executable(${PROJECT_NAME} main.cpp ${IMGUI_SOURCES})

# Link DirectX9 libraries
target_link_libraries(${PROJECT_NAME} d3d9 dwmapi gdi32 )
target_link_directories(${PROJECT_NAME} PRIVATE ${DIRECTX_SDK_LIB})

# GTest
add_subdirectory(tests)

