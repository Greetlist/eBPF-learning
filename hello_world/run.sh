#!/bin/bash
clang-17 -O2 -g -target bpf -c hello.c -o hello.o
sudo bpftool 
