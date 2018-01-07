############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project complex_fir
set_top fir
add_files fir.h
add_files fir.cpp
add_files -tb out.gold.dat
add_files -tb input_q.dat
add_files -tb input_i.dat
add_files -tb fir_test.cpp
open_solution "solution1"
set_part {xc7k160tfbg484-2} -tool vivado
create_clock -period 10 -name default
#source "./complex_fir/solution1/directives.tcl"
csim_design -clean -compiler gcc
csynth_design
cosim_design
export_design -format ip_catalog
