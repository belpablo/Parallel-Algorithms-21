#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <typeinfo>
#include <vector>
#include <ctime>
#include <omp.h>

using namespace std;

// Write a parallel OpenMP program that finds the maximum value of a vector (one-dimensional array). 
// Each thread should only store its maximum value; concurrent 
// access to a shared variable that stores the maximum value is not allowed.
//
// Study the dependence of the runtime on the number of threads used (from 1 to 10) 
// for a vector that contains at least 1,000,000 elements (the more, the better).
//
//The program should display on the screen: the number of threads, the execution time.
//
//Transfer the size of the vector through the argv [1] parameter.

int main(int argc, char* argv[]) {

	int N = atoi(argv[1]);
    vector <int> v(N);

    random_device rnd_device;
    mt19937 mersenne_engine{ rnd_device() };
    uniform_int_distribution <int> dist{ 1, 1000 };
    auto gen = [&dist, &mersenne_engine]() { return dist(mersenne_engine); };
        
    generate(begin(v), end(v), gen);

    for (int threads_num = 1; threads_num < 11; threads_num++) {

        vector <double> thread_maxes(threads_num);
        vector <int> thread_max_ids(threads_num);

        double max_loc = 0;

        clock_t start = clock();

#pragma omp parallel for num_threads(threads_num) firstprivate(max_loc) 

        for (int n = 0; n < N; n++) {

            int thread_num = omp_get_thread_num();

            if (v[n] > max_loc) {
                max_loc = v[n];
                thread_maxes[thread_num] = v[n];
                thread_max_ids[thread_num] = n;
            }
        }

        std::vector<double>::iterator max = std::max_element(thread_maxes.begin(), thread_maxes.end());

        double max_val = *max;

        int max_idx = thread_max_ids[max - thread_maxes.begin()];

        clock_t end = clock();

        double elapsed = double(end - start) / CLOCKS_PER_SEC;

        printf("Number of threads = %d\n", threads_num);

        printf("Execution time: %f ms\n\n", elapsed * 1000);

    }

    return 0;
}
