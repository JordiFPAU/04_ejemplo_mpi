cmake_minimum_required(VERSION 3.16)
 
#nombredle proyecto
project(ejemploMPI)
 
##set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -mavx2 -O3 -fopenmp")
find_package(fmt CONFIG REQUIRED)
 
##find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)
## --
set(MPI_ROOT "C:/oneAPI/mpi/latest")
set(MPI_INCLUDE "${MPI_ROOT}/include")
set(MPI_LIB "${MPI_ROOT}/lib")

include_directories(
    ${MPI_INCLUDE}
    )
 
#generar ejectuable , por que medio se ejecutara main.cpp
add_executable(ejemplo_mpi main.cpp)
 
target_link_libraries(ejemplo_mpi PRIVATE
    fmt::fmt
    ${MPI_LIB}/impi.lib
    )

add_executable(matrices_mult matrices_mult.cpp)
 
target_link_libraries(matrices_mult PRIVATE
    fmt::fmt
    ${MPI_LIB}/impi.lib
    )