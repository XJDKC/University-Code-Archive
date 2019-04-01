`timescale 1ns / 1ps

module FSM_tb();
    reg clk,rst,LevelTrans,OpenDoor,CloseDoor;    //时钟信号，重置信号，平层传感器信号，开门信号，关门信号
    reg [2:0]OutUp;                               //外梯上升信号
    reg [3:1]OutDown;                             //外梯下降信号
    reg [3:0]InNum;                               //内梯楼层信号
    
    wire [1:0]change_floor;                       //楼层变化信号
    wire [3:0]floor;                              //当前楼层 
    wire [3:0]seconds; 
    wire [3:0]left;                               //剩余倒计时
    wire [2:0]direct;                             //电梯运行方向
    wire [15:0]button;                            //按键灯光
    wire start_cd,warning,door,working;           //开始倒计时、报警信号、门状态、工作状态

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

    //状态机
    controler FSM(clk,rst,LevelTrans,OutUp,OutDown,InNum,OpenDoor,CloseDoor
                     ,change_floor,start_cd,seconds,direct,door,warning,working,button
                     ,floor,left);
    
    register FLOOR(clk,change_floor,floor);
    timer #(10,100_00)COUNTDOWN(clk,start_cd,seconds,left);
endmodule
