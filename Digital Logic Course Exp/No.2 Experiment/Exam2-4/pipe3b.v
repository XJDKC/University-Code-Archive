`timescale 1ns / 1ps

module pipe3b(
    input sig_nsyn,
    input clk,
    output q1,
    output q2,
    output sig_syn
      );
    reg q1;
    reg q2;
    reg sig_syn;
   always@(posedge clk) q2=q1;
   always@(posedge clk) sig_syn=q2;
   always@(posedge clk) q1=sig_nsyn;     
endmodule


//module pipe3b(
//    input sig_nsyn,
//    input clk,
//    output q1,
//    output q2,
//    output sig_syn
//      );
//    reg q1;
//    reg q2;
//    reg sig_syn;
    
//    initial 
//    begin
//        q1=0;
//        q2=0;
//        sig_syn=0;
//    end
    
//   always@(posedge clk) q2<=q1;          //
//   always@(posedge clk) sig_syn<=q2;     //
//   always@(posedge clk) q1<=sig_nsyn;    // 
//endmodule
