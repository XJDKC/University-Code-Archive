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
    
    always //��������ʱ���ź�
    begin  
        #10 clk=~clk; //#5 ��ʾ��ʱ5����λʱ�䣬��λʱ����.v�ļ��������Բ鿴��Ϊ1ns��˵����ʱ5ns
    end

    always //��������ʱ���ź�
    begin  
        #100  X=~X;
    end
    
    exam2_2 dut(.clk(clk),.X(X),.Y(Y));
endmodule
