#include <iostream>
#include <omp.h>

using namespace std;

long const P_TEST = 1000;
long const M_TEST = 1000;
long const N_TEST = 1000;

double alg_matmul2D(int m, int n, int p, int** a, int** b, int** c, int T)
{
    double t1 = omp_get_wtime();
    int i, j, k;
#pragma omp parallel num_threads(T) shared(a,b,c) private(i,j,k) 
    {
#pragma omp for schedule(static)
        for (i = 0; i < m; i = i + 1) {
            for (j = 0; j < n; j = j + 1) {
                a[i][j] = 0;
                for (k = 0; k < p; k = k + 1) {
                    a[i][j] += b[i][k] * c[k][j];
                }
            }
        }
    }

    double runtime = omp_get_wtime() - t1;
    if (m == 5 && n == 5 && p == 5) {
        cout << endl << "Result matrix" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return runtime;
}

int main(int argc, char* argv[])
{
    int** A = new int* [5];
    int** B = new int* [5];
    int** C = new int* [5];
    for (int i = 0; i < 5; i++) {
        A[i] = new int[5];
        B[i] = new int[5];
        C[i] = new int[5];
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            B[i][j] = i + j;
            C[i][j] = i + j;
        }
    }

    cout << "B matrix" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << B[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl << "C matrix" << endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    double time = alg_matmul2D(5, 5, 5, A, B, C, 12);
    cout << "Mult 5x5 matrices takes time - " << time << endl << endl;

    for (int i = 0; i < 5; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    int M, N, P;
    if (argc == 4) {
        M = atoi(argv[1]);
        N = atoi(argv[2]);
        P = atoi(argv[2]);
    }
    else {
        M = M_TEST;
        N = N_TEST;
        P = P_TEST;
    }

    A = new int* [M];
    B = new int* [M];
    C = new int* [P];
    for (int i = 0; i < M; i++) {
        A[i] = new int[N];
        B[i] = new int[P];
    }
    for (int i = 0; i < M; i++) {
        C[i] = new int[N];
    }

    int T = 20;
    double singlemodTime = 0;
    for (int j = 0; j < T; j++) {
        singlemodTime += alg_matmul2D(M, N, P, A, B, C, 1);
    }
    singlemodTime = singlemodTime / T;
    cout << "Run with " << 1 << " threads takes average time - " << singlemodTime << ". Efficiency is 1" << endl << endl;

    for (int i = 2; i < 11; i++) {
        int T = 20;
        double time = 0;
        for (int j = 0; j < T; j++) {
            time += alg_matmul2D(M, N, P, A, B, C, i);
        }
        cout << "Run with " << i << " threads takes average time - " << time / T << ". Efficiency is " <<
            singlemodTime / (time / T) << endl << endl;
    }

    for (int i = 0; i < N; i++) {
        delete[] A[i];
        delete[] C[i];
    }
    for (int i = 0; i < P; i++) {
        delete[] B[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;
}