project(gflags_test)

set(gflags_DIR D:/workspace/third_party)
find_package(gflags REQUIRED)

add_library(inet_addr
    addr.cpp
)
target_link_libraries(inet_addr gflags)
add_library(inet::addr ALIAS inet_addr)

add_executable(addr main.cpp)
target_link_libraries(addr
    inet::addr
    gflags
)
