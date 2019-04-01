`timescale 1ns / 1ps

module data_path#(parameter DATA_WIDTH = 8)(clk,rst,SUM_SEL,NEXT_SEL,A_SEL,LD_SUM,LD_NEXT,NEXT_ZERO,ans);
    input clk;
    input rst;
    input SUM_SEL;
    input NEXT_SEL;
    input A_SEL;
    input LD_SUM;
    input LD_NEXT;
    output NEXT_ZERO;
    output ans;
    
    wire [DATA_WIDTH-1:0]ans;
    wire [DATA_WIDTH-1:0]data;
    wire [DATA_WIDTH-1:0]step_ans;
    wire [DATA_WIDTH-1:0]save_ans;
    wire [DATA_WIDTH-1:0]addr;
    wire [DATA_WIDTH-1:0]next_addr;
    wire [DATA_WIDTH-1:0]cur_data_addr;
    wire [DATA_WIDTH-1:0]sel_addr;
    
    full_adder  #(DATA_WIDTH)f1(ans,data,step_ans);
    mux2_1      #(DATA_WIDTH)m1(step_ans,0,SUM_SEL,save_ans);
    register    #(DATA_WIDTH)r1(save_ans,ans,clk,LD_SUM,rst);
    
    mux2_1      #(DATA_WIDTH)m2(data,0,NEXT_SEL,next_addr);
    register    #(DATA_WIDTH)r2(next_addr,addr,clk,LD_NEXT,rst);
    full_adder  #(DATA_WIDTH)f2(1,addr,cur_data_addr);
    mux2_1      #(DATA_WIDTH)m3(cur_data_addr,addr,A_SEL,sel_addr);
    
    memory      #(DATA_WIDTH)mem(sel_addr,data);
    compare     #(DATA_WIDTH)c(next_addr,0,,NEXT_ZERO,);
    
endmodule
