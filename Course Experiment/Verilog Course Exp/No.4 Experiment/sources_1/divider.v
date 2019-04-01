`timescale 1ns / 1ps

module divider#(parameter N = 100_000_000)(clk, clk_N);
input clk;                      // 系统时钟
output clk_N;                   // 分频后的时钟

reg [31:0] counter;             /* 计数器变量，通过计数实现分频。
                                   当计数器从0计数到(N/2-1)时，
                                   输出时钟翻转，计数器清零 */
reg clk_N;
          
always @(posedge clk)  begin    // 时钟上升沿
    if (counter == N/2-1)
        begin
            clk_N<=!clk_N;
            counter<=0;
        end
    else 
        begin 
            counter<=counter+1;
        end
end                      
endmodule
