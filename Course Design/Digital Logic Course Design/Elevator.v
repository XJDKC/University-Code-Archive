`timescale 1ns / 1ps

module Elevator#(parameter D1 = 100000,parameter D2 = 100_000_000)(clk,rst,LevelTrans,OutUp,OutDown,InNum,OpenDoor,CloseDoor,AN,SEG,LED);
    input clk,rst,LevelTrans,OpenDoor,CloseDoor;    //时钟信号，重置信号，平层传感器信号，开门信号，关门信号
    input [2:0]OutUp;                               //外梯上升信号
    input [3:1]OutDown;                             //外梯下降信号
    input [3:0]InNum;                               //内梯楼层信号
    output [7:0]AN;                                 //显示控制信号
    output [7:0]SEG;                                //显示图案输出信号
    output [15:0]LED;                               //显示LED信号
    
    wire [1:0]change_floor;             //楼层变化信号
    wire [3:0]floor;                    //当前楼层 
    wire [3:0]seconds; 
    wire [3:0]left;                     //剩余倒计时
    wire [2:0]direct;                   //电梯运行方向
    wire [15:0]button;                  //按键灯光
    wire start_cd,warning,door,working; //开始倒计时、报警信号、门状态、工作状态
    
    //状态机
    controler FSM(clk,rst,LevelTrans,OutUp,OutDown,InNum,OpenDoor,CloseDoor
                     ,change_floor,start_cd,seconds,direct,door,warning,working,button
                     ,floor,left);
    
    //楼层寄存器 倒计时
    register FLOOR(clk,change_floor,floor);
    timer #(D2)COUNTDOWN(clk,start_cd,seconds,left);
    
    //显示器
    display #(D1,D2)PRINT(clk,floor,left,warning,direct,door,working,button,AN,SEG,LED);
    
endmodule
