if [ $# -eq 0 ]
    then
        echo "Must specify number of threads";
        exit 1;
    else
        g++ -fopenmp -o target/parallel_alt src/cpp/prefix_sum_parallel_alt.cpp && export OMP_NUM_THREADS=$1 && target/parallel_alt
fi
