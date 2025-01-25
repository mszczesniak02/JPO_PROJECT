# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(MyProject LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type if not already defined
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Define the directories
set(LIB_DIR lib/files)  # Directory where your .cpp and .hpp files are located
set(TEST_FILES_DIR test_files)  # Directory for test files

# Source files
set(SOURCES
    ${LIB_DIR}/css_file.cpp
    ${LIB_DIR}/html_file.cpp
    ${LIB_DIR}/file.cpp
    ${LIB_DIR}/text_file.cpp
    ${LIB_DIR}/csv_file.cpp
    ${LIB_DIR}/file_factory.cpp
    main.cpp
)

# Header files (optional, for clarity)
set(HEADERS
    ${LIB_DIR}/css_file.hpp
    ${LIB_DIR}/html_file.hpp
    ${LIB_DIR}/file.hpp
    ${LIB_DIR}/text_file.hpp
    ${LIB_DIR}/csv_file.hpp
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories (necessary to include headers from lib/files)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR})

# Compiler-specific flags
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:/W3 /Zi /RTC1 /DDEBUG>      # Debug: Enable runtime checks and debug info
        $<$<CONFIG:Release>:/W3 /O2>                 # Release: Optimizations
    )
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:Debug>:-Wall -Wextra -g -DDEBUG>  # Debug: Enable runtime checks and debug info
        $<$<CONFIG:Release>:-Wall -Wextra -O2>      # Release: Optimizations
    )
endif()
