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
input [2:0] addr;           // 地址
output [3:0] data;          // 地址addr处存储的数据 

reg [3: 0] mem [7: 0];      //  8个4位的存储器

assign data=mem[addr[2:0]];

initial   begin             // 初始化存储器
    mem[0]=0;
    mem[1]=2;
    mem[2]=4;
    mem[3]=6;
    mem[4]=8;
    mem[5]=10;
    mem[6]=12;
    mem[7]=14;
end     
                        // 读取addr单元的值输出                      
endmodule

