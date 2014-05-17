# Set projectname (must be done AFTER setting configurationtypes)
project(Bino)

# CMake policies (can not be handled elsewhere)
cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0005 OLD)

# Set RPATH-handing (CMake parameters)
set(CMAKE_SKIP_BUILD_RPATH 0)
set(CMAKE_BUILD_WITH_INSTALL_RPATH 0)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH 1)

# set macro-directory
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/macros")

# build in Release-mode by default if not explicitly set
if( NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(CheckCXXSourceRuns)
include(CheckIncludeFiles)

# set default buildoptions and print them
include(cmake/options.cmake)

# turn off PCH totally if enabled (hidden setting, mainly for devs)
if( NOPCH )
  set(USE_PCH 0)
endif()

include(CheckPlatform)

# basic packagesearching and setup (further support will be needed, this is a preliminary release!)
find_package(PCHSupport)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(libusb-1.0 REQUIRED)
find_package(FFMPEG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)


message( STATUS "Running on X11...")
find_package(X11)
if(X11_FOUND)
    add_definitions(-DHAVE_X11)
endif(X11_FOUND)

message( STATUS "Looking for LIRC-Client...")
find_package(LIRCClient)
if (LIRCCLIENT_FOUND)
    add_definitions(-DHAVE_LIBLIRCCLIENT)
endif(LIRCCLIENT_FOUND)

FIND_PACKAGE(Qt4 REQUIRED)
SET(QT_USE_QTXML 1)

  # this command will generate rules that will run rcc on all files from SAMPLE_RCS
  # in result SAMPLE_RC_SRCS variable will contain paths to files produced by rcc
  #QT4_ADD_RESOURCES( SAMPLE_RC_SRCS ${SAMPLE_RCS} )
  
  # this will run uic on .ui files:
  #QT4_WRAP_UI( SAMPLE_UI_HDRS ${SAMPLE_UIS} )
  
# and finally this will run moc:
# QT4_WRAP_CPP( SAMPLE_MOC_SRCS 
#     ${CMAKE_SOURCE_DIR}/src/bino/gui.moc
# )

# Find revision ID and hash of the sourcetree
#include(cmake/genrev.cmake)

# print out the results before continuing
include(cmake/showoptions.cmake)

# add dependencies
#add_subdirectory(dep)

# add core sources
add_subdirectory(src)
