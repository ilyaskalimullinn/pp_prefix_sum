if [ $# -eq 0 ]
    then
        echo "Must specify number of input files and number of threads";
        exit 1;
fi

mkdir -p file/in
mkdir file/out

# Write number of datasets
echo $1 > file/out/measures.txt

echo "Generating data..."
python3 src/py/generate.py $1


echo "Compiling all algorithms..."
c++ -o target/sequential src/cpp/prefix_sum_sequential.cpp
g++ -fopenmp -o target/parallel_recursive src/cpp/prefix_sum_parallel_recursive.cpp
g++ -fopenmp -o target/parallel_alt src/cpp/prefix_sum_parallel_alt.cpp


echo "Running sequential..."
for ((i=1; i <= 2 * $1 ; i++))
do
    echo "$i..."
    target/sequential silent < file/in/input$i.txt >>file/out/measures.txt
done

echo "Running parallel recursive, $1 threads..."
for ((i=1; i <= 2 * $1 ; i++))
do
    echo "$i..."
    export OMP_NUM_THREADS=$2 && target/parallel_recursive silent < file/in/input$i.txt >>file/out/measures.txt
done

echo "Running parallel alternative, $1 threads..."
for ((i=1; i <= 2 * $1 ; i++))
do
    echo "$i..."
    export OMP_NUM_THREADS=$2 && target/parallel_alt silent < file/in/input$i.txt >>file/out/measures.txt
done

python3 src/py/visualise_all.py
