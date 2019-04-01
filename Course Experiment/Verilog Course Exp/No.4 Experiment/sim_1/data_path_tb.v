`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2018/06/11 10:28:41
// Design Name: 
// Module Name: data_path_tb
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


module data_path_tb();
    parameter DATA_WIDTH = 32;
    reg clk,rst,SUM_SEL,NEXT_SEL,A_SEL,LD_SUM,LD_NEXT,done;
    wire NEXT_ZERO;
    wire [DATA_WIDTH-1:0]ans;
    
    integer i=0;
    
    initial
    begin
        i=0;
        clk=0;
        rst=0;
        done=0;
        SUM_SEL=0;
        NEXT_SEL=0;
        LD_SUM=0;
        LD_NEXT=0;
        A_SEL=0; 
    end
    
    always
    begin
        #10 clk=~clk;
    end

    always
    begin
        while (!i)
        begin
            #20 {LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL,done}=6'b101110;
            #20 {LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL,done}=6'b011100;   
            if (NEXT_ZERO == 1) i=i+1;
        end
        #20 {LD_SUM,LD_NEXT,SUM_SEL,NEXT_SEL,A_SEL,done}=6'b000001;
    end
    
    data_path #(DATA_WIDTH)tb(clk,rst,SUM_SEL,NEXT_SEL,A_SEL,LD_SUM,LD_NEXT,NEXT_ZERO,ans);
endmodule
