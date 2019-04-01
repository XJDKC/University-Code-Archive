`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/05 09:05:29
// Design Name: 
// Module Name: rom8x4
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


module rom8x4(addr, data);
input [2:0] addr;           // ��ַ
output [3:0] data;          // ��ַaddr���洢������ 

reg [3: 0] mem [7: 0];      //  8��4λ�Ĵ洢��

assign data=mem[addr[2:0]];

initial   begin             // ��ʼ���洢��
    mem[0]=0;
    mem[1]=2;
    mem[2]=4;
    mem[3]=6;
    mem[4]=8;
    mem[5]=10;
    mem[6]=12;
    mem[7]=14;
end     
                        // ��ȡaddr��Ԫ��ֵ���                      
endmodule

