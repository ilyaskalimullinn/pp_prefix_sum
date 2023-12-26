if [ $# -eq 0 ]
    then
        echo "Must specify number of input files and number of threads";
        exit 1;
fi

g++ -fopenmp -o target/parallel_recursive src/cpp/prefix_sum_parallel_recursive.cpp

echo "Running parallel recursive, $1 threads..."
for ((i=1; i <= 2 * $1 ; i++))
do
    echo "$i..."
    export OMP_NUM_THREADS=$2 && target/parallel_recursive silent < file/in/input$i.txt >>file/out/measures.txt
done

