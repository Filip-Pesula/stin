cmake_minimum_required(VERSION 3.10)
if(WIN32)
  message(STATUS "OS_detect=WIN32")
endif()
if(UNIX)
  message(STATUS "OS_detect=UNIX")
endif()


set(TEST_OUT_DIRECTORY ${CMAKE_BINARY_DIR}/../Test)
set(RELEASE_OUT_DIRECORY ${CMAKE_BINARY_DIR}/../Debug)
include(${CMAKE_SOURCE_DIR}/lib/CMakeLists.txt)

set(CMAKE_CXX_STANDARD 20)

project(main)

message(STATUS "CMAKE_BUILD_TYPE='${CMAKE_BUILD_TYPE}'")


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  message(STATUS "Debug mode")
  set(RELEASE_OUT_DIRECORY ${CMAKE_BINARY_DIR}/../Debug)
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDebug")
  add_definitions( -DDebug )
  SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs --coverag -fmax-errors=5")
  SET(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs --coverag -fmax-errors=5")
  SET(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs --coverag -fmax-errors=5")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "Release mode")
  set(RELEASE_OUT_DIRECORY ${CMAKE_BINARY_DIR}/../Release)
  add_definitions( -DRelease )
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RELEASE_OUT_DIRECORY})



include_directories(${CMAKE_SOURCE_DIR}/src)
#Find all Cpp Files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(APPEND SOURCES ${CMAKE_SOURCE_DIR}/lib/JsonSrc.cpp)
#Log Files
foreach(source  ${SOURCES})
  message(STATUS "source='${source}'")
endforeach()
#Create Library
string(REGEX REPLACE "src/Main.cpp" "" SOURCES "${SOURCES}")

add_library(srcObjects OBJECT ${SOURCES})

add_executable(ChatBot ${CMAKE_SOURCE_DIR}/src/Main.cpp)
target_link_libraries(ChatBot srcObjects)

if(WIN32)
  target_link_libraries(ChatBot wsock32 ws2_32)
endif()
if(UNIX)
  target_link_libraries(ChatBot -pthread)
endif()




get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "includes='${dir}'")
endforeach()
get_directory_property( DirDefs DIRECTORY ${CMAKE_SOURCE_DIR} COMPILE_DEFINITIONS )
message(STATUS "COMPILE_DEFINITIONS='${DirDefs}'")

file(GLOB RESOURCES ${CMAKE_SOURCE_DIR}/res/*)
file(COPY ${RESOURCES} DESTINATION ${RELEASE_OUT_DIRECORY})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  #compile tests
  enable_testing()
  message(STATUS "----------------TEST----------------")

  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TEST_OUT_DIRECTORY})



  file(GLOB TESTS ${CMAKE_SOURCE_DIR}/test/*.cpp)
  string(REGEX REPLACE "src/Main.cpp" "" SOURCES "${SOURCES}")

  foreach(test ${TESTS})
    get_filename_component(TESTNAME ${test} NAME_WLE)
    set(TESTNAME "Test_${TESTNAME}")
    message(STATUS "test='${TESTNAME}'")
    message(STATUS "testDir='${test}'")
    add_executable(${TESTNAME} ${test})
    target_link_libraries(${TESTNAME} srcObjects)
    if(WIN32)
      target_link_libraries(${TESTNAME} wsock32 ws2_32)
    endif()
    if(UNIX)
      target_link_libraries(${TESTNAME} -pthread)
    endif()

    add_test(${TESTNAME} "${TEST_OUT_DIRECTORY}/${TESTNAME}")
  endforeach()
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")


