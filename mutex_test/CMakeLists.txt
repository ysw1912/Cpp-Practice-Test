project(mutex_test)

find_package(Threads)

add_executable(lock lock_test.cpp)
target_link_libraries(lock ${CMAKE_THREAD_LIBS_INIT})
