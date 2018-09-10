# cmake_minimum_required(VERSION <specify CMake version here>)
project(RISC C)

set(CMAKE_C_STANDARD 11)

add_executable(RISC main.c RISCEmulatorLibrary.h errors.c file_parser.c instruction.c run.c)