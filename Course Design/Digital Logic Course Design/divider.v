`timescale 1ns / 1ps

module divider#(parameter N = 100_000_000)(clk,clk_N);
    input clk;
    output clk_N;
    
    reg [31:0] counter;
    reg temp;
    
    initial
    begin
        counter = 0;
        temp = 0;
    end
    
    always@(posedge clk)
    begin
        if (counter == N/2-1)
            begin
                temp <= !temp;
                counter <= 0;
            end
        else 
            begin
                counter <= counter + 1;
            end
    end
    
    assign clk_N = temp;

endmodule
