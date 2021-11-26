#!/bin/bash

set -xe
gcc -I. compiler.c deque.c -o brainfucker -Wall -Wextra -pedantic -std=c11

