`timescale 1ns / 1ps

module exam2_5_tb();
    reg sig_nsyn;
    reg clk;
    wire q1;
    wire q2;
    wire sig_syn;
    
    initial 
    begin
        sig_nsyn=0;
        clk=0;
    end
    
    always
    begin
        #10 clk=~clk;
    end
    
    always
    begin
        #10 sig_nsyn=$random%2;
    end
    
    exam2_5 dut(sig_nsyn,clk,q1,q2,sig_syn);
endmodule
