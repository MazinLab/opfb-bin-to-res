open_project opfb-bin-to-res
set_top bin_to_res_buff_multibuffer
add_files src/bin_to_res_buffer.cpp
add_files src/bin_to_res_buffer.hpp
add_files src/bin_to_res_multibuffer.cpp
add_files src/bin_to_res_multibuffer_struct.cpp
add_files -tb src/tb.cpp -cflags "-Wno-unknown-pragmas"
open_solution "solution1"
set_part {xczu28dr-ffvg1517-2-e}
create_clock -period 550MHz -name default
config_export -description {Extract and output OPFB IQs corresponding to resonators} -display_name "OPFB Bin to Res" -format ip_catalog -library mkidgen3 -rtl verilog -vendor MazinLab -version 0.1
csim_design
#csynth_design
#cosim_design -tool xsim
#export_design -flow impl -rtl verilog -format ip_catalog -description "Extract and output OPFB IQs corresponding to resonators" -vendor "MazinLab" -library "mkidgen3" -version "0.1" -display_name "OPFB Bin to Res"
