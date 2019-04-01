`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/10 22:12:25
// Design Name: 
// Module Name: memory_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module memory_tb();
    parameter DATA_WIDTH = 32;
    reg [DATA_WIDTH-1:0]addr;
    wire [DATA_WIDTH-1:0]data;
    
    initial
    begin
        addr=0;
        #20 addr=1;
        while (addr!=-1)
        begin
           #10 addr=addr-1;
           #10 addr=data+1;
           if (addr==1) addr=-1;
        end
    end
    
    memory #(DATA_WIDTH)tb(addr,data);
endmodule
