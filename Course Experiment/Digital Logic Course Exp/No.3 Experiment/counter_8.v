`timescale 1ns / 1ps

module counter_8(CP,_CLR,M,Qa,Qb,Qc,Qd,_Qcc);
    input CP,_CLR,M;
    output Qa,Qb,Qc,Qd;
    output reg _Qcc;
    
    wire _qcc;
    reg a,b,c,d;
    reg _clr,_LD;
    
    initial
    begin
        {a,b,c,d}=2;
        _clr=1;;
        _LD=1;
        _Qcc=1;
    end
    
    counter #(2)c_16(CP,_clr,M,_LD,a,b,c,d,Qa,Qb,Qc,Qd,_qcc);
    
    //0010 1001
    always@(*)
    begin
        if (_CLR==0)
            {d,c,b,a}=4'b0010;
        else if (M && Qa && !Qb && !Qc && Qd)
            {d,c,b,a}=4'b0010;
        else if (!M && !Qa && Qb && !Qc && !Qd)
            {d,c,b,a}=4'b1001;
    end
    
    always@(posedge CP)
    begin
        if (CP && M && Qa && !Qb && !Qc && Qd)
            _LD=0;
        else if (CP && !M && !Qa && Qb && !Qc && !Qd)
            _LD=0;
        else
            _LD=1;
        if (!_CLR)
            _LD=0; 
    end
    
    always@(posedge CP)
    begin
        if (M && Qa && !Qb && !Qc && Qd)
            _Qcc=0;
        else if (!M && !Qa && Qb && !Qc && !Qd)
            _Qcc=0;
        else
            _Qcc=1;
    end
endmodule
