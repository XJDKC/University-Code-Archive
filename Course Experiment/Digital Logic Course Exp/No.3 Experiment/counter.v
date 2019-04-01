`timescale 1ns / 1ps

module counter#(parameter init = 0)(CP,_CLR,M,_LD,A,B,C,D,Qa,Qb,Qc,Qd,_Qcc);
    input CP,_CLR,M,_LD;
    input A,B,C,D;
    output Qa,Qb,Qc,Qd;
    output reg _Qcc;
    
    reg [3:0]temp;
    
    assign {Qd,Qc,Qb,Qa}=temp;
    
    initial
    begin
        temp=init;
        _Qcc=1;
    end
    
    always@(posedge CP or negedge _CLR or negedge _LD)
    begin
        if (_CLR==0)
        begin
            temp<=0;
            _Qcc<=1;
        end
        else if (_LD==0)
        begin
            temp<={D,C,B,A};
            _Qcc<=1;
        end
        else if (CP)
        begin
            if (temp==15&&M||temp==0&&!M)
                _Qcc<=0;
            else 
                _Qcc<=1;
            if (M)
                temp<=temp+1;
            else
                temp<=temp-1;
        end
    end
endmodule
