`timescale 1ns / 1ps

module counter_final(CP,_CLR,M,_LD,A,B,C,D,Qa,Qb,Qc,Qd,_Qcc);
    input CP,_CLR,M,_LD;
    input A,B,C,D;
    output Qa,Qb,Qc,Qd;
    output _Qcc;
    
    wire CP_N;
    
    divider d(CP,CP_N);
    counter c(CP_N,_CLR,M,_LD,A,B,C,D,Qa,Qb,Qc,Qd,_Qcc);
endmodule
