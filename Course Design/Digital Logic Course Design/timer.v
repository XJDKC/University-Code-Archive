`timescale 1ns / 1ps

module timer#(parameter COUNT = 100_000_000)(clk,start,seconds,left);
    input clk;
    input start;
    input [3:0]seconds;
    output [3:0]left;
    
    reg [31:0]count;
    reg [3:0]temp;
    
    initial
    begin
        temp = 0;
        count = 0;
    end 
    
    always@(negedge clk)
    begin
        if (start == 1)
            begin
                count <= COUNT;
                temp <= seconds;
            end
        else
            begin
                if (left == 0)
                    begin
                        count <= 0;
                    end
                else 
                    begin
                        if (count == 0)
                            begin
                                count <= COUNT - 1;
                                temp <= temp - 1;
                            end
                        else
                            begin
                                count <= count - 1;
                            end
                    end
            end
    end
    
    assign left = temp;
    
endmodule
