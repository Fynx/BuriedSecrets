project(BuriedSecrets)
cmake_minimum_required(VERSION 3.0)

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "DEBUG")
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_FLAGS "-Wall -Werror -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "$-ggdb -pg")
set(CMAKE_CXX_FLAGS_RELEASE "") # Box2D is problematic to use -OX
set(EXECUTABLE_OUTPUT_PATH "${BuriedSecrets_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${BuriedSecrets_BINARY_DIR}/lib")

# Qt
find_package(Qt5 COMPONENTS Core Gui Widgets)
include_directories(${Qt5Widgets_INCLUDE_DIRS} ${BuriedSecrets_SOURCE_DIR}/src)

# SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.1 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIR})

# Box2D
set(BOX2D_VERSION 2.3.0)
set(LIB_INSTALL_DIR lib${LIB_SUFFIX})
set(BOX2D_INSTALL_BY_DEFAULT OFF)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
option(BOX2D_INSTALL "Install Box2D libs, includes, and CMake scripts" ${BOX2D_INSTALL_BY_DEFAULT})
option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" OFF)
add_subdirectory(Box2D)
include_directories(${CMAKE_SOURCE_DIR})

# Tests
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
	find_package(Qt5 COMPONENTS Test)
	include_directories(${Qt5Test_INCLUDE_DIRS})
	enable_testing()
endif(BUILD_TESTS)

# Install
install(DIRECTORY data DESTINATION "${BuriedSecrets_BINARY_DIR}")


# UI Resources
qt5_add_resources(UI_data_RESOURCES UI_data/UI_data.qrc)
add_library(UI_Data ${UI_data_RESOURCES})


add_subdirectory(src)
