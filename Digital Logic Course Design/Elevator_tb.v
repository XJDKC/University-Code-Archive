`timescale 1ns / 1ps

module Elevator_tb();
    reg clk,rst,LevelTrans,OpenDoor,CloseDoor;    //时钟信号，重置信号，平层传感器信号，开门信号，关门信号
    reg [2:0]OutUp;                               //外梯上升信号
    reg [3:1]OutDown;                             //外梯下降信号
    reg [3:0]InNum;                               //内梯楼层信号
    wire [7:0]AN;                                 //显示控制信号
    wire [7:0]SEG;                                //显示图案输出信号
    wire [15:0]LED;                               //显示LED信号

    initial
    begin
        {clk,rst,LevelTrans,OutUp,OutDown,InNum,OpenDoor,CloseDoor} = 0;
        #5 rst = 1;
        LevelTrans = 1;
    end

    always
    begin
        #1 clk = ~clk;
    end

    initial
    begin
        #10 OutUp[0] = 1;
        #5 OutUp[0] = 0;
    end
    
    initial
    begin
        #100 InNum[3] = 1;
        #10 InNum[3] = 0;
        #20 OutDown[1] = 1;
        #10 OutDown[1] = 0;
        #20 OutDown[2] = 1;
        #20 OutDown[2] = 0;
    end
    
    initial
    begin
        #1700 OpenDoor = 1;
        #5  OpenDoor = 0;
        #60 CloseDoor = 1;
        #5  CloseDoor = 0;
    end
    
    initial
    begin
        #2800  LevelTrans = 0;
        #200   LevelTrans = 1;
    end
    
    initial
    begin
        #3300 rst = 0;
    end
    
    Elevator #(2,10)tb(clk,rst,LevelTrans,OutUp,OutDown,InNum,OpenDoor,CloseDoor,AN,SEG,LED);
    
endmodule
