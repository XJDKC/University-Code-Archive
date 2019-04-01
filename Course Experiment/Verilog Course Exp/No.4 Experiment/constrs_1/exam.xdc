set_property -dict { PACKAGE_PIN E3   IOSTANDARD LVCMOS33 } [get_ports { clk }];

set_property -dict { PACKAGE_PIN L3   IOSTANDARD LVCMOS33 } [get_ports { SEG[0] }];
set_property -dict { PACKAGE_PIN N1   IOSTANDARD LVCMOS33 } [get_ports { SEG[1] }];
set_property -dict { PACKAGE_PIN L5   IOSTANDARD LVCMOS33 } [get_ports { SEG[2] }];
set_property -dict { PACKAGE_PIN L4   IOSTANDARD LVCMOS33 } [get_ports { SEG[3] }];
set_property -dict { PACKAGE_PIN K3   IOSTANDARD LVCMOS33 } [get_ports { SEG[4] }];
set_property -dict { PACKAGE_PIN M2   IOSTANDARD LVCMOS33 } [get_ports { SEG[5] }];
set_property -dict { PACKAGE_PIN L6   IOSTANDARD LVCMOS33 } [get_ports { SEG[6] }];
set_property -dict { PACKAGE_PIN M4   IOSTANDARD LVCMOS33 } [get_ports { SEG[7] }];

#set_property -dict { PACKAGE_PIN T8   IOSTANDARD LVCMOS33 } [get_ports { SEG[0] }];
#set_property -dict { PACKAGE_PIN V9   IOSTANDARD LVCMOS33 } [get_ports { SEG[1] }];
#set_property -dict { PACKAGE_PIN R8   IOSTANDARD LVCMOS33 } [get_ports { SEG[2] }];
#set_property -dict { PACKAGE_PIN T6   IOSTANDARD LVCMOS33 } [get_ports { SEG[3] }];
#set_property -dict { PACKAGE_PIN T5   IOSTANDARD LVCMOS33 } [get_ports { SEG[4] }];
#set_property -dict { PACKAGE_PIN T4   IOSTANDARD LVCMOS33 } [get_ports { SEG[5] }];
#set_property -dict { PACKAGE_PIN U7   IOSTANDARD LVCMOS33 } [get_ports { SEG[6] }];
#set_property -dict { PACKAGE_PIN U6   IOSTANDARD LVCMOS33 } [get_ports { SEG[7] }];

set_property -dict { PACKAGE_PIN N6   IOSTANDARD LVCMOS33 } [get_ports { AN[0] }];
set_property -dict { PACKAGE_PIN M6   IOSTANDARD LVCMOS33 } [get_ports { AN[1] }];
set_property -dict { PACKAGE_PIN M3   IOSTANDARD LVCMOS33 } [get_ports { AN[2] }];
set_property -dict { PACKAGE_PIN N5   IOSTANDARD LVCMOS33 } [get_ports { AN[3] }];
set_property -dict { PACKAGE_PIN N2   IOSTANDARD LVCMOS33 } [get_ports { AN[4] }];
set_property -dict { PACKAGE_PIN N4   IOSTANDARD LVCMOS33 } [get_ports { AN[5] }];
set_property -dict { PACKAGE_PIN L1   IOSTANDARD LVCMOS33 } [get_ports { AN[6] }];
set_property -dict { PACKAGE_PIN M1   IOSTANDARD LVCMOS33 } [get_ports { AN[7] }];

set_property -dict { PACKAGE_PIN U9   IOSTANDARD LVCMOS33 } [get_ports { start }];
set_property -dict { PACKAGE_PIN U8   IOSTANDARD LVCMOS33 } [get_ports { rst }];

set_property -dict { PACKAGE_PIN V4   IOSTANDARD LVCMOS33 } [get_ports { done }];
