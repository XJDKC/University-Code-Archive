`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/16 21:02:03
// Design Name: 
// Module Name: T_trigger_tb
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


module T_trigger_tb();
    reg CP;
    reg T;
    wire Q;
    wire QB;
    
    initial
    begin
        CP<=0;
        T<=1;
    end
    T_trigger tb(T,CP,Q,QB);
endmodule
