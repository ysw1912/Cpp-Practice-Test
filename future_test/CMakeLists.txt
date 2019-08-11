project(future_test)

find_package(Threads)

add_executable(async async_test.cpp)
target_link_libraries(async ${CMAKE_THREAD_LIBS_INIT})

add_executable(packaged_task packaged_task_test.cpp)
target_link_libraries(packaged_task ${CMAKE_THREAD_LIBS_INIT})

add_executable(promise promise_test.cpp)
target_link_libraries(promise ${CMAKE_THREAD_LIBS_INIT})
