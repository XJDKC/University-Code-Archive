`timescale 1ns / 1ps

module T_trigger(
    input wire T,
    input wire CP,
    output Q,
    output QB
    );
    
    reg State;
    initial
    begin
        State=0;
    end
    
    always @(negedge CP)
    begin
        State=T^State;
    end
    
    assign Q=State;
    assign QB=~State;
endmodule
