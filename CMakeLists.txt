cmake_minimum_required(VERSION 3.16.2)
project(PDP VERSION 3.0 LANGUAGES C CXX Fortran)

include(ExternalProject)
find_package(MPI REQUIRED)
#find_package(Boost REQUIRED)


include_directories(SYSTEM ${MPI_INCLUDE_PATH})

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -lstdc++ ")
set(TECDIR ${CMAKE_CURRENT_SOURCE_DIR}/3rd_Party/tecio/teciosrc)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ExternalProject_add(Boost 
    URL https://boostorg.jfrog.io/artifactory/main/release/1.76.0/source/boost_1_76_0.tar.gz
    CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    CMAKE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND "" 
)
set(Boost_INCLUDE_DIR ${CMAKE_BINARY_DIR}/Boost-prefix/src/Boost)


ExternalProject_Add(Eigen3
    GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
    CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER} -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} 
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    CMAKE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
set(Eigen_INCLUDE_DIR ${CMAKE_BINARY_DIR}/Eigen3-prefix/src/Eigen3)
add_library(Eigen INTERFACE IMPORTED)
add_dependencies(Eigen Eigen3)








if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
message("${CMAKE_CXX_COMPILER_ID} detected")
set(isINTEL 1)
message("MKLROOT $ENV{MKLROOT}")
set(MKLROOT $ENV{MKLROOT})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -DUSE_MKL")
else()
set(SCALAPACK_INSTALL_DIR ${CMAKE_BINARY_DIR}/external/Scalapack)
ExternalProject_Add(Scalapack
    GIT_REPOSITORY https://github.com/Reference-ScaLAPACK/scalapack.git
    CMAKE_ARGS  "-DCMAKE_INSTALL_PREFIX=${SCALAPACK_INSTALL_DIR}" "-DCMAKE_Fortran_COMPILER=${MPI_Fortran_COMPILER}" "-DCMAKE_C_COMPILER=${MPI_C_COMPILER}"
    UPDATE_COMMAND ""
)
set(SCALAPACK_LIB_DIR ${SCALAPACK_INSTALL_DIR}/lib/)
add_library(scalapack SHARED IMPORTED)
find_package(LAPACK)

set_target_properties(scalapack PROPERTIES IMPORTED_LOCATION ${SCALAPACK_LIB_DIR}/libscalapack.a)
target_link_libraries(scalapack INTERFACE ${LAPACK_LIBRARIES} ${BLAS_LIBRARIES} ${MPI_C_LIBRARIES} gfortran)
endif()




add_subdirectory(3rd_Party/tecio/teciosrc)

add_subdirectory(src)
add_subdirectory(CASLAB_execs)

add_subdirectory(tests)




