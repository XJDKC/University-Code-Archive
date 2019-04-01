#include "lexical.h"

int main()
{
	ReadInfo();
	return 0;
}

/****************************************
 * 函数名称：ReadInfo
 * 函数功能：读入信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
void ReadInfo()
{
	char format[] = "lex";
	printf("请输入需要进行词法分析的文件路径:\n");
	scanf("%s", filename);

	while ((original = fopen(filename, "r")) == NULL)
	{
		printf("您输入的路径打开失败,请重新输入:\n");
		scanf("%s", filename);
	}

	for (int i = 0; i < strlen(filename); i++)
	{
		if (filename[i] == '.')
		{
			filename[i + 1] = '\0';
			strcat(filename, format);
        }
	}
	lexical = fopen(filename, "w");
	fprintf(lexical, " 序号  token类型     token                   行号    列号    出现次数\n"
					 "--------------------------------------------------------------------\n");

	while (!feof(original))
	{
		cur_row++;
		fgets(info,1025,original); 
		AnalysisInfo();
	}
	fclose(original);
	fclose(lexical);
}

/****************************************
 * 函数名称：AnalysisInfo
 * 函数功能：分析该行信息
 * 输入参数：无
 * 输出参数：无
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
void AnalysisInfo()
{
	char *token;
	token = (char *)calloc(81, sizeof(char));
	for (int i = 0; info[i] != '\n'&&info[i] != '\0';)
	{
		i = getmore(i, token);
		if (token[0] != '\0')
		{
			switch (kind(token[0]))
			{
				case 1: if (FindKeyword(token))
							DealOutput(i, 2, token);
						else
							DealOutput(i, 1, token); break;
				case 2: DealOutput(i, ConstantType(token), token); break;
				case 3: DealOutput(i, 7, token); break;
				case 4: DealOutput(i, 8, token); break;
			}
		}
	}
}

//根据首字符来判断是什么类型的token:     1:关键字或者标识符 2:常量 3:其他符号 4:可见分隔符 5:不可见分隔符
/****************************************
 * 函数名称：kind
 * 函数功能：根据首字符初步判断token类型
 * 输入参数：ch 首字符
 * 输出参数：无
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
int kind(char ch)
{

	if (isalpha(ch) || ch == '_')					//如果首字符是下划线_或者是字母 那么为
		return 1;									//标识符或者是关键字
	else if (isdigit(ch) || ch == '\'' || ch == '"')//如果是数字 或者是单引号 双引号
		return 2;									//为常量 （整型 浮点型 字符常量 字符串常量）
	else if (isblank(ch))							//如果是空白字符
		return 5;									//那么就是空白分隔符
	else if (ch == '{' || ch == '}' || ch == ';')   //如果是以上字符
		return 4;                                   //那么就是分隔符
	else
		return 3;                                   //否则就是其他符号
													//包括 运算符 注释 
}

//返回根据首字符识别出的token 和 下一个位置
/****************************************
 * 函数名称：getmore
 * 函数功能：根据首字符拓展出整个token
 * 输入参数：i 该行第i个字符
 * 输出参数：token 拓展后的token字符串
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
int getmore(int i, char *token)
{
	int total = 0;
	memset(token, 0, 81 * sizeof(char));
	switch (kind(info[i]))
	{
		case 1: while (kind(info[i]) == 1 || isdigit(info[i])) //如果当前字符是数字 字母 或者下划线
		        {
			        token[total++] = info[i++];                //那么将当前字符加入字符串中 属于一个token 
		        }break;
	    case 2: while (kind(info[i]) == 2 || info[i]=='.' || info[i]=='x' || info[i]=='X' 
			          || (info[i] >= 'a' && info[i]<='f' )|| (info[i] >= 'A' && info[i] <= 'F') 
			          || info[i] == 'u' || info[i] == 'U' || info[i] == 'l' || info[i] == 'L' ) 
			          //如果当前字符是数字 字母 或者下划线
		        {
			        token[total++] = info[i++];                //那么将当前字符加入字符串中 属于一个token 
					if ((info[i] == '\'' || info[i] == '"') && info[i - 1] != '\\')
					{
						break;
					}
		        }break;
		case 3: if (info[i] == '/' && (info[i + 1] == '/' || info[i + 1] == '*'))
				{
					if (info[i + 1] == '*')
					{
						i += 2;
						while (info[i] != '*'&&info[i + 1] != '/')
						{
							if (info[i+1] == '\n')
							{
								i = 0;
								cur_row++;
								fgets(info, 1025, original);
							}
							else
							{
								i++;
							}
						}
						i += 2;
					}
					else
					{
						i = 0;
						cur_row++;
						fgets(info, 1025, original);
					}
				}
				else
				{
					token[total++] = info[i++];
					while (FindOperator(token))
					{
						token[total++] = info[i++];
					}
					i--;
					token[--total] = '\0';
				}break;
		case 4: token[total++] = info[i++]; break;
		case 5: i++; break;
	}
	return i;
}

/****************************************
 * 函数名称：DealOutput
 * 函数功能：处理输出
 * 输入参数：tail_pos token尾部位置 用于得到坐标
			type     token类型
			token    得到的token
 * 输出参数：无
 * 返 回 值：无
 
 * 调用说明：无
 ****************************************/
void DealOutput(int tail_pos, int type, char *token)
{
	int cur_column;
	TOKEN_NODE *new_node;

	cur_column = tail_pos - strlen(token) + 1;

	if ((new_node = FindToken(token)) != NULL)
	{
		new_node->appear_no++;
		fprintf(lexical, "%5d  %-10s    %-20s    %4d    %4d    %4d\n",
			++token_no, type_list[new_node->type], new_node->token, cur_row, cur_column, new_node->appear_no);
	}
	else
	{
		new_node = (TOKEN_NODE *)calloc(1, sizeof(TOKEN_NODE));

		new_node->type = type;
		new_node->appear_no = 1;
		strcpy(new_node->token, token);
		new_node->next = head;
		fprintf(lexical, "%5d  %-10s    %-20s    %4d    %4d    %4d\n",
			++token_no, type_list[new_node->type], new_node->token, cur_row, cur_column, new_node->appear_no);
		head = new_node;
	}
}

/****************************************
 * 函数名称：ConstantType
 * 函数功能：判断常量类型
 * 输入参数：token    得到的token
 * 输出参数：无
 * 返 回 值：int 类型 常量类型
			3 表示整型
			4 表示浮点
			5 表示字符
			6 表示字符串
 
 * 调用说明：无
 ****************************************/
int ConstantType(char *token)
{
	for (int i = 0; i < strlen(token); i++)
	{
		if (isdigit(token[i])) continue;
		switch (token[i])
		{
		case '.': return 4;
		case '\'': return 5;
		case '"': return 6;
		default: return 3;
		}
	}

	return 3;
}


/****************************************
 * 函数名称：FindKeyword
 * 函数功能：判断token是否为关键字
 * 输入参数：token    得到的token
 * 输出参数：无
 * 返 回 值：表示是否为关键字
 
 * 调用说明：无
 ****************************************/
bool FindKeyword(char *token)

{
	for (int i = 0; i < keyword_no; i++)
	{
		if (strcmp(token, keyword[i]) == 0)
			return true;
	}
	return false;
}

/****************************************
 * 函数名称：FindOperator
 * 函数功能：判断token是否为运算符
 * 输入参数：token    得到的token
 * 输出参数：无
 * 返 回 值：表示是否为运算符
 
 * 调用说明：无
 ****************************************/
bool FindOperator(char *token)
{
	for (int i = 0; i < operator_no; i++)
	{
		if (strcmp(token, operator_list[i]) == 0)
			return true;
	}
	return false;
}

/****************************************
 * 函数名称：FindToken
 * 函数功能：寻找是否之前已经出现果该token
			找到返回在链表中的地址
 * 输入参数：token    得到的token
 * 输出参数：无
 * 返 回 值：NULL 表示没找到
			否则为链表中的地址
 
 * 调用说明：无
 ****************************************/
TOKEN_NODE *FindToken(char *token)
{
	TOKEN_NODE *cur_node;

	cur_node = head;
	while (cur_node != NULL)
	{
		if (strcmp(cur_node->token, token) == 0)
		{
			return cur_node;
		}
		cur_node = cur_node->next;
	}

	return NULL;
}
