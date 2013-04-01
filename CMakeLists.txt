cmake_minimum_required(VERSION 2.6)
project(circuitmod)

add_definitions(-std=c++0x -Wall -fexceptions)

find_package(Qt4 REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

SET(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

option(ENABLE_TESTS "Enabling unit tests" OFF)

if(ENABLE_TESTS)
  message(STATUS "Enabling unit tests")
  enable_testing()
  add_subdirectory(tests)
endif()

set(QT_USE_QTGUI TRUE)
set(QT_USE_QTCORE TRUE)
set(QT_USE_NETWORK TRUE)
set(QT_USE_QTOPENGL TRUE)

include(${QT_USE_FILE})

file(GLOB CIRCUITS_HDRS circuits/*.h)
file(GLOB CIRCUITS_SRCS circuits/*.cpp)

file(GLOB CIRCUITS_VIEW_SRCS views/*.cpp)
file(GLOB CIRCUITS_VIEW_HDRS views/*.h)

file(GLOB SRCS "*.cpp" EXCEPT "main.cpp")

SET(SRCS ${SRCS} ${CIRCUITS_SRCS} ${CIRCUITS_VIEW_SRCS})

file(GLOB HDRS "*.h")
SET(HDRS ${HDRS} ${CIRCUITS_HDRS} ${CIRCUITS_VIEW_HDRS})

file(GLOB UIS "*.ui")

qt4_wrap_cpp(MOC_HDRS ${HDRS})
qt4_wrap_ui(UI_HDRS ${UIS})

add_library(circuitmod-core STATIC ${SRCS} ${HDRS} ${MOC_HDRS} ${UI_HDRS})
target_link_libraries(circuitmod-core ${QT_LIBRARIES})

add_executable(circuitmod main.cpp)
target_link_libraries(circuitmod circuitmod-core)
