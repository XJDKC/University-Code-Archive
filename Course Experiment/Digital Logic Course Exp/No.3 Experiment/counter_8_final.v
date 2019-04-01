`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/13 10:02:00
// Design Name: 
// Module Name: counter_8_final
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


module counter_8_final(CP,_CLR,M,Qa,Qb,Qc,Qd,_Qcc);
    input CP,_CLR,M;
    output Qa,Qb,Qc,Qd;
    output _Qcc;
    
    wire CP_N;
    
    divider d(CP,CP_N);
    counter_8 c(CP_N,_CLR,M,Qa,Qb,Qc,Qd,_Qcc);
    
endmodule
