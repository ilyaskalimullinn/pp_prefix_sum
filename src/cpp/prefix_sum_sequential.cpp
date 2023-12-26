#include <iostream>
#include <chrono>
#include <string.h>


using std::cin, std::cout, std::endl;

int main(int argc, char** argv) {

    bool verbose = true;
    if (argc == 2 && strcmp(argv[1], "silent") == 0) {
        verbose = false;
    }

    long unsigned int length;
    cin >> length;

    // can be skipped if we only want to write prefix sums to out
    long* a = new long[length];
    for (int i = 0; i < length; i++) {
        cin >> a[i];
    }

    // computation
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 1; i < length; i++) {
        a[i] += a[i - 1];
    }

    auto finish = std::chrono::high_resolution_clock::now();
    auto work_time =  std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();

    // out
    if (verbose) {
        cout << "Work time (ns): " << work_time << endl;
        for (int i = 0; i < length; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    } else {
        cout << work_time << endl; // only output time of work
    }
    

    return 0;
}
