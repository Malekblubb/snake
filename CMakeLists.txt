project(snake)
cmake_minimum_required(VERSION 2.8)
file(GLOB_RECURSE SRC_LIST "./include/snk/*" "./src/snk/*")
include_directories("./include" "./external/mlk/include")
set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_COMPILER "clang++")
add_executable(${PROJECT_NAME} ${SRC_LIST})

#sfml
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(snake ${SFML_LIBRARIES})
endif()
