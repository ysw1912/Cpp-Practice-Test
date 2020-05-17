project(unit_test)

include_directories(D:/workspace/third_party/include)
link_directories(D:/workspace/third_party/lib)

add_executable(unit_test main.cpp)
find_package(Threads)

add_executable(cache_line_test cache_line_test.cpp)
target_link_libraries(cache_line_test ${CMAKE_THREAD_LIBS_INIT})

add_executable(write_combining write_combining.cpp)

add_executable(misc misc.cpp)
target_link_libraries(misc boost_iostreams-mgw81-mt-x64-1_72)
if(WIN32)
  target_link_libraries(misc wsock32 ws2_32)
endif()
add_executable(misc_01 misc_01.cpp)
add_executable(misc_02 misc_02.cpp)
