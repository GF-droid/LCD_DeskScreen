cmake_minimum_required(VERSION 4.2.1)
project(main C)
aux_source_directory(. SRCS)
add_executable(main ${SRCS})