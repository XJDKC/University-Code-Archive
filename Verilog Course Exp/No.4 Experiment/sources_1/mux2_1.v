`timescale 1ns / 1ps

module mux2_1#(parameter DATA_WIDTH = 8)(a,b,sel,out);
    input [DATA_WIDTH-1:0]a;
    input [DATA_WIDTH-1:0]b;
    input sel;
    output reg [DATA_WIDTH-1:0]out;
    
    initial
    begin
        out=0;
    end
    
    always@(sel or a or b)
    begin
        if (sel == 1) begin
            out<=a;
            end
        else begin
            out<=b;
            end
    end
    
endmodule
