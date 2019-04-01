`timescale 1ns / 1ps

module Auto_Cal#(parameter DATA_WIDTH = 8)(start,rst,clk,done,sum_out);
    input start;
    input rst;
    input clk;
    output wire done;
    output wire [DATA_WIDTH-1:0]sum_out;
    
    wire NEXT_ZERO,LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL;
    
    FSM control(clk,rst,start,NEXT_ZERO,LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL,done);
    data_path #(DATA_WIDTH)dp(clk,rst,SUM_SEL,NEXT_SEL,A_SEL,LD_SUM,LD_NEXT,NEXT_ZERO,sum_out);
    
endmodule
