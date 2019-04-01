`timescale 1ns / 1ps

module controler(clk,rst,LevelTrans,OutUp,OutDown,InNum,OpenDoor,CloseDoor,change_floor,start_cd,seconds,direct,door,warning,working,button,floor,left);
	input clk,rst,LevelTrans,OpenDoor,CloseDoor;
	input [2:0]OutUp;
	input [3:1]OutDown;
	input [3:0]InNum;
	input [3:0]floor;
	input [3:0]left;
	output reg [3:0]seconds;
	output reg [1:0]change_floor;
	output reg [2:0]direct;
	output reg start_cd,door,warning,working;
	output [15:0]button;

	localparam RST_STATE = 0,IDLE_STATE = 1,UNI_STATE = 2,ARRIVE_STATE = 3,OPEN_STATE = 4,CLOSE_STATE = 5,WARN_STATE = 6;
	reg [3:0]map[3:0];
	reg [2:0]CurState,NextState;

	reg [2:0]Up;
	reg [3:1]Down;
	reg [3:0]Num;

	reg [1:0]temp;
	reg flag;


	assign button[15:0] = {Up[0],Up[1],Down[1],Up[2],Down[2],Down[3],1'B0,Num[0],Num[1],Num[2],Num[3],OpenDoor,CloseDoor,1'B0,LevelTrans,rst};


	initial
	begin
		CurState = 0;
		NextState = 0;
		{Up,Down,Num} = 0;
		{change_floor,start_cd,seconds,direct,door,warning,working} = 0;
		flag = 0;
		temp = 0;
		map[0] = 1;
		map[1] = 3;
		map[2] = 6;
		map[3] = 8;
	end

	always@(posedge clk)
	begin
		if (!rst)
		begin
			if (CurState == CLOSE_STATE || CurState == IDLE_STATE)
			begin
				Up <= 0; Down <= 0; Num = 1;
			end
		end
		else
		begin
			if (Up != OutUp) Up <= Up | OutUp;
			if (Down != OutDown) Down <= Down | OutDown;
			if (Num != InNum) Num <= Num | InNum;
		end
		case(CurState)
			RST_STATE:	begin
							if (rst)
								NextState <= IDLE_STATE;
							else
							begin
								NextState <= RST_STATE;
								{change_floor,start_cd,seconds,direct,door,warning,working} <= 13'B00_0_0000_000_0_0_0;
								Up <= 0;
								Down <= 0;
								Num <= 0;
							end
						end
			IDLE_STATE: begin
							if (floor == map[0] && !rst)
								NextState <= RST_STATE;
							else if (Up!=0||Down!=0||Num!=0)		//如果有楼层信�?
							begin
								if (MAP(hasSignal(Up,Down,Num)) == floor)	 //如果是该层的信号 则状态变为开门状�?
								begin
									NextState <= OPEN_STATE;
									{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_0001_0_0_1;
								end
								else if (MAP(hasSignal(Up,Down,Num)) > floor)  //如果是上面楼层的信号
								begin
									direct <= 3'B010;							//方向向上 不闪�?
									NextState <= UNI_STATE;
									{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_1010_0_0_1;
								end
								else														//否则是下面楼层的信号
								begin
									direct <= 3'B001;							//否则方向向下 不闪�?
									NextState <= UNI_STATE;
									{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_1010_0_0_1;
								end
							end
							else if (OpenDoor)									//如果有开门信�? 则转为开门状�?
							begin
								NextState <= OPEN_STATE;
								{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_0001_0_0_1;
							end
							else
							begin
								NextState <= IDLE_STATE;					//如果没有信号 则状态保持不�?
								{change_floor,start_cd,seconds,direct,door,warning,working} <= 13'B00_0_0000_000_0_0_1;
							end
						end
			UNI_STATE:	begin
							if (left == 0)											//如果计时器�?�计时为0
							begin
								if (ShouldStop(Up,Down,Num,floor,direct)	//如果电梯前进方向有信号或者反向有�?远端信号
									||ForwardSignal(Up,Down,Num,floor,direct)==0&&direct[1]
										&&floor+1 == FarReverse(Up,Down,Num,floor,direct)
									||ForwardSignal(Up,Down,Num,floor,direct)==0&&direct[0]
										&&floor-1 == FarReverse(Up,Down,Num,floor,direct))
								begin
									change_floor <= direct[1:0];			//首先改变电梯楼层
									if (!LevelTrans)								//如果未平�?
										NextState <= WARN_STATE;		//则转为报警状�?
									else
										NextState <= ARRIVE_STATE;	//否则转为到达状�??
								end
								else														//如果不需停靠
								begin
									change_floor <= direct[1:0];			//则改变电梯楼�?
									NextState <= UNI_STATE;
									{start_cd,seconds,door,warning,working} <= 8'B1_1010_0_0_1;		//�?始计�?
								end
							end
							else if (CurState == NextState)
							begin
								direct[2] <= 1'B1;								//闪烁
								NextState <= UNI_STATE;					//继续倒计�?
								{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_0_1010_0_0_1;
							end
						end
			ARRIVE_STATE:begin
							if (floor == map[0])
							begin
								Up[0] <= 0;
								Num[0] <= 0;
							end
							else if (floor == map[1])
							begin
								Num[1] <= 0;
								if (direct[1]) Up[1] <= 0;
								else if (direct[0]) Down[1] <= 0;
							end
							else if (floor == map[2])
							begin
								Num[2] <= 0;
								if (direct[2]) Up[2] <= 0;
								else if (direct[0]) Down[2] <= 0;
							end
							else if (floor == map[3])
							begin
								Down[3] <= 0;
								Num[3] <= 0;
							end
							direct[2] <= 1'B0;
							NextState <= OPEN_STATE;
							{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_0001_0_0_1;
						end
			OPEN_STATE: begin
							if (CloseDoor)
							begin
								NextState <= CLOSE_STATE;
								{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_0001_0_0_1;
							end
							else if (door&&(OpenDoor
										|| floor == map[0] && (Num[0]|(!direct[0]&Up[0]))
										|| floor == map[1] && (Num[1]|(!direct[0]&Up[1])|(!direct[1]&Down[1]))
										|| floor == map[2] && (Num[2]|(!direct[0]&Up[2])|(!direct[1]&Down[2]))
										|| floor == map[3] && (Num[3]|(!direct[1]&Down[3]))))
										//�?门期间按了开门并且门已经�?�?
							begin
								case (floor)
									map[0]: begin	Num[0] <= InNum[0];
													if (!direct[0]) Up[0] <= OutUp[0];
											end
									map[1]: begin	Num[1] <= InNum[1];
													if (!direct[0]) Up[1] <= OutUp[1];
													if (!direct[1]) Down[1] <= OutDown[1];
											end
									map[2]: begin	Num[2] <= InNum[2];
													if (!direct[0]) Up[2] <= OutUp[2];
													if (!direct[1]) Down[2] <= OutDown[2];
											end
									map[3]: begin	Num[3] <= InNum[3];
													if (!direct[1]) Down[3] <= OutDown[3];
											end
									default:;
								endcase
								NextState <= OPEN_STATE;			//重新进行关门倒计�?
								{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_0101_1_0_1;
							end
							else if (left == 0 && !door)				//如果计时到了0 但是门状态是关闭状�??
							begin
								NextState <= OPEN_STATE;			//门状态为�?并且�?始关门�?�计�?
								{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_0101_1_0_1;
							end
							else if (left == 0 && door)				//如果倒计时为0 门的状�?�是打开状�??
							begin
								NextState <= CLOSE_STATE;			//进入关门状�?? 并进行关门计�?
								{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_0001_0_0_1;
							end
							else if (CurState == NextState)			//否则计时继续 状�?�不�?
							begin
								NextState <= OPEN_STATE;
								{change_floor,start_cd,warning,working} <= 5'B00_0_0_1;
							end
						end
			CLOSE_STATE:begin
							if (OpenDoor)										//如果在关门期间按了开门键 那么立刻进入�?门状�?
							begin
								NextState <= OPEN_STATE;			//�?始开门计�?
								{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_0001_0_0_1;
							end
							else if (left == 0)								//如果倒计时为0
							begin
								if (floor == map[0] && !rst)
									NextState <= RST_STATE;
								else if (!(Up!=0||Down!=0||Num!=0)) //如果无其他信�?
									NextState <= IDLE_STATE;			//进入闲置状�??
								else													//否则继续运行 并判断运行方�?
								begin
									if (!rst)
									begin
										if (floor == map[0])
										begin
											NextState <= RST_STATE;
										end
									end
									else if (!ForwardSignal(Up,Down,Num,floor,direct))	//如果运行方向没有信号
									begin
										if (direct[1])							//判断反向有没有信�?
										begin
											if (floor == map[1]) Down[1] <= 0;
											else if (floor == map[2]) Down[2] <= 0;
											else if (floor == map[3]) Down[3] <= 0;
											direct <= 3'B001;				//变为下行
										end
										else if (direct[0])
										begin
											if (floor == map[0]) Up[0] <= 0;
											else if (floor == map[1]) Up[1] <= 0;
											else if (floor == map[2]) Up[2] <= 0;
											direct <= 3'B010;				//变为上行
										end
									end
									else 
									   direct <= direct;							//方向不变
									if (direct)
									begin
									   NextState <= UNI_STATE;
									   {change_floor,start_cd,seconds,door,warning,working} <= 10'B00_1_1010_0_0_1;
                                    end
                                    else 
                                        NextState <= IDLE_STATE;
								end
							end
							else if (CurState == NextState)
							begin
								NextState <= CLOSE_STATE;
								{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_0_0001_0_0_1;
							end
						end
			WARN_STATE: begin
							if (LevelTrans)
								NextState <= ARRIVE_STATE;
							else
							begin
								NextState <= WARN_STATE;
								{change_floor,start_cd,seconds,door,warning,working} <= 10'B00_0_0000_0_1_1;
							end
						end
			default:;
		endcase
	end

	always@(posedge clk)
	begin
		CurState <= NextState;
	end

	function [3:0]MAP;
		input [1:0]no;

		case (no)
			2'B00:MAP = 1;
			2'B01:MAP = 3;
			2'B10:MAP = 6;
			2'B11:MAP = 8;
		endcase

	endfunction

	//判断是否有信�? 如果有返回对应楼层下�?
	function [1:0]hasSignal(input [2:0]Up,input [3:1]Down,input [3:0]Num);

		if (Up[0]||Num[0]) hasSignal = 0;
		else if (Up[1]||Down[1]||Num[1]) hasSignal = 1;
		else if (Up[2]||Down[2]||Num[2]) hasSignal = 2;
		else if (Down[3]||Num[3]) hasSignal = 3;

	endfunction

	//判断前进方向是否有同向信�?
	function ForwardSignal(input [2:0]Up,input [3:1]Down,input [3:0]Num,input [3:0]floor,input [2:0]direct);
	begin
		if (direct[1])
		begin
			if (floor < FarReverse(Up,Down,Num,floor,direct)
			  ||floor<map[1]&&(Up[2:1]||Num[3:1])
			  ||floor<map[2]&&(Up[2]||Num[3:2])
			  ||floor<map[3]&&Num[3])
				ForwardSignal = 1;
			else
				ForwardSignal = 0;
		end
		else if (direct[0])
		begin
			 if (floor > FarReverse(Up,Down,Num,floor,direct)
			   ||floor>map[2]&&(Down[2:1]||Num[2:0])
			   ||floor>map[1]&&(Down[1]||Num[1:0])
			   ||floor>map[0]&&Num[0])
				 ForwardSignal = 1;
			 else
				ForwardSignal = 0;
		end
		else
			ForwardSignal = 0;
	end
	endfunction

	//判断下一层是否应该停
	function ShouldStop(input [2:0]Up,input [3:1]Down,input [3:0]Num,input [3:0]floor,input [2:0]direct);
	begin
		if (direct[1])
		begin
			if (floor == map[1]-1&&(Up[1]||Num[1])
			  ||floor == map[2]-1&&(Up[2]||Num[2])
			  ||floor == map[3]-1&&Num[3])
				ShouldStop = 1;
			else
				ShouldStop = 0;
		end
		else if (direct[0])
		begin
			if (floor == map[0]+1&&Num[0]
			  ||floor == map[1]+1&&(Down[1]||Num[1])
			  ||floor == map[2]+1&&(Down[2]||Num[2]))
				ShouldStop = 1;
			else
				ShouldStop = 0;
		end
		else
			ShouldStop = 0;
	end
	endfunction

	//获取�?远反向信号楼层号
	function [3:0]FarReverse(input [2:0]Up,input [3:1]Down,input [3:0]Num,input [3:0]floor,input [2:0]direct);
	begin
		if (direct[1])
		begin
			if (Down[3]) FarReverse = map[3];
			else if (Down[2]||(floor>map[2]&&Num[2])) FarReverse = map[2];
			else if (Down[1]||(floor>map[1]&&Num[1])) FarReverse = map[1];
			else if (floor>map[0]&&Num[0]) FarReverse = map[0];
			else FarReverse = 0;
		end
		else if (direct[0])
		begin
			if (Up[0]) FarReverse = map[0];
			else if (Up[1]||(floor<map[1]&&Num[1])) FarReverse = map[1];
			else if (Up[2]||(floor<map[2]&&Num[2])) FarReverse = map[2];
			else if (floor<map[3]&&Num[3]) FarReverse = map[3];
			else FarReverse = 0;
		end
	end
	endfunction

endmodule
