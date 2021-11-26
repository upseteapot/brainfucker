#!/bin/bash

set -xe
gcc -I. compiler.c -o compiler -Wall -Wextra -pedantic -std=c11

