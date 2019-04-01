`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/05/15 08:30:12
// Design Name: 
// Module Name: divide
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


module divider(clk, clk_N);
input clk;                      // ϵͳʱ��
output clk_N;                   // ��Ƶ���ʱ��
parameter N = 100_000_000;      // 1Hz��ʱ��,N=fclk/fclk_N
reg [31:0] counter;             /* ������������ͨ������ʵ�ַ�Ƶ��
                                   ����������0������(N/2-1)ʱ��
                                   ���ʱ�ӷ�ת������������ */
reg clk_N,state;
always @(posedge clk)  begin    // ʱ��������
                                // ����ʵ��
      if (2*counter+2 == N)
        begin 
            state<=~state;
            clk_N<=state;
            counter<=32'd0;
        end
      else 
        counter<=counter+32'd1;
end                           
endmodule

