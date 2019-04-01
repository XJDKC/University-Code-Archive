`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/22 09:07:25
// Design Name: 
// Module Name: counter
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

module counter(clk, out);
input clk;                         // ����ʱ��
output reg [2:0] out;             // ����ֵ

always @(posedge clk)  begin  // ��ʱ�������ؼ�������1
    if (out >= 7) begin
        out<=0;
    end
    else begin
        out<=out+1;
    end
end                           
endmodule
