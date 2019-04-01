`timescale 1ns / 1ps

module register#(parameter DATA_WIDTH = 4)(clk,signal,floor);
    input clk;
    input [1:0]signal;
    output [DATA_WIDTH-1:0] floor;
    
    reg [1:0]pre;
    reg [DATA_WIDTH-1:0]temp;
    
    initial
    begin
        temp = 1;
        pre = 0;
    end
    
    always@(posedge clk)
    begin
        pre <= signal;
    end
    
    always@(posedge clk)
    begin
        if ((!pre[1])&&signal[1])
            temp <= temp + 1;
        else if ((!pre[0])&&signal[0])
            temp <= temp - 1;
        else if ((!pre[1])&&signal[1]&&(!pre[0])&&signal[0])
            temp <= temp;
    end
    
    assign floor = temp;
    
endmodule
