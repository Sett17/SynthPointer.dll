cmake_minimum_required(VERSION 3.10)
project(SynthPointer VERSION 1.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
set(CMAKE_C_STANDARD 99)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(SynthPointer SHARED SynthPointer.c)
