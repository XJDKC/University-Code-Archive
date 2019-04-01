`timescale 1ns / 1ps

module memory#(parameter DATA_WIDTH = 8,parameter ADDR_LENTH = 16)(addr,data);
	input	[DATA_WIDTH-1:0]	addr;
    output  reg[DATA_WIDTH-1:0]    data;
    reg     [DATA_WIDTH-1:0]    list[ADDR_LENTH-1:0];

    initial
    begin
        data=0;
        $readmemh("data.dat",list,0,ADDR_LENTH-1);
    end
    
    always@(addr)
    begin
        data<=list[addr];
    end
endmodule
