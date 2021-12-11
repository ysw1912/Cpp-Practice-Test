cmake_minimum_required(VERSION 3.14)

# Find includes in corresponding build directories.
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_library(utils
  src/utils.cpp
)

# Set up boost library.
set(BOOST_ROOT D:/workspace/boost)
set(BOOST_INCLUDEDIR D:/workspace/boost/include)
set(BOOST_LIBRARYDIR D:/workspace/boost/lib)
set(BOOST_MIN_VERSION 1.72.0)
# set(Boost_NO_BOOST_CMAKE ON)
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED)
if(Boost_FOUND)
  message(STATUS "Setting up BOOST")
  message(STATUS " Includes - ${Boost_INCLUDE_DIRS}")
  message(STATUS " Library  - ${Boost_LIBRARY_DIRS}")
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
else()
  message(FATAL_ERROR "Fatal error: Boost not found.")
endif(Boost_FOUND)

set(SUBDIRS
  boost_test
  coroutine
  future_test
  gflags_test
  gtest_test
  lib
  mutex_test
  python_test
  strings_test
  template_test
  unit_test
)
FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()
