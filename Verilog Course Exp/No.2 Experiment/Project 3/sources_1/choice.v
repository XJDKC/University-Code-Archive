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
input [15:0] SW;       // 16λ��������
output [7:0] SEG;      // 7��������������͵�ƽ��Ч
output [7:0] AN;       // 7�������Ƭѡ�źţ��͵�ƽ��Ч
output [15:0] LED;     // 16λLED��ʾ
    
    assign LED=SW;
    selector(SW,SEG,AN,LED);
    decoder(SW,SEG,AN,LED);
endmodule

