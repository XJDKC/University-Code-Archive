`timescale 1ns / 1ps

module register#(parameter DATA_WIDTH = 8)(D,Q,clk,load,rst);
    input [DATA_WIDTH-1:0] D;
    output [DATA_WIDTH-1:0] Q;
    input clk;
    input load;
    input rst;
    
    reg [DATA_WIDTH-1:0]temp;
    
    initial
    begin
        temp=0;
    end
 
    always@(posedge clk)
    begin
        if (rst == 1) begin
            temp<=0;
            end
        else begin
            if (load) begin
                temp<=D;
                end
            else begin
                temp<=temp;
                end
        end
    end
    
    assign Q=temp;
    
endmodule
