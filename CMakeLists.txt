CMAKE_MINIMUM_REQUIRED(VERSION 2.7)
project(OpengGL)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(GLM REQUIRED)

find_package(GLFW3 REQUIRED)

IF(APPLE)
    FIND_LIBRARY(GL_LIBRARY OpenGL)
ENDIF()

include_directories(
        ${GLM_INCLUDE_PATH}
        ${GLFW3_INCLUDE_DIR}
)
include_directories()

add_executable(example_window src/example_window.cpp)
target_link_libraries(example_window ${GLFW3_LIBRARY} ${GL_LIBRARY})