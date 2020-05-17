project(python_test)

include_directories(
  D:/workspace/third_party/include
  D:/packages/python37/include
)
link_directories(
  D:/workspace/third_party/lib
  D:/packages/python37/libs
)

add_executable(python_01 python_01.cpp)
target_link_libraries(python_01 python37)
