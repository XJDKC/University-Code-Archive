`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/05 09:51:08
// Design Name: 
// Module Name: dynamic_scan
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


module dynamic_scan(clk,SEG,AN);
input clk;              // 系统时钟
output [7:0] SEG;          // 分别对应CA、CB、CC、CD、CE、CF、CG和DP
output [7:0] AN;        // 8位数码管片选信号

wire clk_N;
wire [2:0] num;
wire [3:0] code;

divider d(clk,clk_N);
counter c(clk_N,num);
decoder3_8 de(num,AN);
rom8x4 r(num,code);
pattern p(code,SEG);

endmodule
