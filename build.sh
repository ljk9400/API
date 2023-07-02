
#!/bin/bash

# file
function build_file() {
    echo "build file"
    rm test_file.o
    gcc file.c -g -o test_file.o 
}

function run_file() {
    echo "run file"
    ./test_file.o 
}

function build_file2() {
    echo "build file2"
    rm test_file2.o
    gcc file2.c -g -o test_file2.o 
}

function run_file2() {
    echo "run file2"
    ./test_file2.o 
}



if [ $# = 0 ]; then
    echo "nothing"
else
    if [ $1 == 'f' ]; then
        build_file
    elif [ $1 == 'run-f' ]; then
        run_file
    elif [ $1 == 'f2' ]; then
        build_file2
    elif [ $1 == 'run-f2' ]; then
        run_file2
    fi
fi