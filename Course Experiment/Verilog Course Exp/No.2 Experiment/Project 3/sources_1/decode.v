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


module selector(SW, SEG, AN, LED);
	input [15:0] SW;       // 16λ��������
	output [7:0] SEG;      // 7��������������͵�ƽ��Ч
	output [7:0] AN;       // 7�������Ƭѡ�źţ��͵�ƽ��Ч
	output [15:0] LED;     // 16λLED��ʾ
	reg [7:0] AN;
	
always@(SW)begin
    case (SW[15:13])
		4'b000: AN = 8'b11111111;
        4'b001: AN = 8'b11111110;
        4'b010: AN = 8'b11111101;
        4'b011: AN = 8'b11111011;
        4'b100: AN = 8'b11110111;
        4'b101: AN = 8'b11101111;
        4'b110: AN = 8'b11011111;
        4'b111: AN = 8'b10111111;
    endcase
end
endmodule
