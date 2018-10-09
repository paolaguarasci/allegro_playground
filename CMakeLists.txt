cmake_minimum_required(VERSION 3.5)
project(allegroPrimer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(AllegroPrimer ${SOURCE_FILES})



IF(UNIX)
  IF(APPLE)
    SET(GUI "Cocoa")
    INCLUDE_DIRECTORIES(  /usr/local/Cellar/allegro/HEAD-f48989c/include )
    LINK_DIRECTORIES(  /usr/local/Cellar/allegro/HEAD-f48989c/lib )
    file(GLOB LIBRARIES "/usr/local/Cellar/allegro/HEAD-f48989c/lib/*.dylib")
    message("LIBRARIES = ${LIBRARIES}")
  ELSE(APPLE)
    SET(GUI "X11")
  ENDIF(APPLE)
ELSE(UNIX)
  IF(WIN32)
    SET(GUI "Win32")

  ELSE(WIN32)
    SET(GUI "Unknown")
  ENDIF(WIN32)
ENDIF(UNIX)
MESSAGE("Compiled for... ${GUI}")

TARGET_LINK_LIBRARIES(AllegroPrimer  ${LIBRARIES})