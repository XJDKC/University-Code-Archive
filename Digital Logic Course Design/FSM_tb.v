`timescale 1ns / 1ps

module FSM_tb();
    reg clk,rst,LevelTrans,OpenDoor,CloseDoor;    //ʱ���źţ������źţ�ƽ�㴫�����źţ������źţ������ź�
    reg [2:0]OutUp;                               //���������ź�
    reg [3:1]OutDown;                             //�����½��ź�
    reg [3:0]InNum;                               //����¥���ź�
    
    wire [1:0]change_floor;                       //¥��仯�ź�
    wire [3:0]floor;                              //��ǰ¥�� 
    wire [3:0]seconds; 
    wire [3:0]left;                               //ʣ�൹��ʱ
    wire [2:0]direct;                             //�������з���
    wire [15:0]button;                            //�����ƹ�
    wire start_cd,warning,door,working;           //��ʼ����ʱ�������źš���״̬������״̬

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

    //״̬��
    controler FSM(clk,rst,LevelTrans,OutUp,OutDown,InNum,OpenDoor,CloseDoor
                     ,change_floor,start_cd,seconds,direct,door,warning,working,button
                     ,floor,left);
    
    register FLOOR(clk,change_floor,floor);
    timer #(10,100_00)COUNTDOWN(clk,start_cd,seconds,left);
endmodule
