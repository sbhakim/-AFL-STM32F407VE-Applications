$ export AFL_USE_ASAN=1
$ CC=afl-clang-fast make
afl-fuzz -i input/ -o output/ ./vulfoo


