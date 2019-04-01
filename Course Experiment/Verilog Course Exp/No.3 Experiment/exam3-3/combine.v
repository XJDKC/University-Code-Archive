`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/05 09:21:22
// Design Name: 
// Module Name: combine
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


module combine(clk,out);
input clk;
output [2:0]out;
wire clk_N;

    divider d(clk,clk_N);
    counter c(clk_N,out);

endmodule
