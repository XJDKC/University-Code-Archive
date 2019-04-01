`timescale 1ns / 1ps

module exam2_3(X,Q1,Q2,Q3,Q4,Z);
    input X;
    output Q1;
    output Q2;
    output Q3;
    output Q4;   
    output Z;
    
    wire _Q1,_Q2,_Q3,_Q4,temp;
    
    and and1(temp,Q2,Q3); 
    JK_trigger C1(X,1,1,Q1,_Q1);
    JK_trigger C2(Q1,_Q4,1,Q2,_Q2);
    JK_trigger C3(Q2,1,1,Q3,_Q3);
    JK_trigger C4(Q1,temp,1,Q4,_Q4);
    assign Z=Q4&Q1&X;
endmodule
