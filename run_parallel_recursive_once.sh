if [ $# -eq 0 ]
    then
        echo "Must specify number of threads";
        exit 1;
    else
        g++ -fopenmp -o target/parallel_recursive src/cpp/prefix_sum_parallel_recursive.cpp && export OMP_NUM_THREADS=$1 && target/parallel_recursive
fi
