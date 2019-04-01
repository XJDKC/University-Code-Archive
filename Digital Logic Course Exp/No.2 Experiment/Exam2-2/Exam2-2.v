`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/05 22:04:45
// Design Name: 
// Module Name: exam2-2
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


module exam2_2(
    input clk,
    input X,
    output Y
    );
    
    wire w1,w2,w3,w4,w5;

    T_trigger T1(1'b1,clk,w1,w2);
    assign w3=X^w1;
    T_trigger T2(w3,clk,w4,w5);
    assign Y=~(X&w5);
    
endmodule
