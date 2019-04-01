`timescale 1ns / 1ps

module exam2_3_tb();
    parameter clk_period = 10;

    reg X;
    wire Z;
    wire Q1,Q2,Q3,Q4;
    
    initial begin
    X=0;
    end
    
    always //产生虚拟时钟信号
    begin  
    #10 X=~X; //#10 表示延时10个单位时间，单位时间在.v文件顶部可以查看，为1ns，说明延时10ns
    end
    
    exam2_3 dut(.X(X),.Z(Z),.Q1(Q1),.Q2(Q2),.Q3(Q3),.Q4(Q4));

endmodule
