#!/bin/bash
gcc -c client.c
gcc -c vector.c
gcc -c vector_iterator.c
gcc -c algorithms.c
gcc -c iterator.c
gcc client.o vector.o vector_iterator.o algorithms.o iterator.o
./a.out
