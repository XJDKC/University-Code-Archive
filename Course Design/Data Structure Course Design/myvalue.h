#pragma once

CLASS_SET All_Class;			//所有班级信息
TEACHER_SET All_Teacher;		//所有的教师信息
CLASSROOM_SET All_Classroom;	//所有的教室信息
COURSE_SET All_Course;			//所有的课程信息
TIME_MAP All_Time;				//按时间索引指定课堂信息
LESSON_SET All_Lesson;			//所有课堂信息

HWND hWnd;
HANDLE HANDLE_IN=GetStdHandle(STD_INPUT_HANDLE);
HANDLE HANDLE_OUT=GetStdHandle(STD_OUTPUT_HANDLE);

SMALL_RECT win_size = { 0,0,80,25 };
unsigned long ul=0;

struct Menu_Function
{
	std::vector<std::string> *menu_item;
	Status (*corres_fuction)();

	Menu_Function()
	{
		menu_item = NULL;
		corres_fuction = NULL;
	}

	Menu_Function(std::vector<std::string> *a, Status(*b)()=NULL) {
		menu_item = a;
		corres_fuction = b;
	}
};

std::string surface_title = "排课评估与分析助手";

std::string classroom_file = "Classroom Info.csv";
std::string teacher_file = "Teacher Info.csv";
std::string class_file = "Class Info.csv";
std::string course_file = "Course Info.csv";

std::string lesson_file = "Lesson Info.csv";

std::vector<std::string> main_menu = { "文件管理","课堂元素信息管理","课堂信息管理","排课评估与分析" };

std::vector<std::string> file_manage = { "排课文件读入","保存当前信息","退出系统"};
std::vector<std::string> lesson_element_manage = {"教室信息管理","教师信息管理","班级信息管理","课程信息管理"};
std::vector<std::string> lesson_manage = { "添加课堂信息","删除课堂信息","修改课堂信息","查询课堂信息","检索课堂信息" };
std::vector<std::string> analysis_and_evaluate = { "教室查询及分析","教师承担课堂合理性分析","班级参与课堂合理性分析" };

std::vector<std::string> file_input = { "教室文件读入","教师文件读入","班级文件读入","课程文件读入","课堂文件读入" };

std::vector<std::string> classroom_info_manage = { "添加教室信息","删除教室信息","修改教室信息","查询教室信息","检索教室信息" };
std::vector<std::string> teacher_info_manage = { "添加教师信息","删除教师信息","修改教师信息","查询教师信息","检索教师信息" };
std::vector<std::string> class_info_manage = { "添加班级信息","删除班级信息","修改班级信息","查询班级信息","检索班级信息" };
std::vector<std::string> course_info_manage = { "添加课程信息","删除课程信息","修改课程信息","查询课程信息","检索课程信息" };

std::vector<std::string> classroom_manage = { "查询空教室","教室利用率分析","教室能效分析" };

std::vector<std::vector<std::string> > menu = {main_menu,file_manage,lesson_element_manage,lesson_manage,analysis_and_evaluate,file_input,classroom_info_manage,teacher_info_manage,class_info_manage,course_info_manage,classroom_manage};

std::map<int, Menu_Function*> menu_function;



void init();
int needToStudy(COURSE_SET *learned, COURSE_SET *require);
void functionSelect();
void dealMention(int code, int type, std::string);
void drawMenuInterface(int no,Menu_Function *pcur);
void getBits(std::vector<std::string> &bits, std::string &info);
std::string getWeekString(bool weeks[MAX_WEEK]);

Status classroomFileInput();
Status teacherFileInput();
Status classFileInput();
Status courseFileInput();
Status lessonFileInput();

Status saveInfo();
Status exitSys();

Status insertClassroomInfo();
Status deleteClassroomInfo();
Status modifyClassroomInfo();
Status findClassroomInfo();
Status retrieveClassroomInfo();

Status insertTeacherInfo();
Status deleteTeacherInfo();
Status modifyTeacherInfo();
Status findTeacherInfo();
Status retrieveTeacherInfo();

Status insertClassInfo();
Status deleteClassInfo();
Status modifyClassInfo();
Status findClassInfo();
Status retrieveClassInfo();

Status insertCourseInfo();
Status deleteCourseInfo();
Status modifyCourseInfo();
Status findCourseInfo();
Status retrieveCourseInfo();

Status insertLessonInfo();
Status deleteLessonInfo();
Status modifyLessonInfo();
Status findLessonInfo();
Status retrieveLessonInfo();

Status findEmptyClassroom();
Status utilizationAnalysis();
Status efficiencyAnalysis();

Status teacherValidityAnalysis();
Status studentValidityAnalysis();


