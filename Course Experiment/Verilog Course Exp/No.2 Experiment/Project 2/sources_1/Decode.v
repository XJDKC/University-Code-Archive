`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/15 10:36:33
// Design Name: 
// Module Name: Decode
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


module _7Seg_Driver_Decode(SW, SEG, AN, LED);
	input [15:0] SW;       // 16位拨动开关
	output [7:0] SEG;      // 7段数码管驱动，低电平有效
	output [7:0] AN;       // 7段数码管片选信号，低电平有效
	output [15:0] LED;     // 16位LED显示
	
    assign AN=~SW[15:8];
    assign LED=SW;
	
always@(SW)begin
    case (SW) begin
        4'b0000: assign SEG = 8'b11000000;
        4'b0001: assign SEG = 8'b11111001;
        4'b0010: assign SEG = 8'b10100100;
        4'b0011: assign SEG = 8'b10110000;
        4'b0100: assign SEG = 8'b10011001;
        4'b0101: assign SEG = 8'b10010010;
        4'b0110: assign SEG = 8'b10000010;
        4'b0111: assign SEG = 8'b11111000;
        4'b1000: assign SEG = 8'b10000000;
        4'b1001: assign SEG = 8'b10011000;
        4'b1010: assign SEG = 8'b10001000;
        4'b1011: assign SEG = 8'b10000011;
        4'b1100: assign SEG = 8'b11000110;
        4'b1101: assign SEG = 8'b10100001;
        4'b1110: assign SEG = 8'b10000110;
        4'b1111: assign SEG = 8'b10001110;
    end
end
endmodule

