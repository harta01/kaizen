#!/bin/bash

problem=molecules

g++-4.8 -O2 -std=c++11 -o $problem grader.cpp $problem.cpp
