project(gtest_test)

include_directories(D:/workspace/third_party/include)
link_directories(D:/workspace/third_party/lib)

add_executable(gtest_test
    assert_test.cpp
    death_test.cpp
    environment_test.cpp
    main_test.cpp
    parameterize_test.cpp
)
target_link_libraries(gtest_test
    utils
    gtest
    gtest_main
)
