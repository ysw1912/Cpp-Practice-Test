project(boost_test)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(http_server http_server.cpp)
if(WIN32)
  target_link_libraries(http_server wsock32 ws2_32)
endif()

add_executable(server handler.cpp server.cpp)
if(WIN32)
  target_link_libraries(server wsock32 ws2_32)
endif()

add_executable(client handler.cpp client.cpp)
if(WIN32)
  target_link_libraries(client wsock32 ws2_32)
endif()
