#include <iostream>
#include <chrono>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <string.h>

using std::cin, std::cout, std::endl;

void prefix_sum_parallel(long long* a, long unsigned int n) {
    int max_d = 0;
    for (; max_d < std::log2(n); max_d++) {
        int powd, powd1;
        powd = pow(2, max_d);
        powd1 = powd * 2;
        #pragma omp parallel for
        for (int k = 0; k < n; k += powd1) {
            a[k + powd1 - 1] += a[k + powd - 1];
        }
    }

    a[n - 1] = 0;

    for (int d = std::log2(n) - 1; d >= 0; d--) {
        int powd = pow(2, d);
        int powd1 = powd * 2;
        #pragma omp parallel for
        for (int k = 0; k < n; k += powd1) {
            long t = a[k + powd - 1];
            a[k + powd - 1] = a[k + powd1 - 1];
            a[k + powd1 - 1] += t;
        }
    }
}

int main(int argc, char** argv) {

    bool verbose = true;
    if (argc == 2 && strcmp(argv[1], "silent") == 0) {
        verbose = false;
    }

    long unsigned int true_length;
    cin >> true_length;

    int n = pow(2, std::ceil(std::log2(true_length + 1)));
    long long* a = new long long[n];
    for (int i = 0; i < true_length; i++) {
        cin >> a[i];
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    prefix_sum_parallel(a, n);

    auto finish = std::chrono::high_resolution_clock::now();
    auto work_time =  std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

    // out
    if (verbose) {
        cout << "Work time (ns): " << work_time << endl;
        cout << "Num threads: " << omp_get_max_threads() << endl;
        for (int i = 1; i <= true_length; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    } else {
        cout << work_time << endl; // only output time of work
    }


    return 0;
}
