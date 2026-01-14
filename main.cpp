#include <iostream>
#include <fmt/core.h>
#include <mpi.h>
int main(int args, char** argv)
{
    MPI_Init(&args, &argv);
    int nprocs;
    int rank;

    //- ranks
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs); // numero de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);   // id del proceso
    //- version 
    int version, subversion;
    MPI_Get_version(&version, &subversion);

    if(rank == 0){
        fmt::print("Version MPI: {}.{}\n", version, subversion);
        fmt::print("Numero de procesos: {}\n", nprocs);
    }
    
    fmt::println("Rank_{} de {} procesos", rank, nprocs);
    std::cout.flush();
    //while(1<2){
    //}

// Finalizar MPI
//Prueba de commit
    MPI_Finalize();
    return 0;
}
