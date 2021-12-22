#include <mpi.h>
#include <iostream>

using namespace std;
const int N = 1000000;

int dot_product(int* a, int* b, int n)
{
    int prod = 0;
    for (int i = 0; i < n; i++)
        prod += a[i] * b[i];
    return prod;
}

int main(int argc, char* argv[])
{
    int rank, size, result;
    int* a = new int[N];
    int* b = new int[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
        for (int i = 0; i < N; i++)
        {
            a[i] = 1;
            b[i] = 1;
        }
    int local_N = N / size;
    int* local_x = new int[local_N];
    int* local_y = new int[local_N];
    MPI_Scatter(a, local_N, MPI_INT, local_x, local_N, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, local_N, MPI_INT, local_y, local_N, MPI_INT, 0, MPI_COMM_WORLD);

    int local_prod = dot_product(local_x, local_y, local_N);
    MPI_Reduce(&local_prod, &result, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0) cout << "Dot product = " << result << endl;
    MPI_Finalize();
    return 0;
}
