#!/bin/bash
gcc -c client.c
gcc -c vector.c
gcc -c vector_iterator.c
gcc client.o vector.o vector_iterator.o
./a.out
