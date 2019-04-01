`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/15 11:37:42
// Design Name: 
// Module Name: choice
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


module choice(SW, SEG, AN, LED);
input [15:0] SW;       // 16位拨动开关
output [7:0] SEG;      // 7段数码管驱动，低电平有效
output [7:0] AN;       // 7段数码管片选信号，低电平有效
output [15:0] LED;     // 16位LED显示
    
    assign LED=SW;
    selector(SW,SEG,AN,LED);
    decoder(SW,SEG,AN,LED);
endmodule

