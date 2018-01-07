############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project cordic_cart2_polar
set_top cordiccart2pol
add_files cordiccart2pol.h
add_files cordiccart2pol.cpp
add_files -tb cordiccart2pol_test.cpp
open_solution "solution1"
set_part {xc7k160tfbg484-2} -tool vivado
create_clock -period 10 -name default
#source "./cordic_cart2_polar/solution1/directives.tcl"
csim_design -clean -compiler gcc
csynth_design
cosim_design
export_design -format ip_catalog
