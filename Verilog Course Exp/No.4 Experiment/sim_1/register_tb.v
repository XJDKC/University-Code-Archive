`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/10 21:14:00
// Design Name: 
// Module Name: register_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module register_tb();
    parameter DATA_WIDTH = 3;
    reg [DATA_WIDTH-1:0]D;
    wire [DATA_WIDTH-1:0]Q;
    reg load;
    reg rst;
    
    integer i;
    
    initial
    begin
        D=0;
        load=0;
        rst=0;
        for (i=1;i<8;i=i+1)
            #20 D=i;
    end
    
    always
    begin
        #10 load=~load;
    end

    always
    begin
        #50 rst=1;
        #5  rst=0;
    end
    
    register #(DATA_WIDTH)tb(D,Q,load,rst);
endmodule
