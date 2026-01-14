#include <iostream>
#include <fmt/core.h>
#
#include <memory>    //manejo de memoria
#include <vector>    //manejo de vectores
#include <windows.h> //libreria para manejo de tiempo
#include <mpi.h>     //libreria para manejo de MPI
#define MATRIX_DIM 25
std::string machine_name()
{
    std::string mane = "";
    char hostname[128];
    DWORD size = sizeof(hostname);
    GetComputerNameA(hostname, &size);
    mane = hostname;
    return mane;
}

void print_vector(const std::string msg, double *data, int size)
{
    fmt::print("{}: [, ", msg);
    for (int i = 0; i < size; i++)
    {
        fmt::print("{}, ", data[i]);
    }
    fmt::println("]");
}
int main(int argv, char **argc)
{
    MPI_Init(&argv, &argc);
    int nprocs;
    int rank;
    // Ranks
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // nuero de fias para cada RANK:
    int rows_per_rank;

    // Numero de filas de la matriz con el padding

    int rows_alloc = MATRIX_DIM;

    // Numero de filas para relleno de la matriz
    int paddig = 0;

    if (MATRIX_DIM % nprocs != 0)
    {
        int delta = std::ceil(MATRIX_DIM * 1.0 / nprocs); // filas reales tiene =7
        rows_alloc = delta * nprocs;
        paddig = rows_alloc - MATRIX_DIM; // Filas de relleno = 3
    }
    rows_per_rank = rows_alloc / nprocs; // filas por RANK = 7
    // Variables para almacenar los datos:
    std::unique_ptr<double[]> A;                                          // Esta solament en el rank 0, los otros no necesitan la matriz completa
    std::unique_ptr<double[]> b;                                          // rank_0
    std::unique_ptr<double[]> x = std::make_unique<double[]>(MATRIX_DIM); // todos los rank tienen su vector x
    std::unique_ptr<double[]> A_local;                                    // 7*25
    std::unique_ptr<double[]> b_local;                                    // 7
    // en los ranks !=0  A_local *x, de aqui la dimension 7
    if (rank == 0)
    {
        fmt::println("Dimension= {}, rows_alloc = {}, rows_per_rank = {}, padding = {}", MATRIX_DIM, rows_alloc, rows_per_rank, paddig);
        // inicializar A y b
        A = std::make_unique<double[]>(rows_alloc * MATRIX_DIM);
        b = std::make_unique<double[]>(rows_alloc);
        for (int i = 0; i < MATRIX_DIM; i++)
        {
            for (int j = 0; j < MATRIX_DIM; j++)
            {
                int index = i * MATRIX_DIM + j;
                A[index] = i;
            }
        }
        for (int i = 0; i < MATRIX_DIM; i++)
        {
            x[i] = 1;
        }
    }
    A_local = std::make_unique<double[]>(rows_per_rank * MATRIX_DIM);
    b_local = std::make_unique<double[]>(rows_per_rank);

    if (rank == 1)
    {
        print_vector("rank_1, Antes vector x: ", x.get(), MATRIX_DIM );
    }

    if (rank == 2)
    {
        print_vector("rank_2, Antes vector x: ", x.get(), MATRIX_DIM );
    }
    // enviar los datos
    // enviar el vector x a todos los RANKS
    MPI_Bcast(x.get(),         // datos
              MATRIX_DIM,      // cuantos?
              MPI_DOUBLE,      // tipo de dato que enviamos
              0,               // rank de origen, quien envia
              MPI_COMM_WORLD); // grupo
    if (rank == 1)
    {
        print_vector("rank_1, Despues vector x: ", x.get(), MATRIX_DIM );
    }
    if (rank == 2)
    {
        print_vector("rank_2, Despues vector x: ", x.get(), MATRIX_DIM );
    }

    MPI_Finalize();
    return 0;
}