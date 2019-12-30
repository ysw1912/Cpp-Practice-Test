project(unit_test)

include_directories(D:/workspace/third_party/include)
link_directories(D:/workspace/third_party/lib)

add_executable(unit_test main.cpp)
target_link_libraries(strings_test
    gtest
    gtest_main
)

add_executable(misc_01 misc_01.cpp)
add_executable(misc_02 misc_02.cpp)
