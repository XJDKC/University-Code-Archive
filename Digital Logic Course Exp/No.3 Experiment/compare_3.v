`timescale 1ns / 1ps

module compare_3(A,B,G,E,L);
    input [2:0]A;
    input [2:0]B;
    output G;
    output E;
    output L;
    
    wire G2,E2,L2,G1,E1,L1,G0,E0,L0;
    
    compare_1 c2(A[2],B[2],G2,E2,L2);
    compare_1 c1(A[1],B[1],G1,E1,L1);
    compare_1 c0(A[0],B[0],G0,E0,L0);
    
    assign G=G2|(E2&G1)|(E2&E1&G0);
    assign E=E2&E1&E0;
    assign L=L2|(E2&L1)|(E2&E1&L0);
    
endmodule