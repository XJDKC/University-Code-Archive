`timescale 1ns / 1ps

module exam2_3_tb();
    parameter clk_period = 10;

    reg X;
    wire Z;
    wire Q1,Q2,Q3,Q4;
    
    initial begin
    X=0;
    end
    
    always //��������ʱ���ź�
    begin  
    #10 X=~X; //#10 ��ʾ��ʱ10����λʱ�䣬��λʱ����.v�ļ��������Բ鿴��Ϊ1ns��˵����ʱ10ns
    end
    
    exam2_3 dut(.X(X),.Z(Z),.Q1(Q1),.Q2(Q2),.Q3(Q3),.Q4(Q4));

endmodule
