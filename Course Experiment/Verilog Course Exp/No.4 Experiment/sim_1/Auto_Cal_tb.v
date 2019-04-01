`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/11 18:53:32
// Design Name: 
// Module Name: Auto_Cal_tb
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


module Auto_Cal_tb();
    parameter DATA_WIDTH = 32;
    reg start;
    reg rst;
    reg clk;
    wire done;
    wire [DATA_WIDTH-1:0]sum_out;
    
    initial 
    begin
        start=0;
        rst=0;
        clk=0;
    end
    
    always
    begin
        #10 clk=~clk;
    end
    
    always
    begin
        #100 start = 1;
        #400 start = 0;
    end
    
    Auto_Cal #(DATA_WIDTH)tb(start,rst,clk,done,sum_out);
endmodule
