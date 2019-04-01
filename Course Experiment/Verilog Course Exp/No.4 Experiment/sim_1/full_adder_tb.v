`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/10 20:10:07
// Design Name: 
// Module Name: full_adder_tb
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


module full_adder_tb();
    parameter DATA_WIDTH=3;
    reg [DATA_WIDTH-1:0]A;
    reg [DATA_WIDTH-1:0]B;
    wire [DATA_WIDTH-1:0]ans;
    
    integer i,j;
    
    initial
    begin
        for (i=0;i<8;i=i+1)
        begin
            for (j=0;j<8;j=j+1)
            begin
                #20 A=i;
                    B=j;
            end
        end
    end
    
    full_adder #(DATA_WIDTH)tb(A,B,ans);
endmodule
