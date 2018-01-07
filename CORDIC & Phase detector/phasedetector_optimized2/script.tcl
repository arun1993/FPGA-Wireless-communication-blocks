############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project phase_detector
set_top phasedetector
add_files cordiccart2pol.cpp
add_files cordiccart2pol.h
add_files fir.cpp
add_files fir.h
add_files phasedetector.cpp
add_files phasedetector.h
add_files -tb input_i.dat
add_files -tb input_q.dat
add_files -tb out.gold.dat
add_files -tb phasedetector_test.cpp
open_solution "solution4_optimized1"
set_part {xc7k160tfbg484-2}
create_clock -period 10 -name default
#source "./phase_detector/solution4_optimized1/directives.tcl"
csim_design -clean -compiler gcc
csynth_design
cosim_design
export_design -format ip_catalog
