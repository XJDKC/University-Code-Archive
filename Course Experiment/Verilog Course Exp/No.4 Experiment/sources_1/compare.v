`timescale 1ns / 1ps

module compare#(parameter DATA_WIDTH = 8)(A,B,G,E,L);
    input [DATA_WIDTH-1:0]A;
    input [DATA_WIDTH-1:0]B;
    output reg G;
    output reg E;
    output reg L;
    
    initial 
    begin
        G=0;
        E=0;
        L=0;
    end
    
    always@(A or B)
    begin
        if ( A>B ) begin
            G=1;
            E=0;
            L=0;
        end
        else if (A == B) begin
            G=0;
            E=1;
            L=0;
            end
        else begin
            G=0;
            E=0;
            L=1;
            end
    end
endmodule
