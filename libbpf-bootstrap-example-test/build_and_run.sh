#!/bin/bash
clang-17 -O2 -g -target bpf -c mini.bpf.c -o mini_bpf.o
bpftool gen skeleton mini_bpf.o > mini.skel.h
clang-17 -O2 -g mini.bpf.c mini.c -o mini -lelf -lbpf
sudo LD_LIBRARY_PATH=/usr/lib64/:$LD_LIBRARY_PATH ./mini
