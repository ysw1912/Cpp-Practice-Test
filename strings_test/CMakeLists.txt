project(strings_test)

add_library(strings
    strings.cpp
)

include_directories(D:/workspace/third_party/include)
link_directories(D:/workspace/third_party/lib)

add_executable(strings_test strings_test.cpp)
target_link_libraries(strings_test
    strings
    gtest
    gtest_main
)
