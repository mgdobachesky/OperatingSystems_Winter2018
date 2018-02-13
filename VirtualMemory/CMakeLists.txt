cmake_minimum_required(VERSION 3.9)
project(VirtualMemory)

set(CMAKE_CXX_STANDARD 11)

add_executable(VirtualMemory main.cpp Virtual_Memory.cpp Virtual_Memory.h Physical_Memory.cpp Physical_Memory.h Fifo_Implementation.cpp Fifo_Implementation.h Lfu_Implementation.cpp Lfu_Implementation.h Optimal_Implementation.cpp Optimal_Implementation.h)