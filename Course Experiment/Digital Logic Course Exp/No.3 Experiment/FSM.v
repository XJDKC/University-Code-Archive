`timescale 1ns / 1ps

module FSM(clk,in,out,State);
    input clk;
    input in;
    output reg out;
    output reg [2:0]State;

    initial
    begin
        State<=0;
    end
    
    always@(posedge clk)//10110
    begin
        case(State)
            0:  if (in) State<=1;
                else    State<=0;
            1:  if (in) State<=1;
                else    State<=2;
            2:  if (in) State<=3;
                else    State<=0;
            3:  if (in) State<=4;
                else    State<=2;  
            4:  if (in) State<=1;   
                else    State<=5;  
            5:  if (in) State<=1;
                else    State<=0;
            default:State<=State;
        endcase
    end
    
    always@(*)
    begin
        if (State==5)
            out<=1;
        else
            out<=0;
    end
    
endmodule
