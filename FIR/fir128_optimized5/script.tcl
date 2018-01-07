############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project project_fir128
set_top fir
add_files fir.cpp
add_files fir.h
add_files -tb fir_test.cpp
add_files -tb input.dat
add_files -tb out.dat
add_files -tb out.gold.dat
open_solution "solution_pipeline_w_partition"
set_part {xc7k160tfbg484-2}
create_clock -period 10 -name default
#source "./project_fir128/solution_pipeline_w_partition/directives.tcl"
csim_design -clean -compiler gcc
csynth_design
cosim_design
export_design -format ip_catalog
