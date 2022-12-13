# CS 225: light-bulb-puzzle
> By Yifan Zhu, Yidong Zhang, Zhenyi Gai, Pengyuan Cheng

## Introduction

Supporting resources:
  * Youtube video presentation: [light-bulb-puzzle] : https://youtu.be/UFjK_VGRG_E
  * Written Report : https://www.prairielearn.org/pl/course_instance/129448/instance_question/251302276/

Algorithm:
  * Iterative Deepening Depth-first Search (IDS)
  * Breadth-First Search （BFS）
  * A Star

## Root Folder
  * entry: location of main.cpp
  * lib: Imported library
  * src: Specific code we 
  * tests: The location of our test case.

## Root File
  * gitgore: To ignore certain local files
  * Makefile: Compile the code with make commend in terminal
  * README.md

## Setup
  * Clone the repository from the github.
  * Nagivate into repository: cd light-bulb-puzzle-main
  * Create build folder by running `mkdir build`
  * `cd build` to enter the build directory, then `cmake ..` to build the makefile infrastructures
  * To compile and run the solver executable, run `make solve` and then `./solve`. Command line prompts will appear next and tell you what to input

## Test
A quick guide to test whether the code have problems or not
* Complete Setup first
* Run in terminal: make test
* Run in terminal: ./test


