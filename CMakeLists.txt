cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(humangl CXX)

#===========================================================================================
# OPTIONAL LIBRARiES
#
# The following libraries can be pulled down and added to the project by turnning the
# desired options on. Open an issue for additional default support.
# See: https://github.com/Hoshiningen/OpenGL-Template/issues

# set(ENABLE_ASSIMP   ON CACHE BOOL "Add Open Asset Import Library (assimp) to the project" FORCE)

#===========================================================================================
# GLAD CONFIGURATION
#
# Configure GLAD loader generation variables (lines below pulled from the GLAD top-level
# CMakeLists.txt file, with slight modifications.
# Refer to https://github.com/Dav1dde/glad for more information)

set(GLAD_OUT_DIR        "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory" FORCE)
set(GLAD_PROFILE        "core" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_API            "gl=4.1" CACHE STRING "API type/version pairs, like \"gl=4.1,gles=\", no version means latest" FORCE)
set(GLAD_GENERATOR      "c" CACHE STRING "Language to generate the binding for" FORCE)
set(GLAD_EXTENSIONS     "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included" FORCE)
set(GLAD_SPEC           "gl" CACHE STRING "Name of the spec" FORCE)
set(GLAD_ALL_EXTENSIONS OFF CACHE BOOL "Include all extensions instead of those specified by GLAD_EXTENSIONS" FORCE)
set(GLAD_NO_LOADER      OFF CACHE BOOL "No loader" FORCE)
set(GLAD_REPRODUCIBLE   OFF CACHE BOOL "Reproducible build" FORCE)

#===========================================================================================

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set directory paths
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(sources
${SOURCE_DIR}/main.cpp
${SOURCE_DIR}/env.cpp
${SOURCE_DIR}/types.cpp
${SOURCE_DIR}/model.cpp
${SOURCE_DIR}/globj.cpp
${SOURCE_DIR}/shader.cpp
${SOURCE_DIR}/world.cpp
${SOURCE_DIR}/input.cpp
${SOURCE_DIR}/animator.cpp
${SOURCE_DIR}/skelly.cpp
${SOURCE_DIR}/main_loop.cpp
)

add_executable(humangl ${sources} ${includes})

target_include_directories(humangl PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Perform dependency linkage
include(${CMAKE_DIR}/LinkGLFW.cmake)
LinkGLFW(humangl PRIVATE)

include(${CMAKE_DIR}/LinkGLAD.cmake)
LinkGLAD(humangl PRIVATE)

find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    target_include_directories(humangl PRIVATE ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(humangl PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()

# Handle the optional libraries
if (${ENABLE_ASSIMP})
    include(${CMAKE_DIR}/LinkASSIMP.cmake)
    LinkASSIMP(opengl-template PRIVATE)
endif()

# Enable C++17
set_target_properties(humangl PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO)

# Set project folders
set_target_properties(humangl PROPERTIES FOLDER ${PROJECT_NAME})

# Set build type to Release or Debug
set(CMAKE_BUILD_TYPE Release)
