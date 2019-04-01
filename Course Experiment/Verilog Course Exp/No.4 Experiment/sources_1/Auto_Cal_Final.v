`timescale 1ns / 1ps

module Auto_Cal_Final(clk,start,rst,done,SEG,AN);
    parameter DATA_WIDTH = 32;
    input clk;
    input start;
    input rst;
    output done;
    output [7:0]SEG;
    output reg [7:0]AN;
    
    reg [3:0]seg;
    reg count;
    
    wire clk_N;
    wire clk_P;
    wire [DATA_WIDTH-1:0]sum_out;
    
    
    divider d(clk,clk_N);
    divider #(1000000)dd(clk,clk_P);
    Auto_Cal #(DATA_WIDTH)AC(start,rst,clk_N,done,sum_out);
    pattern(seg,SEG);
    
    initial
    begin
        seg=0;
        count=0;
    end
    
    always@(posedge clk_P)
    begin
        if (count%2==0)
        begin
            AN<=8'b11111110;
            seg<=sum_out%10;
            count<=count+1;
        end
        else
        begin
            AN<=8'b11111101;
            seg<=sum_out/10;
            count<=count+1;
        end
    end

endmodule
