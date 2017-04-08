cmake_minimum_required(VERSION 3.1.3)

project(logviewer)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(ut)

find_package(Qt5Widgets)
find_package(Qt5Network)

file(GLOB_RECURSE SOURCE_FILES LIST_DIRECTORIES false src/*.c*)

# For some reason, in this configuration the header files need to be included
# with the target. (stackoverflow.com/questions/37151163)
file(GLOB_RECURSE HEADER_FILES LIST_DIRECTORIES false include/*.h*)

add_executable(logviewer ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(logviewer Qt5::Widgets Qt5::Network)
target_link_libraries(logviewer ${LIBUT_LIBRARIES})
target_include_directories(logviewer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(logviewer PRIVATE ${CMAKE_BUILD_DIR})

set_target_properties(logviewer PROPERTIES CXX_STANDARD 14)
set_target_properties(logviewer PROPERTIES CXX_STANDARD_REQUIRE ON)
