`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/05 09:55:47
// Design Name: 
// Module Name: decoder3_8
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

module decoder3_8(num, sel);
input [2: 0] num;       // 数码管编号：0~7
output reg [7:0] sel;       // 7段数码管片选信号，低电平有效

always@(num)begin
    case (num[2:0])
		4'b000: sel = 8'b11111110;
        4'b001: sel = 8'b11111101;
        4'b010: sel = 8'b11111011;
        4'b011: sel = 8'b11110111;
        4'b100: sel = 8'b11101111;
        4'b101: sel = 8'b11011111;
        4'b110: sel = 8'b10111111;
        4'b111: sel = 8'b01111111;
    endcase
end

endmodule



