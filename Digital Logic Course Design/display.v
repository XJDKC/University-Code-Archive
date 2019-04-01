`timescale 1ns / 1ps

module display#(parameter D1 = 10000,parameter D2 = 100_000_000)(clk,floor,left,warning,direct,door,working,button,AN,SEG,LED);
    input clk,warning,working,door;
    input [3:0]floor;
    input [3:0]left;;
    input [2:0]direct;
    input [15:0]button;
    output reg [7:0]AN;
    output reg [7:0]SEG;
    output [15:0]LED;
    
    wire clk_M,clk_N;
    
    divider #(D2)d2(clk,clk_M);  //1s
    divider #(D1)d1(clk,clk_N);  //1ms
    
    reg [2:0]count1;
    reg count2;
    reg [3:0]temp;
    
    assign LED = button;
    
    initial
    begin
        temp = 0;
        count1 = 0;
        count2 = 0;
    end
    
    always@(posedge clk_M)
    begin
        count2 = ~count2;
    end
    
    always@(posedge clk_N)
    begin
        count1 <= count1 + 1;
    end
    
    always@(posedge clk)
    begin
        case(count1)
            0:AN <= 8'B01111111;
            1:AN <= 8'B10111111;
            2:AN <= 8'B11011111;
            3:AN <= 8'B11101111;     
            4:AN <= 8'B11110111;
            5:AN <= 8'B11111011;
            6:AN <= 8'B11111101; 
            7:AN <= 8'B11111110;     
        endcase
    end
    
    //floor left warning direct door working 
    always@(posedge clk)
    begin
        if (!working)
            SEG <= 8'B11111111;
        else if (warning)
            SEG <= count2 ? 8'B10000000 : 8'B11111111;
        else
        begin
            case (count1)
                0:temp <= floor/10;
                1:temp <= floor%10;
                2:temp <= 4'B1010;
                3:temp <= left/10;
                4:temp <= left%10;
                5:temp <= 4'B1010;
                6:if (direct[1])
                  begin
                    if (direct[2])
                        temp <= count2 ? 4'B1011:4'B1100;
                    else 
                        temp <= 4'B1100;
                  end
                  else if (direct[0])
                  begin
                    if (direct[2])
                        temp <= count2 ? 4'B1101:4'B1110;
                    else 
                        temp <= 4'B1110;
                  end
                  else
                  begin
                    temp <= 4'B1010;
                  end
                7:temp <= door ? 4'B1111 :4'B0000; 
                default:;
            endcase
            SEG <= pattern(temp);
        end
    end
    
    function [7:0]pattern(input [3:0]no);
    begin
        case (no[3:0])
            4'b0000: pattern = 8'b11000000;
            4'b0001: pattern = 8'b11111001;
            4'b0010: pattern = 8'b10100100;
            4'b0011: pattern = 8'b10110000;
            4'b0100: pattern = 8'b10011001;
            4'b0101: pattern = 8'b10010010;
            4'b0110: pattern = 8'b10000010;
            4'b0111: pattern = 8'b11111000;
            4'b1000: pattern = 8'b10000000;
            4'b1001: pattern = 8'b10011000;
            4'b1010: pattern = 8'b10111111;    //-
            4'b1011: pattern = 8'b11011100;    //上1
            4'b1100: pattern = 8'b10101011;    //上2
            4'b1101: pattern = 8'b10011101;    //下1
            4'b1110: pattern = 8'b11100011;    //下2
            4'b1111: pattern = 8'b11001001;    //开门
            default:;
        endcase
    end
    endfunction
    
endmodule
