#include "isystem.h"

int main()
{
    Handle_In = GetStdHandle(STD_INPUT_HANDLE);				//获取输入句柄
    Handle_Out = GetStdHandle(STD_OUTPUT_HANDLE);			//获取输出句柄

	SetConsoleTitle(title);									//设置系统标题

	SetRightConsoleMode();									//设置正确的控制台模式
    SetConsoleScreenBufferSize(Handle_Out,Interface_Size);	//设置控制台缓冲区大小
    SetConsoleWindowInfo(Handle_Out,TRUE,&Win_Size);		//设置窗口大小

	LoadData();												//加载数据

    InitInterface();										//初始化主界面
    InitLayer();											//初始化图层界面

	//MessageBox(Handle_Out, "消息提示", "你好", MB_OKCANCEL | MB_ICONINFORMATION | MB_SYSTEMMODAL);

	RunSys(&head);											//运行系统
    CloseSys();												//关闭系统
    return 0;												
}

/****************************************
 * 函数名称：SetRightConsoleMode
 * 函数功能：设置正确的控制台模式
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 ****************************************/
void SetRightConsoleMode()
{
	DWORD mode;											//声明存放模式信息的DWORD（unsigned long 变量）
	GetConsoleMode(Handle_In, &mode);					//获取当前模式信息 存放到mode变量终
	mode &= ~(ENABLE_QUICK_EDIT_MODE);					//取消快速编辑模式
	mode |= ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;	//激活鼠标输入
	SetConsoleMode(Handle_In, mode);					//设置新的模式
}

/****************************************
 * 函数名称：LoadData
 * 函数功能：加载数据 包括三类数据（TYPE BASIC RECRUIT）
			和备份文件列表信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
void LoadData()
{
	int state = 0;										//加载数据状态信息 二进制位由低到高分别表示不同文件打开情况 1为正常
	BACK_INFO input_back_info,*cur_back_info;			//声明备份信息节点 用于读取存放信息
	BOOL error = TRUE;									//bool 类型错误信息

	printf("正在加载数据...\n");							
	
	FILE *back_list;
	if ((back_list = fopen(back_list_filename, "rb")) == NULL)	//如果打开备份文件列表信息不成功
	{
		back_list = fopen(back_list_filename, "wb");			//那么就创建新的备份文件列表 文件
		fwrite(&back_no, sizeof(unsigned long), 1, back_list);	//写入0 即无任何备份
		fclose(back_list);										//关闭备份文件列表 文件
	}
	else														//否则说明以及有备份文件了 创建过备份了
	{
		fread(&back_no, sizeof(unsigned long), 1, back_list);	//那么就读入备份文件个数
		for (int i = 0; i < back_no; i++)								//for循环依次读入各个备份文件信息
		{
			fread(&input_back_info, sizeof(BACK_INFO), 1, back_list);	//读入一条
			cur_back_info = (BACK_INFO *)calloc(1, sizeof(BACK_INFO));	//创建备份文件列表 链表
			*cur_back_info = input_back_info;
			cur_back_info->next = back_list_head;
			back_list_head = cur_back_info;
		}
		fclose(back_list);
	}
	printf("备份文件列表数据加载成功！\n");

	state = CreateList();					//调用CreateList 函数获取学校分类、基本、招生信息 并得到加载情况

	/*输出加载情况信息 如果错误只输出第一次出现错误的情况*/
	if (state&1 == 0)						//如果二进制位第一位为0 说明没有成功打开学校分类信息文件
	{
		error = FALSE;						//错误标记变量置为false 输出错误信息
		printf("学校类别数据加载失败\n");
	}
	else
	{
		printf("学校类别数据加载成功!\n");	//输出加载成功信息
	}
	if (error && (state&2)>>1 == 0)			//如果之前没有错误 并且二进制位第二位为0 说明没有成功打开学校基本信息文件
	{
		error = FALSE;						//错误标记变量置为false 输出错误信息
		printf("学校基本信息数据加载失败\n");
	}
	else if (error)							//否则 如果没有错误说明加载成果
	{
		printf("学校基本信息数据加载成功!\n");//输出加载成功信息
	}
	if (error && (state&4)>>2 == 0)			//如果之前没有错误 并且二进制位第三位为0 说明没有成功打开学校招生信息文件
	{
		error = FALSE;						//错误标记变量置为false 输出错误信息
		printf("学校招生信息数据加载失败!\n");
	}
	else if (error)							//否则 如果没有错误说明加载成果
	{
		printf("学校招生信息数据加载成功\n");
	}

	if (error == FALSE)						//如果出错 就暂停以下 向用户展示错误信息 否则直接进入系统
	{
		printf("按下任意键继续...");
		_getch();
	}
}

/**************************************************
 * 函数名称：CreateList
 * 函数功能：从文件中读入数据 创建数据链表 
			包括三类数据（TYPE BASIC RECRUIT）
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：int 型变量 
			0 表示学校分类信息文件加载出错或者数据链为空链
			1 表示学校基本信息文件加载出错
			3 表示学校招生信息文件加载出错

 * 调用说明：无
 **************************************************/
int CreateList()
{
	int state=0;											//返回值 加载状态信息
	FILE *input_info;										//文件指针 存放输入信息文件地址
	TYPE type_info, *cur_type, *pre_type = NULL;			//分类信息 分别为 存放输入信息变量 新节点地址 之前数据链主链链首
	BASIC basic_info, *cur_basic;							//基本信息 分别为 存放输入信息变量 新节点地址
	RECRUIT recruit_info, *cur_recruit;						//招生信息 分别为 存放输入信息变量 新节点地址

	if ((input_info = fopen(type_data_filename, "rb")) == NULL) //尝试打开 分类信息数据文件 返回值为空表示打开失败
	{
		return state;											//直接返回状态值
	}

	while (fread(&type_info, sizeof(TYPE), 1, input_info) == 1) //逐条读入分类信息
	{
		cur_type = (TYPE *)calloc(1, sizeof(TYPE));				//为新节点分配内存
		*cur_type = type_info;									//将读入的信息存放进新节点
		cur_type->nextB = NULL;									//更新指针域
		cur_type->next = pre_type;								
		pre_type = cur_type;									//更新链首
	}
	fclose(input_info);	
	if (pre_type == NULL)										//如果链为空
	{
		return state;
	}
	state |= 1;
	head = pre_type;											//更新全局变量 head - 数据链链首

	if ((input_info = fopen(basic_data_filename, "rb")) == NULL)//尝试打开 基本信息数据文件 返回值为空表示打开失败
	{
		return state;											//返回状态值
	}

	while (fread(&basic_info, sizeof(BASIC), 1, input_info) == 1)//逐条读入基本信息
	{
		cur_type = FindTypePoint(basic_info.classes);			//调用函数 寻找读入基本信息属于的分类节点地址 
		if (cur_type != NULL)									//如果找到了
		{
			cur_basic = (BASIC *)calloc(1, sizeof(BASIC));		//为新节点分配内存
			*cur_basic = basic_info;							//将读入的信息存放进新节点
			cur_basic->nextR = NULL;							//更新指针域
			cur_basic->next = cur_type->nextB;
			cur_type->nextB = cur_basic;						
		}
	}
	fclose(input_info);
	state |= 2;


	if ((input_info = fopen(recruit_data_filename, "rb")) == NULL)//尝试打开 招生信息数据文件 返回值为空表示打开失败
	{
		return state;
	}

	while (fread(&recruit_info, sizeof(RECRUIT), 1, input_info) == 1)//逐条读入招生信息
	{
		cur_basic = FindBasicPoint(recruit_info.classes,recruit_info.no);//调用函数 寻找读入招生信息属于的基本信息节点地址 
		if (cur_basic != NULL)										//如果找到了
		{
			cur_recruit = (RECRUIT *)calloc(1, sizeof(RECRUIT));	//调用函数 寻找读入基本信息属于的分类节点地址
			*cur_recruit = recruit_info;							//将读入的信息存放进新节点
			cur_recruit->next = cur_basic->nextR;					//更新指针域
			cur_basic->nextR = cur_recruit;
		}
	}
	fclose(input_info);
	state |= 4;

	return state;	//返回文件打开状态值
}

/**************************************************
 * 函数名称：InitInterface
 * 函数功能：初始化主界面
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void InitInterface()
{
    CONSOLE_SCREEN_BUFFER_INFO Info_Buffer;			//控制台屏幕缓冲区信息
    CONSOLE_CURSOR_INFO cur_state;					//控制台光标信息
    COORD pos={0,0};								//位置信息
    COORD size;										//缓冲区大小信息
    int i;

    SetConsoleTextAttribute(Handle_Out,Interface_Color);	//设置主界面颜色
    Clear_Buffer();											//清空缓冲区 （用空格）

    GetConsoleScreenBufferInfo(Handle_Out,&Info_Buffer);	//获取当前控制台屏幕缓冲区信息

    size.X=Info_Buffer.dwSize.X;							//得到缓冲区大小
    size.Y=1;
    SetConsoleCursorPosition(Handle_Out,pos);				//设置初始光标位置（主菜单输出位置）
    //先输出所有字符 这样等会获取菜单栏的字符信息时就不用一个一个赋值了 直接用ReadConsoleOutput读取
    for (i=0;i<mainmenu_num;i++)							//依次输出主菜单的字符串信息
    {
        printf("%s",I_Main_Menu[i]);
    }
	
    GetConsoleCursorInfo(Handle_Out,&cur_state);			//获取当前光标状态信息
    cur_state.bVisible=FALSE;								//将光标设置为不可见
    //cur_state.dwSize=100;
    SetConsoleCursorInfo(Handle_Out,&cur_state);			//设置新的光标状态

    Buff_Menubar_Info=(CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));		//为菜单栏缓冲区信息分配内存
    SMALL_RECT menu_bar={0,0,size.X-1,0};	//第0行从0到size.X-1这么长的矩形块
	
	//在pos位置处向右下方向读取menu_bar大小的矩形框的字符信息存放到Buff_Menubar_Info中
    ReadConsoleOutput(Handle_Out,Buff_Menubar_Info,size,pos,&menu_bar);
    
    for(i=0;i<size.X;i++)									//设置菜单栏的初始颜色信息
    {
       (Buff_Menubar_Info+i)->Attributes=BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE;
    }

    WriteConsoleOutput(Handle_Out,Buff_Menubar_Info,size,pos,&menu_bar);	//将设置好的颜色信息输出到屏幕
}

/**************************************************
 * 函数名称：Clear_Buffer
 * 函数功能：清空缓冲区 （用空格）
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void Clear_Buffer()
{
     CONSOLE_SCREEN_BUFFER_INFO Info_Buffer;	//控制台屏幕缓冲区信息 
     COORD pos={0,0};							//位置信息（控制台左上角）
     unsigned long lenth;						//缓冲区长度 
     GetConsoleScreenBufferInfo(Handle_Out,&Info_Buffer); //获取控制台屏幕缓冲区信息 
     lenth=Info_Buffer.dwSize.X*Info_Buffer.dwSize.Y;	  //计算缓冲区长度
     FillConsoleOutputAttribute(Handle_Out,Info_Buffer.wAttributes,lenth,pos,&ul);	//将整个缓冲区的颜色设置为当前颜色
     FillConsoleOutputCharacter(Handle_Out,' ',lenth,pos,&ul);	//将整个缓冲区填充为空格
}

/**************************************************
 * 函数名称：InitLayer
 * 函数功能：初始化图层信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void InitLayer()
{
    int i,j;
	COORD pos = { 0,0 };
    int PosA=0,PosB=strlen(I_Main_Menu[0])-1;
    scr_attr=(unsigned short *)calloc(Size_R*Size_C,sizeof(unsigned short));		//为屏幕属性指针分配内存
    top_layer_head = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));						//为图层信息分配内存（顶层）
    top_layer_head->no=0;				//初始化各种图层信息
    top_layer_head->pop_area=Win_Size;
    top_layer_head->cur_attr=scr_attr;
	top_layer_head->cur_info = (CHAR_INFO *)malloc(Size_R*Size_C * sizeof(CHAR_INFO));
	ReadConsoleOutput(Handle_Out, top_layer_head->cur_info,Interface_Size , pos, &Win_Size);
    top_layer_head->next=NULL;
    for (i=1;i<=mainmenu_num;i++)			//设置主菜单属性
    {
        for (j=PosA;j<=PosB;j++)			//设置PosA - PosB 这一段对应的主菜单信息
			scr_attr[j] |=i<<2;				//将当前位置 主菜单编号设置
        if (i<mainmenu_num)
        {
            PosA=PosB+1;
            PosB+=strlen(I_Main_Menu[i]);	//计算下一段主菜单位置
        }
    }
}

/**************************************************
 * 函数名称：RunSys
 * 函数功能：运行系统 根据用户的鼠标键盘输入的信息 
			进行对应操作
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void RunSys()
{
    INPUT_RECORD Signal;		//鼠标键盘信息接收变量
    DWORD num;					//存放接收信息个数
    COORD pos = { 0 , 0 };		//鼠标位置
    BOOL Mark = TRUE;			//系统结束标记
    STATE_AREA cur;				//当前状态信息 （图层编号 主菜单 热区编号）
    int temp=0;					//存放临时信息
    int i;
    char virtual_key,key_asc;	//virtual_key表示虚拟键值 key_asc表示键盘事件对应按键的ascll码值
	LAYER_NODE *pCount;			//通过鼠标位置获取当前图层的属性信心
    while (Mark)				//循环获取信息 并对之处理
    {
        ReadConsoleInput(Handle_In,&Signal,1,&num);			//读入一条鼠标键盘事件信息
        if (Signal.EventType == MOUSE_EVENT)				//如果是鼠标事件
        {
            pos = Signal.Event.MouseEvent.dwMousePosition;	//那么获取鼠标位置
			cur.info = 0;									//字段结构 当前状态信息首先初始化为0
			for (pCount = top_layer_head; pCount != NULL; pCount = pCount->next)	//从顶层图层开始判断 （展现出来的部分是上层的图层）
			{
				if (pCount->pop_area.Left <= pos.X&&pCount->pop_area.Right >= pos.X	//如果鼠标位于当前图层
					&&pCount->pop_area.Top <= pos.Y&&pCount->pop_area.Bottom >= pos.Y)
				{
					pos.Y = pos.Y - pCount->pop_area.Top;		//那么计算鼠标相对于当前图层左上角的位置
					pos.X = pos.X - pCount->pop_area.Left;
					cur.info = pCount->cur_attr[pos.Y*(pCount->pop_area.Right- pCount->pop_area.Left+1) + pos.X];	//并获取当前图层当前鼠标位置的属性信息
					break;										//跳出循环
				}//如果没有找到 那么就网往下一个图层寻找 直到满足条件位置 这样就可以获取鼠标在正确图层的属性信息
			}	

            //情况1:已经有子菜单弹出 当前位置是主菜单 没有子菜单弹出 点了一下
            //情况2:已经有子菜单弹出 当前位置是主菜单 没有子菜单弹出 没点鼠标
            //情况3:已经有子菜单弹出 当前位置是主菜单 有子菜单弹出 点和没点
            //情况4:已经有子菜单弹出 当前位置是子菜单 点了一下
            //情况5:已经有子菜单弹出 当前位置是子菜单 没点

            if (Open_Sub == TRUE)	//如果子菜单以及打开了
            {
                //如果当前处于主菜单的一个位置
				if (cur.comb.sel_main_num > 0)
                {
                    //如果当前处于的子菜单是已经弹出的主菜单
                    if (cur.comb.sel_main_num == sel_main_num)
                    {
                        //如果鼠标左键单击了 就让子菜单收回 open_sub=false
                        if (Signal.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED )
                        {
                            WithdrewPopHot();
                        }
                        else continue;	//否则就进入下一次循环
                    }
                    //否则就是处于别的主菜单
                    //那么就收回之前的子菜单 让sel_main_menu = 当前值 标记当前主菜单 并打开最新的子菜单
                    else
                    {
                        OpenNewMenu(cur.comb.sel_main_num);
                    }
                }
                //如果处于子菜单的位置
                else if (cur.comb.sel_sub_num>0)
                {
					sel_sub_num = cur.comb.sel_sub_num;
					TagHotArea(sel_sub_num);
                    //如果点击了左键那么就打开弹窗
                    if (Signal.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        temp=sel_sub_num+sel_main_num*10;
                        WithdrewPopHot();
                        sel_main_num=0;
                        TagMainMenu(sel_main_num);
						Mark = iFunction(temp / 10, temp % 10);
                    }
                }
                //否则就是其他位置 如果点了鼠标左键
                //那么就收回子菜单 取消主菜单标记
                else if(Signal.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    WithdrewPopHot();
                    sel_main_num=0;
					TagMainMenu(sel_main_num);
                }
				else if (sel_sub_num)	//如果不满足以上所有条件 那么说明鼠标处于其他位置 取消标记
				{
					sel_sub_num = TagHotArea(0);
				}
            }
            //如果没有子菜单弹出
            else if(cur.comb.layer_no == 0)
            {
                //如果当前位置处于主菜单一个位置
                if (cur.comb.sel_main_num>0)
                {
                    sel_main_num = cur.comb.sel_main_num;
                    TagMainMenu(sel_main_num);
                    if (Signal.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                    {
                        PopSubMenu(sel_main_num);
                    }
                }
				else	//否则 就是处于其他位置 取消标记（不然鼠标移开了对应的主菜单 主菜单还是处于标记状态）
                {
                    sel_main_num=0;
                    TagMainMenu(sel_main_num);
                }
            }
        }
        //如果是键盘事件触发了 并且键盘处于按下状态
        else if (Signal.EventType == KEY_EVENT
               &&Signal.Event.KeyEvent.bKeyDown )
        {
			virtual_key = (char)Signal.Event.KeyEvent.wVirtualKeyCode;	//获取键盘事件虚拟键值
            key_asc = Signal.Event.KeyEvent.uChar.AsciiChar;			//获取键盘事件按下按键对应的ascll码

            //如果按下了F1 那么打开帮助窗口
            if (virtual_key == 112)	
            {
                //如果当前图层不为0 说明有窗口弹出
                //关闭当前窗口 将主菜单 子菜单标识取消
                if (top_layer_head->no > 0)
                {
                    WithdrewPopHot();
                }
                sel_main_num=0;
                TagMainMenu(sel_main_num);
                //打开帮助窗口
				Mark = iFunction(5, 1);
            }
            //如果按下了左右alt 说明想要用快捷键打开一个子菜单
            //(位运算 取出 对应的alt信息位 若有一位不为0 说明按了)
            else if (Signal.Event.KeyEvent.dwControlKeyState & (LEFT_ALT_PRESSED|RIGHT_ALT_PRESSED))
            {
                switch (virtual_key)
                {
                    case 'F':OpenNewMenu(1); break;
                    case 'M':OpenNewMenu(2); break;
                    case 'Q':OpenNewMenu(3); break;
                    case 'S':OpenNewMenu(4); break;
                    case 'H':OpenNewMenu(5); break;
                    default:break;
                }
            }
            //如果说ascll码值等于0 说明键入了ascll码表上没有的字符 比如上下左右
            else if(key_asc == 0)
            {
                //如果弹出了子菜单 那么响应上下左右
                if (Open_Sub == TRUE)
                {
                    int mod=top_layer_head->cur_area->no;
                    switch(virtual_key)
                    {
                        case VK_UP   :sel_sub_num=sel_sub_num==0?mod:(sel_sub_num-2+mod)%mod+1;
							          sel_sub_num=TagHotArea(sel_sub_num);
                                      break;
                        case VK_DOWN :sel_sub_num=sel_sub_num==0?1:sel_sub_num%mod+1;
							          sel_sub_num=TagHotArea(sel_sub_num);
                                      break;
                        case VK_LEFT :WithdrewPopHot();
									  sel_main_num=(sel_main_num-2+mainmenu_num)%mainmenu_num+1;
									  sel_sub_num = 1;
                                      TagMainMenu(sel_main_num);
									  PopSubMenu(sel_main_num);
									  TagHotArea(sel_sub_num);
                                      break;
						case VK_RIGHT:WithdrewPopHot();
                                      sel_main_num=sel_main_num%mainmenu_num+1;
									  sel_sub_num = 1;
									  TagMainMenu(sel_main_num);
                                      PopSubMenu(sel_main_num);
									  TagHotArea(sel_sub_num);
                                      break;
                    }
                }
            }
            //如果是普通键 诸如字母数字之类的键(这些键的ascll值与虚拟键值相等 或 差32(大写))
			else if (key_asc - virtual_key == 0 || key_asc - virtual_key == 32)
            {
                //如果没有打开子菜单
                if (Open_Sub == FALSE)
                {
                    switch (virtual_key)
                    {
                        case 'F':OpenNewMenu(1); break;	//文件
                        case 'M':OpenNewMenu(2); break;	//数据维护
                        case 'Q':OpenNewMenu(3); break;	//数据查询
                        case 'S':OpenNewMenu(4); break;	//数据统计
                        case 'H':OpenNewMenu(5); break;	//帮助
                        default:break;					
                    }
                }
                //如果已经打开了子菜单
				else
				{
					//如果按下了ESC键
					if (virtual_key == VK_ESCAPE)
					{
						WithdrewPopHot();					//退出当前子菜单
						sel_main_num = 0;					//取消主菜单标记
						TagMainMenu(sel_main_num);
					}
					//如果按下了回车键 并且选中的子菜单不为0
					else if (virtual_key == VK_RETURN && sel_sub_num)
					{
						temp = sel_sub_num + sel_main_num * 10;	//记录当前选中的编号
						WithdrewPopHot();						//弹出 子菜单
						sel_main_num = 0;						//取消主菜单标记
						TagMainMenu(sel_main_num);
						Mark = iFunction(temp / 10, temp % 10);	//调用对应的选中函数
					}
					//如果是其他按键
					else
					{
						for (i = 0; i < submenu_num[sel_main_num]; i++)
						{
							if (virtual_key == List_Of_All[sel_main_num - 1][i][1]
								&& strlen(List_Of_All[sel_main_num - 1][i]))	//判断当前按下的按键是否是当前子菜单快捷键的一个
							{
								WithdrewPopHot();					//如果是 那么收回子菜单
								temp = sel_main_num;				//记录选中的编号
								sel_main_num = 0;					//取消主菜单标记
								TagMainMenu(sel_main_num);			
								Mark = iFunction(temp, i + 1);		//调用对应函数
								break;
							}
						}
					}
				}
			}
		}
   }
}

/**************************************************
 * 函数名称：CloseSys
 * 函数功能：关闭系统 
			释放内存 关闭热区 清空缓冲区 关闭句柄
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：由文件子菜单中 关闭系统 功能控制
 **************************************************/
void CloseSys()
{
	FreeList(head, NULL, NULL);		//调用函数 释放数据链的内存
	ShutHot();						//关闭热区
	Clear_Buffer();					//清空缓冲区 （用空格）

	free(scr_attr);					//释放存放屏幕属性的内存空间
	free(Buff_Menubar_Info);		//释放存放主菜单信息的内存空间

	CloseHandle(Handle_In);			//关闭输入句柄
	CloseHandle(Handle_Out);		//关闭输出句柄

	SetConsoleTitle("运行结束");		//将系统标题设为 运行结束
}

/**************************************************
 * 函数名称：DealEvent
 * 函数功能：处理简单的事件 根据当前图层的热区信息
			适用的图层类型 只有确认和取消两种按钮
			且其他热区类型为选项型
 * 输入参数：整形 no 表示热区底部按钮数量
 * 输出参数：整形 表示返回的信息
			
 * 返 回 值：无

 * 调用说明：只可处理一些简单的热区 对于复杂的需要处理输
			入信息的热区 图层 需要DealInput来实现
 **************************************************/
int DealEvent(int no)
{
	DWORD num;					//存放读入事件个数
	STATE_AREA cur;				//当前位置的属性信息
	BOOL Mark = TRUE;			//循环标记 
	COORD pos = { 0,0 };		//记录鼠标位置 和 相对于当前热区的位置
	INPUT_RECORD Signal;		//存放接收信号的变量
	HOT_AREA cur_area = *top_layer_head->cur_area;	//存放图层顶层的热区
	int new_num, arrow;			//分别表示新的热区编号 和 箭头（上下左右） 用于处理上下左右按键
	int virtual_key, key_asc;	//分别表示键盘事件对应按键的 虚拟键值 和 对应的ASCLL码
	while (Mark)				//循环读入信息
	{
		ReadConsoleInput(Handle_In, &Signal, 1, &num);		//读入一条信息
		if (Signal.EventType == MOUSE_EVENT)				//如果事件类型是鼠标事件
		{
			pos = Signal.Event.MouseEvent.dwMousePosition;	//获取该事件鼠标的位置
			if (pos.X >= top_layer_head->pop_area.Left&&pos.X <= top_layer_head->pop_area.Right
				&&pos.Y >= top_layer_head->pop_area.Top&&pos.Y <= top_layer_head->pop_area.Bottom) //如果处于顶层图层区域内 （弹窗内）
			{
				pos.Y = pos.Y - top_layer_head->pop_area.Top;						//获取鼠标相对于顶层图层左上角的位置
				pos.X = pos.X - top_layer_head->pop_area.Left;
				cur.info = top_layer_head->cur_attr[pos.Y*cur_area.size.X + pos.X];	//获取当前位置的属性信息
			}
			else continue;									//否则表示在弹窗外面 点击的是下面图层的位置区域 那么进入下一层循环
			if (cur.comb.sel_sub_num > 0)	//如果位置热区编号不为0 证明鼠标位于某个热区上
			{
				sel_sub_num = cur.comb.sel_sub_num;	//更新选中热区编号
				TagHotArea(sel_sub_num);			//标记该热区
				if (Signal.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)	//如果于此同时按下了鼠标左键
				{
					if (sel_sub_num == cur_area.no)	//如果选中的是最后的一个热区 
						return 0;					//证明选中的是取消 那么返回0 表示按下了取消按钮
					else 
					    return sel_sub_num;			//否则返回对应的热区编号
				}
			}
			else	//如果当前热区编号为 0 
			{
				sel_sub_num = TagHotArea(0);	//取消对热区的标记 不然从热区移开 热区还会被标记
			}
		}
		else if (Signal.EventType == KEY_EVENT	//如果当前为键盘事件 并且按键被按下了
			&&Signal.Event.KeyEvent.bKeyDown)
		{
			virtual_key = (char)Signal.Event.KeyEvent.wVirtualKeyCode;	//获取按键的虚拟键值
			key_asc = Signal.Event.KeyEvent.uChar.AsciiChar;			//获取按键对应的ascll码值
			if (key_asc == 0)					//如果按键的ascll码值为0 说明按下的可能为上下左右
			{
				arrow = 0;						//先将箭头变量初始化为0
				switch (virtual_key)			//switch 判断箭头的种类
				{
				    case VK_UP    :arrow = 1; break;
				    case VK_DOWN  :arrow = 2; break;
				    case VK_LEFT  :arrow = 3; break;
				    case VK_RIGHT :arrow = 4; break;
				    default:break;
				}
				if (!arrow) continue;			//如果为0 表示按下的不是箭头 那么进入下一次循环
				new_num = sel_sub_num;			//否则 对应的新的热区编号先置为之前选中的热区标号
				if (sel_sub_num == 0)			//如果选中的热区编号为0 说明没有选中
					new_num = (arrow % 2) ? cur_area.no : 1;	//那么根据箭头是左上还是右下 更新新热区编号为最后或
				else							//否则说明之前已经选中了一个热区
				{
					while (TRUE)				//死循环 直到找到正确的热区
					{
						new_num = (arrow % 2) ? (new_num - 2 + cur_area.no) % cur_area.no + 1
							                  : new_num%cur_area.no + 1;	//根据箭头是左上还是右下进行-1或+1 用取余使得可以数字循环（即在顶部按下上可变到底部热区）
						if (new_num == sel_sub_num) break;					//判断是否于之前选中的热区相同 如果相同 就跳出循环 否则会导致死循环 （此种情况出现在只有一个按钮的情况）
						if (new_num < 1 || new_num>cur_area.no				//如果新的热区编号溢出了（不在图层编号区间内了 由于用了取余也不会溢出）
							|| (arrow < 3) &&								//或者 如果按下了上下并且新热区编号对应热区与原热区不在一行 说明找到了正确的热区 那么跳出 
							cur_area.pArea[sel_sub_num - 1].Top != cur_area.pArea[new_num - 1].Top
							|| (arrow > 2) &&								//或者 如果按下了左右并且新热区编号对应热区与原热区在一行 说明找到了正确的热区 那么跳出 
							cur_area.pArea[sel_sub_num - 1].Top == cur_area.pArea[new_num - 1].Top)
						{
							break;
						}
					}
				}
				if (new_num > 0 && new_num <= cur_area.no)	//如果没有溢出 证明找到了
				{
					sel_sub_num = new_num;		//更新新的标记热区编号
					TagHotArea(sel_sub_num);	//标记新的热区
				}
			}
			else if (virtual_key == VK_ESCAPE)	//如果按下了ESC 那么等同于按下了 取消 退出当前的弹窗
			{	
				return 0;						//返回0 表示取消
			}
			else if (virtual_key == VK_RETURN&&sel_sub_num)	//如果按下了回车并且选中了一个热区
			{
				if (sel_sub_num == cur_area.no)	//如果选中的热区是最后一个 证明对取消按钮按下了 回车
					return 0;					//返回0 退出系统
				else							//否则返回对应的热区编号
					return sel_sub_num;
			}
		}
	}
	return 0; 
}

/**************************************************
 * 函数名称：TagMainMenu
 * 函数功能：标记主菜单 根据选中的主菜单编号来标记
			0表示清空标记
 * 输入参数：整形变量 num 表示待标记的主菜单编号 
			0表示不标记
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void TagMainMenu(int num)
{
    int i;									
	int Left_X = 0, Right_X = -1;			//标记区间 默认左端为0 右端为-1 表示清除标记
	COORD size;								//存放大小变量
    COORD pos = {0,0};						//位置变量
	CONSOLE_SCREEN_BUFFER_INFO Info_Buffer;	//存放缓冲区信息

	if (num > mainmenu_num) return;			//如果传进来的参数大于主菜单菜单数量 那么直接返回

	if (num != 0)							//如果num 不为0 表示要标记新的主菜单选项
    {
       for (i=0;i<num-1;i++)					//根据字符串长度计算标记的左端和右端
           Left_X+=strlen(I_Main_Menu[i]);
       Right_X=Left_X+strlen(I_Main_Menu[i])-1;
    }

    GetConsoleScreenBufferInfo(Handle_Out,&Info_Buffer);	//获取当前控制台屏幕缓冲区信息
    size.X = Info_Buffer.dwSize.X;				//得到主菜单的大小参数
    size.Y = 1;

    for (i=0;i<size.X;i++)						//对每一个字符点的颜色属性进行更新赋值
    {
        if ( i >= Left_X && i <=Right_X)		//如果处于标记区间范围之类 那么 颜色为标记颜色
        {
            (Buff_Menubar_Info+i)->Attributes = BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY;
        }
		else									//否则为正常颜色
        {
            (Buff_Menubar_Info+i)->Attributes = BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE;
        }
    }

    SMALL_RECT rec= {0,0,size.X-1,0};			//主菜单左上角 右下角坐标
    WriteConsoleOutput(Handle_Out,Buff_Menubar_Info,size,pos,&rec);		//写入更新后的颜色信息
}

/**************************************************
 * 函数名称：TagHotArea
 * 函数功能：标记子菜单选项 或者是 对应的热区
 * 输入参数：整形变量 num
			表示对应的子菜单编号 以及 热区编号
			0表示清空标记
 * 输出参数：无
 * 返 回 值：整形变量 
			表示标记成功的热区编号

 * 调用说明：不仅适用于子菜单的标记
			还适用于其他各类弹窗 各类图层的标记
 **************************************************/
int TagHotArea(int num)
{
	int i;
	COORD pos;		//位置信息 变量
	DWORD lenth;	//写入长度变量
	STATE_AREA cur; //当前待标记区域的属性
	HOT_AREA cur_area = *top_layer_head->cur_area;	//顶层图层热区信息 用于判断标记方式

	for (i=0; i<cur_area.no; i++)			//对每个热区进行颜色进行更新
	{
		cur.info = cur_area.pHotNum[i];		//获取当前热区属性
		pos.X = cur_area.pArea[i].Left;		//获取热区左上角坐标
		pos.Y = cur_area.pArea[i].Top;
		lenth = cur_area.pArea[i].Right - cur_area.pArea[i].Left + 1;	//计算热区长度
		if (cur_area.pHotType[i] == 2)		//如果热区类型为2 说明该热区为输入框 写入区 
		{
			FillConsoleOutputAttribute(Handle_Out, Input_Attr, lenth, pos, &ul); //将这一区域填充为写入区域对应的颜色
		}
		else if (cur_area.pHotType[i] == 3)	//如果当前区域类型为3 说明改热区为只读信息框 即展示查询或统计的结果区域
		{
			FillConsoleOutputAttribute(Handle_Out, Fix_Input_Attr, lenth, pos, &ul);	//那么将这一区域颜色填充为固定的输入区域颜色（即只读区域颜色）
		}
		else								//否则就是选项热区或者按钮热区 
		{
			if (num == cur.comb.sel_sub_num)//如果是待标记区域
			{
				FillConsoleOutputAttribute(Handle_Out, Tag_Attr, lenth, pos, &ul);	//标记该热区
			}
			else							//否则
			{
				FillConsoleOutputAttribute(Handle_Out, Hot_Attr, lenth, pos, &ul);	//填充热区正常颜色
			}
		}
	}
	return num;								//返回标记的热区编号
}

/**************************************************
 * 函数名称：PopSubMenu
 * 函数功能：弹出子菜单
 * 输入参数：整型变量 
			表示子菜单对应主菜单编号
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void PopSubMenu(int num)
{
	int i,no;							
	TEXT_BAR cur_text;					//存放弹出的子菜单的各栏的文字和位置信息
	HOT_AREA *cur_area;					//存放子菜单的热区信息
	SMALL_RECT rec_pop = {0,0,0,0};		//存放弹出子菜单的整体区域


	CalSubArea(&rec_pop);				//计算弹出子菜单的方框大小 将结果存入rec_pop

	//完善各个文字条信息
	cur_text.no = submenu_num[num - 1];								//文字条个数
	cur_text.pTextInfo = List_Of_All[num - 1];						//文字条信息
	cur_text.pLPos = (COORD *)calloc(cur_text.no, sizeof(COORD));	//为文字条位置信息分配内存空间
	for (i = 0; i < cur_text.no; i++)								//循环为每个文字条左上角位置赋值
	{
		cur_text.pLPos[i].X = rec_pop.Left + 2;			//左端起始位置为弹出区域左端+2
		cur_text.pLPos[i].Y = rec_pop.Top + 1 + i;		//顶端位置为顶端位置+i+1（弹出区域的i+2行）
	}

	//完善热区信息
	cur_area = (HOT_AREA *)malloc(sizeof(HOT_AREA));		//为热区结构体分配空间
	cur_area->no = submenu_num[num - 1];					//热区个数
	cur_area->size.X = rec_pop.Right - rec_pop.Left + 1;	//计算弹窗大小
	cur_area->size.Y = rec_pop.Bottom - rec_pop.Top + 1;	
	cur_area->pArea = (SMALL_RECT *)malloc(cur_area->no * sizeof(SMALL_RECT));			//为各个指针分配空间
	cur_area->pHotType = (unsigned char *)malloc(cur_area->no * sizeof(unsigned char));
	cur_area->pHotNum = (unsigned short *)calloc(cur_area->no, sizeof(unsigned short));
	
	for (i = 0, no = 0; i < cur_text.no; i++, no++)
	{
		if (cur_text.pTextInfo[i][0] == '\0')		//'\0'表示分割线 不算热区
		{
			no--; continue;							//所以要将no多加的1减去
		}
		*(cur_area->pHotType + no) = 1;				//热区类型为1

		(cur_area->pArea + no)->Left = rec_pop.Left + 2;			//第no个热区 左端位置为 弹窗左端坐标+2
		(cur_area->pArea + no)->Top = rec_pop.Top + i + 1;			//第no个热区 顶端位置为 弹窗顶端坐标+i+1 上面有i+1行
		(cur_area->pArea + no)->Right = rec_pop.Right - 2;			//第no个热区 右端位置为 弹窗右端坐标-2
		(cur_area->pArea + no)->Bottom = rec_pop.Top + i + 1;		//第no个热区 低端位置为 弹窗左端坐标+2

		*(cur_area->pHotNum + no) = ((top_layer_head->no + 1) & 3) | ((no + 1) << 5); //第no个热区 左端位置为 弹窗左端坐标+2
	}
	cur_area->no = no;								//将统计的热区数量赋值给热区结构体下的热区数量变量

	DrawRec(&rec_pop,Rec_Attr);						//画弹窗的边框
	PopHot(&rec_pop, Hot_Attr, &cur_text,cur_area);	//弹出弹窗

	Open_Sub = TRUE;								//子菜单打开标记 置为 TRUE
}

/**************************************************
 * 函数名称：WithdrewPopHot
 * 函数功能：撤回
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void WithdrewPopHot()		//收回当前子菜单 并让 sel_main_num 置为0 open_sub置为false
{
	ShutHot();				//弹出 关闭图层 热区
	sel_sub_num = 0;		//让选中的热区编号置为0
	Open_Sub = FALSE;		//子菜单打开标记置为FALSE
}

/**************************************************
 * 函数名称：ShutHot
 * 函数功能：关闭弹窗 图层
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void ShutHot()
{
	LAYER_NODE *Second_Layer;				//下一层图层指针
	COORD pos = { top_layer_head->pop_area.Left,top_layer_head->pop_area.Top };	//顶层图层左上角坐标
	Second_Layer = top_layer_head->next;	//将下一层图层指针指向顶层的下一层
	
	if (top_layer_head->next == NULL)		//如果只有一层图层 那么返回
		return;

	if (Second_Layer != NULL)				//如果下一层不为空 说明有至少两层
	{										//将下一层被覆盖的信息重新恢复
		WriteConsoleOutput(Handle_Out, Second_Layer->cur_info,Interface_Size, pos, &(top_layer_head->pop_area));
	}
	free(top_layer_head->cur_info);			//释放顶层图层的各种信息
	free(top_layer_head->cur_attr);
	free(top_layer_head->cur_area->pArea);
    free(top_layer_head->cur_area->pHotNum);
	free(top_layer_head->cur_area->pHotType);
	free(top_layer_head);
	top_layer_head = Second_Layer;			//将顶层图层指针更新 （下一层变为顶层）
}

/**************************************************
 * 函数名称：DrawRec
 * 函数功能：绘制弹窗的 边框
 * 输入参数：SMALL_RECT类型 弹窗的位置
			WORD	  类型 弹窗边框的颜色
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void DrawRec(SMALL_RECT *rec_pop,WORD attr)
{	
	char (*element[7])[3];							//存放用于绘制边框的字符
	int sub = rec_pop->Right - rec_pop->Left + 1;	//边框宽
	COORD pos1 = { rec_pop->Left,rec_pop->Top };	//左上角位置
	COORD pos2 = { rec_pop->Left,rec_pop->Bottom };	//左下角位置

	//SetConsoleOutputCP(437);						//设置代码页
	
	element[0] = &"┏";       // 左上角点  
	element[1] = &"┗";       // 左下角点  
	element[2] = &"┓";       // 右上角点  
	element[3] = &"┛";       // 右下角点  
	element[4] = &"━";       // 水平  
	element[5] = &"┃";       // 坚直  

	WriteConsoleOutputCharacter(Handle_Out, element[0], 2, pos1, &ul);		//画左上角
	WriteConsoleOutputCharacter(Handle_Out, element[1], 2, pos2, &ul);		//画左下角

	for (pos1.X = pos2.X = rec_pop->Left + 2; pos1.X <= rec_pop->Right - 2; pos1.X+=2, pos2.X+=2)
	{
		WriteConsoleOutputCharacter(Handle_Out, element[4], 2, pos1, &ul);	//画上边框
		WriteConsoleOutputCharacter(Handle_Out, element[4], 2, pos2, &ul);	//画下边框
	}

	pos1.X = pos2.X = rec_pop->Right-1;
	WriteConsoleOutputCharacter(Handle_Out, element[2], 2, pos1, &ul);		//画右上角
	WriteConsoleOutputCharacter(Handle_Out, element[3], 2, pos2, &ul);		//画右下角

	pos1.X = rec_pop->Left;	
	pos2.X = rec_pop->Right-1;

	for (pos1.Y = pos2.Y = rec_pop->Top + 1; pos1.Y < rec_pop->Bottom; pos1.Y++, pos2.Y++)
	{
		WriteConsoleOutputCharacter(Handle_Out, element[5], 2, pos1, &ul);	//画左边框
		WriteConsoleOutputCharacter(Handle_Out, element[5], 2, pos2, &ul);	//画右边框
	}

	pos1.X = rec_pop->Left;
	for (pos1.Y = rec_pop->Top; pos1.Y <= rec_pop->Bottom; pos1.Y++)
	{
		FillConsoleOutputAttribute(Handle_Out, attr, sub, pos1, &ul);		//为弹窗填充颜色
	}

	SetConsoleOutputCP(936);												//设置代码页为中文代码页
}

/**************************************************
 * 函数名称：OpenNewMenu
 * 函数功能：打开新的子菜单
 * 输入参数：整形 num 表示新子菜单的编号
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void OpenNewMenu(int num)
{
	if (sel_main_num == num) return;	//如果当前标记的子菜单就是要标记的子菜单
    else if (Open_Sub == TRUE)			//如果以及弹出了子菜单
        WithdrewPopHot(sel_main_num);	//那么先弹出
    sel_main_num=num;					//标记
    TagMainMenu(sel_main_num);			//标记新的主菜单
    PopSubMenu(sel_main_num);			//弹出
}

/**************************************************
 * 函数名称：CalSubArea
 * 函数功能：计算子菜单的弹出区域
 * 输入参数：无
 * 输出参数：SMALL_RECT 指针 rec_pop mean 弹出的小方块
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void CalSubArea(SMALL_RECT *rec_pop)
{
	int i;
	for (i = 1; i < sel_main_num; i++)
	{
		rec_pop->Left += strlen(I_Main_Menu[i-1]);		//计算左端的坐标 为当前子菜单之前的主菜单选项字符串长度之和
	}
	for (i = 0; i < submenu_num[sel_main_num - 1]; i++)
	{
		rec_pop->Right = max(rec_pop->Right, strlen(List_Of_All[sel_main_num - 1][i]));	//长度为最长的子菜单选项字符长度
	}
	rec_pop->Right += rec_pop->Left+5;					//长度+左端坐标+边框长度以及多留出的空格5=右端坐标
	rec_pop->Top = 1;									//顶端坐标由于是在主菜单下方 故就为1
	rec_pop->Bottom = submenu_num[sel_main_num - 1] + 2;//底部坐标根据子菜单选项数量计算

	if (rec_pop->Right > Size_C)						//如果右端坐标超过窗口的右端（缓冲区最右端）
	{
		i = rec_pop->Right - Size_C;					//那么整体向左移 让右端靠边
		rec_pop->Left -= i + 1;
		rec_pop->Right = Size_C - 1;
	}
}

/**************************************************
 * 函数名称：iFunction
 * 函数功能：根据选中的主菜单和子菜单编号
			调用对应函数实现对应功能 
 * 输入参数：整形变量 x_num mean主菜单编号
			整形变量 y_num mean子菜单编号
 * 输出参数：无
 * 返 回 值：BOOL类型 
			TRUE 表示继续运行
			FALSE 表示结束运行 关闭系统

 * 调用说明：无
 **************************************************/
BOOL iFunction(int x_num,int y_num)
{
	BOOL(*pFunction[5][5])(void);			//建立一个5*5的二位函数指针数组 每个指针指向一个函数 
											//第一维下标表示主菜单编号第二维下标表示子菜单编号 
	pFunction[0][0] = SaveData;				//将各个指针指向对应的函数
	pFunction[0][1] = BackData;
	pFunction[0][2] = RecoveryData;
	pFunction[0][3] = DeleteBack;
	pFunction[0][4] = ExitSys;

	pFunction[1][0] = MaintainType;
	pFunction[1][1] = MaintainBasic;
	pFunction[1][2] = MaintainRecruit;
	pFunction[1][3] = NULL;
	pFunction[1][4] = NULL;
	
	pFunction[2][0] = QueryType;
	pFunction[2][1] = QueryBasic;
	pFunction[2][2] = QueryRecruit;
	pFunction[2][3] = NULL;
	pFunction[2][4] = NULL;

	pFunction[3][0] = StatTypePeople;
	pFunction[3][1] = StatAllPeople;
	pFunction[3][2] = StatEnrollNum;
	pFunction[3][3] = StatHighScore;
	pFunction[3][4] = StatHighIndex;

	pFunction[4][0] = HelpSys;
	pFunction[4][1] = AboutSys;
	pFunction[4][2] = NULL;
	pFunction[4][3] = NULL;
	pFunction[4][4] = NULL;
	
	return pFunction[x_num - 1][y_num - 1]();//调用对应函数 并将函数返回值返回给RunSys函数
}

/**************************************************
 * 函数名称：PopHot
 * 函数功能：根据传入的参数信息 弹出热区 图层
			在rec_pop区域 的指定位置弹出文字条 
			并根据热区信息添加新的图层
			更新新的图层信息
 * 输入参数：SAMLL_RECT *类型 rec_pop 表示弹出窗口区域
			WORD		类型 attr    表示窗口背景颜色
			TEXT_BAR *	类型 cur_text表示当前窗口文字条信息
			HOT_AREA *	类型 cur_area表示当前窗口热区信息
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void PopHot(SMALL_RECT *rec_pop, WORD attr, TEXT_BAR *cur_text, HOT_AREA *cur_area)
{
	char *OInfo;				//输出信息指针
	int i, j;	
	DWORD lenth;				//填充颜色的长度
	LAYER_NODE *new_top_layer;	//新的顶层图层
	COORD pos = { rec_pop->Left + 1,rec_pop->Top + 1 };	//位置

	new_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));	//为新图层节点分配内存空间
	new_top_layer->pop_area = *rec_pop;							//弹出区域
	new_top_layer->cur_area = cur_area;							//弹出窗口热区信息
	new_top_layer->next = top_layer_head;						//指向下一层图层
	new_top_layer->no = top_layer_head->no + 1;					//图层编号
	new_top_layer->cur_info = (CHAR_INFO *)malloc(cur_area->size.X*cur_area->size.Y * sizeof(CHAR_INFO));			//为当前图层信息文字信息分配空间
	new_top_layer->cur_attr = (unsigned short *)calloc(cur_area->size.X*cur_area->size.Y, sizeof(unsigned short));	//为当前图层各个位置属性信息分配信息

	for (i = 0; i < cur_text->no; i++)
	{
		OInfo = cur_text->pTextInfo[i];	//将输出指针指向要输出的信息
		if (strlen(OInfo))
		{
			WriteConsoleOutputCharacter(Handle_Out, OInfo, strlen(OInfo), cur_text->pLPos[i], &ul);	//从该文字条左边的位置开始输出
		}
	}

	pos.X = rec_pop->Left + 1;			
	for (pos.Y = rec_pop->Top + 1; pos.Y < rec_pop->Bottom; pos.Y++)	//从上到下填充背景颜色
	{
		FillConsoleOutputAttribute(Handle_Out, attr, cur_area->size.X - 2, pos, &ul);
	}

	for (i = 0; i<cur_text->no; i++)
	{
		//如果字符串首地址存的是'\0'说明是空串 那么就输入分割线
		if (cur_text->pTextInfo[i][0] == '\0')
		{
			pos = cur_text->pLPos[i];
			FillConsoleOutputCharacter(Handle_Out, '-', cur_area->size.X - 4, pos, &ul);
		}
	}

	for (i = 0; i < cur_area->no; i++)			//热区颜色设置
	{
		if (cur_area->pHotType[i] == 2)			//如果该热区为输入框
		{
			lenth = cur_area->pArea[i].Right - cur_area->pArea[i].Left + 1;
			pos.X = cur_area->pArea[i].Left;
			pos.Y = cur_area->pArea[i].Top;
			FillConsoleOutputAttribute(Handle_Out, Input_Attr, lenth, pos, &ul);
		}
		else if (cur_area->pHotType[i] == 3)	//如果为显示框 （展现信息）
		{
			lenth = cur_area->pArea[i].Right - cur_area->pArea[i].Left + 1;
			pos.X = cur_area->pArea[i].Left;
			pos.Y = cur_area->pArea[i].Top;
			FillConsoleOutputAttribute(Handle_Out, Fix_Input_Attr, lenth, pos, &ul);
		}
	}

	pos.X = 0;
	pos.Y = 0;
	ReadConsoleOutput(Handle_Out, new_top_layer->cur_info, cur_area->size, pos, rec_pop);	//读入显示在控制台上的输出信息 
	for (i = 0; i < cur_area->size.Y; i++)
	{
		for (j = 0; j < cur_area->size.X; j++)
		{
			*(new_top_layer->cur_attr + i*cur_area->size.X + j) = new_top_layer->no;		//将各个位置属性先初始化为 图层编号
		}
	}
	for (i = 0; i < cur_area->no; i++)
	{
		for (j = cur_area->pArea[i].Left; j <= cur_area->pArea[i].Right; j++)
		{
			if (cur_area->pHotType[i] != 0)
			{
				*(new_top_layer->cur_attr + (cur_area->pArea[i].Top - rec_pop->Top)*cur_area->size.X + j - rec_pop->Left)
					= cur_area->pHotNum[i] | (cur_area->pHotType[i] << 9);					//各个热区属性进行重新计算 （不同于其他区域） 
			}

		}
	}

	top_layer_head = new_top_layer;		//更新图层信息顶层节点
}

/**************************************************
 * 函数名称：CalPopArea
 * 函数功能：计算热区弹出区域 
			计算各个文字条的字符信息和左端位置信息
 * 输入参数：char **类型 text_info 二位字符数组 表示窗口文字的具体信息和位置信息
			int	*  类型 space_num 一维整形数组 表示各个输入框长度
			int *  类型 bottom    整形变量     表示底部按钮数量
 * 输出参数：SMALL_RECT *类型	 rec_pop  表示弹出窗口区域信息
			TEXT_BAR   *类型 cur_text 表示弹出窗口文字条信息
 * 返 回 值：无

 * 调用说明：输入的text_info不仅有要显示到屏幕上的文字信息 
			还有所有文字的布局 位置 格式信息
			格式规则：
			1.'\0'字符表示这一行为分隔符
			2.'\n'字符表示空一行 即下一条文字信息在上一条的下方两格
			3.'-'字符表示该文字信息或者其他信息接在上一条文字信息后面 在同一行 如果没有默认跳到下一行
			4.'&'字符表示该文字信息在该行居中显示
			5.'h'表示这一个文字信息 用热区替换 是一个热区
 **************************************************/
void CalPopArea(SMALL_RECT *rec_pop, TEXT_BAR *cur_text, char **text_info, int *space_num, int bottom_no)
{
	int i,j,k;
	int row = 2;									//表示根据text_info 内每条字符串中格式信息计算出来的窗口行数 最小为两行
	int temp;										//存放临时数据
	int lenth = strlen(text_info[0]);				//表示窗口最短横向长度
	int text_bar_no = bottom_no;					//文字条的个数 初始化为底部按钮个数 （因为上部信息与底部按钮是分开处理的）
	COORD pos = { 0,0 };							//位置信息

	//计算窗口大小 和 文字条个数
	rec_pop->Right = max(rec_pop->Right, lenth);	//先将计算时当前窗口横向长度最大值保存到弹出区域的右端坐标
	for (i = 0, k = 0; i < cur_text->no; i++)		//循环处理text_info中各个文字信息 
	{												//此时cur_text存放的并不是文字条个数 而是text_info共存放了几个字符串
		if (i < cur_text->no - bottom_no)			//如果不是按钮部分 （text_info 分主体部分和按钮部分）
		{
			switch (text_info[i][0])				//对首字符进行判断
			{
			case '\0':row++; text_bar_no++; break;	//如果是空字符 说明这一行为分割线 文字条个数++
			case '\n':row++; break;					//如果是换行符 说明这一行为空行   不计入文字条个数
			case '-':if (text_info[i][1] != 'h') text_bar_no++; break;	//如果这一行为'-'并且不是热区 说明这一条文字信息接在上一条的尾部
			default:row++; text_bar_no++; break;	//如果不是以上所有情况 则说明是文字信息 行数+1 文字条信息+1
			}
		}
		//计算窗口横向长度
		if (text_info[i][0] == '-')					//如果为'-'说明该条信息接在上一条的后面
		{
			if (text_info[i][1] != 'h')				//如果不为热区 
				lenth += strlen(text_info[i]);		//那么长度为这一行之前的长度 加上 现在这个输出信息的长度
			else									//否则说明是热区
			{
				lenth += space_num[k++] + 2;		//那么就 加上 将对应热区长度 多加的2表示热区与边框留出的距离
			}
		}
		else										//否则 说明为新的一行
		{
			lenth = strlen(text_info[i]);			//那么舍弃原来长度 长度更新为新的长度
		}
		rec_pop->Right = max(rec_pop->Right, lenth);//将最新的长度与原来最长的相比 得到最大横向长度
	}

	if (bottom_no) row++;							//如果底部有按钮 行数还要再加一行
													//开始得出最终窗口区域坐标
	if ((rec_pop->Right - rec_pop->Left + 1) % 2 == 0)		rec_pop->Right++;	//保证长度为奇数 （为了边框显示更美观）
	rec_pop->Left = (Size_C - rec_pop->Right - 4) / 2;		//将求得得最长长度 窗口占用得行数 按照居与主界面中央的标准赋值给rec_pop变量
	rec_pop->Right = rec_pop->Left + rec_pop->Right + 3;	
	rec_pop->Top = (Size_R - row - 2) / 2 + 1;
	rec_pop->Bottom = rec_pop->Top + row - 1;

	//开始给cur_text赋值
	pos.X = rec_pop->Left + 2;	//初始化文字条左端位置信息		（存放的是下一条信息的左端位置）
	pos.Y = rec_pop->Top + 1;
	cur_text->pTextInfo = (char **)calloc(text_bar_no, sizeof(char *));	//分配内存
	cur_text->pLPos = (COORD *)malloc(text_bar_no * sizeof(COORD));		
	for (i = 0, j = 0, k = 0; i < cur_text->no; i++)					//对每一条输入格式字符信息进行再次处理
	{
		if (i < cur_text->no - bottom_no)								//该循环只对主体部分进行处理
		{
		    switch (text_info[i][0])									//根据首字符判断格式
			{
			case '\0': cur_text->pTextInfo[j] = text_info[i];			//如果是分割线 那么将分隔符存入文字条
					   cur_text->pLPos[j++] = pos;						//将位置信息赋值给分隔符位置
					   pos.Y++; pos.X = rec_pop->Left + 2; break;		//计算下一条文字的位置 由于是分隔符 肯定在下一行
			case '\n': pos.Y++; pos.X = rec_pop->Left + 2; break;		//如果是空行 那么计算下一行位置 即下一行
			case '-':  if (text_info[i][1] != 'h')						//如果碰到了承接符 - 说明该条信息接在上一条后面
			           {												//如果不是热区证明 是一个文字条信息
						   cur_text->pTextInfo[j] = text_info[i] + 1;	//将对应的文字信息 开始地址（除去了-） 给当前文字条文字信息
					       cur_text->pLPos[j++] = pos;					//将位置信息赋值给当前文字条左端位置
						   if (text_info[i + 1][0] != '-')				//如果下一条不是承接在后面
						   {
							   pos.Y++; pos.X = rec_pop->Left + 2;		//那么下一个文字条就在下一行
						   }
						   else if (text_info[i + 1][0] == '-')			//如果下一条承接在后面
						   {
							   pos.X += strlen(text_info[i]);			//那么就在当前文字条的尾部
						   }
			           }
					   else												//否则就是热区 如果热区后面一条信息不是承接符
					   {
						   if (text_info[i + 1][0] != '-')
						   {
							   	pos.Y++; pos.X = rec_pop->Left + 2;		//那么下一个文字条就在下一行
						   }
						   else
							   pos.X += space_num[k++];					//否则就在该热区的后面
					   }
					   break;
			case '&' : cur_text->pTextInfo[j] = text_info[i] + 1;		//如果是居中符 &
					   cur_text->pLPos[j].X = (rec_pop->Right + rec_pop->Left - strlen(cur_text->pTextInfo[j])) / 2 + 1;	//计算这一条文字信息居中该行时 左端位置
					   cur_text->pLPos[j++].Y = pos.Y;					//就在这一行
					   pos.Y++; pos.X = rec_pop->Left + 2;				//下一个文字条就在下一行
					   break;
			default  : cur_text->pTextInfo[j] = text_info[i];			//如果是其他情况 说明新的文字条
				       cur_text->pLPos[j++] = pos;						//为其左端位置赋值
					   if (text_info[i + 1][0] != '-')					//和上面一样计算下一条信息左端位置
					   {
					       pos.Y++; pos.X = rec_pop->Left + 2;
					   }
					   else if (text_info[i + 1][0] == '-')
					   {
						   pos.X += strlen(text_info[i]);
					   }
					   break;
			}
		}
		else
		{
			cur_text->pTextInfo[j++] = text_info[i];
		}
	}

	//为按钮类信息赋值新的文字信息
	pos.Y = rec_pop->Bottom - 1;	
	if (bottom_no == 1)											//一个按钮的时候就居中
	{
		pos.X = (rec_pop->Right + rec_pop->Left) / 2 - 1;
        cur_text->pLPos[text_bar_no - 1] = pos;
	}
	else if (bottom_no == 2)									//两个按钮就关于对称轴对称
	{
		pos.X = (rec_pop->Right + rec_pop->Left) / 2 - 4;
		cur_text->pLPos[text_bar_no - 2] = pos;
		pos.X = (rec_pop->Right + rec_pop->Left) / 2 + 4;
		cur_text->pLPos[text_bar_no - 1] = pos;
	}
	else if (bottom_no == 3)									//三个按钮 说明含上下页 则对称分布
	{
		pos.X = (rec_pop->Right + rec_pop->Left) / 2 - 1;
		cur_text->pLPos[text_bar_no - 2] = pos;
		pos.X = pos.X - 8;
		cur_text->pLPos[text_bar_no - 3] = pos;
		pos.X = pos.X + 8 + strlen(cur_text->pTextInfo[text_bar_no-2]) + 4;
		cur_text->pLPos[text_bar_no - 1] = pos;
	}
	cur_text->no = text_bar_no;
}

/**************************************************
 * 函数名称：InitHotArea
 * 函数功能：初始化热区 翻译格式信息 显示窗口 处理鼠标事件
 * 输入参数：整型 mode 表示处理鼠标键盘事件的模式 0表示不处理 1表示对简单型图层和对于含输入框的图层进行处理
			整型 bottom_no 表示弹出窗口按钮数量
			整型 text_no 表示格式以及文字信息字符串数量
			整型 area_no 表示热区数量
			整型 min_width 表示窗口的最小宽度 （由于后来算法的改进 这个已经不需要了）
			整型指针 space_num 表示各个输入框或者显示框（只读框）的最大字符数
			整型指针 hot_type 各个热区的类型 
			二级字符指针 text_info 表示待显示到屏幕上的字符串及其位置格式，还有热区位置信息
 * 输出参数：整型指针 cur_char_num 表示各个输入框或者显示框（只读框）当前输入的字符数
 * 返 回 值：鼠标键盘事件返回值
			根据不同的处理模式 mode 返回值的意义不一样
			具体见鼠标键盘事件处理函数

 * 调用说明：这个函数将前端的显示控制，鼠标键盘事件处理 
			与后端的数据处理联系起来了 是前段与后端的一个桥梁
			相当于把各种面向用户的功能封装在这个函数里
			几乎所有后端功能只用调用这一个函数即可完成
			显示 以及对于用户操作信息的获取
 **************************************************/
int InitHotArea(int mode,int bottom_no, int text_no, int area_no, int min_width,int *cur_char_num, int *space_num, int *hot_type, char **text_info)
{
	int command;				//返回的鼠标键盘命令
	TEXT_BAR *cur_text=(TEXT_BAR *)malloc(sizeof(TEXT_BAR));			//分配各种指针的内存
	HOT_AREA *cur_area=(HOT_AREA *)malloc(sizeof(HOT_AREA));
	SMALL_RECT *rec_pop = (SMALL_RECT *)calloc(1,sizeof(SMALL_RECT));

	cur_text->no = text_no;				//让文字条个数先等于 “密文”字符串的个数
	cur_area->no = area_no;				//为热区数量赋值
	cur_area->bottom_no = bottom_no;	//为热区底部按钮数量赋值
	rec_pop->Right = min_width;			//将弹出窗口区域右端坐标先赋值为 最短横向长度

	CalPopArea(rec_pop, cur_text, text_info, space_num, bottom_no);					//计算弹出区域 并 为文字条结构体赋值
	InitHotInfo(rec_pop, cur_text, cur_area, text_info,text_no,hot_type, space_num);//初始化热区信息
	DrawRec(rec_pop, Rec_Attr);						//画边框和背景
	PopHot(rec_pop, Hot_Attr, cur_text, cur_area);	//弹出热区
	if (mode == 1)									//如果模式 需要处理鼠标键盘事件
	{
		if (space_num == NULL)						//如果不含输入框
			command = DealEvent(bottom_no);			//那么处理简单弹窗事件
		else										//否则处理含输入框的鼠标键盘事件
			command = DealIntput(cur_area, space_num, cur_char_num);
		return command;								//返回处理状态结果
	}
	else return -1;									//返回-1 表示没有处理鼠标键盘事件
}

/**************************************************
 * 函数名称：InitHotInfo
 * 函数功能：初始化热区信息 
			将传进来的各种信息 进行分析和处理 并根据这些
			信息对热区的各个信息进行赋值
 * 输入参数：SMALL_RECT *类型 rec_pop 表示弹窗的区域信息
			TEXT_BAR   *类型 cur_text 当前文字条信息
			char **类型 二级字符指针 表示待显示到屏幕上的字符串及其位置格式，还有热区位置信息
			int 整型类型 text_no "密文"字符串个数
			int *整型指针类型 hot_type 表示各个密文字符串的热区类型 0表示不是热区
			int *整型指针类型 space_num 表示各个输入框的最大字符数量
 * 输出参数：HOT_AREA *类型 cur_area 当前热区信息
 * 返 回 值：无

 * 调用说明：无
 **************************************************/
void InitHotInfo(SMALL_RECT *rec_pop, TEXT_BAR *cur_text, HOT_AREA *cur_area, char **text_info, int text_no, int *hot_type, int *space_num)
{
	BOOL mark = FALSE;			//标记信息 表示是否找到了下一个热区
	int i,j,k,l,temp;			//i 表示第i个热区 j表示第j条文字条 k表示第k条密文
	cur_area->size.X = (rec_pop->Right - rec_pop->Left + 1);
	cur_area->size.Y = (rec_pop->Bottom - rec_pop->Top + 1);
	cur_area->pHotType = (char *)calloc(cur_area->no, sizeof(char));
	cur_area->pArea = (SMALL_RECT *)malloc(cur_area->no * sizeof(SMALL_RECT));
	cur_area->pHotNum = (unsigned short *)malloc(cur_area->no * sizeof(unsigned short));

	for (i = 0, j = -1, k = 0, l = 0; i < cur_area->no; i++,k++)
	{
		//寻找第i个热区 并寻找第i个热区对应的第k条密文（text_info） 并寻找第i个热区对应的文字条信息（需要用到其位置信息）
		while (!mark)					//如果没有找到第i个热区 那么就寻下一个热区 下一个就是第i个热区
		{
			switch (text_info[k][0])				//根据密文首字符进行判断 用来找到当前密文对应的文字条 如果密文代表的是热区则前一条文字条与之对应（跟在前一个文字条后面）
			{
			case '\0':j++; break;					//如果是分隔符 说明第k条密文不是热区 当前文字条也不是第k条密文对应的文字条 那么肯定是下一个文字条
			case '\n' :break;						//否则如果是空行 说明第k条密文不是热区 由于文字条没有存放空行 当前文字条可能为下一个密文对应的文字条 那么直接跳出
			case '-': if (text_info[k][1] != 'h')	//如果是承接符 并且如果不是热区 说明第k条密文不是热区 那么当前文字条也不是第k条密文对应的文字条 肯定是下一个文字条
					  {
					      j++;
					  }
					  break;						//如果是热区当前的第j条文字条就是其对应的文字条
			default:j++; break;						//否则说明是单独的文字条 没有将之前的文字条下表更新到当前下标
			}
			if (hot_type[k]) mark = TRUE;			//如果第k条密文是要寻找的第i个热区
			else k++;								//否则说明当前密文代表的不是热区 那么判断下一条密文
		}

		cur_area->pHotNum[i] = ((top_layer_head->no + 1) & 3) | ((i + 1) << 5);	//为第i个热区 的编号信息进行赋值 
		cur_area->pHotType[i] = hot_type[k];									//为第i个热区的热区类型进行赋值
		cur_area->pArea[i].Top = cur_text->pLPos[j].Y;							//为第i个热区的顶部底部坐标进行赋值
		cur_area->pArea[i].Bottom = cur_text->pLPos[j].Y;
		switch (hot_type[k])													//根据热区类型的不同来对左右坐标进行赋值
		{
			case 1: cur_area->pArea[i].Left = cur_text->pLPos[j].X;
					cur_area->pArea[i].Right = cur_area->pArea[i].Left + strlen(cur_text->pTextInfo[j]) - 1;
					break;
			case 2: cur_area->pArea[i].Left = cur_text->pLPos[j].X+ strlen(cur_text->pTextInfo[j]);
					cur_area->pArea[i].Right = cur_area->pArea[i].Left + space_num[l++];
					break;
			case 3: cur_area->pArea[i].Left = cur_text->pLPos[j].X + strlen(cur_text->pTextInfo[j]);
					cur_area->pArea[i].Right = cur_area->pArea[i].Left + space_num[l++];
				    break;
			case 4: cur_area->pArea[i].Left = cur_text->pLPos[j].X;
				    cur_area->pArea[i].Right = cur_area->pArea[i].Left + strlen(cur_text->pTextInfo[j]) - 1; 
					break;
			case 5: cur_area->pArea[i].Left = cur_text->pLPos[j].X;
				    cur_area->pArea[i].Right = cur_area->pArea[i].Left + strlen(cur_text->pTextInfo[j]) - 1; 
					break;
			case 6: cur_area->pArea[i].Left = cur_text->pLPos[j].X;
				    cur_area->pArea[i].Right = cur_area->pArea[i].Left + strlen(cur_text->pTextInfo[j]) - 1; 
					break;
			case 7: cur_area->pArea[i].Left = cur_text->pLPos[j].X;
				    cur_area->pArea[i].Right = cur_area->pArea[i].Left + strlen(cur_text->pTextInfo[j]) - 1;
				    break;
			default:break;
		}
		mark = FALSE;					//重新寻找下一个热区
	}
}

/**************************************************
 * 函数名称：ErrorMention
 * 函数功能：错误信息提醒 各种消息提醒
 * 输入参数：整型 num 消息提醒类型（编号） 0-18 分别表示
			0-有空未输出  1-信息录入成功   2-未找到对应编号学校
			3-格式有误    4-输入信息已存在 5-删除成功
			6-未找到对应的学校类型 7-未找到对应年份的招生信息
			8-修改成功	 9-未查询到对应信息 10-保存成功
			11-备份成功  12-备份数量达到上限 13-恢复成功
			14-打开文件失败 15-删除备份成功 16-删除备份失败
			17-帮助信息 18-关于信息
 * 输出参数：无
 * 返 回 值：整型 鼠标键盘事件处理结果 

 * 调用说明：消息提醒的封装函数
 **************************************************/
int ErrorMention(int num)
{
	if (top_layer_head->no>0) WithdrewPopHot();				//先弹出顶层非主界面的窗口
	char *empty_info[]   =  { "&还有空未输入！","\n",			//声明各种信息 对应的密文
						      "确定" };
	char *success_info[] =  { "&信息录入成功！","\n",
						      "确定" };
	char *found_no[]     =  { "&未找到对应编号学校！","\n",
						      "确定" };
    char *format_info[]  =  { "&格式输入有误！",
							  "&详情参考帮助！","\n",
							  "确定" };
	char *exist_info[]   =  { "&输入的信息已存在！","\n",
							  "确定" };
	char *del_info[]     =  { "&删除成功！","\n",
							  "确定" };
	char *found_classes[]=  { "&未找到对应的学校类型！","\n",
					   	      "确定" };
	char *found_year[]   =  { "&未找到对应年份的招生信息！","\n",
					   	      "确定" };
	char *mod_info[]     =  { "&修改成功！","\n",
							  "确定" };
	char *query_error[]  =  { "&未查询到对应信息!","\n",
		                      "确定"};
	char *store_info[]   =  { "&保存成功！","\n",
							  "确定" };
	char *back_info[]    =  { "&备份成功！","\n",
							   "确定" };
	char *back_error[]   =  { "&备份数量达到上限！","\n",
							  "确定" };
	char *recovery_info[]=  { "&恢复成功！","\n",
							  "确定" };
	char *open_error[]   =  { "&打开文件失败！","\n",
							  "确定" };
	char *del_back_info[]=  { "&删除备份成功！","\n",
							  "确定" };
	char *del_back_error[]= { "&删除备份失败！","\n",
						      "确定" };
	char *help_info[] = {"&系统说明","\n",
						 "&本系统支持多种操作",
	                     "&一切问题请联系:",
		                 "&1140764706@qq.com","\n",
	                     "确定"};
	char *about_info[] = {"&作者:幸儒林",
						  "&学号:U201610282",
						  "&华中科技大学CSEE1601","\n",
	                      "确定"};

	char **error_info[19] = { empty_info,success_info,found_no,format_info,exist_info,
		                      del_info, found_classes,found_year,mod_info,query_error,
		                      store_info,back_info,back_error,recovery_info,open_error,
							  del_back_info,del_back_error,help_info,about_info };
	int no;				//按钮数量
	int delta;			//热区类型下标偏移量
	int command;		//接收鼠标键盘事件返回值
	int hot_type[] = { 0,0,0,0,0,0,0,4 };	//通用热区类型

	int text_no[] = { 3,3,3,4,3,3,3,3,3,3,3,3,3,3,3,3,3,7,5 };	//各个提醒密文信息的数量
	TEXT_BAR cur_text;				
	HOT_AREA cur_area;
	SMALL_RECT rec_pop = { 0,0,0,0 };
	
	switch (num)					//根据不同的消息设定不同的偏移量
	{
	case 3:delta = 4; break;
	case 17:delta = 1; break;
	case 18:delta = 3; break;
	default:delta = 5; break;
	}
	no = 1;
	cur_text.no = text_no[num];		//指向对应的密文
	cur_area.no = 1;
	CalPopArea(&rec_pop, &cur_text, error_info[num], NULL, 1);		//计算消息提醒窗口弹出区域
	InitHotInfo(&rec_pop, &cur_text, &cur_area, error_info[num], text_no[num],hot_type+delta,NULL);	//初始化热区信息
	DrawRec(&rec_pop, Rec_Attr);	//画边框
	PopHot(&rec_pop, Hot_Attr, &cur_text, &cur_area);				//弹出热区 窗口
	command = DealEvent(no);		//处理接收鼠标键盘事件
	WithdrewPopHot();				//弹出消息提醒窗口
	return command;					//返回鼠标键盘事件处理结果
}

/**************************************************
 * 函数名称：DealInput 
 * 函数功能：处理含输入框的窗口的鼠标键盘事件
 * 输入参数：HOT_AREA *类型 cur_area 表示当前窗口的热区信息
			int *整型指针类型 space_num 表示各个输入框或只读框的最大字符数
 * 输出参数：int *整型指针类型 表示当前输入框或只读框的字符数量
 * 返 回 值：1 表示按下了或点击了确认键 即 提交输入信息 并且每个空都不为空
			2 表示按下了或点击了确认键 但是有空为空
			5 表示按下了或点击了取消键 
			6 表示按下了或点击了上一页 
			7 表示按下了或点击了下一页

 * 调用说明：这个函数应用于各个含有输入框的窗口的鼠标键盘事件处理 
 **************************************************/
int DealIntput(HOT_AREA *cur_area,int *space_num,int *cur_char_num)
{
	DWORD num;                               //存储读入的信号个数
	CHAR key_asc;                            //鼠标事件按键对应的ascll码值
	STATE_AREA cur;                          //当前热区标识
	WORD virtual_key;                        //鼠标事件虚拟键值
	BOOL Mark = TRUE;                        //最外层循环记号
	BOOL Caps = FALSE;                       //shift状态
	INPUT_RECORD Signal;                     //鼠标键盘信号输入
	COORD pos = { 0 , 0 };                   //鼠标位置
	COORD cursor_pos = { 0,0 };              //光标位置
	CONSOLE_CURSOR_INFO cursor_state;        //光标状态 （可见性 大小）
	int arrow, new_num;                      //用于处理上下左右按键时定位到新的热区

	GetConsoleCursorInfo(Handle_Out, &cursor_state);		//获取当前鼠标状态
	
	while (Mark)											//循环读入信息
	{
		ReadConsoleInput(Handle_In, &Signal, 1, &num);		//读入一条鼠标键盘事件
		if (Signal.EventType == MOUSE_EVENT)				//如果是鼠标事件
		{
			pos = Signal.Event.MouseEvent.dwMousePosition;	//取出鼠标位置
			if (pos.X >= top_layer_head->pop_area.Left&&pos.X <= top_layer_head->pop_area.Right		//如果在当前窗口内 计算相对于当前窗口的坐标
				&&pos.Y >= top_layer_head->pop_area.Top&&pos.Y <= top_layer_head->pop_area.Bottom) 
			{
				pos.Y = pos.Y - top_layer_head->pop_area.Top;
				pos.X = pos.X - top_layer_head->pop_area.Left;
				cur.info = top_layer_head->cur_attr[pos.Y*cur_area->size.X + pos.X];				//获取当前位置的属性信息
			}
			else											//否则说明在顶层窗口外面
			{
				if (Signal.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)	//如果按下了左键
				{
					cursor_state.bVisible = FALSE;										//将光标设为不可见
					SetConsoleCursorInfo(Handle_Out, &cursor_state);
				}
				continue;
			}
			if (Signal.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) //如果按下了鼠标左键
			{
				switch (cur.comb.type)										//根据鼠标处于哪个热区来进行不同处理
				{
				case 1: cursor_state.bVisible = FALSE;						//如果是选项区
						SetConsoleCursorInfo(Handle_Out, &cursor_state);	//设置光标为不可见
						sel_sub_num = cur.comb.sel_sub_num;					//标记该选项
						TagHotArea(sel_sub_num);							//这一个分支可能用不到
						break;
				case 2: sel_sub_num = cur.comb.sel_sub_num;					//如果是输入框
					    cursor_pos.X = cur_area->pArea[sel_sub_num - 1].Left + cur_char_num[sel_sub_num - 1];	//光标位置设置到输入框最后一个字符后面
					    cursor_pos.Y = cur_area->pArea[sel_sub_num - 1].Top;
					    SetConsoleCursorPosition(Handle_Out, cursor_pos);	//设置光标位置
					    cursor_state.bVisible = TRUE;						//光标设置为可见
					    SetConsoleCursorInfo(Handle_Out, &cursor_state);
					    TagHotArea(sel_sub_num);
						break;
				case 3: break;												//如果是显示框 只读框 那么不作任何处理
				case 4: for (int i = 0, j = 0; i < cur_area->no; i++)		//如果是确认区域
				        {
					        if (cur_area->pHotType[i] == 2)					//那么判断所有输入框是否为空
							{
								if (!cur_char_num[j]) return 2;				//如果找到了空的输入框 那么就返回对应信息
								else										//否则继续找
								{
									while (i<cur_area->no&&cur_area->pHotType[i] != 2)
									{
										i++;
									}
									if (i < cur_area->no) j++;
								}
							}
						}
						return 1; break;		//没有找到则返回对应信息
				case 5: return 5; break;		//如果点击了取消   返回对应信息	
				case 6: return 6; break;		//如果点击了上一页 返回对应信息
				case 7: return 7; break;		//如果点击了下一页 返回对应信息
				}
			}
			//没有按下鼠标左键时
			else if (cur.comb.type == 1|| cur.comb.type == 4||cur.comb.type == 5|| cur.comb.type == 6||cur.comb.type == 7)	//如果是热区 并且 不是输入框
			{
				sel_sub_num = TagHotArea(cur.comb.sel_sub_num);		//标记该热区	
				cursor_state.bVisible = FALSE;						//设置光标为不可见
				SetConsoleCursorInfo(Handle_Out, &cursor_state);
			}
			else if (cur_area->pHotType[sel_sub_num] != 2)			//否则如果不是输入框
			{
				TagHotArea(0);										//取消标记
			}
		}
		else if (Signal.EventType == KEY_EVENT && Signal.Event.KeyEvent.bKeyDown)	//如果是键盘事件 并且键盘被按下了
		{
			virtual_key = Signal.Event.KeyEvent.wVirtualKeyCode;	//获取按键的虚拟键值
			key_asc = Signal.Event.KeyEvent.uChar.AsciiChar;		//获取按键对应的ascll码
			if (key_asc == 0)				//如果ascll是0 说明可能按下了上下左右方向键
			{
				arrow = 0;					//将方向键信息置为0 
				switch (virtual_key)		//判断是哪个方向
				{
				    case VK_UP    :arrow = 1; break;
				    case VK_DOWN  :arrow = 2; break;
				    case VK_LEFT  :arrow = 3; break;
				    case VK_RIGHT :arrow = 4; break;
				    default:break;
				}
				if (!arrow) continue;		//如果按下了不是方向键 那么返回

				new_num = sel_sub_num;		//否则 首先将根据方向键 寻找的 新的热区编号初始化为 当前选中的编号
				if (sel_sub_num == 0)		//如果当前没有选中任何一个热区
				{
					new_num = (arrow % 2) ? cur_area->no : 1;		//根据箭头是左上还是右下来寻找新的热区编号
					while (cur_area->pHotType[new_num - 1] == 3)	//如果是只读框 那么寻找下一个
					{
						new_num = new_num%cur_area->no + 1;
					}
				}
				else						//否则证明已经选中了一个热区
				{
					while (TRUE)			//根据箭头寻找下一个热区 直到直到跳出循环
					{
						do{					//先用取余运算（编号可以循环 比如在最顶端热区 按下上 可跳到低端） 根据左上还是右下来循环寻找箭头对应的新的热区
							new_num = (arrow % 2) ? (new_num - 2 + cur_area->no) % cur_area->no + 1
								: new_num%cur_area->no + 1;
						  } while (cur_area->pHotType[new_num - 1] == 3);	//如果为只读框 就继续寻找
						if (new_num == sel_sub_num) break;					//判断是否于之前选中的热区相同 如果相同 就跳出循环 否则会导致死循环 （此种情况出现在只有一个按钮的情况）
						if ((new_num < 1 || new_num>cur_area->no			//如果新的热区编号溢出了（不在图层编号区间内了 由于用了取余也不会溢出）
							|| (arrow < 3) &&								//或者 如果按下了上下并且新热区编号对应热区与原热区不在一行 说明找到了正确的热区 那么跳出 
							cur_area->pArea[sel_sub_num - 1].Top != cur_area->pArea[new_num - 1].Top
							|| (arrow > 2) &&								//或者 如果按下了左右并且新热区编号对应热区与原热区在一行 说明找到了正确的热区 那么跳出 
							cur_area->pArea[sel_sub_num - 1].Top == cur_area->pArea[new_num - 1].Top)
							)
						{
							break;
						}
					}
				}
				if (new_num > 0 && new_num <= cur_area->no)					//如果没有溢出
				{
					sel_sub_num = new_num;									//那么选中的热区为新找到的热区
					if (cur_area->pHotType[new_num - 1] == 2)				//如果找到的热区 类型 为写入区
					{
						cursor_pos.X = cur_area->pArea[sel_sub_num-1].Left + cur_char_num[sel_sub_num-1];	//光标位置设置到输入框最后一个字符后面
						cursor_pos.Y = cur_area->pArea[sel_sub_num-1].Top;	
						SetConsoleCursorPosition(Handle_Out, cursor_pos);	//设置更新的光标位置
						cursor_state.bVisible = TRUE;						//将光标设置为可见
						SetConsoleCursorInfo(Handle_Out, &cursor_state);	
						TagHotArea(sel_sub_num);							//标记当前热区
					}
					else
					{
						cursor_state.bVisible = FALSE;						//否则就是其他类型热区
						SetConsoleCursorInfo(Handle_Out, &cursor_state);	//那么就将鼠光标设置为不可见
					    TagHotArea(sel_sub_num);							//标记当前热区
					}
				}
			}
			else if (key_asc - virtual_key == 0 || key_asc - virtual_key == 32
				   || virtual_key == VK_DECIMAL || virtual_key == 190)		//如果是字母 数字 等普通按键（根据虚拟键值与ascll码规律找出） 或者是 小数点
			{
				if (virtual_key == VK_ESCAPE)								//如果是ESC键
				{
					return 0;												//返回对应信息 -- 取消
				}
				else if (virtual_key == VK_BACK)							//如果是退格键
				{
					if (cur_area->pHotType[sel_sub_num-1] == 2 && cur_char_num[sel_sub_num - 1])	//如果当前选中区域是输入框并且不为当前字符数不为0 
					{
						cur_char_num[sel_sub_num - 1]--;											//将当前的字符数减一
						cursor_pos.X--;																//将光标左移一格
					    FillConsoleOutputCharacter(Handle_Out, ' ', 1, cursor_pos, &ul);			//将原来的位置设置用空格填充 覆盖原来的字符
						SetConsoleCursorPosition(Handle_Out, cursor_pos);
					}
				}
				else if (virtual_key == VK_RETURN || virtual_key == VK_TAB)		//如果是回车 或者是 TAB键
				{
					if (sel_sub_num < cur_area->no - cur_area->bottom_no + 1)	//如果不是按钮部分 那么进入下一个热区
					{
						sel_sub_num++;											
						if (cur_area->pHotType[sel_sub_num - 1] == 2)			//如果下一个热区是输入框 那么同理就显示光标
						{
							cursor_pos.X = cur_area->pArea[sel_sub_num - 1].Left + cur_char_num[sel_sub_num - 1];
							cursor_pos.Y = cur_area->pArea[sel_sub_num - 1].Top;
							SetConsoleCursorPosition(Handle_Out, cursor_pos);
						}
						else													//否则就将光标状态显示为不可见
						{
                            cursor_state.bVisible = FALSE;
							SetConsoleCursorInfo(Handle_Out, &cursor_state);
							TagHotArea(sel_sub_num);							//标记新的热区
						}

					}
					else if (virtual_key == VK_RETURN)							//否则就是按钮区 如果是回车键
					{
						switch (cur_area->pHotType[sel_sub_num - 1])			//如果是
						{														//如果是确认键 同理 那么判断各个输入框是否为空 返回对应信息
						case 4: for (int i = 0; i < cur_area->no - cur_area->bottom_no; i++)
							    {
									if (cur_area->pHotType[i] == 2)
									{
										if (cur_char_num[i] == 0 && space_num[i] != 0) return 2;
									}
								}
								return 1; break;			
						case 5: return 5; break;			//如果是取消键 返回对应信息
						case 6: return 6; break;			//如果是上一页 返回对应信息
						case 7: return 7; break;			//如果是下一页 返回对应信息
						}
					}
				}
			    else if (cur_area->pHotType[sel_sub_num - 1] == 2)					//如果不是以上字符 并且当前选中的是输入框 那么就输入字符
				{
					if (cur_char_num[sel_sub_num - 1] < space_num[sel_sub_num - 1])	//如果当前字符数小于当前输入框最大字符数
					{
						if (key_asc>='A'&&key_asc<='Z')								//如果是字母
						key_asc += Caps * 32;										//根据 Caps大小写标记来对信息进行转换
						FillConsoleOutputCharacter(Handle_Out, key_asc, 1, cursor_pos, &ul);	//将输入的信息回显到屏幕
						cur_char_num[sel_sub_num - 1]++;							//当前字符数加一
						cursor_pos.X++;												//光标位置右移一格
						SetConsoleCursorPosition(Handle_Out, cursor_pos);
					}

				}
			}
			else if (virtual_key == VK_CAPITAL)						//如果按了 大小写键
			{
				Caps ^= 1;											//切换大小写标记
			}
		}
	}
}

/**************************************************
 * 函数名称：FreeList
 * 函数功能：释放链表内存 防止内存占用
 * 输入参数：TYPE *分类信息 指针节点 del_type 释放的分类起始节点
			BASIC *基本信息 指针节点 del_type 释放的分类起始节点
			RECRUIT *招生信息 指针节点 del_type 释放的分类起始节点
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：使用的时候 根据传进来指针是否为空进行 操作
			若TYPE *不为空则释放该分类信息 以及其下的所有BASIC信息 和 RECRUIT 信息
			BASIC * RECRUIT *以此类推
 **************************************************/
void FreeList(TYPE *del_type, BASIC *del_basic, RECRUIT *del_recruit)
{
	TYPE *cur_type_point;								//当前待释放的分类信息节点
	BASIC *cur_basic_point,*basic_temp;				//当前待释放的基本信息节点
	RECRUIT *cur_recruit_point,*recruit_temp;			//当前待释放的招生信息节点
	if (del_type != NULL)								//如果要释放的分类信息节点不为空 
	{
		cur_type_point=del_type;						//待释放的分类节点为要释放的节点
		cur_basic_point = cur_type_point->nextB;		//循环释放基本信息节点
		while (cur_basic_point != NULL)
		{
			cur_recruit_point = cur_basic_point->nextR;	//循环释放招生信息节点
			while (cur_recruit_point != NULL)		
			{
				recruit_temp = cur_recruit_point->next;
				free(cur_recruit_point);
				cur_recruit_point = recruit_temp;
			}
			basic_temp = cur_basic_point->next;
			free(cur_basic_point);
			cur_basic_point = basic_temp;
		}
		free(cur_type_point);							//释放当前分类信息节点
	}
	else if (del_basic != NULL)							//如果要释放的基本信息指针不为空
	{
		cur_basic_point = del_basic;					//待释放的基本信息节点等于要是放的基本信息节点
		cur_recruit_point = cur_basic_point->nextR;		//循环释放招生信息节点
		while (cur_recruit_point != NULL)				
		{
			recruit_temp = cur_recruit_point->next;
			free(cur_recruit_point);
			cur_recruit_point = recruit_temp;
		}
		free(cur_basic_point);							//释放当前的基本信息节点
	}
	else if (del_recruit != NULL)						//如果要释放的招生信息指针不为空
	{
		cur_recruit_point = del_recruit;				//释放当前招生信息节点
		free(cur_recruit_point);
	}
}

/**************************************************
 * 函数名称：PresentQueryInfo
 * 函数功能：展现查询信息 
			根据传进函数的指针 展现指针对应的信息
 * 输入参数：BASIC *类型 basic_query_ans 表示查询到的基本信息
			RECRUIT *类型 recruit_query_ans 表示查询到的招生信息
			int *整型指针 cur_char_num 表示各个输入框总字符个数
			int *整形指针 space_num	  表示各个输入框的长度
			int  整型类型 total        表示查询到的信息链总长度
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：仅限 基本信息和招生 分类信息另外处理
			调用时 两个信息链的指针有一个为NULL
 **************************************************/
void PresentQueryInfo(BASIC *basic_query_ans, RECRUIT *recruit_query_ans, int *cur_char_num, int *space_num, int total)
{ 
	int count = 0;				//当前页数
	int command = 0;			//接收鼠标键盘事件命令
	char temp[10];				//数字转换成字符时 临时存放数据的数组

	COORD pos;					//位置
	COORD page_pos;				//页码 中心位置
	COORD right_pos;			//正确的页码输入位置 相对于页码中心page_pos
	HOT_AREA *cur_area;			//当前热区信息
	BASIC *cur_basic_pos;		//当前的统计信息链节点 
	RECRUIT *cur_recruit_pos;	//当前的统计信息链节点 

	count = 1;					//初始页数为1
	command = 1;				//初始指令 
	sprintf(temp, "%d", total);	//将总页数变成字符串赋值给temp数组
	cur_area = top_layer_head->cur_area;				//获取顶层图层信息
	page_pos.Y = top_layer_head->pop_area.Bottom - 2;	//计算页码中心位置 即 '/'的位置
	page_pos.X = (top_layer_head->pop_area.Left + top_layer_head->pop_area.Right) / 2;

	cur_basic_pos = basic_query_ans;					//设置为信息链的初始位置
	cur_recruit_pos = recruit_query_ans;

	//显示初始页码 格式如 1/10
	right_pos = page_pos;														//根据页码的中心位置计算/的位置
	WriteConsoleOutputCharacter(Handle_Out, "/", 1, page_pos, &ul);				//将/显示到屏幕上
	right_pos.X++;																//计算输出总页数的起始位置
	WriteConsoleOutputCharacter(Handle_Out, temp, strlen(temp), right_pos, &ul);//输出总页数
	sprintf(temp, "%d", count);													//将当前页数字转换成字符串存到temp数组里面
	right_pos.X = right_pos.X - 1 - strlen(temp);								//计算当前页数的起始位置
	WriteConsoleOutputCharacter(Handle_Out, temp, strlen(temp), right_pos, &ul);//输出当前页数

	if (basic_query_ans != NULL)												//如果基本信息查询结果不为空 说明要输出基本信息
	{
		DealBasicInputInfo(cur_basic_pos, 5, 1, space_num, cur_char_num);		//那么先显示第一条基本信息
	}
	else																		//否则说明要显示招生信息查询结果
	{
		DealRecruitInputInfo(cur_recruit_pos, 5, 1, space_num, cur_char_num);	//那么先显示第一条招生信息
	}


	while (command != 5)											//如果不是按了确认键
	{
		if (basic_query_ans != NULL)								//如果要显示基本信息查询结果
		{
			if (command == 6 && cur_basic_pos->prev != NULL)		//如果按了上一页 并且当前节点前面还有节点 那么就翻页
			{
				count--;											//页数减一
				cur_basic_pos = cur_basic_pos->prev;				//当前节点变为前一个节点
			}
			else if (command == 7 && cur_basic_pos->next != NULL)	//如果按了下一页 并且之后还有不为空的节点 说明之后还有页数
			{
				count++;											//页数加一
				cur_basic_pos = cur_basic_pos->next;				//当前节点为后一个节点
			}
			else													//否则为第一次进入循环 那么直接获取鼠标键盘命令
			{
				TagHotArea(0);										//首先取消标记
				command = DealIntput(cur_area, space_num, cur_char_num);	//获取鼠标键盘命令
				continue;											//进入下一次循环处理
			}
		}
		else														//如果要显示招生信息查询结果
		{
			if (command == 6 && cur_recruit_pos->prev != NULL)		//如果按了上一页 并且当前节点前面还有节点 那么就翻页
			{
				count--;											//页数减一
				cur_recruit_pos = cur_recruit_pos->prev;			//当前节点变为前一个节点
			}
			else if (command == 7 && cur_recruit_pos->next != NULL)	//如果按了下一页 并且之后还有不为空的节点 说明之后还有页数
			{
				count++;											//页数加一
				cur_recruit_pos = cur_recruit_pos->next;			//当前节点为后一个节点
			}
			else													//否则为第一次进入循环 那么直接获取鼠标键盘命令
			{
				TagHotArea(0);										//首先取消标记
				command = DealIntput(cur_area, space_num, cur_char_num);	//获取鼠标键盘命令
				continue;											//进入下一次循环处理
			}
		}
		for (int i = 0; i < cur_area->no - cur_area->bottom_no; i++)//先将原来的信息用空格覆盖 除去
		{
			pos.X = cur_area->pArea[i].Left;
			pos.Y = cur_area->pArea[i].Top;
			FillConsoleOutputCharacter(Handle_Out, ' ', space_num[i], pos, &ul);
		}

		//与之前同理 根据页码的中心 计算位置 输出最新的页码 
		sprintf(temp, "%d", count);
		right_pos.X = page_pos.X - strlen(temp);
		WriteConsoleOutputCharacter(Handle_Out, temp, strlen(temp), right_pos, &ul);
		right_pos.X = page_pos.X - strlen(temp) - 1;
		WriteConsoleOutputCharacter(Handle_Out, "-", 1, right_pos, &ul);	//将翻页导致的位数减少时高位未被覆盖的字符用分割线覆盖
		if (basic_query_ans != NULL)										//显示新一页的信息
		{
			DealBasicInputInfo(cur_basic_pos, 5, 1, space_num, cur_char_num);
		}
		else
		{
			DealRecruitInputInfo(cur_recruit_pos, 5, 1, space_num, cur_char_num);
		}
		command = DealIntput(top_layer_head->cur_area, space_num, cur_char_num);	//获取新的鼠标键盘命令 
	}

	if (basic_query_ans != NULL)					//根据传进来的指针 是否为空 释放查询信息占用的内存空间
	{
		FreeList(NULL, basic_query_ans, NULL);
	}
	else
	{
		FreeList(NULL, NULL, recruit_query_ans);
	}
	WithdrewPopHot();								//将弹窗 热区弹出
}

/**************************************************
 * 函数名称：PresentStatInfo
 * 函数功能：根据统计的模式不同 展现统计信息 
			将排好序的统计信息展现到屏幕上
 * 输入参数：int 整型变量 mode  表示统计的模式 分五种 按照统计子菜单由上到下编号
			int 整形变量 total 表示一共得到的统计信息数
			COORD *指针类型 write_pos 表示各列信息的起始位置
			RECRUIT *指针类型 stat_ans 根据统计类型得到排好序后的统计结果
 * 输出参数：无
 * 返 回 值：无

 * 调用说明：被PrintStatInfo调用 用于展现统计结果信息
 **************************************************/
void PresentStatInfo(int mode, int total, int column_no, COORD *write_pos, RECRUIT *stat_ans)
{
	int count = 0;				//表示翻页时 需要指针跳转的次数
	int command = 1;			//接收到的鼠标键盘事件命令
	int cur_page = 1;			//当前页数
	int total_page = 0;			//总页数
	char temp[10];				//页数转换成字符时临时存放数据数组

	COORD pos;					//信息输出的位置
	COORD page_pos;				//页码的中间位置 即/的位置
	COORD right_pos;			//根据page_pos中间位置 得到的正确的输出位置
	HOT_AREA *cur_area;			//当前弹窗热区信息
	SMALL_RECT pop_area;		//弹出区域信息
	RECRUIT *cur_recruit_pos;	//当前待展现的招生信息节点


	total_page = (total % 5) == 0 ? total / 5 : total / 5 + 1;	//获取总页数 一页五行数据
	sprintf(temp, "%d", total_page);							//将总页数转换成字符串存入temp
	cur_area = top_layer_head->cur_area;						//获取当前图层热区信息
	pop_area = top_layer_head->pop_area;						//获取当前图层弹出区域信息
	page_pos.Y = top_layer_head->pop_area.Bottom - 2;			//计算页码中间位置坐标
	page_pos.X = (top_layer_head->pop_area.Left + top_layer_head->pop_area.Right) / 2;


	right_pos = page_pos;										//和之前类型情况一样方式 输出页码
	WriteConsoleOutputCharacter(Handle_Out, "/", 1, page_pos, &ul);
	right_pos.X++;
	WriteConsoleOutputCharacter(Handle_Out, temp, strlen(temp), right_pos, &ul);

	cur_recruit_pos = stat_ans;
	do															//先展现一页信息 再接收鼠标键盘事件命令
	{
		if (command != 1)										//如果不是第一次进入循环
		{
			if (command == 6)									//如果命令式上一页
			{
				if (cur_page != 1)								//不是第一页 就计算翻页时 需要指针跳转的次数
				{
					cur_page--;
					count = 5 + min(5, total - cur_page * 5);
					while (count--)								//将指针跳转到上一页第一行的信息节点
					{
						cur_recruit_pos = cur_recruit_pos->prev;
					}
				}
				else continue;
			}
			else if (command == 7)								//如果是下一页
			{
				if (cur_page != total_page)						//不是最后一页 页数++ 当前节点就是下一页第一行的信息节点
				{
					cur_page++;
				}
				else continue;
			}
		}
		for (pos.Y = pop_area.Top + 5; pos.Y < pop_area.Bottom - 2; pos.Y++)		//先用空格将原来信息覆盖掉
		{
			pos.X = pop_area.Left + 2;
			FillConsoleOutputCharacter(Handle_Out, ' ', pop_area.Right - pop_area.Left - 3, pos, &ul);
		}

		write_pos[0].X = pop_area.Left + 3;											//第一列写入位置的横坐标为 居左
		pos.Y = pop_area.Top + 5;													//初始化纵坐标
		for (int i = (cur_page - 1) * 5; i < min(total, 5 * cur_page); i++, pos.Y++)//循环输出五行 不够五行就空出来
		{
			pos.X = pop_area.Left + 2;
			WriteConsoleOutputCharacter(Handle_Out, &"#", strlen(&"#"), pos, &ul);	//输出序号标记
			for (int j = 0; j < column_no; j++)										//根据不同统计模式 将不同列的输出信息存放到temp里面
			{																		//并计算输出位置
				write_pos[j].Y = pos.Y;
				switch (mode)
				{
				case 1: switch (j)
						{
						case 0: sprintf(temp, "%d", i + 1); break;
						case 1: temp[0] = cur_recruit_pos->classes;
								temp[1] = '\0'; break;
						case 2: sprintf(temp, "%d", cur_recruit_pos->enroll_num);
								write_pos[j].X = pop_area.Right - 3 - strlen(temp);
								break;
						}break;
				case 2:
				case 3: switch (j)
						{
						case 0: sprintf(temp, "%d", i + 1);       break;
						case 1: temp[0] = cur_recruit_pos->classes;
								temp[1] = '\0';                   break;
						case 2: strcpy(temp, cur_recruit_pos->no); break;
						case 3: sprintf(temp, "%d", cur_recruit_pos->enroll_num);
								write_pos[j].X = pop_area.Right - 3 - strlen(temp);
								break;
						}break;
				case 4: switch (j)
						{
						case 0: sprintf(temp, "%d", i + 1);       break;
						case 1: temp[0] = cur_recruit_pos->classes;
								temp[1] = '\0';                   break;
						case 2: strcpy(temp, cur_recruit_pos->no); break;
						case 3: sprintf(temp, "%.2f", cur_recruit_pos->high_score);
								break;
						case 4: sprintf(temp, "%.2f", cur_recruit_pos->ad_score);
								write_pos[j].X = pop_area.Right - 3 - strlen(temp);
						}break;
				case 5: switch (j)
						{
						case 0: sprintf(temp, "%d", i + 1);       break;
						case 1: temp[0] = cur_recruit_pos->classes;
								temp[1] = '\0';                   break;
						case 2: strcpy(temp, cur_recruit_pos->no); break;
						case 3: sprintf(temp, "%.2f", cur_recruit_pos->high_score);
								write_pos[j].X = pop_area.Right - 3 - strlen(temp);
								break;
						}break;
				}

				pos = write_pos[j];														
				WriteConsoleOutputCharacter(Handle_Out, temp, strlen(temp), pos, &ul);	//输出信息
			}

			cur_recruit_pos = cur_recruit_pos->next;									//对下一个节点进行处理
		}

		//输出新的页码
		sprintf(temp, "%d", cur_page);	
		right_pos.X = page_pos.X - strlen(temp);
		WriteConsoleOutputCharacter(Handle_Out, temp, strlen(temp), right_pos, &ul);
		right_pos.X = page_pos.X - strlen(temp) - 1;
		WriteConsoleOutputCharacter(Handle_Out, "-", 1, right_pos, &ul);

	} while ((command = DealIntput(top_layer_head->cur_area, NULL, NULL)) != 5);		//获取鼠标键盘事件


	FreeList(NULL, NULL, stat_ans);														//释放统计信息链
	WithdrewPopHot();																	//弹出当前的图层 窗口
}

/**************************************************
 * 函数名称：PrintStatInfo
 * 函数功能：打印统计信息 根据不同的统计模式 弹出不同的窗口
			将招生信息链构建起来 并对其排序 
			交给PresentStatInfo函数进行处理 展现统计信息
 * 输入参数：int 整型变量 mode 统计模式 分五种 按照统计子菜单由上到下编号
			int *整型指针 present_type 展示信息窗口各个密文的热区类型
			int 整型变量 column_no 表示展示信息的列数 
			char **二维字符指针 present_info 表示展窗口布局&信息密文 
			COORD *类型 pos 表示各个列信息的输出位置信息

 * 输出参数：无
 * 返 回 值：无

 * 调用说明：可被所有统计信息的功能函数调用 整合所有的统计模式
			更高效与模块化
 **************************************************/
void PrintStatInfo(int mode, int *present_type, int column_no, char **present_info, COORD *pos)
{
	int stat_no = 0;								//统计信息链节点个数 用于截取10个信息点
	int total = 0;									//统计信息链节点个数
	int command;									//接收鼠标键盘事件
	int *cur_char_num;								//当前输入框的字符个数
	int space_num[] = { 1,5,8,4 };					//统计时 输入要统计的信息（年份）
	int hot_type[] = { 0,0,0,2,0,4,5 };				//输入统计信息的窗口 密文 各个信息的热区类型
	COORD title_pos;								//标题中需要输出年份的位置
	RECRUIT *input_info = NULL;						//用户输入的信息
	RECRUIT *stat_ans = NULL;						//统计结果信息
	RECRUIT *cur_node;								//当前的节点
	char *text_info[] = { "&请输入统计年份","\n",		//输入信息 密文
						  "年份  ","-h",
						  "",
						  "确定",
						  "取消"};

	cur_char_num = (int *)calloc(4, sizeof(int));	//分配内存
	if (mode != 3)									//根据统计模式判断要不要输入年份
	{
		command = InitHotArea(1, 2, 7, 3, 0, cur_char_num + 3, space_num + 3, hot_type, text_info);
		input_info = DealRecruitInputInfo(input_info, 8, command, space_num + 3, cur_char_num + 3);
	}
	if (mode == 3 || input_info != NULL)			//根据模式得到不同的统计信息链 如有的需要学校录取分数线信息 有的需要人数信息
	{
		stat_ans = StatListCreate(mode, &total, input_info);	//根据输入的信息创建统计链表
		if (mode == 3 || mode == 4 || mode == 5)				//有的统计信息只需要前10个
		{
			cur_node = stat_ans->next;
			while (cur_node != NULL)
			{
				stat_no++;
				if (stat_no == 10)
				{
					cur_node->next->next = NULL;
					total = 10;
					break;
				}
				cur_node = cur_node->next;
			}
		}
		if (total)												//如果统计信息非空 就输出
		{
			InitHotArea(0, 3, 12 + column_no, 3, 0, cur_char_num, space_num, present_type, present_info);	//先弹出窗口
			if (mode != 3)										//根据模式决定是否在标题的指定位置加上年份
			{
				title_pos.Y = top_layer_head->pop_area.Top + 1;
				title_pos.X = top_layer_head->pop_area.Left + (mode == 2 ? 4 : 3);;
				WriteConsoleOutputCharacter(Handle_Out, input_info->year, strlen(input_info->year), title_pos, &ul);
			}
			stat_ans = StatListSort(mode, stat_ans);			//对统计结果的信息链按照不同的模式进行排序 

			for (int i = 1; i < column_no; i++)					//计算左端加上窗口弹出的左端坐标 得到相对于整个主界面的坐标
			{
				pos[i].X += top_layer_head->pop_area.Left;
			}
			PresentStatInfo(mode, total, column_no, pos, stat_ans);		//展现统计结果
		}
		else
		{
			ErrorMention(9);									//否则说明 不存在该年份的信息 那么提示响应信息
		}
	}
}

/**************************************************
 * 函数名称：SaveData
 * 函数功能：保存数据 到文件中
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL SaveData(void)
{
	FILE *output_info;								//文件指针 指向输出文件
	TYPE *cur_type_pos;								//要存入文件的分类信息
	BASIC *cur_basic_pos;							//要存入文件的基本信息
	RECRUIT *cur_recruit_pos;						//要存入文件的招生信息

	output_info = fopen(type_data_filename, "wb");	//输出分类信息 
	cur_type_pos = head;
	while (cur_type_pos != NULL)					//循环输出 直到碰到链表尾部 一次输出一条
	{
		fwrite(cur_type_pos,sizeof(TYPE), 1 , output_info);
		cur_type_pos = cur_type_pos->next;
	}
	fclose(output_info);

	output_info = fopen(basic_data_filename, "wb");	//输出基本信息 
	cur_type_pos = head;
	while (cur_type_pos != NULL)					//循环输出 直到碰到链表尾部 一次输出一条
	{
		cur_basic_pos = cur_type_pos->nextB;
		while (cur_basic_pos != NULL)
		{
			fwrite(cur_basic_pos, sizeof(BASIC), 1, output_info);
			cur_basic_pos = cur_basic_pos->next;
		}
		cur_type_pos = cur_type_pos->next;
	}
	fclose(output_info);

	output_info = fopen(recruit_data_filename, "wb");//输出招生信息 
	cur_type_pos = head;
	while (cur_type_pos != NULL)					//循环输出 直到碰到链表尾部 一次输出一条
	{
		cur_basic_pos = cur_type_pos->nextB;	
		while (cur_basic_pos != NULL)
		{
			cur_recruit_pos = cur_basic_pos->nextR;
			while (cur_recruit_pos != NULL)
			{
				fwrite(cur_recruit_pos, sizeof(RECRUIT), 1, output_info);
				cur_recruit_pos = cur_recruit_pos->next;
			}
			cur_basic_pos = cur_basic_pos->next;
		}
		cur_type_pos = cur_type_pos->next;
	}
	fclose(output_info);

	ErrorMention(10);								//显示保存的信息提示框

	return TRUE;		
}

/**************************************************
 * 函数名称：BackData
 * 函数功能：备份数据 到文件中
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL BackData(void)
{
	if (back_no == 5) {					//如果备份文件数量等于 五个 达到上限那么就输出对应提示框
		ErrorMention(12);
		return TRUE;
	}
	unsigned long type_no = 0;			//分类信息节点个数
	unsigned long basic_no = 0;			//基本信息节点个数
	unsigned long recruit_no = 0;		//招生信息节点个数
    struct tm *right_time;				//时间结构体 获取当前的时间 相对与1900年 
	BACK_INFO *new_back;				//创建新的备份列表信息链表节点
	BACK_INFO *cur_back;				//当前的备份信息列表链表节点
	TYPE *cur_type_pos = head;			//分类信息链表头
	BASIC *cur_basic_pos;				//当前基本信息节点
	RECRUIT *cur_recruit_pos;			//当前的招生信息节点
	time_t cur_time;					//当前的时间
	FILE *back_info;					//备份文件指针

	time(&cur_time);					//获取当前时间 并根据时间 得出备份文件名
	right_time = localtime(&cur_time);
	right_time->tm_year += 1900;
	new_back = (BACK_INFO *)calloc(1, sizeof(BACK_INFO));
	sprintf(new_back->filename, "%d年%2d月%2d日%2d时%2d分的备份", right_time->tm_year, right_time->tm_mon, right_time->tm_mday,right_time->tm_hour,right_time->tm_min);

	back_info=fopen(new_back->filename,"wb");	//创建备份文件
	
	while (cur_type_pos != NULL)				//统计各类节点个数
	{
		type_no++;
		cur_basic_pos = cur_type_pos->nextB;
		while (cur_basic_pos != NULL)
		{
			basic_no++;
			cur_recruit_pos = cur_basic_pos->nextR;
			while (cur_recruit_pos != NULL)
			{
				recruit_no++;
				cur_recruit_pos = cur_recruit_pos->next;
			}
			cur_basic_pos = cur_basic_pos->next;
		}
		cur_type_pos = cur_type_pos->next;
	}

	fwrite(&type_no   , sizeof(unsigned long), 1, back_info);	//写入分类信息节点个数
	fwrite(&basic_no  , sizeof(unsigned long), 1, back_info);	//写入基本信息节点个数
	fwrite(&recruit_no, sizeof(unsigned long), 1, back_info);	//写入招生信息节点个数
	
	cur_type_pos = head;										//依次存放各个分类信息
	while (cur_type_pos != NULL)
	{
		fwrite(cur_type_pos, sizeof(TYPE), 1, back_info);
		cur_type_pos = cur_type_pos->next;
	}

	cur_type_pos = head;
	while (cur_type_pos != NULL)								//依次存放各个基本信息
	{
		cur_basic_pos = cur_type_pos->nextB;
		while (cur_basic_pos != NULL)
		{
			fwrite(cur_basic_pos, sizeof(BASIC), 1, back_info);
			cur_basic_pos = cur_basic_pos->next;
		}
		cur_type_pos = cur_type_pos->next;
	}

	cur_type_pos = head;
	while (cur_type_pos != NULL)								//依次存放各个招生信息
	{
		cur_basic_pos = cur_type_pos->nextB;
		while (cur_basic_pos != NULL)
		{
			cur_recruit_pos = cur_basic_pos->nextR;
			while (cur_recruit_pos != NULL)
			{
				fwrite(cur_recruit_pos, sizeof(RECRUIT), 1, back_info);
				cur_recruit_pos = cur_recruit_pos->next;
			}
			cur_basic_pos = cur_basic_pos->next;
		}
		cur_type_pos = cur_type_pos->next;
	}
	fclose(back_info);

	back_no++;													//更新 备份列表信息 链表
	new_back->next = back_list_head;
	back_list_head = new_back;

	back_info = fopen(back_list_filename, "wb");				//将新的备份信息列表信息 存放进文件保存起来
	fwrite(&back_no, sizeof(unsigned long), 1, back_info);
	cur_back = back_list_head;
	for (int i = 0; i < back_no; i++)
	{
		fwrite(cur_back, sizeof(BACK_INFO), 1, back_info);
		cur_back = cur_back->next;
	}
	fclose(back_info);


	ErrorMention(11);											//备份信息保存提示框
	return TRUE;
}

/**************************************************
 * 函数名称：RecoveryData
 * 函数功能：从备份文件中恢复备份数据 
			（可以让用户选择 从哪个 备份文件中恢复数据）
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL RecoveryData(void)
{
	int command;									//接收鼠标键盘命令
	int *hot_type;									//窗口的热区类型
	unsigned long type_no;							//备份数据的分类信息节点个数
	unsigned long basic_no;							//备份数据的基本信息节点个数
	unsigned long recruit_no;						//备份数据的招生信息节点个数
	TYPE type_info, *cur_type, *pre_type = NULL;	//用于构建新的数据链的分类信息节点 
	BASIC basic_info, *cur_basic;					//用于构建新的数据链的基本信息节点 
	RECRUIT recruit_info, *cur_recruit;				//用于构建新的数据链的招生信息节点 
	BACK_INFO *cur_back=back_list_head;				//备份信息
	FILE *input_info;
	char *text_info[10] = {"&备份列表","\n"};		//备份选择窗口的密文

	hot_type = (int *)calloc(10, sizeof(int));		//分配内存空间
	for (int i = 0; i < back_no; i++)				//计算各类密文的热区类型 并得到密文
	{
		hot_type[i + 2] = 1;
		text_info[i + 2] = (char *)calloc(22, sizeof(char));
		strcpy(text_info[i + 2], cur_back->filename);
		cur_back = cur_back->next;
	}
	hot_type[back_no + 3] = 5;						//计算按钮密文的热区类型 并得到密文
	text_info[back_no + 2] = (char *)calloc(22, sizeof(char)); strcpy(text_info[back_no + 2], &"");
	text_info[back_no + 3] = (char *)calloc(22, sizeof(char)); strcpy(text_info[back_no + 3], &"取消");
	
	command = InitHotArea(1, 1, back_no + 4, back_no + 1, 20, NULL, NULL, hot_type, text_info);	//弹出备份选择窗口 并得到鼠标键盘命令
	WithdrewPopHot();								//弹出窗口
	if (command)									//根据命令来判断是否恢复数据
	{
		input_info = fopen(text_info[command + 1], "rb");	//恢复指定选项的数据
		if (input_info != NULL)
		{
			fread(&type_no   , sizeof(unsigned long), 1, input_info);	//从文件中获取备份数据的分类信息节点个数
			fread(&basic_no  , sizeof(unsigned long), 1, input_info);	//从文件中获取备份数据的基本信息节点个数
			fread(&recruit_no, sizeof(unsigned long), 1, input_info);	//从文件中获取备份数据的招生信息节点个数
			for (int i = 0; i < type_no; i++)							//逐条读入分类信息 创建链表 更新指针域
			{
				fread(&type_info, sizeof(TYPE), 1, input_info);		
				cur_type = (TYPE *)calloc(1, sizeof(TYPE));
				*cur_type = type_info;
				cur_type->nextB = NULL;
				cur_type->next = pre_type;
				pre_type = cur_type;
			}
			head = pre_type;											//更新总的链表头

			for (int i = 0; i < basic_no; i++)							//逐条读入基本信息 创建链表 更新指针域
			{
				fread(&basic_info, sizeof(BASIC), 1, input_info);
				cur_type = FindTypePoint(basic_info.classes);
				if (cur_type != NULL)
				{
					cur_basic = (BASIC *)calloc(1, sizeof(BASIC));
					*cur_basic = basic_info;
					cur_basic->nextR = NULL;
					cur_basic->next = cur_type->nextB;
					cur_type->nextB = cur_basic;
				}
			}

			for (int i = 0; i < recruit_no; i++)						//逐条读入招生信息 创建链表 更新指针域
			{
				fread(&recruit_info, sizeof(RECRUIT), 1, input_info);
				cur_basic = FindBasicPoint(recruit_info.classes, recruit_info.no);
				if (cur_basic != NULL)
				{
					cur_recruit = (RECRUIT *)calloc(1, sizeof(RECRUIT));
					*cur_recruit = recruit_info;
					cur_recruit->next = cur_basic->nextR;
					cur_basic->nextR = cur_recruit;
				}
			}
			fclose(input_info);
			ErrorMention(13);											//备份消息提示
		}
		else
		{
			ErrorMention(14);											//备份消息提示
		}
	}
	return TRUE;
}

/**************************************************
 * 函数名称：DeleteBack
 * 函数功能：删除备份文件 方便用户对于备份进行管理
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL DeleteBack(void)
{	
	int command;						//鼠标键盘事件命令
	int *hot_type;						//选择删除备份选项窗口 的密文热区类型
	BACK_INFO *pre_back;				//用于更新备份列表信息链表的节点
	BACK_INFO *cur_back = back_list_head;
	FILE *back_info;
	char *text_info[10] = { "&请选择要删除的备份","\n" };	//备份信息密文

	hot_type = (int *)calloc(10, sizeof(int));	//分配内存空间
	for (int i = 0; i < back_no; i++)			//计算密文 以及 各个密文对应的热区类型
	{
		hot_type[i + 2] = 1;
		text_info[i + 2] = (char *)calloc(22, sizeof(char));
		strcpy(text_info[i + 2], cur_back->filename);
		cur_back = cur_back->next;
	}
	hot_type[back_no + 3] = 5;					//计算按钮的密文 以及热区类型
	text_info[back_no + 2] = (char *)calloc(22, sizeof(char)); strcpy(text_info[back_no + 2], &"");
	text_info[back_no + 3] = (char *)calloc(22, sizeof(char)); strcpy(text_info[back_no + 3], &"取消");

	command = InitHotArea(1, 1, back_no + 4, back_no + 1, 20, NULL, NULL, hot_type, text_info);	//弹出删除备份选择窗口 获取鼠标键盘命令
	WithdrewPopHot();							//弹出窗口
	if (command)
	{
		if (!remove(text_info[command + 1]))	//删除备份文件 成功返回0
		{
			back_no--;							//更新备份列表信息链
			cur_back = back_list_head;
			pre_back = back_list_head;
			if (command == 1)
			{
				back_list_head = cur_back->next;
			}
			else
			{
				cur_back = cur_back->next;
				for (int i = 1; i < back_no; i++)
				{
					if (i + 1 == command)
					{
						pre_back->next = cur_back->next;
						break;
					}
					cur_back = cur_back->next;
					pre_back = pre_back->next;
				}
			}
			free(cur_back);						//释放删除的节点
			ErrorMention(15);					//消息提示框
		}
		else
		{
			ErrorMention(16);					//删除失败消息提示框
		}

		back_info = fopen(back_list_filename, "wb");			//将更新的备份列表信息写入文件
		fwrite(&back_no, sizeof(unsigned long), 1, back_info);
		cur_back = back_list_head;
		for (int i = 0; i < back_no; i++)
		{
			fwrite(cur_back, sizeof(BACK_INFO), 1, back_info);
			cur_back = cur_back->next;
		}
		fclose(back_info);
	}
	return TRUE;
}

/**************************************************
 * 函数名称：ExitSys
 * 函数功能：退出系统
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL ExitSys(void)
{
	int command;									//鼠标键盘事件命令
	int hot_type[] = { 0,0,0,4,5 };					//确认窗口各个密文的热区类型
	char *text_info[] = { "&确定退出系统？","\n",		//确认窗口密文 （代表显示信息 以及 格式）
		                  "",
		                  "确定",
		                  "取消"
	};
	command = InitHotArea(1, 2, 5, 2, 0, NULL, NULL, hot_type, text_info);	//弹出确认窗口 并获取鼠标键盘事件命令
	WithdrewPopHot();								//弹出窗口
	if (command == 1)								//根据返回值来判断是否退出系统
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}


/**************************************************
 * 函数名称：MaintainType
 * 函数功能：维护学校分类信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL MaintainType(void)
{
	int command;								//接收鼠标键盘事件命令
	int hot_type[] = { 1,1,1,0,5 };				//弹出窗口 图层的各个热区 文字条的 热区类型
	char *text_info[] = { "高考分类信息录入",		//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息
		                  "高考分类信息修改",
					      "高考分类信息删除",
						  "",
						  "取消"
	};
	command = InitHotArea(1, 1, 5, 4, 0, NULL,NULL,hot_type, text_info);	//弹出窗口 并得到鼠标键盘事件命令
	WithdrewPopHot();							//弹出窗口
	switch (command)							//根据用户点击的不同选项来决定调用对应的功能函数
	{
		case 1:InsertType(); break;
		case 2:ModifyType(); break;
		case 3:DeleteType(); break;
	}

	return TRUE;
}

/**************************************************
 * 函数名称：MaintainBasic
 * 函数功能：维护学校基本信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL MaintainBasic(void)
{
	int command;								//接收鼠标键盘事件命令
	int hot_type[] = { 1,1,1,0,5 };				//弹出窗口 图层的各个热区 文字条的 热区类型
	char *text_info[] = { "高考基本信息录入",		//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文
						  "高考基本信息修改",
						  "高考基本信息删除",
						  "",
						  "取消"
	};
	command = InitHotArea(1, 1, 5, 4, 0, NULL, NULL, hot_type, text_info);	//弹出窗口 并得到鼠标键盘事件命令
	WithdrewPopHot();							//弹出窗口
	switch (command)							//根据用户点击的不同选项来决定调用对应的功能函数				
	{
		case 1:InsertBasic(); break;
		case 2:ModifyBasic(); break;
		case 3:DeleteBasic(); break;
	}

	return TRUE;
}

/**************************************************
 * 函数名称：MaintainRecruit
 * 函数功能：维护学校招生信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL MaintainRecruit()
{
	int command;									//接收鼠标键盘事件命令
	int hot_type[] = { 1,1,1,0,5 };					//弹出窗口 图层的各个热区 文字条的 热区类型
	char *text_info[] = { "高考招生基本信息录入",		//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文	
		                  "高考招生基本信息修改",		
		                  "高考招生基本信息删除",
		                  "",
		                  "取消"
	                    };
	command = InitHotArea(1, 1, 5, 4, 0, NULL, NULL, hot_type, text_info);		//弹出窗口 并得到鼠标键盘事件命令
	WithdrewPopHot();								//弹出窗口
	switch (command)								//根据用户点击的不同选项来决定调用对应的功能函数
	{
	    case 1:InsertRecruit(); break;
		case 2:ModifyRecruit(); break;
		case 3:DeleteRecruit(); break;
	}

	return TRUE;
}


/**************************************************
 * 函数名称：QueryType
 * 函数功能：查询分类信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL QueryType(void)
{
	int command;								//接收鼠标键盘事件命令
	int hot_type[] = { 1,0,5 };					//弹出窗口 图层的各个热区 文字条的 热区类型
	char *text_info[] = { "按照学校类别查询",		//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文
		                  "",
	                      "取消"
	};
	command = InitHotArea(1, 1, 3, 2, 0, NULL, NULL, hot_type, text_info);	//弹出窗口 并得到鼠标键盘事件命令
	WithdrewPopHot();							//弹出窗口
	switch (command)							//根据用户点击的不同选项来决定调用对应的功能函数
	{		
	case 1:QueryType_Classes();break;			
	default:break;
	}

	return TRUE;
}

/**************************************************
 * 函数名称：QueryBasic
 * 函数功能：查询基本信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL QueryBasic(void)
{
	int command;								//接收鼠标键盘事件命令
	int hot_type[] = { 1,1,0,5 };				//弹出窗口 图层的各个热区 文字条的 热区类型
	char *text_info[] = { "按照学校编号查询",		//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文
		                  "按照学校名称查询",
						  "",
						  "取消"
	};
	command = InitHotArea(1, 1, 4, 3, 0, NULL, NULL, hot_type, text_info);	//弹出窗口 并得到鼠标键盘事件命令
	WithdrewPopHot();							//弹出窗口
	switch (command)							//根据用户点击的不同选项来决定调用对应的功能函数
	{
	case 1:QueryBasic_No(); break;
	case 2:QueryBasic_Name(); break;
	default:break;
	}

	return TRUE;
}

/**************************************************
 * 函数名称：QueryRecruit
 * 函数功能：查询招生信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL QueryRecruit(void)
{
	int command;									//接收鼠标键盘事件命令
	int hot_type[] = { 1,1,0,5 };					//弹出窗口 图层的各个热区 文字条的 热区类型
	char *text_info[] = { "按照学校编号和年份查询",	//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文
						  "按照录取分数线范围查询",
						  "",
						  "取消"
	};
	command = InitHotArea(1, 1, 4, 3, 0, NULL, NULL, hot_type, text_info);	//弹出窗口 并得到鼠标键盘事件命令
	WithdrewPopHot();								//弹出窗口
	switch (command)								//根据用户点击的不同选项来决定调用对应的功能函数
	{
	case 1:QueryRecruit_NoYear(); break;
	case 2:QueryRecruit_Score(); break;
	default:break;
	}

	return TRUE;
}


/**************************************************
 * 函数名称：StatTypePeople
 * 函数功能：按年度统计各类高校实录人数
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL StatTypePeople(void)
{
	COORD *pos = (COORD *)calloc(3, sizeof(COORD));				//每一列信息的输出位置信息
	int present_type[] = { 0,0,0,0,0,0,0,0,0,0,0,0,6,5,7 };		//弹出窗口 图层的各个热区 文字条的 热区类型
	char *present_info[] = { "&    年各类高校实际录取学生人数统计结果","\n",		//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文
		                     "# ","-          高校类别","-      实际录取人数","",
							 "", "", "", "", "","",
		                     "<--",
							 "确定",
		                     "-->"
						     };

	pos[1].X =18;												//初始化中间列的位置信息 
	PrintStatInfo(1, present_type, 3, present_info, pos);		//调用函数展现统计信息

	return TRUE;
}

/**************************************************
 * 函数名称：StatAllPeople
 * 函数功能：按年度统计高校实录人数
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL StatAllPeople(void)
{
	COORD *pos = (COORD *)calloc(4, sizeof(COORD));				//每一列信息的输出位置信息
	int present_type[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,6,5,7 };	//弹出窗口 图层的各个热区 文字条的 热区类型
	char *present_info[] = { "&    年各高校实际录取学生人数统计结果","\n",				//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文
							 "# ","-  高校类别","-  高校编号","-  实际录取人数","",
							 "", "", "", "", "","",
							 "<--",
							 "确定",
							 "-->"
	};

	pos[1].X = 9;												//初始化中间列的位置信息 
	pos[2].X = 19;
	PrintStatInfo(2, present_type, 4, present_info, pos);		//调用函数展现统计信息
	return TRUE;
}

/**************************************************
 * 函数名称：StatEnrollNum
 * 函数功能：统计历年录取人数最多高校
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL StatEnrollNum(void)
{
	COORD *pos = (COORD *)calloc(4, sizeof(COORD));				//每一列信息的输出位置信息
	int present_type[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,6,5,7 };	//弹出窗口 图层的各个热区 文字条的 热区类型
	char *present_info[] = { "&历年来录取人数最多的10所高校","\n",						//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文
							"# ","-  高校类别","-  高校编号","-  历年录取人数","",
							"", "", "", "", "","",
							"<--",
							"确定",
							"-->"
	};

	pos[1].X = 9;												//初始化中间列的位置信息 
	pos[2].X = 19;
	PrintStatInfo(3, present_type, 4, present_info, pos);		//调用函数展现统计信息
	return TRUE;
}

/**************************************************
 * 函数名称：StatHighScore
 * 函数功能：统计录取最高分高出分数线最多的10所中学
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL StatHighScore(void)
{
	COORD *pos;													//每一列信息的输出位置信息
	int present_type[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,5,7 };	//弹出窗口 图层的各个热区 文字条的 热区类型
	char *present_info[] = { "&    年录取最高分高出录取分数线最多的10所中学","\n",			//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文
							 "# ","-  高校类别","-  高校编号","-  最高分","- 录取分数线","",
						 	 "", "", "", "", "","",
							 "<--",
							 "确定",
							 "-->"
	};

	pos = (COORD *)calloc(5, sizeof(COORD));
	pos[1].X = 9;												//初始化中间列的位置信息 
	pos[2].X = 18;
	pos[3].X = 28;
	PrintStatInfo(4, present_type, 5, present_info, pos);		//调用函数展现统计信息
	return TRUE;
}

/**************************************************
 * 函数名称：StatHighIndex
 * 函数功能：按年度统计录取分数线最高的10所中学
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL StatHighIndex(void)
{
	COORD *pos = (COORD *)calloc(5, sizeof(COORD));				//每一列信息的输出位置信息
	int present_type[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,6,5,7 };	//弹出窗口 图层的各个热区 文字条的 热区类型
	char *present_info[] = { "&    年录取最高分高出录取分数线最多的10所中学","\n",			//弹出窗口 图层的各个热区 文字条的 格式 以及 显示信息 即密文
							 "# ","-  高校类别","-    高校编号","-        录取分数线","",
							 "", "", "", "", "","",
							 "<--",
							 "确定",
							 "-->"
	};

	pos[1].X = 9;												//初始化中间列的位置信息 
	pos[2].X = 20;
	PrintStatInfo(5, present_type, 4, present_info, pos);		//调用函数展现统计信息
	return TRUE;
}


/**************************************************
 * 函数名称：HelpSys
 * 函数功能：展现帮助信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL HelpSys(void)
{
	ErrorMention(17);		//调用消息提示函数 直接显示消息
	return TRUE;
}

/**************************************************
 * 函数名称：AboutSys
 * 函数功能：展现关于信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
BOOL AboutSys(void)
{
	ErrorMention(18);		//调用消息提示函数 直接显示消息
	return TRUE;
}

/**************************************************
 * 函数名称：InsertType
 * 函数功能：数据维护-插入分类信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void InsertType()
{
	int command;								//接收鼠标键盘命令
	int *cur_char_num;							//各个输入框当前字符数
	int space_num[] = { 1 };					//各个输入框最大字符数
	int hot_type[] = { 0,2,0,4,5 };				//各个密文对应的热区类型
	TYPE *input_info = NULL;					//用于链表操作的分类信息节点
	char *text_info[] = { "学校类别  ","-h",		//弹出窗口 文字条 热区的 显示信息以及布局格式 即密文
						  "",
						  "确定",
						  "取消"
	};

	cur_char_num = (int *)calloc(1, sizeof(int));//分配内存空间
	command = InitHotArea(1, 2, 5, 3, 20, cur_char_num, space_num,hot_type, text_info);	//弹出窗口 并接收鼠标键盘事件
	input_info = DealTypeInputInfo(input_info, 1, command, space_num, cur_char_num);	//处理各个输入框输入的信息
	if (input_info != NULL)						//如果获取到了输入信息
	{
		input_info->next = head;				//那么进行插入操作
		head = input_info;
	}
}

/**************************************************
 * 函数名称：ModifyType
 * 函数功能：数据维护-修改分类信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void ModifyType()
{
	int command;											//接收鼠标键盘命令
	int *cur_char_num;										//各个输入框当前字符数
	int hot_type[] = { 0,0,0,2,0,4,5 };						//各个输入框最大字符数
	int space_num[] = { 1 };								//各个密文对应的热区类型
	HOT_AREA *cur_area;										//当前弹窗的热区信息
	TYPE *input_info = NULL;								//用于链表操作的一系列指针
	TYPE *new_info = NULL;
	TYPE *cur_type_point;
	BASIC *cur_basic_point;
	RECRUIT *cur_recruit_point;
	char *text_info[] = { "&请输入待修改的学校类别","\n",		//待修改节点 信息录入窗口 密文
						  "学校类别  ","-h",
						  "",
						  "确定",
						  "取消"
	};
	char *modify_info[] = { "&请输入待修改的信息","\n",		//修改对应节点 窗口 密文
						    "学校类别  ","-h",
						    "",
						    "确定",
						    "取消"
	};

	cur_char_num = (int *)calloc(1, sizeof(int));			//分配内存空间
	command = InitHotArea(1, 2, 7, 3, 20, cur_char_num, space_num, hot_type, text_info);	//弹出窗口 并接收鼠标键盘事件
	input_info = DealTypeInputInfo(input_info, 2, command, space_num, cur_char_num);		//处理各个输入框输入的信息

	if (input_info != NULL)									//如果获取到了待修改节点信息
	{
		InitHotArea(0, 2, 7, 3, 18, cur_char_num, space_num, hot_type, modify_info);		//弹出修改窗口 不接收鼠标键盘事件
		DealTypeInputInfo(input_info, 5, command, space_num, cur_char_num);					//展示原来信息

		cur_area = top_layer_head->cur_area;												//获取当前窗口热区信息
		command = DealIntput(cur_area, space_num, cur_char_num);							//处理鼠标键盘事件
		new_info = DealTypeInputInfo(new_info, 3, command, space_num, cur_char_num);		//获取修改后的信息 
		if (new_info != NULL)																//如果 成功获取到修改后的信息
		{
			cur_type_point = FindTypePoint(input_info->classes);							//寻找待修改节点
			cur_type_point->classes = new_info->classes;									//修改分类节点信息
			cur_basic_point = cur_type_point->nextB;
			while (cur_basic_point != NULL)													//循环修改该分类下 基本信息以及招生信息的 分类
			{
				cur_basic_point->classes = new_info->classes;
				cur_recruit_point = cur_basic_point->nextR;
				while (cur_recruit_point != NULL)
				{
					cur_recruit_point->classes = new_info->classes;
					cur_recruit_point = cur_recruit_point->next;
				}
				cur_basic_point = cur_basic_point->next;
			}
		}
	}
}

/**************************************************
 * 函数名称：DeleteType
 * 函数功能：数据维护-删除分类信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void DeleteType()
{
	int command;											//接收鼠标键盘命令
	int *cur_char_num;										//各个输入框当前字符数
	int hot_type[] = { 0,0,0,2,0,4,5 };						//各个密文对应的热区类型
	int space_num[] = { 1 };								//各个输入框最大字符数
	TYPE *input_info = NULL;								//用于链表操作的分类信息节点
	TYPE *right_pos;
	TYPE *pre_pos;
	char *text_info[] = { "&请输入待删除的学校类别","\n",		//弹出窗口 文字条 热区的 显示信息以及布局格式 即密文
		                  "学校类别  ","-h",
						  "",
						  "确定",
						  "取消"
	};

	cur_char_num = (int *)calloc(1, sizeof(int));			//分配内存
	command = InitHotArea(1, 2, 7, 3, 20, cur_char_num, space_num, hot_type, text_info);	//弹出窗口 并接收鼠标键盘事件
	input_info = DealTypeInputInfo(input_info, 4, command, space_num, cur_char_num);		//处理各个输入框输入的信息

	if (input_info != NULL)									//如果获取到了输入信息
	{
		right_pos = FindTypePoint(input_info->classes);		//那么进行删除操作
		if (right_pos != NULL)
		{
			pre_pos = head;
			if (pre_pos->classes == right_pos->classes)
			{
				head = head->next;
			}
			else
			{
				while (pre_pos->next->classes != input_info->classes)
				{
					pre_pos = pre_pos->next;
				}
				pre_pos->next = input_info->next;
			}
			FreeList(right_pos, NULL, NULL);				//释放掉被删除的节点
		}
	}
}


/**************************************************
 * 函数名称：InsertBasic
 * 函数功能：数据维护-插入基本信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void InsertBasic()
{
	int command;													//接收鼠标键盘命令
	int *cur_char_num;												//各个输入框当前字符数
	int space_num[] = { 1,11,29,49,19,19 };							//各个输入框最大字符数
	int hot_type[] = { 0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,4,5 };	//各个密文对应的热区类型
	TYPE *right_pos;												//用于链表操作的分各类信息节点
	BASIC *input_info = NULL;
	char *text_info[] = { "学校类别 ","-h","\n",						//弹出窗口 文字条 热区的 显示信息以及布局格式 即密文
						  "学校编号 ","-h","\n",
						  "学校名称 ","-h","\n",
						  "学校地址 ","-h","\n",
						  "联系人   ","-h","\n",
						  "联系电话 ","-h",
						  "",
						  "确定",
						  "取消"
	};

	cur_char_num = (int *)calloc(6, sizeof(int));					//分配内存空间
	command = InitHotArea(1, 2, 20, 8, 60, cur_char_num, space_num,hot_type, text_info);	//弹出窗口 并接收鼠标键盘事件
	input_info = DealBasicInputInfo(input_info, 1, command, space_num, cur_char_num);		//处理各个输入框输入的信息
		
	if (input_info != NULL)								//如果获取到了输入信息
	{
		right_pos = FindTypePoint(input_info->classes);	//那么进行插入操作
		input_info->next = right_pos->nextB;
		right_pos->nextB = input_info;
		right_pos->num++;
	}
}

/**************************************************
 * 函数名称：ModifyBasic
 * 函数功能：数据维护-修改基本信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void ModifyBasic()
{
	int command;								//接收鼠标键盘命令
	int *cur_char_num;							//各个输入框当前字符数
	int space_num[] = { 1,11,29,49,19,19 };		//各个输入框最大字符数
	int hot_type[] = { 0,0,0,2,0,0,2,0,4,5 };	//各个密文对应的热区类型 修改节点 信息录入窗口
	int modify_type[] = { 0,0,0,3,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,4,5 };	//各个密文对应的热区类型 修改信息录入窗口
	HOT_AREA *cur_area;							//当前窗口热区信息
	BASIC *input_info = NULL;					//用于链表操作的各个指针
	BASIC *new_info = NULL;
	BASIC *cur_basic_point;
	RECRUIT *cur_recruit_point;
	char *text_info[] = { "&请输入待修改学校的类别和编号","\n",	//要修改的节点信息录入窗口 文字条 热区的 显示信息以及布局格式 即密文
						  "学校类别 ","-h","\n",
						  "学校编号 ","-h",
						  "",
						  "确定",
						  "取消"
	};
	char *modify_info[] = { "&请输入待修改的信息","\n",	//修改信息录入窗口 文字条 热区的 显示信息以及布局格式 即密文
							"学校类别 ","-h","\n",
							"学校编号 ","-h","\n",
							"学校名称 ","-h","\n",
							"学校地址 ","-h","\n",
							"联系人   ","-h","\n",
							"联系电话 ","-h",
							"",
							"确定",
							"取消"
	};

	cur_char_num = (int *)calloc(6, sizeof(int));		//分配内存空间
	command = InitHotArea(1, 2, 10, 4, 0, cur_char_num, space_num,hot_type, text_info);	//弹出窗口 并接收鼠标键盘事件
	input_info = DealBasicInputInfo(input_info, 2, command, space_num, cur_char_num);	//处理各个输入框输入的信息

	if (input_info != NULL)								//如果获取到了要修改的节点信息
	{
		cur_basic_point = FindBasicPoint(input_info->classes, input_info->no);			//找到要修改的节点
		InitHotArea(0, 2, 22, 8, 60, cur_char_num, space_num, modify_type, modify_info);//弹出修改窗口 不处理鼠标键盘事件
		DealBasicInputInfo(cur_basic_point, 5, command, space_num, cur_char_num);		//展现要修改节点原来的信息

		cur_area = top_layer_head->cur_area;			//获取当前图层热区信息
		command = DealIntput(cur_area, space_num, cur_char_num);	//处理鼠标键盘事件
		new_info = DealBasicInputInfo(new_info, 3, command, space_num, cur_char_num);	//从各个输入框读入输入信息

		if (new_info != NULL)							//如果成功获取到了修改信息
		{
			strcpy(cur_basic_point->no, new_info->no);	//那么更新修改信息
			strcpy(cur_basic_point->name, new_info->name);
			strcpy(cur_basic_point->address, new_info->address);
			strcpy(cur_basic_point->contacts, new_info->contacts);
			strcpy(cur_basic_point->con_num, new_info->con_num);
			if (strcmp(cur_basic_point->no, new_info->no) != 0)	//更新该基本节点之下的招生信息节点的编号信息
			{
				cur_recruit_point = cur_basic_point->nextR;
				while (cur_recruit_point != NULL)
				{
					strcpy(cur_recruit_point->no, new_info->no);
					cur_recruit_point = cur_recruit_point->next;
				}
			}
		}
	}
}

/**************************************************
 * 函数名称：DeleteBasic
 * 函数功能：数据维护-删除基本信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void DeleteBasic()
{
	int command;								//接收鼠标键盘命令
	int *cur_char_num;							//各个输入框当前字符数
	int space_num[] = { 1,11 };					//各个输入框最大字符数
	int hot_type[] = { 0,0,0,2,0,0,2,0,4,5 };	//各个密文对应的热区类型
	TYPE *right_type_pos;						//用于链表操作的各类信息节点
	BASIC *pre_pos;
	BASIC *right_pos;
	BASIC *input_info = NULL;
	char *text_info[] = { "&请输入待删除学校的类别和编号","\n",	//弹出窗口 文字条 热区的 显示信息以及布局格式 即密文
						  "学校类别 ","-h","\n",
					  	  "学校编号 ","-h",
						  "",
						  "确定",
						  "取消"
	};

	cur_char_num = (int *)calloc(2, sizeof(int));//分配内存空间
	command = InitHotArea(1, 2, 10, 4, 0, cur_char_num, space_num, hot_type, text_info);//弹出窗口 并接收鼠标键盘事件
	input_info = DealBasicInputInfo(input_info, 4, command, space_num, cur_char_num);	//处理各个输入框输入的信息

	if (input_info != NULL)						//如果获取到了要删除节点的信息
	{ 
		right_type_pos = FindTypePoint(input_info->classes);			//找到删除节点对应的分类节点信息
		right_pos = FindBasicPoint(input_info->classes, input_info->no);//找到要删除节点
		pre_pos = right_type_pos->nextB;								//进行删除操作
		if (strcmp(pre_pos->no, input_info->no) == 0)
		{
			right_type_pos->nextB = right_pos->next;
		}
		else
		{
			while (strcmp(pre_pos->next->no, input_info->no) != 0)
			{
				pre_pos = pre_pos->next;
			}
			pre_pos->next = right_pos->next;
		}
		FreeList(NULL, right_pos, NULL);								//释放掉删除节点占用的内存
	}
}

/**************************************************
 * 函数名称：InsertRecruit
 * 函数功能：数据维护-插入招生信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void InsertRecruit()
{
	int command;							//接收鼠标键盘命令
	int *cur_char_num;						//各个输入框当前字符数
	int space_num[] = { 1,11,4,8,8,8,8,8 };	//各个输入框最大字符数
	int hot_type[] = { 0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,4,5 };	//各个密文对应的热区类型
	BASIC *right_pos;						//用于链表操作的各类信息节点指针
	RECRUIT *input_info = NULL;
	char *text_info[] = { "学校类别   ","-h","\n",	//弹出窗口 文字条 热区的 显示信息以及布局格式 即密文
		                  "学校编号   ","-h","\n",
						  "年份       ","-h","\n",
						  "招生指标数 ","-h","\n",
						  "实录人数   ","-h","\n",
						  "录取分数线 ","-h","\n",
						  "最高分     ","-h","\n",
						  "最低分     ","-h",
						  "",
						  "确定",
						  "取消"
	};

	cur_char_num = (int *)calloc(8, sizeof(int));	//分配内存
	command = InitHotArea(1, 2, 26, 10, 26, cur_char_num, space_num, hot_type, text_info);	//弹出窗口 并接收鼠标键盘事件
	input_info = DealRecruitInputInfo(input_info, 1, command, space_num, cur_char_num);		//处理各个输入框输入的信息

	if (input_info != NULL)							//如果获取到了输入信息
	{
		right_pos = FindBasicPoint(input_info->classes, input_info->no);	//那么进行插入操作
		input_info->next=right_pos->nextR;
		right_pos->nextR = input_info;
	}
}

/**************************************************
 * 函数名称：ModifyRecruit
 * 函数功能：数据维护-修改招生信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void ModifyRecruit()
{
	int command;									//接收鼠标键盘命令
	int *cur_char_num;								//各个输入框当前字符数
	int space_num[] = { 1,11,4,8,8,8,8,8 };			//各个输入框最大字符数
	int hot_type[] = { 0,0,0,2,0,0,2,0,0,2,0,4,5 };	//各个密文对应的热区类型 待修改节点信息录入窗口
 	int modify_type[] = { 0,0,0,3,0,0,3,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,0,2,0,4,5 };	//各个密文对应的热区类型 修改窗口
	HOT_AREA *cur_area;								//当前图层热区信息
	RECRUIT *input_info = NULL;						//用于链表操作的各类信息节点指针
	RECRUIT *new_info = NULL;
	RECRUIT *cur_recruit_point;
	char *text_info[] = { "&请输入待修改的学校信息","\n",	//待修改节点信息录入窗口 文字条 热区的 显示信息以及布局格式 即密文
                          "学校类别  ","-h","\n",
                          "学校编号  ","-h","\n",
						  "年份      ","-h",
						  "",
						  "确定",
						  "取消"
	};
	char *modify_info[] = { "&请输入待修改的信息","\n",	//修改窗口 文字条 热区的 显示信息以及布局格式 即密文
							"学校类别   ","-h","\n",
							"学校编号   ","-h","\n",
							"年份       ","-h","\n",
							"招生指标数 ","-h","\n",
							"实录人数   ","-h","\n",
							"录取分数线 ","-h","\n",
							"最高分     ","-h","\n",
							"最低分     ","-h",
							"",
							"确定",
							"取消"
	};

	cur_char_num = (int *)calloc(8, sizeof(int));		//分配内存空间
	command = InitHotArea(1, 2, 13, 5, 26, cur_char_num, space_num, hot_type, text_info);	//弹出窗口 并接收鼠标键盘事件
	input_info = DealRecruitInputInfo(input_info, 2, command, space_num, cur_char_num);		//处理各个输入框输入的信息
	
	if (input_info != NULL)								//如果获取到了待删除节点信息
	{
		cur_recruit_point = FindRecruitPoint(input_info->classes, input_info->no,input_info->year);	//找到要修改的节点
		InitHotArea(0, 2, 28, 10, 26, cur_char_num, space_num , modify_type, modify_info);			//弹出修改窗口 不接收鼠标键盘事件
		DealRecruitInputInfo(cur_recruit_point, 5, command, space_num, cur_char_num);				//将原来的信息显示出来

		cur_area = top_layer_head->cur_area;														//获取当前图层信息
		command = DealIntput(cur_area, space_num, cur_char_num);									//处理鼠标键盘事件
		new_info = DealRecruitInputInfo(new_info, 3, command, space_num, cur_char_num);				//得到修改信息

		if (new_info != NULL)							//如果成功获取到了修改信息
		{
			strcpy(cur_recruit_point->year, new_info->year);			//更新要修改节点的信息
			cur_recruit_point->index_num = new_info->index_num;
			cur_recruit_point->enroll_num = new_info->enroll_num;
			cur_recruit_point->ad_score = new_info->ad_score;
			cur_recruit_point->high_score = new_info->high_score;
			cur_recruit_point->low_score = new_info->low_score;
		}
	}
}

/**************************************************
 * 函数名称：InsertRecruit
 * 函数功能：数据维护-删除招生信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void DeleteRecruit()
{
	int command;									//接收鼠标键盘命令
	int *cur_char_num;								//各个输入框当前字符数
	int space_num[] = { 1,11,4 };					//各个输入框最大字符数
	int hot_type[] = { 0,0,0,2,0,0,2,0,0,2,0,4,5 };	//各个密文对应的热区类型
	BASIC *right_basic_pos;							//用于链表操作的各类信息节点指针
	RECRUIT *pre_pos;		
	RECRUIT *right_pos;
	RECRUIT *input_info = NULL;
	char *text_info[] = { "&请输入待删除学校信息","\n",	//弹出窗口 文字条 热区的 显示信息以及布局格式 即密文
		                  "学校类别  ","-h","\n",
						  "学校编号  ","-h","\n",
						  "年份      ","-h",
						  "",
						  "确定",
						  "取消"
	};

	cur_char_num = (int *)calloc(3, sizeof(int));	//分配内存
	command = InitHotArea(1, 2, 13, 5, 26, cur_char_num, space_num, hot_type, text_info);	//弹出窗口 并接收鼠标键盘事件
	input_info = DealRecruitInputInfo(input_info, 4, command, space_num, cur_char_num);		//处理各个输入框输入的信息
	
	if (input_info != NULL)							//如果获取到了删除信息
	{
		right_basic_pos = FindBasicPoint(input_info->classes, input_info->no);				//那么进行删除操作
		right_pos = FindRecruitPoint(input_info->classes, input_info->no, input_info->year);
		pre_pos = right_basic_pos->nextR;
		if (strcmp(pre_pos->year, input_info->year) == 0)
		{
			right_basic_pos->nextR = right_pos->next;
		}
		else
		{
			while (strcmp(pre_pos->next->year, input_info->year) != 0)
			{
				pre_pos = pre_pos->next;
			}
			pre_pos->next = right_pos->next;
		}
		FreeList(NULL, NULL, right_pos);		//释放掉删除节点的内存
	}
}


/**************************************************
 * 函数名称：QueryType_Classes
 * 函数功能：数据查询-查询招生信息-按照分类查询
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void QueryType_Classes()
{
	int command;								//接收鼠标键盘命令
	int *cur_char_num;							//各个输入框当前字符数
	int hot_type[] = {0,0,0,2,0,4,5};			//查询信息输入窗口 各个密文对应的热区类型
	int present_type[] = { 0,0,0,3,0,0,3,0,4 };	//查询结果展示窗口 各个密文对应的热区类型
	int space_num[] = { 1,8 };					//各个输入框最大字符数
	TYPE *input_info = NULL;					//用于链表操作的各类信息节点指针
	TYPE *right_pos;
	char *text_info[] = { "&请输入待查询的学校类别","\n",	//查询信息输入窗口 文字条 热区的 显示信息以及布局格式 即密文
						  "学校类别  ","-h",
						  "",
						  "确定",
					 	  "取消"
	};
	char *present_info[] = { "&查询结果","\n",			//查询结果展示窗口 文字条 热区的 显示信息以及布局格式 即密文
		                     "学校类别       ","-h","\n",
		                     "该类别学校总数 ","-h",
							 "",
							 "确定"
	};

	cur_char_num = (int *)calloc(2, sizeof(int));		//分配内存空间
	command = InitHotArea(1, 2, 7, 3, 0, cur_char_num, space_num, hot_type, text_info);	//弹出查询信息输入窗口 并接收鼠标键盘事件
	input_info = DealTypeInputInfo(input_info, 2, command, space_num, cur_char_num);	//处理各个输入框输入的信息

	if (input_info != NULL)						//如果成功获取到了查询信息
	{
		right_pos = FindTypePoint(input_info->classes);//得到查询结果
	    InitHotArea(0, 1, 9, 3, 24, cur_char_num, space_num, present_type, present_info);	//弹出查询结果展示窗口 
		input_info = DealTypeInputInfo(right_pos, 5, 1, space_num, cur_char_num);			//显示查询信息
        
		DealIntput(top_layer_head->cur_area, space_num, cur_char_num);						//处理鼠标键盘事件
		WithdrewPopHot();						//弹出窗口
	}
}


/**************************************************
 * 函数名称：QueryBasic_No
 * 函数功能：数据查询-查询基本信息-按照编号查询
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void QueryBasic_No()
{
	int total = 0;							//一共找到的查询结果数
	int command;							//接收鼠标键盘命令
	int *cur_char_num;						//各个输入框当前字符数
	int hot_type[] = { 0,0,0,2,0,4,5 };		//查询信息输入窗口 各个密文对应的热区类型
	int present_type[] = { 0,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,6,5,7 };	//查询结果展示窗口 各个密文对应的热区类型
	int space_num[] = { 1,11,29,49,19,19 };	//各个输入框最大字符数
	COORD pos = { 0,0 };					//位置信息节点
	BASIC *input_info = NULL;				//用于链表操作的各类信息节点指针
	TYPE *cur_type_pos = head;
	BASIC *cur_basic_pos;
	BASIC *query_ans=NULL;
	BASIC *p;
	char *text_info[] = { "&请输入待查询的学校编号","\n",	//查询信息输入窗口 文字条 热区的 显示信息以及布局格式 即密文
						  "学校编号 ","-h",
						  "",
						  "确定",
						  "取消"
	};
	char *present_info[] = { "&查询结果","\n",			//查询结果展示窗口 文字条 热区的 显示信息以及布局格式 即密文
							 "学校类别 ","-h","\n",
							 "学校编号 ","-h","\n",
							 "学校名称 ","-h","\n",
							 "学校地址 ","-h","\n",
							 "联系人   ","-h","\n",
							 "联系电话 ","-h",
							 "",
		                     "<--",
							 "确定",
		                     "-->"
	};

	cur_char_num = (int *)calloc(6, sizeof(int));		//分配内存空间
	command = InitHotArea(1, 2, 7, 3, 0, cur_char_num + 1, space_num + 1, hot_type, text_info);
	input_info = DealBasicInputInfo(input_info, 6, command, space_num + 1, cur_char_num + 1); //查询模式1 按照学校编号查询

	if (input_info != NULL)								//如果成功获取到了输入信息
	{
		while (cur_type_pos != NULL)					//那么获取查询结果
		{
			cur_basic_pos = FindBasicPoint(cur_type_pos->classes, input_info->no);
			if (cur_basic_pos != NULL)
			{
				total++;
				p = (BASIC *)calloc(1,sizeof(BASIC));
				*p = *cur_basic_pos;
				p->next = query_ans;
				p->prev = NULL;
				p->nextR = NULL;
				if (query_ans!=NULL) query_ans->prev = p;
				query_ans = p;
			}
			cur_type_pos = cur_type_pos->next;
		}

		if (query_ans != NULL)							//如果查询结果不为空
		{
			InitHotArea(0, 3, 23, 9, 0, cur_char_num, space_num, present_type, present_info);	//弹出查询结果展示窗口
			PresentQueryInfo(query_ans, NULL, cur_char_num, space_num,total);					//调用函数显示查询结果信息
		}
		else
		{
			ErrorMention(9);							//否则报错
		}
	}
}

/**************************************************
 * 函数名称：QueryBasic_Name
 * 函数功能：数据查询-查询基本信息-按照名字查询
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void QueryBasic_Name()
{
	int total = 0;							//一共找到的查询结果数
	int command;							//接收鼠标键盘命令
	int *cur_char_num;						//各个输入框当前字符数
	int hot_type[] = { 0,0,0,2,0,4,5 };		//查询信息输入窗口 各个密文对应的热区类型
	int present_type[] = { 0,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,6,5,7 };	//查询结果展示窗口 各个密文对应的热区类型
	int space_num[] = { 1,11,29,49,19,19 };	//各个输入框最大字符数
	COORD pos = { 0,0 };					//位置信息
	BASIC *input_info = NULL;				//用于链表操作的各类信息节点指针
	TYPE *cur_type_pos = head;
	BASIC *cur_basic_pos;
	BASIC *query_ans = NULL;
	BASIC *p;
	char *text_info[] = { "&请输入待查询的学校名称","\n",	//查询信息输入窗口 文字条 热区的 显示信息以及布局格式 即密文
		                  "学校名称 ","-h",
		                  "",
		                  "确定",
		                  "取消"
	};
	char *present_info[] = { "&查询结果","\n",			//查询结果展示窗口 文字条 热区的 显示信息以及布局格式 即密文
							 "学校类别 ","-h","\n",
							 "学校编号 ","-h","\n",
							 "学校名称 ","-h","\n",
							 "学校地址 ","-h","\n",
							 "联系人   ","-h","\n",
							 "联系电话 ","-h",
							 "",
							 "<--",
							 "确定",
							 "-->"
						   };

	cur_char_num = (int *)calloc(6, sizeof(int));		//分配内存空间
	command = InitHotArea(1, 2, 7, 3, 0, cur_char_num + 2, space_num + 2, hot_type, text_info);	//弹出查询信息输入窗口
	input_info = DealBasicInputInfo(input_info, 7, command, space_num + 2, cur_char_num + 2);	//查询模式2 按照学校名称查询

	if (input_info != NULL)								//如果成功获取到了输入信息
	{
		while (cur_type_pos != NULL)					//那么获取查询结果
		{
			cur_basic_pos = cur_type_pos->nextB;
			while (cur_basic_pos != NULL)
			{
				if (strstr(cur_basic_pos->name, input_info->name) != NULL)
				{
					total++;
					p = (BASIC *)calloc(1, sizeof(BASIC));
					*p = *cur_basic_pos;
					p->next = query_ans;
					p->prev = NULL;
					p->nextR = NULL;
					if (query_ans != NULL) query_ans->prev = p;
					query_ans = p;
				}
				cur_basic_pos = cur_basic_pos->next;
			}
			cur_type_pos = cur_type_pos->next;
		}

		if (query_ans != NULL)							//如果查询结果不为空
		{
			InitHotArea(0, 3, 23, 9, 0, cur_char_num, space_num, present_type, present_info);	//弹出查询结果展示窗口
			PresentQueryInfo(query_ans, NULL, cur_char_num, space_num, total);					//调用函数显示查询结果信息
		}
		else
		{
			ErrorMention(9);							//否则报错
		}
	}
}


/**************************************************
 * 函数名称：QueryRecruit_NoYear
 * 函数功能：数据查询-查询招生信息-按照编号和年份查询
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void QueryRecruit_NoYear()
{
	int total = 0;								//一共找到的查询结果数
	int command;								//接收鼠标键盘命令
	int *cur_char_num;							//各个输入框当前字符数
	int hot_type[] = { 0,0,0,2,0,0,2,0,4,5 };	//查询信息输入窗口 各个密文对应的热区类型
	int present_type[] = { 0,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,6,5,7 };	//查询结果展示窗口 各个密文对应的热区类型
	int space_num[] = { 1,11,4,8,8,8,8,8 };		//各个输入框最大字符数
	COORD pos = { 0,0 };						//位置信息节点
	RECRUIT *input_info = NULL;					//用于链表操作的各类信息节点指针
	TYPE *cur_type_pos = head;
	RECRUIT *cur_recruit_pos;
	RECRUIT *query_ans = NULL;
	RECRUIT *p;
	char *text_info[] = { "&请输入待查询的学校编号和年份","\n",	//查询信息输入窗口 文字条 热区的 显示信息以及布局格式 即密文
						  "学校编号 ","-h","\n",
						  "年份     ","-h",
						  "",
						  "确定",
						  "取消"};
	char *present_info[] = { "&查询结果","\n",					//查询结果展示窗口 文字条 热区的 显示信息以及布局格式 即密文
							 "学校类别   ","-h","\n",
							 "学校编号   ","-h","\n",
							 "年份       ","-h","\n",
							 "招生指标数 ","-h","\n",
							 "实录人数   ","-h","\n",
							 "录取分数线 ","-h","\n",
							 "最高分     ","-h","\n",
							 "最低分     ","-h",
							 "",
							 "<--",
							 "确定",
							 "-->"
	};

	cur_char_num = (int *)calloc(8, sizeof(int));				//分配内存
	command = InitHotArea(1, 2, 10, 4, 0, cur_char_num + 1, space_num + 1, hot_type, text_info);	//弹出查询信息输入窗口
	input_info = DealRecruitInputInfo(input_info, 6, command, space_num + 1, cur_char_num + 1);		//按照学校编号查询 得到输入的查询信息

	if (input_info != NULL)						//如果成功获取到了输入信息
	{
		while (cur_type_pos != NULL)			//那么获取查询结果
		{
			cur_recruit_pos = FindRecruitPoint(cur_type_pos->classes, input_info->no, input_info->year);
			if (cur_recruit_pos != NULL)
			{
				total++;
				p = (RECRUIT *)calloc(1, sizeof(RECRUIT));
				*p = *cur_recruit_pos;
				p->next = query_ans;
				p->prev = NULL;
				if (query_ans != NULL) query_ans->prev = p;
				query_ans = p;
			}
			cur_type_pos = cur_type_pos->next;
		}

		if (query_ans != NULL)					//如果查询结果不为空
		{
			InitHotArea(0, 3, 29, 11, 0, cur_char_num, space_num, present_type, present_info);	//弹出查询结果展示窗口
			PresentQueryInfo(NULL, query_ans, cur_char_num, space_num, total);					//调用函数显示查询结果信息
		}
		else
		{
			ErrorMention(9);					//否则报错
		}
	}
}

/**************************************************
 * 函数名称：QueryRecruit_Score
 * 函数功能：数据查询-查询招生信息-按照分数段查询
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：BOOL 类型 表示系统结束标记
 
 * 调用说明：无
 **************************************************/
void QueryRecruit_Score()
{
	int total = 0;								//一共找到的查询结果数
	int command;								//接收鼠标键盘命令
	int *cur_char_num;							//各个输入框当前字符数
	int hot_type[] = { 0,0,0,2,0,0,2,0,4,5 };	//查询信息输入窗口 各个密文对应的热区类型
	int present_type[] = { 0,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,0,3,0,6,5,7 };	//查询结果展示窗口 各个密文对应的热区类型
	int space_num[] = { 1,11,4,8,8,8,8,8 };		//各个输入框最大字符数
	COORD pos = { 0,0 };						//位置信息节点
	RECRUIT *input_info = NULL;					//用于链表操作的各类信息节点指针
	TYPE *cur_type_pos = head;
	BASIC *cur_basic_pos;
	RECRUIT *cur_recruit_pos;
	RECRUIT *query_ans = NULL;
	RECRUIT *p;
	char *text_info[] = { "&请输入待查询的录取分数段区间","\n",	//查询信息输入窗口 文字条 热区的 显示信息以及布局格式 即密文
		                  "最高分  ","-h","\n",
		                  "最低分  ","-h",
		                  "",
		                  "确定",
		                  "取消" };
	char *present_info[] = { "&查询结果","\n",			//查询结果展示窗口 文字条 热区的 显示信息以及布局格式 即密文
							 "学校类别   ","-h","\n",
							 "学校编号   ","-h","\n",
							 "年份       ","-h","\n",
							 "招生指标数 ","-h","\n",
							 "实录人数   ","-h","\n",
							 "录取分数线 ","-h","\n",
						 	 "最高分     ","-h","\n",
							 "最低分     ","-h",
							 "",
							 "<--",
							 "确定",
							 "-->"
	};

	cur_char_num = (int *)calloc(8, sizeof(int));	//分配内存
	command = InitHotArea(1, 2, 10, 4, 0, cur_char_num + 6, space_num + 6, hot_type, text_info);	//弹出查询信息输入窗口
	input_info = DealRecruitInputInfo(input_info, 7, command, space_num + 6, cur_char_num + 6);		//按照分数段查询

	if (input_info != NULL)							//如果成功获取到了输入信息
	{
		while (cur_type_pos != NULL)				//那么获取查询结果
		{
			cur_basic_pos = cur_type_pos->nextB;
			while (cur_basic_pos != NULL)
			{
				cur_recruit_pos = cur_basic_pos->nextR;
				while (cur_recruit_pos != NULL)
				{
					if (input_info->high_score >= cur_recruit_pos->ad_score
						&&input_info->low_score <= cur_recruit_pos->ad_score)
					{
						total++;
						p = (RECRUIT *)calloc(1, sizeof(RECRUIT));
						*p = *cur_recruit_pos;
						p->next = query_ans;
						p->prev = NULL;
						if (query_ans != NULL) query_ans->prev = p;
						query_ans = p;
					}
					cur_recruit_pos = cur_recruit_pos->next;
				}
				cur_basic_pos = cur_basic_pos->next;
			}
			cur_type_pos = cur_type_pos->next;
		}

		if (query_ans != NULL)					//如果查询结果不为空
		{
			InitHotArea(0, 3, 29, 11, 0, cur_char_num, space_num, present_type, present_info);	//弹出查询结果展示窗口
			PresentQueryInfo(NULL, query_ans, cur_char_num, space_num, total);					//调用函数显示查询结果信息
		}
		else
		{
			ErrorMention(9);					//否则报错
		}		
	}
}


/**************************************************
 * 函数名称：FindTypePoint
 * 函数功能：根据传进函数的分类信息 寻找对应的分类信息节点
 * 输入参数：char 字符类型 classes 学校类型
 * 输出参数：无
 * 返 回 值：TYPE *找到的分类信息节点指针
			NULL表示没有找到

 * 调用说明：无
 **************************************************/
TYPE *FindTypePoint(char classes)
{
	TYPE *cur_type_point;			//当前查询到的分类信息节点
	cur_type_point = head;
	while (cur_type_point)			//循环查询对比 是否等于传进来分类
	{
		if (cur_type_point->classes == classes)
		{
			return cur_type_point;
		}
		cur_type_point = cur_type_point->next;
	}
	return NULL;					//如果没有找到那么 返回NULL
}

/**************************************************
 * 函数名称：FindBasicPoint
 * 函数功能：根据传进函数的分类信息 学校编号 
			寻找对应的基本信息节点
 * 输入参数：char 字符类型 classes 学校类型
			char *字符串  no      学校编号
 * 输出参数：无
 * 返 回 值：BASIC *找到的基本信息节点指针
			NULL表示没有找到

 * 调用说明：无
 **************************************************/
BASIC *FindBasicPoint(char classes, char *no)
{
	TYPE *cur_type_point;				//当前查询的分类
	BASIC *cur_basic_point;				//当前查询的学校基本信息
	cur_type_point = head;

	while (cur_type_point != NULL)		//遍历每一条信息链 查找满足传进参数的基本信息节点
	{
		if (cur_type_point->classes == classes)
			break;
		cur_type_point = cur_type_point->next;
	}
	if (cur_type_point == NULL) return NULL;	//如果没有找到分类信息 返回空
	cur_basic_point = cur_type_point->nextB;
	while (cur_basic_point != NULL)
	{
		if (strcmp(cur_basic_point->no, no) == 0)
		{
			return cur_basic_point;
		}
		cur_basic_point = cur_basic_point->next;
	}
	return NULL;						//如果没有找到返回空
}

/**************************************************
 * 函数名称：FindRecruitPoint
 * 函数功能：根据传进函数的分类信息 学校编号 招生信息年份
			寻找对应的招生信息节点
 * 输入参数：char 字符类型 classes 学校类型
			char *字符串  no      学校编号
			char *字符串  year    招生年份
 * 输出参数：无
 * 返 回 值：RECRUIT *找到的招生信息节点指针
			NULL表示没有找到

 * 调用说明：无
 **************************************************/
RECRUIT *FindRecruitPoint(char classes, char *no, char *year)
{
	TYPE *cur_type_point;				//当前查找的分类信息节点
	BASIC *cur_basic_point;				//当前查找的基本信息节点
	RECRUIT *cur_recruit_point;			//当前查找的招生信息节点
	cur_type_point = head;
	while (cur_type_point != NULL)		//遍历整个分类信息链 查找是否有该分类
	{
		if (cur_type_point->classes == classes)
			break;
		cur_type_point = cur_type_point->next;
	}
	if (cur_type_point == NULL) return NULL;	//如果没有找到就返回 NULL
	cur_basic_point = cur_type_point->nextB;

	while (cur_basic_point != NULL)		//遍历整个该分类下基本信息链 查找是否有该编号的学校
	{
		if (strcmp(cur_basic_point->no, no) == 0)
			break;
		cur_basic_point = cur_basic_point->next;
	}
	if (cur_basic_point == NULL)
		return NULL;							//如果没有找到就返回 NULL
	cur_recruit_point = cur_basic_point->nextR;
	
	while (cur_recruit_point != NULL)	//遍历整个该学校下历年招生信息链 查找是否有该年份的招生信息
	{
		if (strcmp(cur_recruit_point->year, year) == 0)
		{
			return cur_recruit_point;
		}
		cur_recruit_point = cur_recruit_point->next;
	}

	return NULL;								//如果没有找到就返回NULL
}


/**************************************************
 * 函数名称：DealTypeInputInfo
 * 函数功能：根据处理输入信息或者展示信息 的模式
			对输入信息进行处理或者显示 下面是不同编号对应的模式
			1 表示插入节点模式
			2 表示修改节点模式
			3 表示展示要修改的节点模式
			4 表示删除节点模式
			5 表示展现查询节点模式
 * 输入参数：TYPE *指针类型 input_info 表示需要处理的信息
			int	  整型类型 mode       表示对信息的处理模式
			int   整型变量 command    表示传进来的鼠标键盘命令
			int * 整型指针 space_num  表示各个输入框对应的最大字符数
			int * 整型指针 cur_char_num 表示各个输入框对应的当前字符数 （在显示信息的时候是输入参数）
 * 输出参数：int * 整型指针 cur_char_num 表示各个输入框对应的当前字符数 （在插入信息 修改信息的时候是出输出参数）
 * 返 回 值：TYPE *处理后的信息节点
			NULL表示处理失败 有错误（中间会有提示框显示对应错误）

 * 调用说明：该函数 集成了 所有关于分类信息 读入和显示的功能
 **************************************************/
TYPE *DealTypeInputInfo(TYPE *input_info, int mode, int command, int *space_num, int *cur_char_num)
{
	int sort;						//表示输入信息 重复标记 个位表示分类信息重复 是为表示基本信息重复 百位表示招生信息重复
	int lenth;						//输入长度
	BOOL success = FALSE;			//成功处理 标记
	COORD pos = { 0, 0 };			//位置信息
	HOT_AREA cur_area;				//当前区域的热区信息
	BOOL format = TRUE;				//格式正确与否 标记
	TYPE *right_pos;				//用于查询的信息节点
	char *temp, *endptr = NULL;		//分别表示暂存数据字符串 格式错误指针（指向错误的字符地址）
	if (command == 1)				//如果是按下了确认键
	{
		cur_area = *top_layer_head->cur_area;						//获取当前图层的热区信息
		temp = (char *)malloc(20 * sizeof(char));					//分配内存
		if (mode != 5)												//如果不是显示模式 那么需要分配空间接收读入信息
			input_info = (TYPE *)calloc(1, sizeof(TYPE));
			
		for (int i = 0; i < cur_area.no - cur_area.bottom_no; i++)	//循环对各个热区进行处理
		{
			pos.X = cur_area.pArea[i].Left;
			pos.Y = cur_area.pArea[i].Top;
			if (mode != 5)											//读入信息
			{
				ReadConsoleOutputCharacter(Handle_Out, temp, cur_char_num[i], pos, &ul);	//在控制台中读入当前输入框的输入信息
				temp[cur_char_num[i]] = '\0';
				switch (i)											//转换后传递给输入信息节点
				{
					case 0:input_info->classes = temp[0]; break;
					default:break;
				}
				if (input_info->classes == ' ' || input_info->classes == '.')	//判断输入信息格式是否有误
				{
					format = FALSE;
					ErrorMention(3);
					break;
				}
			}
			else													//如果是显示信息模式
			{
				switch (i)											//将要显示的节点对应信息转换成temp字符串 准备输出 
				{
				case 0:temp[0] = input_info->classes; temp[1] = '\0'; break;
				case 1:sprintf(temp, "%d", input_info->num); break;
				}
				lenth = cur_area.pArea[i].Right - cur_area.pArea[i].Left + 1;
				cur_char_num[i] = i == 0 ? 1 : strlen(temp);		//计算字符串长度
				WriteConsoleOutputCharacter(Handle_Out, temp, cur_char_num[i], pos, &ul);	//输出信息 让信息显示到屏幕上
				if (cur_area.pHotType[i] == 2)						//如果是输入框 显示对应颜色
				{
					FillConsoleOutputAttribute(Handle_Out, Input_Attr, lenth, pos, &ul);
				}
				else												//如果是只读框 显示对应颜色
				{
					FillConsoleOutputAttribute(Handle_Out, Fix_Input_Attr, lenth, pos, &ul);
				}
			}
		}
		if (mode == 5)												//显示模式 直接结束
			return NULL;
		if (format == TRUE)											//格式没错的情况下
		{
			right_pos = FindTypePoint(input_info->classes);			//判断输入信息是否存在了
			sort = right_pos == NULL ? (mode * 10) : (mode * 10 + 1);	//获取重复标记
			switch (sort)											//根据重复标记 提示对应的错误或者成功信息
			{			
				case 10: ErrorMention(1);   success = TRUE; break;
				case 11: ErrorMention(4);                   break;
				case 20: ErrorMention(6);                   break;
				case 21: WithdrewPopHot();  success = TRUE; break;
				case 30: ErrorMention(8);   success = TRUE; break;
				case 31: ErrorMention(4);                   break;
				case 40: ErrorMention(6);                   break;
				case 41: ErrorMention(5);   success = TRUE; break;
			}
		}
	}
	else if (command == 2)		//如果有空未输入 
	{
		ErrorMention(0);		//提示对应信息
	}
	else if (command == 5)		//如果点了 取消 或者ESC
	{ 
		WithdrewPopHot();		//弹出窗口
	}

	if (success)				//如果成功处理 返回处理后的结果指针
		return input_info;
	else 
		return NULL;			//否则返回NULL
}

/**************************************************
 * 函数名称：DealBasicInputInfo
 * 函数功能：根据处理输入信息或者展示信息 的模式
			对输入信息进行处理或者显示 下面是不同编号对应的模式
			1 表示插入节点模式
			2 表示修改节点模式
			3 表示展示要修改的节点模式
			4 表示删除节点模式
			5 表示展现查询节点模式
			6 表示读入编号
			7 表示读入名字
 * 输入参数：BASIC *指针类型 input_info 表示需要处理的信息
			int	   整型类型 mode       表示对信息的处理模式
			int    整型变量 command    表示传进来的鼠标键盘命令
			int *  整型指针 space_num  表示各个输入框对应的最大字符数
			int *  整型指针 cur_char_num 表示各个输入框对应的当前字符数 （在显示信息的时候是输入参数）
 * 输出参数：int *  整型指针 cur_char_num 表示各个输入框对应的当前字符数 （在插入信息 修改信息的时候是出输出参数）
 * 返 回 值：BASIC *处理后的信息节点
			NULL表示处理失败 有错误（中间会有提示框显示对应错误）

 * 调用说明：该函数 集成了 所有关于基本信息 读入和显示的功能
 **************************************************/
BASIC *DealBasicInputInfo(BASIC *input_info, int mode, int command, int *space_num, int *cur_char_num)
{
	int sort;										//由于本函数与DealTypeInputInfo十分类似 故不作注释
	int lenth;
	int delta = 0;
	int count=0;
	char original_no[12];
	BOOL success = FALSE;
	COORD pos = { 0, 0 };
	HOT_AREA cur_area;
	BOOL format = TRUE;
	TYPE *right_type_pos;
	BASIC *right_basic_pos;
	char *temp, *endptr = NULL;
	if (command == 1)
	{
		cur_area = *top_layer_head->cur_area;
		temp = (char *)malloc(50 * sizeof(char));
		if (mode != 5)
			input_info = (BASIC *)calloc(1, sizeof(BASIC));
		switch (mode)
		{
		case 3: pos.X = cur_area.pArea[1].Left;
				pos.Y = cur_area.pArea[1].Top;
				ReadConsoleOutputCharacter(Handle_Out, original_no, cur_char_num[1], pos, &ul);
				original_no[cur_char_num[1]] = '\0';
				break;
		case 6:delta = 1; break;
		case 7:delta = 2; break;
		}
		for (int i = 0; i < cur_area.no - cur_area.bottom_no; i++)
		{
			pos.X = cur_area.pArea[i].Left;
			pos.Y = cur_area.pArea[i].Top;
			if (mode != 5)
			{
				ReadConsoleOutputCharacter(Handle_Out, temp, cur_char_num[i], pos, &ul);
				temp[cur_char_num[i]] = '\0';
				switch (i + delta)
				{
					case 0:input_info->classes = temp[0];      break;
					case 1:strcpy(input_info->no, temp);       break;
					case 2:strcpy(input_info->name, temp);     break;
					case 3:strcpy(input_info->address, temp);  break;
					case 4:strcpy(input_info->contacts, temp); break;
					case 5:strcpy(input_info->con_num, temp);  break;
				    default:break;
				}
				if (i + delta == 0 && (input_info->classes == ' ' || input_info->classes == '.'))
				{
					ErrorMention(3);
				}
				else if (i + delta == 5)
				{
					for (int j = 0; j < strlen(temp); j++)
					{
						if (!isdigit(temp[j]) && count > 1)
						{
							format = FALSE;
							ErrorMention(3);
							break;
						}
						else if (temp[j] == '-')
						{
							count++;
						}
					}
				}
			}
			else
			{
				lenth = cur_area.pArea[i].Right - cur_area.pArea[i].Left + 1;
				switch (i)
				{
				    case 0: temp = &input_info->classes; break;
					case 1: temp = input_info->no;       break;
					case 2: temp = input_info->name;     break;
					case 3: temp = input_info->address;  break;
					case 4: temp = input_info->contacts; break;
					case 5: temp = input_info->con_num;  break;
					default:break;
				}
				cur_char_num[i] = i == 0 ? 1 : strlen(temp);
				WriteConsoleOutputCharacter(Handle_Out, temp, cur_char_num[i], pos, &ul);
				if (cur_area.pHotType[i] == 2)
				{
					FillConsoleOutputAttribute(Handle_Out, Input_Attr, lenth, pos, &ul);
				}
				else
				{
					FillConsoleOutputAttribute(Handle_Out, Fix_Input_Attr, lenth, pos, &ul);
				}
			}
		}
		if (mode == 5)
			return NULL;
		if (format == TRUE)
		{
			if (mode == 6 || mode == 7)
			{
				WithdrewPopHot();
				return input_info;
			}
			right_type_pos = FindTypePoint(input_info->classes);
			right_basic_pos = FindBasicPoint(input_info->classes,input_info->no);
			sort = right_basic_pos == NULL ? (mode * 10) : (mode * 10 + 1);
			if (strcmp(original_no, input_info->no) == 0 && right_basic_pos != NULL)
			{
				sort--;
			}
			if (mode !=3&&right_type_pos == NULL)
			{
				ErrorMention(6);
			}
			else
			{
				switch (sort)
				{
					case 10: ErrorMention(1);   success = TRUE; break;
					case 11: ErrorMention(4);                   break;
					case 20: ErrorMention(2);                   break;
					case 21: WithdrewPopHot(); success = TRUE; break;
					case 30: ErrorMention(8);   success = TRUE; break;
					case 31: ErrorMention(4);                   break;
					case 40: ErrorMention(2);                   break;
					case 41: ErrorMention(5);   success = TRUE; break;
				}
			}
		}
	}
	else if (command == 2)
	{
		ErrorMention(0);
	}
	else if (command == 5)
	{
		WithdrewPopHot();
	}

	if (success)
		return input_info;
	else
		return NULL;
}

/**************************************************
 * 函数名称：DealRecruitInputInfo
 * 函数功能：根据处理输入信息或者展示信息 的模式
			对输入信息进行处理或者显示 下面是不同编号对应的模式
			1 表示插入节点模式
			2 表示修改节点模式
			3 表示展示要修改的节点模式
			4 表示删除节点模式
			5 表示展现查询节点模式
			6 表示读入编号和年份
			7 表示读入最高分 最低分用于查询
			8 表示读入年份
 * 输入参数：RECRUIT *指针类型 input_info 表示需要处理的信息
			int	     整型类型 mode       表示对信息的处理模式
			int      整型变量 command    表示传进来的鼠标键盘命令
			int *    整型指针 space_num  表示各个输入框对应的最大字符数
			int *    整型指针 cur_char_num 表示各个输入框对应的当前字符数 （在显示信息的时候是输入参数）
 * 输出参数：int *    整型指针 cur_char_num 表示各个输入框对应的当前字符数 （在插入信息 修改信息的时候是出输出参数）
 * 返 回 值：RECRUIT *处理后的信息节点
			NULL表示处理失败 有错误（中间会有提示框显示对应错误）

 * 调用说明：该函数 集成了 所有关于分类信息 读入和显示的功能
 **************************************************/
RECRUIT *DealRecruitInputInfo(RECRUIT *input_info, int mode, int command, int *space_num, int *cur_char_num)
{
	int sort;										//由于本函数与DealTypeInputInfo十分类似 故不作注释
	int lenth;
	int delta = 0;
	int count = 0;
	char original_year[10];
	BOOL success = FALSE;
	COORD pos = { 0, 0 };
	HOT_AREA cur_area;
	BOOL format = TRUE;
	TYPE *right_type_pos;
	BASIC *right_basic_pos;
	RECRUIT *right_recruit_pos;
	char *temp, *endptr ="" ;
	if (command == 1)
	{
		cur_area = *top_layer_head->cur_area;
		temp = (char *)malloc(20 * sizeof(char));
		if (mode != 5)
			input_info = (BASIC *)calloc(1, sizeof(BASIC));
		switch (mode)
		{
		case 3: pos.X = cur_area.pArea[2].Left;
				pos.Y = cur_area.pArea[2].Top;
				ReadConsoleOutputCharacter(Handle_Out, original_year, cur_char_num[2], pos, &ul);
				original_year[cur_char_num[2]] = '\0';
				break;
		case 6:delta = 1; break;
		case 7:delta = 6; break;
		case 8:delta = 2; break;
		}
		for (int i = 0; i < cur_area.no - cur_area.bottom_no; i++)
		{
			pos.X = cur_area.pArea[i].Left;
			pos.Y = cur_area.pArea[i].Top;
			if (mode != 5)
			{
				ReadConsoleOutputCharacter(Handle_Out, temp, cur_char_num[i], pos, &ul);
				temp[cur_char_num[i]] = '\0';
				switch (i + delta)
				{
				case 0:input_info->classes = temp[0]; break;
				case 1:strcpy(input_info->no, temp); break;
				case 2:strcpy(input_info->year, temp); break;
				case 3:input_info->index_num = strtol(temp, &endptr, 10); break;
				case 4:input_info->enroll_num = strtol(temp, &endptr, 10); break;
				case 5:input_info->ad_score = strtof(temp, &endptr); break;
				case 6:input_info->high_score = strtof(temp, &endptr); break;
				case 7:input_info->low_score = strtof(temp, &endptr); break;
				default:break;
				}
				if (*endptr != '\0')
				{
					format = FALSE;
					ErrorMention(3);
					break;
				}
				else if (i + delta == 0 && (input_info->classes == ' ' || input_info->classes == '.'))
				{
					format = FALSE;
					ErrorMention(3);
				}
				else if (i + delta == 2)
				{
					for (int j = 0; j < strlen(input_info->year); j++)
					{
						if (!isdigit(input_info->year[j]))
						{
							format = FALSE;
							ErrorMention(3);
							break;
						}
					}
				}
			}
			else
			{
				lenth = cur_area.pArea[i].Right - cur_area.pArea[i].Left + 1;
				switch (i)
				{
				case 0: temp[0] = input_info->classes; temp[1] = '\0'; break;
				case 1: strcpy(temp,input_info->no);                   break;
				case 2: strcpy(temp,input_info->year);                 break;
				case 3: sprintf(temp, "%d", input_info->index_num);    break;
				case 4: sprintf(temp, "%d", input_info->enroll_num);   break;
				case 5: sprintf(temp, "%.2f", input_info->ad_score);   break;
				case 6: sprintf(temp, "%.2f", input_info->high_score); break;
				case 7: sprintf(temp, "%.2f", input_info->low_score);  break;
				default:break;
				}
				cur_char_num[i] = i == 0 ? 1 : strlen(temp);;
				WriteConsoleOutputCharacter(Handle_Out, temp, cur_char_num[i], pos, &ul);
				if (cur_area.pHotType[i] == 2)
				{
					FillConsoleOutputAttribute(Handle_Out, Input_Attr, lenth, pos, &ul);
				}
				else 
				{
					FillConsoleOutputAttribute(Handle_Out, Fix_Input_Attr, lenth, pos, &ul);
				}
			}
		}
		if (mode == 5)
			return NULL;
		if (format == TRUE)
		{
			if (mode == 6 || mode == 7 || mode==8)
			{
				WithdrewPopHot();
				return input_info;
			}
			right_type_pos = FindTypePoint(input_info->classes);
			right_basic_pos = FindBasicPoint(input_info->classes, input_info->no);
			right_recruit_pos = FindRecruitPoint(input_info->classes, input_info->no, input_info->year);
			sort = right_recruit_pos == NULL ? (mode * 10) : (mode * 10 + 1);
			if (strcmp(original_year, input_info->year) == 0 && right_recruit_pos != NULL)
			{
				sort--;
			}
			if (mode != 3&& right_type_pos == NULL)
			{
				ErrorMention(6);				
			}
			else if (mode != 3 && right_basic_pos == NULL)
			{
				ErrorMention(2);
			}
			else
			{
				switch (sort)
				{
				case 10: ErrorMention(1);   success = TRUE; break;
				case 11: ErrorMention(4);                   break;
				case 20: ErrorMention(7);                   break;
				case 21: WithdrewPopHot(); success = TRUE; break;
				case 30: ErrorMention(8);   success = TRUE; break;
				case 31: ErrorMention(4);                   break;
				case 40: ErrorMention(7);                   break;
				case 41: ErrorMention(5);   success = TRUE; break;
				}
			}
		}
	}
	else if (command == 2)
	{
		ErrorMention(0);
	}
	else if (command == 5)
	{
		WithdrewPopHot();
	}

	if (success)
		return input_info;
	else
		return NULL;
}


/**************************************************
 * 函数名称：StatComp
 * 函数功能：统计排序比较，对统计出的结果链表按照对应的统计模式
			给出比较方式 支持多级比较 即先按一个标准比较 相同按另一个标准
 * 输入参数：int 整型变量 mode 统计模式
			RECRUIT *指针类型 x 待比较的两个招生信息节点之一
			RECRUIT *指针类型 y 待比较的两个招生信息节点之一
 * 输出参数：无
 * 返 回 值：比较结果 
			TURE表示 x 比 y 要“大”

 * 调用说明：所有的统计均可调用这一个函数 所以不用写多个统计排序函数
 **************************************************/
BOOL StatComp(int mode, RECRUIT *x, RECRUIT *y)
{
	switch (mode)		//根据模式给出不同基表方式
	{
	case 1: if (x->enroll_num != y->enroll_num)			//如果实际录取人数不同
			{
				return x->enroll_num > y->enroll_num;	//返回比较结果
			}
			break;
	case 2: if (x->enroll_num != y->enroll_num)			//如果实际录取人数不同
			{
				return x->enroll_num > y->enroll_num;	//返回比较结果
			}
			break;
	case 3: if (x->enroll_num != y->enroll_num)			//如果实际录取人数不同
			{	
				return x->enroll_num > y->enroll_num;	//返回比较结果
			}
			break;
	case 4: if ((x->high_score - x->ad_score) != (y->high_score - y->ad_score))			//如果最高分-录取分数差不等 
			{
				return (x->high_score - x->ad_score) > (y->high_score - y->ad_score);	//返回比较结果
			}
			break;
	case 5: if (x->ad_score != y->ad_score)				//如果录取分数线不同
			{
				return x->ad_score > y->ad_score;		//返回比较结果
			}
			break;
	}
	return x->classes < y->classes;						//否则说明 之前比较方式 不能比较出 大小 那么按照学校类型比较大小
}

/**************************************************
 * 函数名称：StatListSort
 * 函数功能：对统计结果链进行排序
 * 输入参数：int 整型变量 mode 表示统计模式
			RECRUIT *指针变量 stat_head 表示统计结果链的链头
 * 输出参数：排序好的统计结果链
 * 返 回 值：无

 * 调用说明：所有统计模式均可调用该函数
 **************************************************/
RECRUIT *StatListSort(int mode, RECRUIT *stat_head)
{
	RECRUIT *deal_pos, *max_pos, *cur_recruit_pos,*temp;			//用于排序的各个指针
	stat_head = stat_head->next;									//由于用了双向链表用了哨兵节点 故先跳到下一个
	for (deal_pos = stat_head; deal_pos->next->next != NULL; deal_pos = deal_pos->next)	//从前往后排序
	{
		max_pos = deal_pos;											//对最大节点进行初始化
		for (cur_recruit_pos = deal_pos->next; cur_recruit_pos->next != NULL; cur_recruit_pos = cur_recruit_pos->next)
		{
			if (StatComp(mode, cur_recruit_pos, max_pos))			//循环找最大的一个 
			{
				max_pos = cur_recruit_pos;
			}
		}
		if (deal_pos != max_pos)									//如果不与初始节点相同 那么max_pos节点更大 交换位置
		{
			if (deal_pos == stat_head) stat_head = max_pos;
			if (deal_pos->next != max_pos)							//按照相邻还是不相邻 进行交换
			{
				deal_pos->next->prev = max_pos;
				deal_pos->prev->next = max_pos;
				max_pos->next->prev = deal_pos;
				max_pos->prev->next = deal_pos;

				temp = deal_pos->next;
				deal_pos->next = max_pos->next;
				max_pos->next = temp;

				temp = deal_pos->prev;
				deal_pos->prev = max_pos->prev;
				max_pos->prev = temp;
			}
			else
			{
				deal_pos->prev->next = max_pos;
				max_pos->next->prev = deal_pos;
				deal_pos->next = max_pos->next;
				max_pos->next = deal_pos;
				max_pos->prev = deal_pos->prev;
				deal_pos->prev = max_pos;
			}
			deal_pos = max_pos;
		}
	}
	return stat_head;								//返回排序结果
}

/**************************************************
 * 函数名称：StatListCreate
 * 函数功能：根据统计模式 和传进来的统计信息 创建统计结果链
 * 输入参数：int 整型变量 mode 表示统计模式
			RECRUIT *指针变量 表示统计信息 比如要统计的年份
 * 输出参数：int *total 统计结果链的总信息个数
 * 返 回 值：统计结果链的链头 （哨兵）

 * 调用说明：所有统计均可调用该函数进行创建统计结果链
 **************************************************/
RECRUIT *StatListCreate(int mode, int *total,RECRUIT *input_info)
{
	RECRUIT *stat_ans,*temp;						//用于链表操作的各个指针
	TYPE *cur_type_pos;
	BASIC *cur_basic_pos;
	RECRUIT *cur_recruit_pos;
	cur_type_pos = head;
	stat_ans = (RECRUIT *)calloc(1, sizeof(RECRUIT));	//分配内存空间
	temp = (RECRUIT *)calloc(1, sizeof(RECRUIT));
	stat_ans->next = temp;
	temp->prev = stat_ans;
	while (cur_type_pos != NULL)					//如果数据链不为空就 查询统计信息
	{
		if (mode == 1)								//根据模式来得出不同的统计信息链
		{
			(*total)++;
			temp = (RECRUIT *)calloc(1, sizeof(RECRUIT));
			temp->classes = cur_type_pos->classes;
			temp->enroll_num = 0;

			temp->next = stat_ans->next;
			stat_ans->next->prev = temp;
			stat_ans->next = temp;
			temp->prev = stat_ans;
		}
		cur_basic_pos = cur_type_pos->nextB;
		while (cur_basic_pos != NULL)
		{
			if (mode == 1)
			{
				cur_recruit_pos = cur_basic_pos->nextR;
				while (cur_recruit_pos != NULL)
				{
					strcpy(temp->no, cur_recruit_pos->no);
					if (strcmp(cur_recruit_pos->year, input_info->year) == 0)
					{
						temp->enroll_num += cur_recruit_pos->enroll_num;
					}
					cur_recruit_pos = cur_recruit_pos->next;
				}
			}
			else if (mode == 3)
			{
				(*total)++;
				temp = (RECRUIT *)calloc(1, sizeof(RECRUIT));
				temp->classes = cur_basic_pos->classes;
				strcpy(temp->no, cur_basic_pos->no);
				temp->enroll_num = 0;

				temp->next = stat_ans->next;
				stat_ans->next->prev = temp;
				stat_ans->next = temp;
				temp->prev = stat_ans;

				cur_recruit_pos = cur_basic_pos->nextR;
				while (cur_recruit_pos != NULL)
				{
					temp->enroll_num += cur_recruit_pos->enroll_num;
					cur_recruit_pos = cur_recruit_pos->next;
				}
			}
			else 
			{
				cur_recruit_pos = cur_basic_pos->nextR;
				while (cur_recruit_pos != NULL)
				{
					if (strcmp(cur_recruit_pos->year, input_info->year) == 0)
					{
						(*total)++;
						temp = (RECRUIT *)calloc(1, sizeof(RECRUIT));
						*temp = *cur_recruit_pos;
						temp->next = stat_ans->next;
						stat_ans->next->prev = temp;
						stat_ans->next = temp;
						temp->prev = stat_ans;
					}
					cur_recruit_pos = cur_recruit_pos->next;
				}
			}
			cur_basic_pos = cur_basic_pos->next;
		}
		cur_type_pos = cur_type_pos->next;								//判断下一个类型是否满足统计要求
	}	
	return stat_ans;			//返回结果链的链头
}
