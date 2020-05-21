project(template_test)

include_directories(D:/workspace/third_party/include)
link_directories(D:/workspace/third_party/lib)

add_executable(flow_control_mock flow_control_mock.cpp)
add_executable(output_test output_test.cpp)
add_executable(py_map_mock py_map_mock.cpp)
