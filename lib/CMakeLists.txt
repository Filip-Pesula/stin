cmake_minimum_required(VERSION 3.10)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/boost_1_78_0/)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/googletest/googlemock/include/)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/googletest/googlemock/)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/googletest/googletest/include/)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR}/googletest/googletest/)


set(GTESTSORCES ${CMAKE_CURRENT_LIST_DIR}/gtestSrc.cpp)
#Log Files
foreach(source  ${GTESTSORCES})
  message(STATUS "gtestSource='${GTESTSORCES}'")
endforeach()
#Create Library

add_library(gtestSrcObjects OBJECT ${GTESTSORCES})
