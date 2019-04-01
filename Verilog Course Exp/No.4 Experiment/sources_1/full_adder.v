`timescale 1ns / 1ps

module full_adder#(parameter DATA_WIDTH = 8)(A,B,ans);
    input [DATA_WIDTH-1:0]A;
    input [DATA_WIDTH-1:0]B;
    output reg [DATA_WIDTH-1:0]ans;
    
    initial
    begin
        ans=0;
    end
    
    always@(A or B)
    begin
        ans<=A+B;
    end
endmodule
