`timescale 1ns / 1ps

module JK_trigger(clk,J,K,Q,QF);
    input clk;
    input J;
    input K;
    output Q;
    output QF;
    
    reg temp;
    
    initial
    begin
        temp=0;
    end
    
    assign QF=~Q;
    
    always @(negedge clk)
    begin
        temp=(J&~temp)|(~K&temp);
    end
    assign Q=temp;
endmodule
