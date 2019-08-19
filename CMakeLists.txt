cmake_minimum_required(VERSION 3.14)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_library(utils
    src/utils.cpp
)

set(SUBDIRS future_test gflags_test gtest_test mutex_test strings_test)
FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()
