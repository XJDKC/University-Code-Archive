set_property -dict { PACKAGE_PIN U9   IOSTANDARD LVCMOS33 } [get_ports { X }];

set_property -dict { PACKAGE_PIN T8   IOSTANDARD LVCMOS33 } [get_ports { Z }];
set_property -dict { PACKAGE_PIN R8   IOSTANDARD LVCMOS33 } [get_ports { Q1 }];
set_property -dict { PACKAGE_PIN T6   IOSTANDARD LVCMOS33 } [get_ports { Q2 }];
set_property -dict { PACKAGE_PIN T5   IOSTANDARD LVCMOS33 } [get_ports { Q3 }];
set_property -dict { PACKAGE_PIN T4   IOSTANDARD LVCMOS33 } [get_ports { Q4 }];

set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets X_IBUF]