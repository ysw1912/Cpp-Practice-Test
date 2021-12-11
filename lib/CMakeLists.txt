project(thread_test)

find_package(Threads)

add_executable(thread thread_test.cpp)
target_link_libraries(thread ${CMAKE_THREAD_LIBS_INIT})
