cmake_minimum_required(VERSION 3.22.1)

project(genscene)

add_library(genscene SHARED genscene.c)
add_library(reset SHARED reset.c)