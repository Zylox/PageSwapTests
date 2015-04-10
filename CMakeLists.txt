cmake_minimum_required (VERSION 2.8)
project (libSoneFivePaging)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=c99 -D_XOPEN_SOURCE=500 -Wall")

include_directories(${CMAKE_CURRENT_DIRECTORY}/include)

add_library(SoneFivePaging SHARED src/S15Paging.c src/doublylinkedlist.c)

install(TARGETS SoneFivePaging DESTINATION lib)
install(FILES include/S15Paging.h include/Datum.h include/doublylinkedlist.h DESTINATION include)

target_link_libraries(SoneFivePaging vbs)

add_executable (test_S15FS src/test_S15Paging.c)
target_link_libraries (test_S15FS SoneFivePaging)
