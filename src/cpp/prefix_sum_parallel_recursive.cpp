#include <iostream>
#include <chrono>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <string.h>

using std::cin, std::cout, std::endl;

void prefix_sum_parallel(long long* a, long unsigned int length, int step) {
    int stride = step * 2;
    #pragma omp parallel for shared(a)
    for (int i = stride - 1; i < length; i += stride) {
        a[i] += a[i - step];
    }
    if (stride * 2 <= length) {
        prefix_sum_parallel(a, length, stride);
    }
    #pragma omp parallel for shared(a)
    for (int i = stride + step - 1; i < length; i += stride) {
        a[i] += a[i - step];
    }
}

void prefix_sum_parallel(long long* a, long unsigned int length) {
    prefix_sum_parallel(a, length, 1);
}

int main(int argc, char** argv) {

    bool verbose = true;
    if (argc == 2 && strcmp(argv[1], "silent") == 0) {
        verbose = false;
    }

    long unsigned int length;
    cin >> length;

    long long* a = new long long[length];
    for (int i = 0; i < length; i++) {
        cin >> a[i];
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    prefix_sum_parallel(a, length);

    auto finish = std::chrono::high_resolution_clock::now();
    auto work_time =  std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();



    // out
    if (verbose) {
        cout << "Work time (ns): " << work_time << endl;
        cout << "Num threads: " << omp_get_max_threads() << endl;
        for (int i = 0; i < length; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    } else {
        cout << work_time << endl; // only output time of work
    }


    return 0;
}
