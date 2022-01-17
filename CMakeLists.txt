cmake_minimum_required(VERSION 3.12)
project(sct LANGUAGES C VERSION 1.0.0)

include(CTest)
set(C_STANDARD 99)

add_library(sct STATIC src/sct.c)
target_include_directories(sct PRIVATE include)
target_compile_options(sct PRIVATE /W4 /Wall)

add_executable(sct_test tests/sct_test.c)
target_include_directories(sct_test PRIVATE include)
target_link_libraries(sct_test sct)
add_test(NAME sct_test COMMAND sct_test)