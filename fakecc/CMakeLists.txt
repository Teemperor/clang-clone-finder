cmake_minimum_required(VERSION 3.3)
project(standalone)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(Boost COMPONENTS system thread REQUIRED)

if (NOT Boost_FOUND)
    message(FATAL "Boost not found")
endif()

include_directories(${Boost_INCLUDE_DIRS})
find_package(Threads)
set(LIBS ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

set(SOURCE_FILES fakecc.cpp)

add_executable(clang-clone-finder-fakecc ${SOURCE_FILES})

target_link_libraries(clang-clone-finder-fakecc ${LIBS} rt)