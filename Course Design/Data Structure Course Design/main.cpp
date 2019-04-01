#include<iostream>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<queue>
#include<stack>
#include<vector>
#include<map>
#include<set>
#include<cstdio>
#include<cstdlib>
#include<string>
#include<limits>
#include<time.h>
#include<conio.h>
#include<iomanip>
#include<cstring>
#include<Windows.h>
#include"DataStructure.h"
#include"myvalue.h"
using namespace std;
int main()
{
	init();
	functionSelect();
	return 0;
}

void init()
{
	menu_function.insert(make_pair(0, new Menu_Function(&main_menu, NULL)));
	menu_function.insert(make_pair(1, new Menu_Function(&file_manage, NULL)));
	menu_function.insert(make_pair(2, new Menu_Function(&lesson_element_manage, NULL)));
	menu_function.insert(make_pair(3, new Menu_Function(&lesson_manage, NULL)));
	menu_function.insert(make_pair(4, new Menu_Function(&analysis_and_evaluate, NULL)));
	menu_function.insert(make_pair(11, new Menu_Function(&file_input, NULL)));
	menu_function.insert(make_pair(21, new Menu_Function(&classroom_info_manage, NULL)));
	menu_function.insert(make_pair(22, new Menu_Function(&teacher_info_manage, NULL)));
	menu_function.insert(make_pair(23, new Menu_Function(&class_info_manage, NULL)));
	menu_function.insert(make_pair(24, new Menu_Function(&course_info_manage, NULL)));
	menu_function.insert(make_pair(41, new Menu_Function(&classroom_manage, NULL)));
	menu_function.insert(make_pair(12, new Menu_Function(NULL, saveInfo)));
	menu_function.insert(make_pair(13, new Menu_Function(NULL, exitSys)));
	menu_function.insert(make_pair(111, new Menu_Function(NULL, classroomFileInput)));
	menu_function.insert(make_pair(112, new Menu_Function(NULL, teacherFileInput)));
	menu_function.insert(make_pair(113, new Menu_Function(NULL, classFileInput)));
	menu_function.insert(make_pair(114, new Menu_Function(NULL, courseFileInput)));
	menu_function.insert(make_pair(115, new Menu_Function(NULL, lessonFileInput)));
	menu_function.insert(make_pair(211, new Menu_Function(NULL, insertClassroomInfo)));
	menu_function.insert(make_pair(212, new Menu_Function(NULL, deleteClassroomInfo)));
	menu_function.insert(make_pair(213, new Menu_Function(NULL, modifyClassroomInfo)));
	menu_function.insert(make_pair(214, new Menu_Function(NULL, findClassroomInfo)));
	menu_function.insert(make_pair(215, new Menu_Function(NULL, retrieveClassroomInfo)));
	menu_function.insert(make_pair(221, new Menu_Function(NULL, insertTeacherInfo)));
	menu_function.insert(make_pair(222, new Menu_Function(NULL, deleteTeacherInfo)));
	menu_function.insert(make_pair(223, new Menu_Function(NULL, modifyTeacherInfo)));
	menu_function.insert(make_pair(224, new Menu_Function(NULL, findTeacherInfo)));
	menu_function.insert(make_pair(225, new Menu_Function(NULL, retrieveTeacherInfo)));
	menu_function.insert(make_pair(231, new Menu_Function(NULL, insertClassInfo)));
	menu_function.insert(make_pair(232, new Menu_Function(NULL, deleteClassInfo)));
	menu_function.insert(make_pair(233, new Menu_Function(NULL, modifyClassInfo)));
	menu_function.insert(make_pair(234, new Menu_Function(NULL, findClassInfo)));
	menu_function.insert(make_pair(235, new Menu_Function(NULL, retrieveClassInfo)));
	menu_function.insert(make_pair(241, new Menu_Function(NULL, insertCourseInfo)));
	menu_function.insert(make_pair(242, new Menu_Function(NULL, deleteCourseInfo)));
	menu_function.insert(make_pair(243, new Menu_Function(NULL, modifyCourseInfo)));
	menu_function.insert(make_pair(244, new Menu_Function(NULL, findCourseInfo)));
	menu_function.insert(make_pair(245, new Menu_Function(NULL, retrieveCourseInfo)));
	menu_function.insert(make_pair(31, new Menu_Function(NULL, insertLessonInfo)));
	menu_function.insert(make_pair(32, new Menu_Function(NULL, deleteLessonInfo)));
	menu_function.insert(make_pair(33, new Menu_Function(NULL, modifyLessonInfo)));
	menu_function.insert(make_pair(34, new Menu_Function(NULL, findLessonInfo)));
	menu_function.insert(make_pair(35, new Menu_Function(NULL, retrieveLessonInfo)));
	menu_function.insert(make_pair(411, new Menu_Function(NULL, findEmptyClassroom)));
	menu_function.insert(make_pair(412, new Menu_Function(NULL, utilizationAnalysis)));
	menu_function.insert(make_pair(413, new Menu_Function(NULL, efficiencyAnalysis)));
	menu_function.insert(make_pair(42, new Menu_Function(NULL, teacherValidityAnalysis)));
	menu_function.insert(make_pair(43, new Menu_Function(NULL, studentValidityAnalysis)));

	SetConsoleWindowInfo(HANDLE_OUT, true, &win_size);
	SetConsoleTitle(TEXT("排课评估与分析助手"));
	hWnd = FindWindow(NULL, TEXT("排课评估与分析助手"));

	string info;
	ifstream inFile;
	CLASSROOM *new_classroom;
	TEACHER *new_teacher;
	CLASS *new_class;
	COURSE *new_course;
	LESSON *new_lesson;

	//读取教室信息
	inFile.open(classroom_file);
	if (!inFile.is_open())
	{
		dealMention(0, 1, "");
	}
	else
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_classroom = new CLASSROOM;
			inFile >> *new_classroom;
			if (new_classroom->building != "")
				All_Classroom.insert(new_classroom);
			else
				delete(new_classroom);
		}
	}
	inFile.close();

	//读取教师信息
	inFile.open(teacher_file);
	if (!inFile.is_open())
	{
		dealMention(0, 2, "");
	}
	else 
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_teacher = new TEACHER;
			inFile >> *new_teacher;
			if (new_teacher->t_name != ""&&new_teacher->institute != "")
				All_Teacher.insert(new_teacher);
			else
				delete(new_teacher);
		}
	}
	inFile.close();

	//读取课程信息
	inFile.open(course_file);
	if (!inFile.is_open())
	{
		dealMention(0, 4, "");
	}
	else
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_course = new COURSE;
			inFile >> *new_course;
			if (new_course->ID != ""&&new_course->name != ""&&new_course->institute != "")
				All_Course.insert(new_course);
			else
				delete(new_course);
		}
	}
	inFile.close();

	//读取班级信息
	inFile.open(class_file);
	if (!inFile.is_open())
	{
		dealMention(0, 3, "");
	}
	else 
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_class = new CLASS;
			inFile >> *new_class;	
			if (new_class->c_name != ""&&new_class->institute != ""&&new_class->student_num)
				All_Class.insert(new_class);
			else
				delete(new_class);
		}
	}
	inFile.close();

	//读取课堂信息
	inFile.open(lesson_file);
	if (!inFile.is_open())
	{
		dealMention(0, 5, "");
	}
	else 
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_lesson = new LESSON;
			inFile >> *new_lesson;	
			if (new_lesson->classroom&&new_lesson->teacher&&!new_lesson->classes.empty()&&new_lesson->course&&!new_lesson->conflictDetection(All_Time))
				new_lesson->insertLessonSet(All_Time, All_Lesson);
			else delete(new_lesson);
		}
	}
	inFile.close();
}
void functionSelect()
{
	int op = -1;					//获取输入命令
	int cur_pos = 0;				//获取当前所在菜单位置
	int status = 0;					//当前状态
	bool EXIT=true;					//是否退出系统
	Menu_Function *pcur = NULL;
	while (EXIT)
	{
		pcur=menu_function.find(cur_pos)->second;
		if (pcur->menu_item != NULL)
		{
			drawMenuInterface(cur_pos, pcur);
			scanf("%d",&op);
			if (op == 0) cur_pos = 0;
			else if (op<0 || op>pcur->menu_item->size())
			{
				op = cur_pos = 0;
				dealMention(cur_pos, 0, "");
			}
			else
			{
				cur_pos = cur_pos * 10 + op;
			}
		}
		else
		{
			if (cur_pos == 13) EXIT = false;
			status = (*pcur->corres_fuction)();
			dealMention(cur_pos, status, "");
			cur_pos = 0;
		}
	}
}
int needToStudy(COURSE_SET *learned, COURSE_SET *require)
{
	int ret=0;
	COURSE_SET::iterator course_it;
	for (course_it = learned->begin(); course_it != learned->end(); course_it++)
	{
		if (learned->find(*course_it) == learned->end())
			ret++;
		if (!(*course_it)->require.empty())
			ret += needToStudy(learned, &(*course_it)->require);
	}
	return ret;
}
void dealMention(int code, int type, std::string info)
{
	string mention = "";
	switch (code)
	{
		case 0:
			switch (type)
			{
				case 0:mention = "请输入正确的操作数!"; break;
				case 1:mention = "打开教室信息文件失败!"; break;
				case 2:mention = "打开教师信息文件失败!"; break;
				case 3:mention = "打开班级信息文件失败!"; break;
				case 4:mention = "打开课程信息文件失败!"; break;
				case 5:mention = "打开课堂信息文件失败!"; break;
			}break;
		case 1:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 2:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 3:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 4:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 11:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 21:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 22:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 23:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 24:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 41:
			switch (type)
			{
				case 0:mention = "请输入正确操作数!"; break;
			}break;
		case 111:
			switch (type)
			{
				case ERROR:mention = "打开文件失败!"; break;
				case OK:mention = "导入教室信息成功!"; break;
			}break;
		case 112:
			switch (type)
			{
				case ERROR:mention = "打开文件失败!"; break;
				case OK:mention ="导入教师信息成功!"; break;
			}break;
		case 113:
			switch (type)
			{
				case ERROR:mention = "打开文件失败!"; break;
				case OK:mention = "导入班级信息成功!"; break;
			}break;
		case 114:
			switch (type)
			{
				case ERROR:mention = "打开文件失败!"; break;
				case OK:mention = "导入课程信息成功!"; break;
			}break;
		case 115:
			switch (type)
			{
				case ERROR:mention = "打开文件失败!"; break;
				case OK:mention = "导入课堂信息成功!"; break;
			}break;
		case 12:
			switch (type)
			{
				case 0:mention = "保存教室信息失败!"; break;
				case 2:mention = "保存教师信息失败!"; break;
				case 3:mention = "保存班级信息失败!"; break;
				case 4:mention = "保存课程信息失败!"; break;
				case 5:mention = "保存课堂信息失败!"; break;
				case OK:mention = "导入成功!"; break;
			}break;
		case 13:
			switch (type)
			{
				case OK:mention = "欢迎下次使用!"; break;
			}break;
		case 211:
			switch (type)
			{
				case OK:mention = "插入教室信息成功!"; break;
				case ERROR:mention = "请输入正确格式!"; break;
				case EXIST:mention = "输入教室信息已存在!"; break;
			}break;
		case 212:
			switch (type)
			{
				case OK:mention = "删除教室信息成功!"; break;
				case CANCEL:mention = ""; break;
				case NOTEXIST:mention = "未找到对应教室信息!"; break;
			}break;
		case 213:
			switch (type)
			{
				case OK:mention = "修改教室信息成功!"; break;
				case EXIST:mention = "输入信息已存在!"; break;
				case NOTEXIST:mention = "未找到对应教室信息!"; break;
			}break;
		case 214:
			switch (type)
			{
				case OK:mention = ""; break;
				case NOTEXIST:mention = "未找到对应教室信息!"; break;
			}break;
		case 215:
			switch (type)
			{
				case OK:mention = ""; break;
			}break;
		case 221:
			switch (type)
			{
				case OK:mention = "插入教师信息成功!"; break;
				case ERROR:mention = "请输入正确格式!"; break;
				case EXIST:mention = "输入教师信息已存在!"; break;
			}break;
		case 222:
			switch (type)
			{
				case OK:mention = "删除教师信息成功!"; break;
				case CANCEL:mention = ""; break;
				case NOTEXIST:mention = "未找到对应教师信息!"; break;
			}break;
		case 223:
			switch (type)
			{
				case OK:mention = "修改教师信息成功!"; break;
				case EXIST:mention = "输入信息已存在!"; break;
				case NOTEXIST:mention = "未找到对应教师信息!"; break;
			}break;
		case 224:
			switch (type)
			{
				case OK:mention = ""; break;
				case NOTEXIST:mention = "未找到对应教师信息!"; break;
			}break;
		case 225:
			switch (type)
			{
				case OK:mention = ""; break;
			}break;
		case 231:
			switch (type)
			{
				case OK:mention = "插入班级信息成功!"; break;
				case ERROR:mention = "请输入正确格式!"; break;
				case EXIST:mention = "输入班级信息已存在!"; break;
			}break;
		case 232:
			switch (type)
			{
				case OK:mention = "删除班级信息成功!"; break;
				case CANCEL:mention = ""; break;
				case NOTEXIST:mention = "未找到对应班级信息!"; break;
			}break;
		case 233:
			switch (type)
			{
				case OK:mention = "修改班级信息成功!"; break;
				case EXIST:mention = "输入信息已存在!"; break;
				case NOTEXIST:mention = "未找到对应班级信息!"; break;
			}break;
		case 234:
			switch (type)
			{
				case OK:mention = ""; break;
				case NOTEXIST:mention = "未找到对应班级信息!"; break;
			}break;
		case 235:
			switch (type)
			{
				case OK:mention = ""; break;
			}break;
		case 241:
			switch (type)
			{
				case OK:mention = "插入课程信息成功!"; break;
				case ERROR:mention = "请输入正确格式!"; break;
				case EXIST:mention = "输入课程信息已存在!"; break;
			}break;
		case 242:
			switch (type)
			{
				case OK:mention = "删除课程信息成功!"; break;
				case CANCEL:mention = ""; break;
				case NOTEXIST:mention = "未找到对应课程信息!"; break;
			}break;
		case 243:
			switch (type)
			{
				case OK:mention = "修改课程信息成功!"; break;
				case EXIST:mention = "输入信息已存在!"; break;
				case NOTEXIST:mention = "未找到对应课程信息!"; break;
			}break;
		case 244:
			switch (type)
			{
				case OK:mention = ""; break;
				case NOTEXIST:mention = "未找到对应班级信息!"; break;
			}break;
		case 245:
			switch (type)
			{
				case OK:mention = ""; break;
			}break;
		case 31:
			switch (type)
			{
				case OK:mention = "插入成功!"; break;
				case 2:mention = "未找到输入课程信息!"; break;
				case 3:mention = "未找到输入教室信息!"; break;
				case 4:mention = "在输入时间地点下已存在一节课!"; break;
				case 5:mention = "未找到输入教师信息!"; break;
				case 6:mention = "未找到输入班级信息!"; break;
			}break;
		case 32:
			switch (type)
			{
				case OK:mention = "删除成功!"; break;
				case NOTEXIST:mention = "未找到对应的课堂信息!"; break;
				case 2:mention = "未找到输入的教室信息!"; break;
			}break;
		case 33:
			switch (type)
			{
				case OK:mention = "修改成功!"; break;
				case NOTEXIST:mention = "未找到对应的课堂信息!"; break;
				case 2:mention = "未找到输入的教室信息!"; break;
			}break;
		case 34:
			switch (type)
			{
				case OK:mention = ""; break;
				case NOTEXIST:mention = "未找到对应的课堂信息!"; break;
				case 2:mention = "未找到输入的教室信息!"; break;
			}break;
		case 35:
			switch (type)
			{
				case OK:mention = ""; break;
			}break;
		case 411:
			switch (type)
			{
				case OK:mention = ""; break;
			}break;	
		case 412:
			switch (type)

			{
				case OK:mention = ""; break;
				case CANCEL:mention = ""; break;
				case ERROR:mention = "请输入正确操作数!"; break;
				case NOTEXIST:mention = "未找到对应的教室!"; break;
			}break;	
		case 413:
			switch (type)
			{
				case OK:mention = ""; break;
			}break;	
		case 42:
			switch (type)
			{
				case OK:mention = ""; break;
			}break;	
		case 43:
			switch (type)
			{
				case OK:mention = ""; break;
			}break;	
	}

	if (mention != "")
	{
		size_t converted = 0;
		wchar_t *W_mention = (wchar_t *)calloc(mention.size() + 1, sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, mention.c_str(), mention.size() + 1, W_mention, mention.size() + 1);
		//mbstowcs_s(&converted, W_mention, mention.size() + 1, mention.c_str(), _TRUNCATE);
		if (MessageBox(hWnd, W_mention, TEXT("提示"), MB_OK | MB_SYSTEMMODAL) == IDOK)
		{
			delete(W_mention);
			return;
		}
	}

}
void drawMenuInterface(int no, Menu_Function *pcur)
{
	SetConsoleOutputCP(936);
	string side[7] = { "-", "─","│","┌","┐","└","┘" };
	string print_info[2] = {"Function Menu","请输入指令代号[0-"};
	CONSOLE_SCREEN_BUFFER_INFO cursor_pos;
	system("cls");
	
	int max_len = 20;
	COORD pos;
	std::vector<std::string> present_info = *pcur->menu_item;
	for (int i = 0; i < present_info.size(); i++)
	{
		max_len = max(max_len + 2, present_info[0].length() + 2);
	}
	pos.X = win_size.Right / 2 - (max_len + 14) / 2;
	pos.Y = win_size.Bottom / 2 - (present_info.size() + 7) / 2;
	
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("%s", side[3].c_str());
	for (int i = 1; i <= max_len + 12; i++) printf("%s", side[1].c_str());
	printf("%s", side[4].c_str());
	
	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos); 
	printf("%s", side[2].c_str());
	for (int i = 1,mark=0; i <= max_len + 12; i++)
		if (i <= (max_len + 12 - print_info[0].length()) / 2) printf(" ");
		else if (i > (max_len + 12 + print_info[0].length()) / 2) printf(" ");
		else if (!mark) { mark = 1; printf("%s", print_info[0].c_str()); }
	printf("%s", side[2].c_str());

	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos); 	
	printf("%s ", side[2].c_str());
	for (int i = 1; i <= max_len + 11; i++) printf("-");
	printf("%s", side[2].c_str());
	
	for (int i = 1; i <= present_info.size(); i++)
	{
		pos.Y++;
		SetConsoleCursorPosition(HANDLE_OUT, pos);
		printf("%s            %d:%s", side[2].c_str(), i, present_info[i - 1].c_str());
		GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
		while (cursor_pos.dwCursorPosition.X < pos.X+max_len+13) { printf(" "); cursor_pos.dwCursorPosition.X++; }
		printf("%s", side[2].c_str());
	}

	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos);
	printf("%s            0:Exit", side[2].c_str());
	GetConsoleScreenBufferInfo(HANDLE_OUT, &cursor_pos);
	while (cursor_pos.dwCursorPosition.X < pos.X+max_len+13) { printf(" "); cursor_pos.dwCursorPosition.X++; }
	printf("%s", side[2].c_str());
	
	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos); 	
	printf("%s ", side[2].c_str());
	for (int i = 1; i <= max_len + 11; i++) printf("-");
	printf("%s", side[2].c_str());

	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos); 
	printf("%s", side[2].c_str());
	for (int i = 1,mark=0; i <= max_len + 12; i++)
		if (i < (max_len + 12 - print_info[1].length()) / 2) printf(" ");
		else if (i > (max_len + 12 + print_info[1].length()) / 2 + 2) printf(" ");
		else if (!mark) { mark = 1; printf("%s%d]:", print_info[1].c_str(), present_info.size()); }
	printf("%s", side[2].c_str());

	pos.Y++;
	SetConsoleCursorPosition(HANDLE_OUT, pos); 
	printf("%s", side[5].c_str());
	for (int i = 1; i <= max_len + 12; i++)  printf("%s", side[1].c_str());
	printf("%s", side[6].c_str());

	pos.X += (max_len + 12 - print_info[1].length()) / 2 + print_info[1].length() + 3;
	pos.Y--;
	SetConsoleCursorPosition(HANDLE_OUT, pos); 
}
void getBits(std::vector<std::string> &bits, std::string &info)
{
	bool mark;
	int left, right, length = info.length();
	for (left = 0, right = 0; right < length; right++)
	{
		if (info[right] == ',')
		{
			if (info[left] == '"'&&right > 0 && info[right - 1] != '"')
				continue;
			if (left == right) bits.push_back("");
			else if (info[left] == '"')
				bits.push_back(info.substr(left + 1, right - left - 1));
			else 
				bits.push_back(info.substr(left, right - left));
			left =  right + 1;
		}
	}
	if (left < length) bits.push_back(info.substr(left, right - left));
	else bits.push_back("");
}
std::string getWeekString(bool weeks[MAX_WEEK])
{
	stringstream ret("");
	for (int i = 1, mark = 0,first=1,last; i < MAX_WEEK; i++)
	{
		if (weeks[i] && !mark)
		{
			mark = 1;
			if (!first) ret<< ",";
			else first = 0;
			ret << i;
		}
		else if (weeks[i])
		{
			last = i;
		}
		else if (mark){
			mark = 0;
			if (i > 1 && weeks[i - 2])
			{
				ret << "-" << last;
			}
		}
		if (i == MAX_WEEK - 1 && mark == 1)
		{
			ret << "-" << last;
		}
	}
	return ret.str();
}

Status classroomFileInput()
{
	system("cls");
	CLASSROOM *new_classroom;
	string file_path, info;
	ifstream inFile;
	cout << "请输入CSV表格格式的教室信息文件路径:"; cin >> file_path;
	inFile.open(file_path);
	if (!inFile.is_open())
	{
		inFile.close();
		return ERROR;
	}
	else
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_classroom = new CLASSROOM;
			inFile >> *new_classroom;
			if (new_classroom->building != "")
				All_Classroom.insert(new_classroom);
			else
				delete(new_classroom);
		}
		inFile.close();
		return OK;
	}
}
Status teacherFileInput()
{
	system("cls");
	TEACHER *new_teacher;
	string file_path, info;
	ifstream inFile;
	cout << "请输入CSV表格格式的教师信息文件路径:"; cin >> file_path;
	inFile.open(file_path);
	if (!inFile.is_open())
	{
		inFile.close();
		return	ERROR;
	}
	else 
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_teacher = new TEACHER;
			inFile >> *new_teacher;
			if (new_teacher->t_name != ""&&new_teacher->institute != "")
				All_Teacher.insert(new_teacher);
			else
				delete(new_teacher);
		}
		inFile.close();
		return OK;
	}
}
Status classFileInput()
{
	system("cls");
	CLASS *new_class;
	string file_path, info;
	ifstream inFile;
	cout << "请输入CSV表格格式的班级信息文件路径:"; cin >> file_path;
	inFile.open(file_path);
	if (!inFile.is_open())
	{
		inFile.close();
		return	ERROR;
	}
	else 
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_class = new CLASS;
			inFile >> *new_class;	
			if (new_class->c_name != ""&&new_class->institute != ""&&new_class->student_num)
				All_Class.insert(new_class);
			else
				delete(new_class);
		}
		inFile.close();
		return OK;
	}
}
Status courseFileInput()
{
	system("cls");
	COURSE *new_course;
	string file_path, info;
	ifstream inFile;
	cout << "请输入CSV表格格式的课程信息文件路径:"; cin >> file_path;
	inFile.open(file_path);
	if (!inFile.is_open())
	{
		inFile.close();
		return	ERROR;
	}
	else 
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_course = new COURSE;
			inFile >> *new_course;
			if (new_course->ID != ""&&new_course->name != ""&&new_course->institute != "")
				All_Course.insert(new_course);
			else
				delete(new_course);
		}
		inFile.close();
		return OK;
	}
}
Status lessonFileInput()
{
	system("cls");
	LESSON *new_lesson;
	string file_path, info;
	ifstream inFile;
	cout << "请输入CSV表格格式的课程信息文件路径:"; cin >> file_path;
	inFile.open(file_path);
	if (!inFile.is_open())
	{
		inFile.close();
		return	ERROR;
	}
	else 
	{
		getline(inFile, info);
		while (!inFile.eof())
		{
			new_lesson = new LESSON;
			inFile >> *new_lesson;	
			if (new_lesson->classroom&&new_lesson->teacher&&!new_lesson->classes.empty()&&new_lesson->course&&!new_lesson->conflictDetection(All_Time))
				new_lesson->insertLessonSet(All_Time, All_Lesson);
			else delete(new_lesson);
		}
		inFile.close();
		return OK;
	}
}

Status saveInfo()
{
	int status;
	status = my_file_out(classroom_file, All_Classroom.begin(), All_Classroom.end(), "教学楼,教室编号,最大容纳人数");	if(!status)	dealMention(12, 0, "");
	status = my_file_out(teacher_file, All_Teacher.begin(), All_Teacher.end(), "教师姓名,任职学院");	if(!status)	dealMention(12, 2, "");
	status = my_file_out(class_file, All_Class.begin(), All_Class.end(), "班级名称,班级所在学院,班级人数,已学课程");	if(!status)	dealMention(12, 3, "");
	status = my_file_out(course_file, All_Course.begin(), All_Course.end(), "课程ID,课程名称,所属学院,所需基础课程");	if(!status)	dealMention(12, 4, "");
	status = my_file_out(lesson_file, All_Lesson.begin(), All_Lesson.end(), "课程名称,周次,星期,节数,教学楼,教室编号,教师姓名,班级");	if(!status)	dealMention(12, 5, "");
	return OK;
}
Status exitSys()
{
	saveInfo();
	return OK;
}

Status insertClassroomInfo()
{
	system("cls");
	CLASSROOM *pnew = new CLASSROOM;
	CLASSROOM_SET::iterator it;
	cout << "请输入教室所在教学楼:";cin >> pnew->building;
	cout << "请输入教室编号:"; cin >> pnew->room;
	cout << "请输入教室可容纳人数:"; cin >> pnew->max_capacity;
	if (cin.good())
	{
		it=my_find_if(All_Classroom.begin(),All_Classroom.end(),pnew->building,pnew->room,0);
		if (it == All_Classroom.end())
		{
			All_Classroom.insert(pnew);
			return OK;
		}
		else
			return EXIST;
	}
	return ERROR;
}
Status deleteClassroomInfo()
{
	system("cls");
	string building, room;
	CLASSROOM_SET::iterator it;
	LESSON_SET::iterator lesson_it;
	cout << "请输入待删除教室所在教学楼:"; cin >> building;
	cout << "请输入待删除教室编号:"; cin >> room;
	it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0);
	if (it != All_Classroom.end())
	{
		if (MessageBox(hWnd, TEXT("删除教室信息会将与之相关的课堂信息也删除"), TEXT("警告"), MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
		{
			for (lesson_it = (*it)->lessons.begin(); lesson_it != (*it)->lessons.end(); lesson_it++)
			{
				(*lesson_it)->deleteLessonSet(All_Time,All_Lesson);
				delete(*lesson_it);
			}
			All_Classroom.erase(it);
			return OK;
		}
		else return CANCEL;
	}
	return NOTEXIST;
}
Status modifyClassroomInfo()
{
	system("cls");
	char c;
	int max_capacity;
	string building, room;
	CLASSROOM_SET::iterator it,temp;
	cout << "请输入待修改教室所在教学楼:"; cin >> building;
	cout << "请输入待修改教室编号:"; cin >> room;
	it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0);
	if (it != All_Classroom.end())
	{
		system("cls");
		cout << "原信息:" << endl;
		cout << *(*it) << endl;
		max_capacity = (*it)->max_capacity;
		cout << "请输入要修改的信息(N表示不修改)"<<endl;
		cout << "教学楼:"; cin >> c; if (c != 'N') { cin.putback(c); cin >> building; }
		cout << "教室编号:";cin >> c; if (c != 'N') { cin.putback(c); cin >> room; } 
		cout << "最大容纳人数:"; cin >> c; if (c != 'N') { cin.putback(c); cin >>max_capacity; }
		temp = my_find_if(All_Classroom.begin(), All_Classroom.begin(), building, room, 0);
		if (temp != All_Classroom.end())
		{
			(*it)->building = building;
			(*it)->room = room;
			(*it)->max_capacity = max_capacity;
			return OK;
		}
		else 
			return EXIST;
	}
	return NOTEXIST;
}
Status findClassroomInfo()
{
	system("cls");
	string building, room;
	CLASSROOM_SET::iterator it;
	LESSON_SET::iterator iter;
	cout << "请输入待查询教室所在教学楼:"; cin >> building;
	cout << "请输入待查询教室编号:"; cin >> room;
	it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0);
	if (it != All_Classroom.end())
	{
		system("cls");
		cout << "教室所在教学楼:" << (*it)->building << endl;
		cout << "教室编号:" << (*it)->room << endl;
		cout << "教室最大容纳人数:" << (*it)->max_capacity << endl;
		cout << "与该教室有关的课堂信息:" << endl;
		iter = (*it)->lessons.begin();
		for (int i = 1; iter != (*it)->lessons.end(); i++, iter++)
		{
			cout << "课堂序号" << i << endl;
			cout << *(*iter) << endl;
		}
		system("pause");
		return OK;
	}
	return NOTEXIST;
}
Status retrieveClassroomInfo()
{
	system("cls");
	int left, right, op, count = 0;
	string building, room;
	CLASSROOM_SET::iterator it;
	cout << "索引方式:" << endl;
	cout << "1.按教学楼索引" << endl;
	cout << "2.按编号索引" << endl;
	cout << "3.按最大容纳人数区间索引" << endl;
	cout << "请输入索引方式[0-3]:";
	scanf("%d",&op);
	system("cls");
	switch (op)
	{
		case 0:return OK;
		case 1:cout << "请输入教学楼名称:"; cin >> building; break;
		case 2:cout << "请输入编号:"; cin >> room; break;
		case 3:cout << "请输入区间下界:"; cin >> left;
			cout << "请输入区间上界:"; cin >> right; break;
		default:return ERROR;
	}
	system("cls");
	cout << "索引结果:" << endl;
	for (it = All_Classroom.begin(); it != All_Classroom.end(); it++)
	{
		switch (op)
		{
			case 1:if ((*it)->building == building)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
			case 2:if ((*it)->room == room)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
			case 3:if ((*it)->max_capacity >= left && (*it)->max_capacity <= right)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
		}
	}
	if (!All_Classroom.size()) cout << endl;
	system("pause");
	return OK;
}

Status insertTeacherInfo()
{
	system("cls");
	TEACHER *pnew = new TEACHER;
	TEACHER_SET::iterator it;
	cout << "请输入教师姓名:";cin >> pnew->t_name;
	cout << "请输入教师任职学院:"; cin >> pnew->institute;
	if (cin.good())
	{
		it=my_find_if(All_Teacher.begin(),All_Teacher.end(),pnew->t_name,pnew->institute,0);
		if (it == All_Teacher.end())
		{
			All_Teacher.insert(pnew);
			return OK;
		}
		else
			return EXIST;
	}
	return ERROR;
}
Status deleteTeacherInfo()
{
	system("cls");
	string t_name, institute;
	TEACHER_SET::iterator it;
	LESSON_SET::iterator lesson_it;
	cout << "请输入教师姓名:";cin >> t_name;
	cout << "请输入教师任职学院:"; cin >> institute;
	it = my_find_if(All_Teacher.begin(), All_Teacher.end(), t_name, institute, 0);
	if (it != All_Teacher.end())
	{
		if (MessageBox(hWnd, TEXT("删除教师信息会将与之相关的课堂信息也删除"), TEXT("警告"), MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
		{
			for (lesson_it = (*it)->lessons.begin(); lesson_it != (*it)->lessons.end(); lesson_it++)
			{
				(*lesson_it)->deleteLessonSet(All_Time,All_Lesson);
				delete(*lesson_it);
			}
			All_Teacher.erase(it);
			return OK;
		}
		else return CANCEL;
	}
	return NOTEXIST;
}
Status modifyTeacherInfo()
{
	system("cls");
	char c;
	string t_name, institute;
	TEACHER_SET::iterator it, temp;
	cout << "请输入教师姓名:";cin >> t_name;
	cout << "请输入教师任职学院:"; cin >> institute;
	it = my_find_if(All_Teacher.begin(), All_Teacher.end(), t_name, institute, 0);
	if (it != All_Teacher.end())
	{
		system("cls");
		cout << "原信息:" << endl;
		cout << *(*it) << endl;
		cout << "请输入要修改的信息(N表示不修改)"<<endl;
		cout << "教师姓名:"; cin >> c; if (c != 'N') { cin.putback(c); cin >> t_name; }
		cout << "教室任职学院:";cin >> c; if (c != 'N') { cin.putback(c); cin >> institute; } 
		temp = my_find_if(All_Teacher.begin(), All_Teacher.begin(), t_name, institute, 0);
		if (temp != All_Teacher.end())
		{
			(*it)->t_name = t_name;
			(*it)->institute = institute;
			return OK;
		}
		else 
			return EXIST;
	}
	return NOTEXIST;
}
Status findTeacherInfo()
{
	system("cls");
	string t_name, institute;
	TEACHER_SET::iterator it;
	LESSON_SET::iterator iter;
	cout << "请输入教师姓名:";cin >> t_name;
	cout << "请输入教师任职学院:"; cin >> institute;

	it = my_find_if(All_Teacher.begin(), All_Teacher.end(), t_name, institute, 0);
	if (it != All_Teacher.end())
	{
		system("cls");
		cout << "教师姓名:" << (*it)->t_name << endl;
		cout << "教室任职学院:" << (*it)->institute << endl;
		cout << "与该教师有关的课堂信息:" << endl;
		iter = (*it)->lessons.begin();
		for (int i = 1; iter != (*it)->lessons.end(); i++, iter++)
		{
			cout << "课堂序号" << i << endl;
			cout << *(*iter) << endl;
		}
		system("pause");
		return OK;
	}
	return NOTEXIST;
}
Status retrieveTeacherInfo()
{
	system("cls");
	int  op, count = 0;
	string t_name, institute;
	TEACHER_SET::iterator it;
	cout << "索引方式:" << endl;
	cout << "1.按教师姓名索引" << endl;
	cout << "2.按学院索引" << endl;
	cout << "请输入索引方式[0-2]:";
	scanf("%d",&op);
	system("cls");
	switch (op)
	{
		case 0:return OK;
		case 1:cout << "请输入教师姓名:"; cin >> t_name; break;
		case 2:cout << "请输入学院名称:"; cin >> institute; break;
		default:return ERROR;
	}
	system("cls");
	cout << "索引结果:" << endl;
	for (it = All_Teacher.begin(); it != All_Teacher.end(); it++)
	{
		switch (op)
		{
			case 1:if ((*it)->t_name == t_name)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
			case 2:if ((*it)->institute == institute)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
		}
	}
	system("pause");
	return OK;
}

Status insertClassInfo()
{
	system("cls");
	char c;
	string name;
	CLASS *pnew = new CLASS;
	CLASS_SET::iterator it;
	COURSE_SET::iterator course_it;
	cout << "请输入班级名称:";cin >> pnew->c_name;
	cout << "请输入班级所在学院:"; cin >> pnew->institute;
	if (cin.good())
	{
		it = my_find_if(All_Class.begin(), All_Class.end(), pnew->c_name, "", 1);
		if (it == All_Class.end())
		{
			cout << "请输入班级人数:"; cin >> pnew->student_num;
			cout << "请输入班级已经学过的课程:";
			for (int i = 1;; i++)
			{
				cout << "第" << i << "门课程名称或ID:";
				cin >> c;
				if (c != 'N')
				{
					cin.putback(c);
					cin >> name;
					if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), name, name, 3)) == All_Course.end())
					{
						delete pnew;
						return NOTEXIST;
					}
					pnew->learned.insert(*course_it);
				}
				else break;
			}
			All_Class.insert(pnew);
			return OK;
		}
		else
		{
			delete pnew;
			return EXIST;
		}
	}
	delete pnew;
	return ERROR;
}
Status deleteClassInfo()
{
	system("cls");
	string c_name;
	CLASS_SET::iterator it;
	LESSON_SET::iterator lesson_it;
	cout << "请输入待删除班级名称:"; cin >> c_name;
	it = my_find_if(All_Class.begin(), All_Class.end(), c_name, "", 1);
	if (it != All_Class.end())
	{
		if (MessageBox(hWnd, TEXT("删除班级信息会将与之相关的课堂信息也删除"), TEXT("警告"), MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
		{
			for (lesson_it = (*it)->lessons.begin(); lesson_it != (*it)->lessons.end(); lesson_it++)
			{
				(*lesson_it)->deleteLessonSet(All_Time,All_Lesson);
				delete(*lesson_it);
			}
			All_Class.erase(it);
			return OK;
		}
		else return CANCEL;
	}
	return NOTEXIST;
} 
Status modifyClassInfo()
{
	system("cls");
	bool mark = false;;
	char c;
	int student_num;
	string c_name, institute, name;
	CLASS_SET::iterator it, temp;
	COURSE_SET::iterator course_it;
	COURSE_SET learned;
	cout << "请输入待修改班级名称:"; cin >> c_name;
	it = my_find_if(All_Class.begin(), All_Class.end(), c_name, "", 1);
	if (it != All_Class.end())
	{
		system("cls");
		cout << "原信息:" << endl;
		cout << *(*it) << endl;
		student_num = (*it)->student_num;
		cout << "请输入要修改的信息(N表示不修改)";
		cout << "班级名称:"; cin >> c; if (c != 'N') { cin.putback(c); cin >> c_name; }
		cout << "班级所在学院:";cin >> c; if (c != 'N') { cin.putback(c); cin >> institute; } 
		cout << "班级学生人数:"; cin >> c; if (c != 'N') { cin.putback(c); cin >>student_num; }
		cout << "班级学过课程:" << endl;
		if (cin >> c && c != 'N')
		{
			mark = true;
			for (int i = 1;; i++)
			{
				cout << "第" << i << "门课程名称或ID:";
				cin >> c;
				if (c != 'N')
				{
					cin.putback(c);
					cin >> name;
					if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), name, name, 3)) == All_Course.end())
						return ERROR;
					learned.insert(*course_it);
				}
				else break;
			}
		}
		temp = my_find_if(All_Class.begin(), All_Class.begin(), c_name, "", 1);
		if (temp != All_Class.end())
		{
			(*it)->c_name = c_name;
			(*it)->institute = institute;
			(*it)->student_num = student_num;
			if (mark) (*it)->learned = learned;
			return OK;
		}
		else 
			return EXIST;
	}
	return NOTEXIST;
}
Status findClassInfo()
{
	system("cls");
	string c_name;
	CLASS_SET::iterator it;
	COURSE_SET::iterator course_it;
	LESSON_SET::iterator iter;
	cout << "请输入待查询班级名称:"; cin >> c_name;
	it = my_find_if(All_Class.begin(), All_Class.end(), c_name, "", 1);
	if (it != All_Class.end())
	{
		system("cls");
		cout << "班级名称:" << (*it)->c_name << endl;
		cout << "班级所在学院:" << (*it)->institute << endl;
		cout << "班级学生人数:" << (*it)->student_num << endl;
		cout << "班级已学课程:";
		for (course_it = (*it)->learned.begin(); course_it != (*it)->learned.end(); course_it++)
		{
			cout << (*course_it)->name << " ";
		}
		cout << endl;
		cout << "与该班级有关的课堂信息:" << endl;
		iter = (*it)->lessons.begin();
		for (int i = 1; iter != (*it)->lessons.end(); i++, iter++)
		{
			cout << "课堂序号" << i << endl;
			cout << *(*iter) << endl;
		}
		system("pause");
		return OK;
	}
	return NOTEXIST;
}
Status retrieveClassInfo()
{
	system("cls");
	int left, right, op, count = 0;
	string c_name, institute;
	CLASS_SET::iterator it;
	cout << "索引方式:" << endl;
	cout << "1.按班级名称索引" << endl;
	cout << "2.按学院索引" << endl;
	cout << "3.按学生人数区间索引" << endl;
	cout << "请输入索引方式[0-3]:";
	scanf("%d",&op);
	system("cls");
	switch (op)
	{
		case 0:return OK;
		case 1:cout << "请输入班级名称:"; cin >> c_name; break;
		case 2:cout << "请输入学院名称:"; cin >> institute; break;
		case 3:cout << "请输入区间下界:"; cin >> left;
			cout << "请输入区间上界:"; cin >> right; break;
		default:return ERROR;
	}
	system("cls");
	cout << "索引结果:" << endl;
	for (it = All_Class.begin(); it != All_Class.end(); it++)
	{
		switch (op)
		{
			case 1:if ((*it)->c_name == c_name)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
			case 2:if ((*it)->institute == institute)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
			case 3:if ((*it)->student_num >= left && (*it)->student_num <= right)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
		}
	}
	system("pause");
	return OK;
}

Status insertCourseInfo()
{
	system("cls");
	char c;
	string name;
	COURSE *pnew = new COURSE;
	COURSE_SET::iterator it;
	cout << "请输入课程ID:";cin >> pnew->ID;
	cout << "请输入课程名称:"; cin >> pnew->name;
	if (cin.good())
	{
		it=my_find_if(All_Course.begin(),All_Course.end(),pnew->ID,pnew->name,3);
		if (it == All_Course.end())
		{
			cout << "请输入以该课程为专业课的学院:"; cin >> pnew->institute;
			cout << "请输入该门课程需要的基础课程:" << endl;
			for (int i = 1;; i++)
			{
				cout << "第" << i << "门课程:";
				if (cin >> c && c != 'N') 
				{ 
					cin.putback(c); 
					cin >> name;
					if ((it = my_find_if(All_Course.begin(), All_Course.end(), name, name, 3)) == All_Course.end())
					{
						delete(pnew);
						return NOTEXIST;
					}
					else
					{
						pnew->require.insert(*it);
					}
				}
				else break;
			}
			All_Course.insert(pnew);
			return OK;
		}
		else
		{
			delete(pnew);
			return EXIST;
		}
	}
	delete(pnew);
	return ERROR;
}
Status deleteCourseInfo()
{
	system("cls");
	int op;
	string ID, name;
	COURSE_SET::iterator it;
	LESSON_SET::iterator lesson_it;
	cout << "请选择查找待删除课程方式:" << endl << "1.按课程ID查找" << endl << "2.按课程名称查找" << endl << "0.取消" << endl << "请输入操作数[0-2]:";
	scanf("%d",&op);
	system("cls");
	switch (op)
	{
		case 0:return CANCEL;
		case 1:cout << "请输入待删除课程ID:"; cin >> ID;
			it = my_find_if(All_Course.begin(), All_Course.end(), ID, name, 1);break;
		case 2:cout << "请输入待删除课程名称:"; cin >> name; 
			it = my_find_if(All_Course.begin(), All_Course.end(), ID, name, 2);break;
	}
	if (it != All_Course.end())
	{
		if (MessageBox(hWnd, TEXT("删除课程信息会将与之相关的课堂信息也删除"), TEXT("警告"), MB_OKCANCEL | MB_SYSTEMMODAL) == IDOK)
		{
			for (lesson_it = (*it)->lessons.begin(); lesson_it != (*it)->lessons.end(); lesson_it++)
			{
				(*lesson_it)->deleteLessonSet(All_Time,All_Lesson);
				delete(*lesson_it);
			}
			All_Course.erase(it);
			return OK;
		}
		else return CANCEL;
	}
	return NOTEXIST;
}
Status modifyCourseInfo()
{
	system("cls");
	bool mark = false;;
	char c;
	int op;
	string ID, name,institute,course_name;
	COURSE_SET::iterator it, temp, course_it;
	COURSE_SET require;
	cout << "请选择查找待修改课程方式:" << endl << "1.按课程ID查找" << endl << "2.按课程名称查找" << endl << "0.取消" << endl << "请输入操作数[0-2]:";
	scanf("%d",&op);
	system("cls");
	switch (op)
	{
		case 0:return CANCEL;
		case 1:cout << "请输入待修改课程ID:"; cin >> ID;
			it = my_find_if(All_Course.begin(), All_Course.end(), ID, name, 1);break;
		case 2:cout << "请输入待修改课程名称:"; cin >> name; 
			it = my_find_if(All_Course.begin(), All_Course.end(), ID, name, 2);break;
	}

	if (it != All_Course.end())
	{
		system("cls");
		cout << "原信息:" << endl;
		cout << *(*it) << endl;
		ID = (*it)->ID;
		name = (*it)->name;
		institute = (*it)->institute;
		cout << "请输入要修改的信息(N表示不修改)"<<endl;
		cout << "课程ID:"; cin >> c; if (c != 'N') { cin.putback(c); cin >> ID; }
		cout << "课程名称:";cin >> c; if (c != 'N') { cin.putback(c); cin >> name; } 
		cout << "以该课程为专业课的学院:"; cin >> c; if (c != 'N') { cin.putback(c); cin >>institute; }
		cout << "该门课需要的基础课:";
		if (cin >> c && (c != 'N'))
		{
			mark = true;
			for (int i = 1;; i++)
			{
				cout << "第" << i << "门课程ID或名称:";
				if (cin >> c && c != 'N') 
				{ 
					cin.putback(c); 
					cin >> course_name;
					if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), course_name, course_name, 3)) == All_Course.end())
					{
						return NOTEXIST;
					}
					else
					{
						require.insert(*course_it);
					}
				}
				else break;
			}
		}

		temp = my_find_if(All_Course.begin(), All_Course.begin(), ID, name, 3);
		if (temp != All_Course.end())
		{
			(*it)->ID = ID;
			(*it)->name = name;
			(*it)->institute = institute;
			if (mark)
				(*it)->require = require;
			return OK;
		}
		else 
			return EXIST;
	}
	return NOTEXIST;
}
Status findCourseInfo()
{
	system("cls");
	int op;
	string ID, name;
	COURSE_SET::iterator it,temp;
	LESSON_SET::iterator iter;

	cout << "请选择查找方式:" << endl << "1.按课程ID查找" << endl << "2.按课程名称查找" << endl << "0.取消" << endl << "请输入操作数[0-2]:";
	scanf("%d",&op);
	system("cls");
	switch (op)
	{
		case 0:return CANCEL;
		case 1:cout << "请输入待查找课程ID:"; cin >> ID;
			it = my_find_if(All_Course.begin(), All_Course.end(), ID, name, 1);break;
		case 2:cout << "请输入待查找课程名称:"; cin >> name; 
			it = my_find_if(All_Course.begin(), All_Course.end(), ID, name, 2);break;
	}

	it = my_find_if(All_Course.begin(), All_Course.end(), ID, name, 3);
	if (it != All_Course.end())
	{
		system("cls");
		cout << "课程ID:" << (*it)->ID << endl;
		cout << "课程名称:" << (*it)->name << endl;
		cout << "以该课程为专业课学院:" << (*it)->institute << endl;
		cout << "该门课程需要的基础课程:";
		for (temp = (*it)->require.begin(); temp != (*it)->require.end(); temp++)
		{
			cout << (*temp)->name << " ";
		}
		cout << endl;
		cout << "与该课程有关的课堂信息:" << endl;
		iter = (*it)->lessons.begin();
		for (int i = 1; iter != (*it)->lessons.end(); i++, iter++)
		{
			cout << "课堂序号" << i << endl;
			cout << *(*iter) << endl;
		}
		system("pause");
		return OK;
	}
	return NOTEXIST;
}
Status retrieveCourseInfo()
{
	system("cls");
	int  op, count = 0;
	string ID, name, institute;
	COURSE_SET::iterator it;
	cout << "索引方式:" << endl;
	cout << "1.按课程ID索引" << endl;
	cout << "2.按课程名称索引" << endl;
	cout << "3.按学院索引" << endl;
	cout << "请输入索引方式[0-3]:";
	scanf("%d",&op);
	system("cls");
	switch (op)
	{
		case 0:return OK;
		case 1:cout << "请输入课程ID:"; cin >> ID; break;
		case 2:cout << "请输入课程名称:"; cin >> name; break;
		case 3:cout << "请输入学院名称:"; cin >> institute; break;
		default:return ERROR;
	}
	system("cls");
	cout << "索引结果:" << endl;
	for (it = All_Course.begin(); it != All_Course.end(); it++)
	{
		switch (op)
		{
			case 1:if ((*it)->ID == ID)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
			case 2:if ((*it)->name == name)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
			case 3:if ((*it)->institute == institute)
				cout << "索引编号:" << ++count << endl << *(*it) << endl; break;
		}
	}
	system("pause");
	return OK;
}

Status insertLessonInfo()
{
	system("cls");
	int day;
	string name, t_name,c_name;
	string building, room;
	string weeks,period;
	LESSON *pnew = new LESSON;
	LESSON_SET::iterator it;
	CLASSROOM_SET::iterator classroom_it;
	TEACHER_SET::iterator teacher_it;
	CLASS_SET::iterator class_it;
	COURSE_SET::iterator course_it;

	cout << "请输入课堂的课程名称:"; cin >> name;
	course_it = my_find_if(All_Course.begin(), All_Course.end(), "", name, 2);
	if (course_it == All_Course.end()) return 2;
	pnew->course = *course_it;

	cout << "请输入上课教室所在教学楼:"; cin >> building;
	cout << "请输入上课教室的编号:"; cin >> room;
	classroom_it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0);
	if (classroom_it == All_Classroom.end()) return 3;
	pnew->classroom = *classroom_it;

	cout << "请输入上课周数:"; cin >> weeks;
	cout << "请输入上课星期:"; cin >> pnew->day;
	cout << "请输入上课节数:"; cin >> pnew->period;
	pnew->getWeeks(weeks);
	pnew->classroom = *classroom_it;
	if (pnew->conflictDetection(All_Time) != NULL) return 4;

	cout << "请输入课堂教师名称:"; cin >> t_name;
	teacher_it = my_find_if(All_Teacher.begin(), All_Teacher.end(), t_name, "", 1);
	if (teacher_it == All_Teacher.end()) return 5;
	pnew->teacher = *teacher_it;

	cout << "上课班级信息:" << endl;
	for (int i = 1;; i++)
	{
		cout << "请输入第" << i << "个班级名称:"; cin >> c_name;
		if (c_name == "N")	break;
		else
		{
			class_it = my_find_if(All_Class.begin(), All_Class.end(), c_name, "", 1);
			if (class_it != All_Class.end())
			{
				pnew->classes.insert(*class_it);
			}
			else return 6;
		}
	}

	pnew->insertLessonSet(All_Time,All_Lesson);

	return OK;
}
Status deleteLessonInfo()
{
	system("cls");
	int day,week;
	string  period, building, room;
	CLASSROOM *temp;
	LESSON *target = NULL;
	LESSON_SET::iterator lesson_it;
	CLASS_SET::iterator class_it;
	CLASSROOM_SET::iterator classroom_it;
	cout << "请输入待删除课堂任意一周次"; cin >> week;
	cout << "请输入待删除课堂的星期:"; cin >> day;
	cout << "请输入待删除课堂的节数:"; cin >> period;
	cout << "请输入待删除课堂的教学楼信息:"; cin >> building;
	cout << "请输入待删除课堂的教室编号:"; cin >> room;
	classroom_it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0);
	if (classroom_it != All_Classroom.end())
	{
		temp = *classroom_it;
		for (lesson_it = temp->lessons.begin(); lesson_it != temp->lessons.end(); lesson_it++)
		{
			if ((*lesson_it)->weeks[week]&&(*lesson_it)->day == day && (*lesson_it)->period == period)
			{
				target = *lesson_it;
				break;
			}
		}
		if (target)
		{
			target->deleteLessonSet(All_Time, All_Lesson);
			return OK;
		}
		return NOTEXIST;
	}
	return 2;
}
Status modifyLessonInfo()
{
	system("cls");
	char c;
	int day, week;
	string t_name, c_name, name;
	string weeks, period, building, room;
	CLASSROOM *temp;
	LESSON *target = NULL;
	LESSON *pnew;
	LESSON_SET::iterator lesson_it;
	CLASSROOM_SET::iterator classroom_it;
	TEACHER_SET::iterator teacher_it;
	CLASS_SET::iterator class_it;
	COURSE_SET::iterator course_it;
	cout << "请输入待修改课堂任意一周次"; cin >> week;
	cout << "请输入待修改课堂的星期:"; cin >> day;
	cout << "请输入待修改课堂的节数:"; cin >> period;
	cout << "请输入待修改课堂的教学楼信息:"; cin >> building;
	cout << "请输入待修改课堂的教室编号:"; cin >> room;
	classroom_it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0);
	if (classroom_it != All_Classroom.end())
	{
		temp = *classroom_it;
		for (lesson_it = temp->lessons.begin(); lesson_it != temp->lessons.end(); lesson_it++)
		{
			if ((*lesson_it)->weeks[week]&&(*lesson_it)->day == day && (*lesson_it)->period == period)
			{
				target = *lesson_it;
				break;
			}
		}
		if (target)
		{
			system("cls");
			cout << "原信息:" << endl;
			cout << *target << endl;
			cout << "请输入要修改的信息(N表示不修改)"<<endl;
			pnew = new LESSON;
			*pnew = *target;
			t_name = target->teacher->t_name;
			name = target->course->name;
			cout << "上课周数:"; if (cin >> c && c != 'N') { cin.putback(c); cin >> week; pnew->getWeeks(weeks); }
			cout << "上课星期:"; if (cin >> c && c != 'N') { cin.putback(c); cin >> pnew->day; }
			cout << "上课节数:"; if (cin >> c && c != 'N') { cin.putback(c); cin >> pnew->period; }

			cout << "上课教室所在教学楼:";if (cin >> c && c != 'N') { cin.putback(c); cin >> building; }
			cout << "上课教室编号:";if (cin >> c && c != 'N') { cin.putback(c); cin >> room; }
			if ((classroom_it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0)) == All_Classroom.end()) return 2;
			if (pnew->conflictDetection(All_Time) != NULL && pnew->conflictDetection(All_Time) != target)	return 3;

			cout << "上课教师姓名:"; if (cin >> c && c != 'N') { cin.putback(c); cin >> t_name; }
			if ((teacher_it = my_find_if(All_Teacher.begin(), All_Teacher.end(), t_name, "", 1)) == All_Teacher.end()) return 4;

			cout << "上课课程名:";if (cin >> c && c != 'N') { cin.putback(c); cin >> name; }
			if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), "",name, 2)) == All_Course.end()) return 5;

			cout << "上课班级信息(N结束):" << endl;
			if (cin >> c && c != 'N')
			{
				pnew->classes.clear();
				for (int i = 1;; i++)
				{
					cout << "请输入第" << i << "个班级名称:"; cin >> c_name;
					if (c_name == "N")	break;
					else
					{
						class_it = my_find_if(All_Class.begin(), All_Class.end(), c_name, "", 1);
						if (class_it != All_Class.end())
						{
							pnew->classes.insert(*class_it);
						}
						else return 6;
					}
				}
			}

			target->deleteLessonSet(All_Time, All_Lesson);
			delete(target);
			pnew->insertLessonSet(All_Time, All_Lesson);

			return OK;
		}
		return NOTEXIST;
	}
	return 2;
}
Status findLessonInfo()
{
	system("cls");
	int day,week;
	string  period, building, room;
	CLASSROOM *temp;
	LESSON *target = NULL;
	LESSON_SET::iterator lesson_it;
	CLASS_SET::iterator class_it;
	CLASSROOM_SET::iterator classroom_it;
	cout << "请输入待查询课堂任意一周次:"; cin >> week;
	cout << "请输入待查询课堂的星期:"; cin >> day;
	cout << "请输入待查询课堂的节数:"; cin >> period;
	cout << "请输入待查询课堂的教学楼信息:"; cin >> building;
	cout << "请输入待查询课堂的教室编号:"; cin >> room;
	classroom_it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0);
	if (classroom_it != All_Classroom.end())
	{
		temp = *classroom_it;
		for (lesson_it = temp->lessons.begin(); lesson_it != temp->lessons.end(); lesson_it++)
		{
			if ((*lesson_it)->weeks[week]&&(*lesson_it)->day == day && (*lesson_it)->period == period)
			{
				target = *lesson_it;
				break;
			}
		}
		if (target)
		{
			system("cls");
			cout << "查询结果:" << endl;
			cout << *target << endl;
			system("pause");
			return OK;
		}
		return NOTEXIST;
	}
	return 2;
}
Status retrieveLessonInfo()
{
	system("cls");
	int op, count = 0;
	int day,week;
	string  period, building, room;
	string t_name, c_name, name;
	LESSON_SET *target = NULL;
	LESSON_SET::iterator lesson_it;
	CLASS_SET::iterator class_it;
	TEACHER_SET::iterator teacher_it;
	COURSE_SET::iterator course_it;
	CLASSROOM_SET::iterator classroom_it;
	PLACE::iterator place_it;
	PLACE *findout = NULL;

	cout << "索引方式:" << endl;
	cout << "1.按时间索引" << endl;
	cout << "2.按教室索引" << endl;
	cout << "3.按教师名称索引" << endl;
	cout << "4.按班级名称索引" << endl;
	cout << "5.按课程索引" << endl;
	cout << "请输入索引方式[0-5]:";scanf("%d",&op);
	
	system("cls");
	switch (op)
	{
		case 0:return OK;
		case 1:	cout << "请输入课堂任意一周次"; cin >> week;
				cout << "请输入课堂的星期:"; cin >> day;
				cout << "请输入课堂的节数:"; cin >> period;
				if (All_Time.find(week) == All_Time.end() || All_Time[week].find(day) == All_Time[week].end() || All_Time[week][day].find(period) == All_Time[week][day].end())
					return 2;
				findout = &All_Time[week][day][period];break;
		case 2:	cout << "请输入课堂的教学楼信息:"; cin >> building;
				cout << "请输入课堂的教室编号:"; cin >> room; 
				if ((classroom_it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0)) == All_Classroom.end())
					return 3;
				target = &(*classroom_it)->lessons;
				break;
		case 3:cout << "请输入教师名称:"; cin >> t_name; 
				if ((teacher_it = my_find_if(All_Teacher.begin(), All_Teacher.end(), t_name, "", 1)) == All_Teacher.end())
					return 4;
				target = &(*teacher_it)->lessons;
				break;
		case 4:cout << "请输入班级名称:"; cin >> c_name; 
				if ((class_it = my_find_if(All_Class.begin(), All_Class.end(), c_name, "", 1)) == All_Class.end())
					return 5;
				target = &(*class_it)->lessons;
				break;
		case 5:cout << "请输入课程ID或名称:"; cin >> name;
				if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), name, "", 1)) == All_Course.end())
					if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), "", name, 1)) == All_Course.end())
						return 6;
				target = &(*course_it)->lessons;
				break;
		default:return ERROR;
	}
	system("cls");
	cout << "索引结果:" << endl;
	if (op == 1)
	{
		for (place_it = findout->begin(); place_it != findout->end(); place_it++)
		{
			cout << "索引编号:" << ++count << endl << *(*place_it).second << endl;
		}
	}
	else
	{
		for (lesson_it = target->begin(); lesson_it != target->end(); lesson_it++)
		{
			cout << "索引编号:" << ++count << endl << *(*lesson_it) << endl;
		}
	}

	system("pause");
	return OK;
	
}

Status findEmptyClassroom()
{
	system("cls");
	int count = 0;
	int week, day;
	string period, building;
	PLACE *temp = NULL;
	CLASSROOM_SET busy;
	CLASSROOM_SET::iterator classroom_it;
	PLACE::iterator place_it;
	cout << "请输入要查询的周次:"; cin >> week;
	cout << "请输入要查询的星期:"; cin >> day;
	cout << "请输入要查询的节次:"; cin >> period;
	cout << "请输入教学楼名称:"; cin >> building;
	if (All_Time.find(week) != All_Time.end())
	{
		if (All_Time[week].find(day) != All_Time[week].end())
		{
			if (All_Time[week][day].find(period) != All_Time[week][day].end())
			{
				temp = &All_Time[week][day][period];
				for (place_it = temp->begin(); place_it != temp->end(); place_it++)
				{
					busy.insert(place_it->first);
				}
			}
		}
	}
	cout << endl << "查询结果:"<<endl;
	cout << setw(5) << left << "序号" << setw(15) << left << "教学楼名称" << setw(5) << left << "教室编号" << endl;
	for (classroom_it = All_Classroom.begin(); classroom_it != All_Classroom.end(); classroom_it++)
	{
		if ((*classroom_it)->building == building && busy.find(*classroom_it) == busy.end())
		{
			cout << setw(5) << left << ++count << setw(15) << left << (*classroom_it)->building << setw(5) << left << (*classroom_it)->room << endl;
		}
	}
	system("pause");
	return OK;
}
Status utilizationAnalysis()
{
	system("cls");
	int op;
	int week, day;
	double specific_day;
	string building, room;
	CLASSROOM_SET used;
	CLASSROOM_SET::iterator classroom_it;
	TIME_MAP::iterator it;
	DAY::iterator day_it;
	PERIOD::iterator period_it;
	PLACE::iterator place_it;
	double average[MAX_WEEK] = { 0 };

	cout << "分析内容:" << endl;
	cout << "1.具体某一天教室利用率" << endl;
	cout << "2.具体某一教室利用率" << endl;
	cout << "3.所有教室每周利用率" << endl;
	cout << "0.取消" << endl;
	cout << "请输入操作数[0-3]:"; 
	scanf("%d", &op);
	system("cls");
	switch (op)
	{
		case 1:
			cout << "请输入周次:"; cin >> week;
			cout << "请输入星期:"; cin >> day;

			if (All_Time.find(week) == All_Time.end())
			{
				specific_day = 0;
			}
			else if (All_Time[week].find(day) == All_Time[week].end())
			{
				specific_day = 0;
			}
			else
			{
				for (period_it = All_Time[week][day].begin(); period_it != All_Time[week][day].end(); period_it++)
					for (place_it = period_it->second.begin(); place_it != period_it->second.end(); place_it++)
					{
						used.insert(place_it->first);
					}
				specific_day = used.size() / (double)All_Classroom.size();

			}
			cout << endl;
			cout << "第" << week << "周 星期" << day << " 的教室利用率为:" << specific_day * 100 << "%" << endl;
			system("pause");
			return OK;
		case 2:
			cout << "请输入教学楼:"; cin >> building;
			cout << "请输入教室编号:"; cin >> room;

			if ((classroom_it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0)) == All_Classroom.end())
			{
				return NOTEXIST;
			}
			cout << endl;
			cout << "该教室各周利用率:" << endl;
			cout << setw(5) << left << "周次" << setw(10) << left << "利用率(%)" << endl;
			for (int i = 1, count = 0; i < MAX_WEEK; i++)
			{
				if (All_Time.find(i) != All_Time.end())
				{
					count = 5;
					for (day_it = All_Time[i].begin(); day_it != All_Time[i].end(); day_it++)
					{
						for (period_it = day_it->second.begin(); period_it != day_it->second.end(); period_it++)
						{
							if (period_it->second.find(*classroom_it) != period_it->second.end())
							{
								average[i]++;
								break;
							}
						}
						if (day_it->first == 6 || day_it->first == 7)
							count++;
					}
					average[i] /= count;
				}
				cout << setw(5) << left << i << setw(10) << left << average[i] * 100 << endl;
			}
			system("pause");
			return OK;
		case 3:
			cout << endl;
			cout << "各周教室利用率:" << endl;
			cout << setw(5) << left << "周次" << setw(10) << left << "教室利用率(%)" << endl;
	
			for (int i = 1, count = 0; i < MAX_WEEK; i++)
			{
				if (All_Time.find(i) != All_Time.end())
				{
					count = 5;
					for (day_it = All_Time[i].begin(); day_it != All_Time[i].end(); day_it++)
					{
						used.clear();
						for (period_it = day_it->second.begin(); period_it != day_it->second.end(); period_it++)
							for (place_it = period_it->second.begin(); place_it != period_it->second.end(); place_it++)
							{
								used.insert(place_it->first);
							}
						average[i] += used.size();
						if (day_it->first == 5 || day_it->first == 6)
							count++;
					}
					average[i] /= count * All_Classroom.size();
				}
				cout << setw(5) << left << i << setw(10) << left << average[i] * 100 << endl;
			}
			system("pause");
			return OK;
		case 0:return CANCEL;
		default:return ERROR;
	}
}
Status efficiencyAnalysis()
{
	system("cls");
	int op;
	int count = 0, student_num, night_num;
	stringstream ans1, ans2;
	string building, room;
	CLASSROOM_SET analysis_set;
	LESSON_SET::iterator lesson_it;
	CLASS_SET::iterator class_it;
	CLASSROOM_SET::iterator classroom_it;
	cout << "分析内容:" << endl;
	cout << "1.具体某一教室能效分析" << endl;
	cout << "2.所有教室能效分析" << endl;
	cout << "0.取消" << endl;
	cout << "请输入操作数[0-2]:";
	scanf("%d", &op);
	system("cls");

	switch (op)
	{
		case 1:
			cout << "请输入教学楼名称:"; cin >> building;
			cout << "请输入教室能效分析:"; cin >> room;
			if ((classroom_it = my_find_if(All_Classroom.begin(), All_Classroom.end(), building, room, 0)) == All_Classroom.end())
			{
				return NOTEXIST;
			}
			analysis_set.insert(*classroom_it);
			break;
		case 2:
			analysis_set = All_Classroom;
			cout << setw(5) << left << "序号" << setw(12) << left << "教学楼" << setw(10) << left << "教室编号" << setw(15) << left << "平均能效(%)" << setw(10) << left << "夜间课程占比(%)" << endl;
			break;
		case 0:return CANCEL;
		default:return ERROR;
	}

	for (classroom_it = analysis_set.begin(); classroom_it != analysis_set.end(); classroom_it++)
	{
		night_num = 0;
		student_num = 0;
		for (lesson_it = (*classroom_it)->lessons.begin(); lesson_it != (*classroom_it)->lessons.end(); lesson_it++)
		{
			for (class_it = (*lesson_it)->classes.begin(); class_it != (*lesson_it)->classes.end(); class_it++)
			{
				student_num += (*class_it)->student_num;
			}
			if ((*lesson_it)->period == "9-12" || (*lesson_it)->period == "9-10" || (*lesson_it)->period == "11-12")
			{
				night_num++;
			}
		}
		ans1.str("");
		ans2.str("");
		if ((*classroom_it)->max_capacity*(*classroom_it)->lessons.size())
			ans1 << (double)student_num * 100 / ((*classroom_it)->max_capacity*(*classroom_it)->lessons.size());
		else
			ans1 << "---";
		if ((*classroom_it)->lessons.size())
			ans2 << (double)night_num * 100 / (*classroom_it)->lessons.size();
		else 
			ans2 << "---";
		switch (op)
		{
			case 1:cout << "该教室平均能效为:" << ans1.str() << "%" << endl;
				cout << "该教室夜间课程占比为:" << ans2.str() << "%" << endl; break;
			case 2:
				cout << setw(5) << left << ++count << setw(12) << left << (*classroom_it)->building << setw(10) << left << (*classroom_it)->room
					<< setw(15) << left << ans1.str()<< setw(10) << left << ans2.str() << endl;
				break;
		}
	}
	system("pause");
	return OK;
}

Status teacherValidityAnalysis()
{
	//分析内容 教师上课频次 上课时间(晚上还是周末) 教师上课地点变化 教师所上课程合理性 矛盾检测 
	//perfect great good well bad
	system("cls");
	bool contra = false;
	int op, temp1, temp2, rating, count = 0;
	bool has_course[MAX_WEEK];
	double lesson_num, week_num, night_num, weekend_num, change_num, right_num;
	string t_name;
	string rate[7] = { "Perfect","Great","Good","Well","Not Bad","Bad", "Awful"};
	stringstream ans1, ans2, ans3, ans4, ans5, ans6;
	TEACHER_SET analysis_set;
	TEACHER_SET::iterator teacher_it;
	LESSON_SET::iterator lesson_it,lesson_it2;

	cout << "分析内容:" << endl;
	cout << "1.具体某一位教师课堂合理性分析" << endl;
	cout << "2.所有教师课堂合理性分析" << endl;
	cout << "0.取消" << endl;
	cout << "请输入操作数[0-2]:"; 
	scanf("%d", &op);
	system("cls");

	switch (op)
	{
		case 1:cout << "请输入教师名称:"; cin >> t_name;
			if ((teacher_it = my_find_if(All_Teacher.begin(), All_Teacher.end(), t_name, "", 1)) == All_Teacher.end())
				return NOTEXIST;
			system("cls");
			analysis_set.insert(*teacher_it); break;
		case 2:analysis_set = All_Teacher;
			cout << setw(5) << left << "序号" << setw(9) << left << "教师姓名" << setw(9) << left << "课程冲突" << setw(9) << left << "地点突变"
				<< setw(9) << left << "上课频次" << setw(9) << left << "晚间课程" << setw(9) << left << "周末课程"
				<< setw(11) << left << "课程匹配度" << setw(8) << left << "总体评级" << endl;break;
		case 0:return CANCEL;
		default:return ERROR;
	}
	
	for (teacher_it = analysis_set.begin(); teacher_it != analysis_set.end(); teacher_it++)
	{
		contra = false;
		memset(has_course, 0, sizeof(has_course));
		lesson_num = week_num = night_num = weekend_num = change_num = right_num = 0;
		for (lesson_it = (*teacher_it)->lessons.begin(); lesson_it != (*teacher_it)->lessons.end(); lesson_it++)
		{
			int temp = 0;
			for (int i = 1; i < MAX_WEEK; i++)
			{
				if ((*lesson_it)->weeks[i])
				{
					for (lesson_it2 = lesson_it, lesson_it2++; lesson_it2 != (*teacher_it)->lessons.end(); lesson_it2++)
					{
						if ((*lesson_it2)->weeks[i])
						{
							if ((*lesson_it)->day == (*lesson_it2)->day)
							{
								if ((*lesson_it)->period == (*lesson_it2)->period)			//矛盾检测
								{
									contra = true;
								}
								else														//更换地点检测
								{
									temp1 = (*lesson_it)->period[0] - '0';
									temp2 = (*lesson_it2)->period[0] - '0';
									if (temp1 < 5 && temp2 < 5 && abs(temp1 - temp2) == 2
										|| temp1 == 5 && temp2 == 7 || temp1 == 7 && temp2 == 5)
									{
										if ((*lesson_it)->classroom->building != (*lesson_it2)->classroom->building)
											change_num++;
									}
								}
							}
						}
					}
					temp++;
					if (!has_course[i])
					{
						has_course[i] = true;
						week_num++;
					}
				}
			}				
			if ((*lesson_it)->course->institute == (*teacher_it)->institute)
				right_num += temp;
			if ((*lesson_it)->day == 6 || (*lesson_it)->day == 7)			//周末课程分析
				weekend_num+=temp;
			if ((*lesson_it)->period[0] - '0' > 8)
				night_num += temp;
			lesson_num+=temp;			//上课频次分析
		}
		if (lesson_num == 0)
		{
			ans1.str(" NO"); ans2.str(" NO");
			ans3.str("0"); ans4.str("0"); ans5.str("0");
			ans6.str("---");
			rating = 3;
		}
		else
		{
			rating = 0;
			ans1.str(" "); ans2.str(" ");  ans3.str(" "); ans4.str(" "); ans5.str(" "); ans6.str(" ");
			if (contra) ans1.str(" YES"), rating = 6;
			else ans1.str(" NO");
			if (change_num) ans2.str(" YES"), rating++;
			else ans2.str(" NO");
			ans3 << lesson_num / week_num;
			ans4 << night_num / lesson_num;
			ans5 << weekend_num / lesson_num;
			ans6 << right_num / lesson_num * 100;
			if (lesson_num / week_num >= 3) rating++;
			if (night_num / lesson_num > 0.33) rating++;
			if (weekend_num / lesson_num > 0.285) rating++;
			if (right_num / lesson_num < 0.9) rating++;
		}
		switch (op)
		{
			case 1:cout << "教师名称:" << (*teacher_it)->t_name << endl;
				cout << "教师承担课堂是否在时间地点上冲突:" << ans1.str() << endl;
				cout << "教师上课频次(节/周):" << ans3.str() << endl;
				cout << "教师晚上课频次(节/周):" << ans4.str() << endl;
				cout << "教师周末上课频次(节/周):" << ans5.str() << endl;
				cout << "教师上课地点是否突变:" << ans2.str() << endl;
				cout << "教师承担课程匹配度(%):" << ans6.str() << endl;
				cout << "总体课程合理度:" << rate[rating] << endl;
			case 2:
				cout << setw(5) << left << ++count << setw(9) << left << (*teacher_it)->t_name << setw(9) << left << ans1.str() << setw(9) << left << ans2.str()
					<< setw(9) << left << ans3.str() << setw(9) << left << ans4.str() << setw(9) << left << ans5.str()
					<< setw(11) << left << ans6.str() << setw(8) << left << rate[rating>6?6:rating] << endl;
		}
	}
	system("pause");
	return OK;
}
Status studentValidityAnalysis()
{
	//矛盾检测 学生上课地点变化 上课时间 学生这学期上的课的基础课程是否已经上过
	system("cls");
	bool contra = false, change = false, has_course[MAX_WEEK];
	int op, rating = 0, temp, count = 0;
	double lesson_num, week_num, night_num, weekend_num;
	string c_name;
	string rate[7] = { "Perfect","Great","Good","Well","Not Bad","Bad", "Awful"};
	stringstream ans1, ans2, ans3, ans4, ans5, ans6;
	CLASS_SET analysis_set;
	COURSE_SET unstudy;
	CLASS_SET::iterator class_it;
	COURSE_SET::iterator course_it;
	LESSON_SET::iterator lesson_it, lesson_it2;
	cout << "分析内容:" << endl;
	cout << "1.具体某一个班级课堂合理性分析" << endl;
	cout << "2.所有班级合理性分析" << endl;
	cout << "0.取消" << endl;
	cout << "请输入操作数[0-2]:";
	scanf("%d", &op);
	system("cls");

	switch (op)
	{
		case 1:cout << "请输入班级名称:"; cin >> c_name;
			if ((class_it = my_find_if(All_Class.begin(), All_Class.end(), c_name, "", 1)) == All_Class.end())
				return NOTEXIST;
			system("cls");
			analysis_set.insert(*class_it); break;
		case 2:analysis_set = All_Class;
			cout << setw(5) << left << "序号" << setw(13) << left << "班级名称" << setw(9) << left << "课程冲突" << setw(9) << left << "地点突变"
				<< setw(9) << left << "上课频次" << setw(9) << left << "晚间课程" << setw(9) << left << "周末课程"
				<< setw(9) << left << "需修课程" << setw(7) << left << "总体评级" << endl;break;
		case 0:return CANCEL;
		default:return ERROR;
	}

	for (class_it = analysis_set.begin(); class_it != analysis_set.end(); class_it++)
	{
		unstudy.clear();
		contra = change  = false;
		memset(has_course, 0, sizeof(has_course));
		lesson_num = week_num = night_num = weekend_num = 0;
		for (lesson_it = (*class_it)->lessons.begin(); lesson_it != (*class_it)->lessons.end(); lesson_it++)
		{
			temp = 0;
			for (int i = 1; i < MAX_WEEK; i++)
			{
				if ((*lesson_it)->weeks[i])
				{
					for (lesson_it2 = lesson_it, lesson_it2++; lesson_it2 != (*class_it)->lessons.end(); lesson_it2++)
					{
						if ((*lesson_it2)->weeks[i])									
						{
							if ((*lesson_it2)->day == (*lesson_it)->day)							
							{
								if ((*lesson_it2)->period == (*lesson_it)->period)				//冲突检测
								{
									contra = true;
								}
								else															//地点突变检测
								{
									int temp1 = (*lesson_it)->period[0] - '0', temp2 = (*lesson_it2)->period[0] - '0';
									if (temp1 / 4 == temp2 / 4 && abs(temp1 - temp2) == 2)
									{
										change = true;
									}
								}
							}
						}
					}
					temp++;
					if (!has_course[i])
					{
						has_course[i] = true;
						week_num++;
					}
				}
			}
			if ((*lesson_it)->period[0] > 8)
				night_num += temp;
			if ((*lesson_it)->day == 6 || (*lesson_it)->day == 7)
				weekend_num += temp;
			lesson_num += temp;

			for (course_it = (*lesson_it)->course->require.begin(); course_it != (*lesson_it)->course->require.end(); course_it++)
			{
				if ((*class_it)->learned.find(*course_it) == (*class_it)->learned.end())
				{
					unstudy.insert(*course_it);
				}
			}
		}

		if (!week_num)
		{
			ans1.str("NO");ans2.str("NO");
			ans3.str("0");ans4.str("0");ans5.str("0");
			ans6.str("0");
			rating = 3;
		}
		else
		{
			rating = 0;
			ans1.str(""); ans2.str(""); ans3.str(""); ans4.str(""); ans5.str(""); ans6.str("");
			if (contra) ans1.str("YES"), rating = 6;
			else ans1.str("NO");
			if (change) ans2.str("YES"), rating++;
			else ans2.str("NO");
			ans3 << lesson_num / week_num;
			ans4 << night_num / week_num;
			ans5 << weekend_num / week_num;
			ans6 << unstudy.size();
			if (lesson_num / week_num > 15) rating++;
			if (night_num / week_num > 0.33) rating++;
			if (weekend_num / week_num > 0.285) rating++;
			if (unstudy.size()) rating++;
		}
		switch (op)
		{
			case 1:cout << "班级名称:" << (*class_it)->c_name << endl;
				cout << "班级所上课程是否存在时间地点上的冲突:" << ans1.str() << endl;
				cout << "班级所上课程是否存在地点上的突变:" << ans2.str() << endl;
				cout << "班级上课频次(节/周):" << ans3.str() << endl;
				cout << "班级晚间课程频次(节/周):" << ans4.str() << endl;
				cout << "班级周末课程频次(节/周):" << ans5.str() << endl;
				cout << "班级还需修课程数:" << ans6.str() << endl;
				cout << "总体合理度评级:" << rate[rating];
			case 2:
				cout << setw(5) << left<<++count << setw(13) << left <<(*class_it)->c_name << setw(9) << left << ans1.str() << setw(9) << left << ans2.str()
				<< setw(9) << left << ans3.str() << setw(9) << left << ans4.str() << setw(9) << left << ans5.str()
				<< setw(9) << left << ans6.str() << setw(7) << left << rate[rating>6?6:rating] << endl;
		}
	}
	system("pause");
	return OK;
}

LESSON *LESSON::conflictDetection(TIME_MAP &source)
{
	TIME_MAP::iterator week_it;
	DAY::iterator day_it;
	PERIOD::iterator period_it;
	PLACE::iterator place_it;
	for (int i = 1; i < MAX_WEEK; i++)
	{
		if (weeks[i])
		{
			week_it=source.find(i);
			if (week_it != source.end())
			{
				day_it = week_it->second.find(day);
				if (day_it != week_it->second.end())
				{
					period_it = day_it->second.find(period);
					if (period_it != day_it->second.end())
					{
						place_it = period_it->second.find(classroom);
						if (place_it != period_it->second.end())	return place_it->second;
					}
				}
			}
		}
	}
	return NULL;
}
Status LESSON::insertTimeMap(TIME_MAP &source)
{
	DAY *new_day;
	PERIOD *new_period;
	PLACE *new_place;

	TIME_MAP::iterator week_it;
	DAY::iterator day_it;
	PERIOD::iterator period_it;
	PLACE::iterator place_it;
	for (int i = 1; i < MAX_WEEK; i++)
	{
		if (weeks[i])
		{
			week_it=source.find(i);
			if (week_it == source.end())
			{
				new_day = new DAY;
				source[i] = *new_day;
				week_it = source.find(i);
			}
			day_it = week_it->second.find(day);
			if (day_it == week_it->second.end())
			{
				new_period = new PERIOD;
				source[i][day] = *new_period;
				day_it = week_it->second.find(day);
			}
			period_it = day_it->second.find(period);
			if (period_it == day_it->second.end())
			{
				new_place = new PLACE;
				source[i][day][period] = *new_place;
				period_it = day_it->second.find(period);
			}
			source[i][day][period][classroom] = this;
		}
	}
	return OK;
}
Status LESSON::insertLessonSet(TIME_MAP &time_map,LESSON_SET &lesson_set)
{
	CLASS_SET::iterator class_it;

	classroom->lessons.insert(this);
	teacher->lessons.insert(this);
	course->lessons.insert(this);
	for (class_it = classes.begin(); class_it != classes.end(); class_it++)
	{
		(*class_it)->lessons.insert(this);
	}
	
	lesson_set.insert(this);

	insertTimeMap(time_map);
	
	return OK;
}
Status LESSON::deleteLessonSet(TIME_MAP &time_map,LESSON_SET &lesson_set)
{
	CLASS_SET::iterator class_it;

	classroom->lessons.erase(this);
	teacher->lessons.erase(this);
	course->lessons.erase(this);
	for (class_it = classes.begin(); class_it != classes.end(); class_it++)
	{
		(*class_it)->lessons.erase(this);
	}
	
	for (int i = 1; i < MAX_WEEK; i++)
	{
		if (weeks[i])
		{
			time_map[i][day][period].erase(classroom);
		}
	}

	lesson_set.erase(this);

	return OK;
}

std::ostream &operator<<(std::ostream &outPut, LESSON &lesson)
{
	outPut << "课程时间信息:" << std::endl;
	outPut << "第"<<getWeekString(lesson.weeks);
	outPut << "周 星期" << lesson.day << " " << lesson.period << "节" << std::endl << std::endl;

	outPut << "课堂地点信息:" << std::endl;
	outPut << *(lesson.classroom);
	outPut << std::endl;

	int count = 0;	
	outPut << "课堂教师信息:" << std::endl;
	outPut << "教师编号:" << count + 1 << std::endl;
	outPut << "教师名称:" << lesson.teacher->t_name << std::endl << std::endl;

	CLASS_SET::iterator it_classes=lesson.classes.begin();
	outPut << "上课班级信息:";
	outPut << "上课班级数量:" << lesson.classes.size() << std::endl;
	outPut << "上课班级:";
	for ( count = 0; it_classes != lesson.classes.end(); it_classes++)
	{
		outPut << (*it_classes)->c_name << " ";
		count += (*it_classes)->student_num;
	}
	outPut << std::endl;
	outPut << "课堂学生总数:" << count << std::endl << std::endl;
	
	outPut << "课程信息:" << std::endl;
	outPut << *(lesson.course);

	return outPut;
}
std::ostream &operator<<(std::ostream &outPut, CLASSROOM &classroom)
{
	outPut << "上课教学楼:" << classroom.building<<std::endl;
	outPut << "上课教室编号:" << classroom.room<<std::endl;
	outPut << "教室最大容量:" << classroom.max_capacity << "人" << std::endl;
	return outPut;
}
std::ostream &operator<<(std::ostream &outPut, TEACHER &teacher)
{
	outPut << "教师名称:" << teacher.t_name<<std::endl;
	outPut << "任职学院:" << teacher.institute << std::endl;
	return outPut;
}
std::ostream &operator<<(std::ostream &outPut, CLASS &Class)
{
	COURSE_SET::iterator course_it;
	outPut << "班级名称:" << Class.c_name << std::endl;
	outPut << "班级所在学院:" << Class.institute << std::endl;
	outPut << "学生人数:" << Class.student_num << std::endl;
	outPut << "已学课程:";
	for (course_it = Class.learned.begin(); course_it != Class.learned.end(); course_it++)
	{
		outPut << (*course_it)->name<<" ";
	}
	outPut << std::endl;
	return outPut;
}
std::ostream &operator<<(std::ostream &outPut, COURSE &course)
{
	outPut << "课程ID:" << course.ID << std::endl;
	outPut << "课程名称:" << course.name << std::endl;
	outPut << "以该门课为专业课的学院:" << course.institute << std::endl;
	outPut << "该门课需要的基础课程:";
	for (COURSE_SET::iterator it = course.require.begin(); it != course.require.end(); it++)
	{
		outPut << (*it)->name << " ";
	}
	outPut << endl;
	return outPut;
}

std::ifstream &operator>>(std::ifstream &inFile, CLASSROOM &classroom)
{
	std::string info;
	vector<string> bits;

	getline(inFile, info);
	getBits(bits, info);
	if (bits.size() < 3) return inFile;
	
	classroom.building = bits[0];
	classroom.room = bits[1];
	classroom.max_capacity = atoi(bits[2].c_str());
	
	return inFile;
}
std::ifstream &operator>>(std::ifstream &inFile, TEACHER &teacher)
{
	std::string info;
	vector<string> bits;
	
	getline(inFile, info);	
	getBits(bits, info);
	if (bits.size() < 2) return inFile;

	teacher.t_name = bits[0];
	teacher.institute = bits[1];

	return inFile;
}
std::ifstream &operator>>(std::ifstream &inFile, CLASS &Class)
{
	std::string info;
	vector<string> bits;
	COURSE_SET::iterator course_it;
	
	getline(inFile, info);
	getBits(bits, info);
	if (bits.size() < 3) return inFile;

	Class.c_name = bits[0];
	Class.institute = bits[1];
	Class.student_num = atoi(bits[2].c_str());

	for (int i = 3; i < bits.size(); i++)
	{
		if (bits[i] != "")
		{
			if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), bits[i], bits[i], 3)) == All_Course.end())
			{
				Class.c_name = "";
				return inFile;
			}
			Class.learned.insert(*course_it);
		}
		else break;
	}
	return inFile;
}
std::ifstream &operator>>(std::ifstream &inFile, COURSE &course)
{
	std::string info;
	vector<string> bits;
	COURSE_SET::iterator course_it;

	getline(inFile, info);
	getBits(bits, info);
	if (bits.size() < 3) return inFile;

	course.ID = bits[0];
	course.name = bits[1];
	course.institute = bits[2];

	for (int i = 3; i < bits.size(); i++)
	{
		if (bits[i] != "")
		{
			if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), bits[i], bits[i], 3)) == All_Course.end())
			{
				course.ID = "";
				return inFile;
			}
			course.require.insert(*course_it);
		}
		else break;
	}
	return inFile;
}
std::ifstream &operator>>(std::ifstream &inFile, LESSON &lesson)
{
	std::string info;
	vector<string> bits;
	vector<string>::iterator it;
	CLASSROOM_SET::iterator classroom_it;
	TEACHER_SET::iterator teacher_it;
	CLASS_SET::iterator class_it;
	COURSE_SET::iterator course_it;

	getline(inFile, info);
	getBits(bits, info);
	if (bits.size() < 8) return inFile;

	if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), bits[0], "", 1)) == All_Course.end())
		if ((course_it = my_find_if(All_Course.begin(), All_Course.end(), "", bits[0], 2)) == All_Course.end())
		{
			return inFile;
		}
	lesson.getWeeks(bits[1]);
	lesson.day = atoi(bits[2].c_str());
	lesson.period = bits[3];
	if ((classroom_it = my_find_if(All_Classroom.begin(), All_Classroom.end(), bits[4], bits[5], 0)) == All_Classroom.end())
	{
		return inFile;	
	}
	if ((teacher_it = my_find_if(All_Teacher.begin(), All_Teacher.end(), bits[6], "", 1)) == All_Teacher.end())
	{
		return inFile;
	}
	for (int i = 7; i < bits.size(); i++)
	{
		if (bits[i] != "")
		{
			if ((class_it = my_find_if(All_Class.begin(), All_Class.end(), bits[i], "", 1)) == All_Class.end())
			{
				lesson.classes.clear();
				return inFile;
			}
			lesson.classes.insert(*class_it);
		}
	}
	lesson.classroom = *classroom_it;
	lesson.teacher = *teacher_it;
	lesson.course = *course_it;
	return inFile;
}

std::ofstream &operator<<(std::ofstream &outFile, CLASSROOM &classroom)
{
	outFile << classroom.building << "," << classroom.room << "," << classroom.max_capacity << std::endl;
	return outFile;
}
std::ofstream &operator<<(std::ofstream &outFile, TEACHER &teacher)
{
	outFile << teacher.t_name << "," << teacher.institute << std::endl;
	return outFile;
}
std::ofstream &operator<<(std::ofstream &outFile, CLASS &Class)
{
	COURSE_SET::iterator it;
	outFile << Class.c_name << "," << Class.institute << "," << Class.student_num;
	for (it = Class.learned.begin(); it != Class.learned.end(); it++)
		outFile << "," << (*it)->name;
	outFile << std::endl;
	return outFile;
}
std::ofstream &operator<<(std::ofstream &outFile, COURSE &course)
{
	COURSE_SET::iterator it;
	outFile << course.ID << "," << course.name << "," << course.institute;
	for (it = course.require.begin(); it != course.require.end(); it++)
		outFile << "," << (*it)->name;
	outFile << std::endl;
	return outFile;
}
std::ofstream &operator<<(std::ofstream &outFile, LESSON &lesson)
{
	int npos;
	std::string temp = getWeekString(lesson.weeks);
	outFile << lesson.course->name << ",";
	if ((npos=temp.find(',')) >= 0)
		outFile << "\"" << temp << "\"";
	else
		outFile << temp;
	outFile << "," << lesson.day << "," << lesson.period << ",";
	outFile << lesson.classroom->building << "," << lesson.classroom->room << "," << lesson.teacher->t_name;
	for (CLASS_SET::iterator class_it = lesson.classes.begin(); class_it != lesson.classes.end(); class_it++)
	{
		outFile << "," << (*class_it)->c_name;
	}
	outFile << std::endl;
	return outFile;
}
