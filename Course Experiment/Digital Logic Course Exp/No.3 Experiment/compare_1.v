`timescale 1ns / 1ps

module compare_1(A,B,G,E,L);
    input A;
    input B;
    output reg G;
    output reg E;
    output reg L;
    
    always@(*)
    begin
        if (A>B)
            {G,E,L}=3'B100;
        else if (A==B)
            {G,E,L}=3'B010;
        else
            {G,E,L}=3'B001;
    end
endmodule
