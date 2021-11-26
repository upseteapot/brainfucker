#!/bin/bash

set -xe
gcc -I. compiler.c -o brainfucker -Wall -Wextra -pedantic -std=c11

