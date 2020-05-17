set(SUBDIRS
  async_server_test
  sync_client_server_test
  variant_test
)
FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(${subdir})
ENDFOREACH()

add_executable(msic_asio main.cpp)
if(WIN32)
  target_link_libraries(msic_asio wsock32 ws2_32)
endif()