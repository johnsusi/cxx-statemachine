cmake_minimum_required(VERSION 3.2)

project(cxx-statemachine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type selected, default to Release")
  set(CMAKE_BUILD_TYPE "Release")
endif()

include(CheckCXXCompilerFlag)

check_cxx_compiler_flag("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-stdlib=libc++" COMPILER_SUPPORTS_LIBCXX)

if(COMPILER_SUPPORTS_CXX1Y)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
elseif(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

if (COMPILER_SUPPORTRS_LIBCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=libc++")
endif()

include_directories(
    include
)

add_subdirectory(src)


