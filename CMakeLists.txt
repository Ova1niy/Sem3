cmake_minimum_required(VERSION 3.15)
project(sem3_lab2)

set(CMAKE_CXX_STANDARD 20)

#add_executable(sem3_lab2 tests/sparce_matrix_test.cpp list_for_pairs.h hash_table.h idictionary.h histogram.h dynamic_array.h sparce_matrix.h graph.h)
#add_executable(sem3_lab2 main.cpp list_for_pairs.h hash_table.h idictionary.h histogram.h dynamic_array.h sparce_matrix.h graph.h)
add_executable(sem3_lab2 tests/histogram_test.cpp list_for_pairs.h hash_table.h idictionary.h histogram.h dynamic_array.h sparce_matrix.h graph.h)
#add_executable(sem3_lab2 tests/graph_test.cpp list_for_pairs.h hash_table.h idictionary.h histogram.h dynamic_array.h sparce_matrix.h graph.h)