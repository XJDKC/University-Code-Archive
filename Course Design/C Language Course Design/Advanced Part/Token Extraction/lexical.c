#include "lexical.h"

int main()
{
	ReadInfo();
	return 0;
}

/****************************************
 * �������ƣ�ReadInfo
 * �������ܣ�������Ϣ
 * �����������
 * �����������
 * �� �� ֵ����
 
 * ����˵������
 ****************************************/
void ReadInfo()
{
	char format[] = "lex";
	printf("��������Ҫ���дʷ��������ļ�·��:\n");
	scanf("%s", filename);

	while ((original = fopen(filename, "r")) == NULL)
	{
		printf("�������·����ʧ��,����������:\n");
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
	fprintf(lexical, " ���  token����     token                   �к�    �к�    ���ִ���\n"
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
 * �������ƣ�AnalysisInfo
 * �������ܣ�����������Ϣ
 * �����������
 * �����������
 * �� �� ֵ����
 
 * ����˵������
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

//�������ַ����ж���ʲô���͵�token:     1:�ؼ��ֻ��߱�ʶ�� 2:���� 3:�������� 4:�ɼ��ָ��� 5:���ɼ��ָ���
/****************************************
 * �������ƣ�kind
 * �������ܣ��������ַ������ж�token����
 * ���������ch ���ַ�
 * �����������
 * �� �� ֵ����
 
 * ����˵������
 ****************************************/
int kind(char ch)
{

	if (isalpha(ch) || ch == '_')					//������ַ����»���_��������ĸ ��ôΪ
		return 1;									//��ʶ�������ǹؼ���
	else if (isdigit(ch) || ch == '\'' || ch == '"')//��������� �����ǵ����� ˫����
		return 2;									//Ϊ���� ������ ������ �ַ����� �ַ���������
	else if (isblank(ch))							//����ǿհ��ַ�
		return 5;									//��ô���ǿհ׷ָ���
	else if (ch == '{' || ch == '}' || ch == ';')   //����������ַ�
		return 4;                                   //��ô���Ƿָ���
	else
		return 3;                                   //���������������
													//���� ����� ע�� 
}

//���ظ������ַ�ʶ�����token �� ��һ��λ��
/****************************************
 * �������ƣ�getmore
 * �������ܣ��������ַ���չ������token
 * ���������i ���е�i���ַ�
 * ���������token ��չ���token�ַ���
 * �� �� ֵ����
 
 * ����˵������
 ****************************************/
int getmore(int i, char *token)
{
	int total = 0;
	memset(token, 0, 81 * sizeof(char));
	switch (kind(info[i]))
	{
		case 1: while (kind(info[i]) == 1 || isdigit(info[i])) //�����ǰ�ַ������� ��ĸ �����»���
		        {
			        token[total++] = info[i++];                //��ô����ǰ�ַ������ַ����� ����һ��token 
		        }break;
	    case 2: while (kind(info[i]) == 2 || info[i]=='.' || info[i]=='x' || info[i]=='X' 
			          || (info[i] >= 'a' && info[i]<='f' )|| (info[i] >= 'A' && info[i] <= 'F') 
			          || info[i] == 'u' || info[i] == 'U' || info[i] == 'l' || info[i] == 'L' ) 
			          //�����ǰ�ַ������� ��ĸ �����»���
		        {
			        token[total++] = info[i++];                //��ô����ǰ�ַ������ַ����� ����һ��token 
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
 * �������ƣ�DealOutput
 * �������ܣ��������
 * ���������tail_pos tokenβ��λ�� ���ڵõ�����
			type     token����
			token    �õ���token
 * �����������
 * �� �� ֵ����
 
 * ����˵������
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
 * �������ƣ�ConstantType
 * �������ܣ��жϳ�������
 * ���������token    �õ���token
 * �����������
 * �� �� ֵ��int ���� ��������
			3 ��ʾ����
			4 ��ʾ����
			5 ��ʾ�ַ�
			6 ��ʾ�ַ���
 
 * ����˵������
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
 * �������ƣ�FindKeyword
 * �������ܣ��ж�token�Ƿ�Ϊ�ؼ���
 * ���������token    �õ���token
 * �����������
 * �� �� ֵ����ʾ�Ƿ�Ϊ�ؼ���
 
 * ����˵������
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
 * �������ƣ�FindOperator
 * �������ܣ��ж�token�Ƿ�Ϊ�����
 * ���������token    �õ���token
 * �����������
 * �� �� ֵ����ʾ�Ƿ�Ϊ�����
 
 * ����˵������
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
 * �������ƣ�FindToken
 * �������ܣ�Ѱ���Ƿ�֮ǰ�Ѿ����ֹ���token
			�ҵ������������еĵ�ַ
 * ���������token    �õ���token
 * �����������
 * �� �� ֵ��NULL ��ʾû�ҵ�
			����Ϊ�����еĵ�ַ
 
 * ����˵������
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
