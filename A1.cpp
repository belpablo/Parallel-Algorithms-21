#include <cstdlib>
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <typeinfo>
#include <vector>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {

	int num = atoi(argv[1]);
    vector <int> vec(num);

    random_device rnd_device;
    mt19937 mersenne_engine{ rnd_device() };
    uniform_int_distribution <int> dist{ 1, 52 };
    auto gen = [&dist, &mersenne_engine]() {
        return dist(mersenne_engine);
    };
        
    generate(begin(vec), end(vec), gen);
        
    int tmp = 0;
    unsigned int start_time = clock();
    for (auto i : vec) {
        tmp += i;
    }
    unsigned int end_time = clock();

    cout << "\ntime without openMP: " << end_time - start_time << endl;

    for (int i = 1; i < 11; i++) {

        tmp = 0;
        start_time = clock();
        #pragma omp parallel for num_threads(i)
        for (auto j : vec) {
            tmp += j;
        }
        end_time = clock();

        cout << "\ntime with " << i << " threads: " << end_time - start_time << endl;
    }

    return 0;
}