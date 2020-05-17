project(ClientServer_test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(sync_client sync_client.cpp)
if(WIN32)
  target_link_libraries(sync_client wsock32 ws2_32)
endif()

add_executable(sync_server sync_server.cpp)
if(WIN32)
  target_link_libraries(sync_server wsock32 ws2_32)
endif()
