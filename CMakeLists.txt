cmake_minimum_required(VERSION 2.8)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Build type")
    message(STATUS "No build type selected, default to ${CMAKE_BUILD_TYPE}")
endif()

project(test1)


find_package(OpenMP)
find_package(MPI QUIET)

include_directories(${MPI_CXX_INCLUDE_PATH})

enable_testing()

add_executable(mpi mpi.cpp)
target_link_libraries(mpi ${MPI_CXX_LIBRARIES})

add_executable(openmp openmp.cpp)
set_target_properties(openmp PROPERTIES
    COMPILE_FLAGS ${OpenMP_CXX_FLAGS}
    LINK_FAGS     ${OpenMP_CXX_FLAGS}
    )

add_test(mpi mpi)
add_test(openmp openmp)
