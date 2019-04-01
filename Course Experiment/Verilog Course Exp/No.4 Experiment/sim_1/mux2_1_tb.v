`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/10 20:52:46
// Design Name: 
// Module Name: mux2_1_tb
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


module mux2_1_tb();
    parameter DATA_WIDTH = 8;
    reg [DATA_WIDTH-1:0]A;
    reg [DATA_WIDTH-1:0]B;
    reg sel;
    wire [DATA_WIDTH-1:0]out;
    
    integer i,j;
    
    initial
    begin
        sel=0;
        A=0;
        B=0;
        for (i=0;i<8;i=i+1)
        begin
            for (j=0;j<8;j=j+1)
            begin
                #20 A=i;
                    B=j;
            end
        end
    end
    
    always
    begin
        #10 sel=~sel;
    end
    
    mux2_1 #(DATA_WIDTH)tb(A,B,sel,out);
endmodule
