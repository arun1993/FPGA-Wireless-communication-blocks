############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project fir128-sol4
set_top fir
add_files Documents/Courses/Fall_2017/CSE_237C/Projects/1st_assignment/fir128-solution3/fir.h
add_files Documents/Courses/Fall_2017/CSE_237C/Projects/1st_assignment/fir128-solution3/fir.cpp
add_files -tb Documents/Courses/Fall_2017/CSE_237C/Projects/1st_assignment/fir128-solution3/out.gold.dat
add_files -tb Documents/Courses/Fall_2017/CSE_237C/Projects/1st_assignment/fir128-solution3/out.dat
add_files -tb Documents/Courses/Fall_2017/CSE_237C/Projects/1st_assignment/fir128-solution3/input.dat
add_files -tb Documents/Courses/Fall_2017/CSE_237C/Projects/1st_assignment/fir128-solution3/fir_test.cpp
open_solution "solution1"
set_part {xc7k160tfbg484-2} -tool vivado
create_clock -period 10 -name default
#source "./fir128-sol4/solution1/directives.tcl"
csim_design -clean
csynth_design
cosim_design
export_design -format ip_catalog
