project(coroutine_macro)

add_executable(coroutine_macro coroutine_macro_main.cpp)
target_link_libraries(coroutine_macro
  ${CMAKE_THREAD_LIBS_INIT}
  utils
)
