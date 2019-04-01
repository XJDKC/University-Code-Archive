`timescale 1ns / 1ps

module Elevator#(parameter D1 = 100000,parameter D2 = 100_000_000)(clk,rst,LevelTrans,OutUp,OutDown,InNum,OpenDoor,CloseDoor,AN,SEG,LED);
    input clk,rst,LevelTrans,OpenDoor,CloseDoor;    //ʱ���źţ������źţ�ƽ�㴫�����źţ������źţ������ź�
    input [2:0]OutUp;                               //���������ź�
    input [3:1]OutDown;                             //�����½��ź�
    input [3:0]InNum;                               //����¥���ź�
    output [7:0]AN;                                 //��ʾ�����ź�
    output [7:0]SEG;                                //��ʾͼ������ź�
    output [15:0]LED;                               //��ʾLED�ź�
    
    wire [1:0]change_floor;             //¥��仯�ź�
    wire [3:0]floor;                    //��ǰ¥�� 
    wire [3:0]seconds; 
    wire [3:0]left;                     //ʣ�൹��ʱ
    wire [2:0]direct;                   //�������з���
    wire [15:0]button;                  //�����ƹ�
    wire start_cd,warning,door,working; //��ʼ����ʱ�������źš���״̬������״̬
    
    //״̬��
    controler FSM(clk,rst,LevelTrans,OutUp,OutDown,InNum,OpenDoor,CloseDoor
                     ,change_floor,start_cd,seconds,direct,door,warning,working,button
                     ,floor,left);
    
    //¥��Ĵ��� ����ʱ
    register FLOOR(clk,change_floor,floor);
    timer #(D2)COUNTDOWN(clk,start_cd,seconds,left);
    
    //��ʾ��
    display #(D1,D2)PRINT(clk,floor,left,warning,direct,door,working,button,AN,SEG,LED);
    
endmodule
