`timescale 1ns / 1ps

module exam2_2_tb(
    );
    parameter clk_period = 10;
    reg clk;
    reg X;
    wire Y;
    
    initial begin
        clk=0;
        X=0;
    end
    
    always //产生虚拟时钟信号
    begin  
        #10 clk=~clk; //#5 表示延时5个单位时间，单位时间在.v文件顶部可以查看，为1ns，说明延时5ns
    end

    always //产生虚拟时钟信号
    begin  
        #100  X=~X;
    end
    
    exam2_2 dut(.clk(clk),.X(X),.Y(Y));
endmodule
