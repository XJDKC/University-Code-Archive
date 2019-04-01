#pragma once

CLASS_SET All_Class;			//���а༶��Ϣ
TEACHER_SET All_Teacher;		//���еĽ�ʦ��Ϣ
CLASSROOM_SET All_Classroom;	//���еĽ�����Ϣ
COURSE_SET All_Course;			//���еĿγ���Ϣ
TIME_MAP All_Time;				//��ʱ������ָ��������Ϣ
LESSON_SET All_Lesson;			//���п�����Ϣ

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

std::string surface_title = "�ſ��������������";

std::string classroom_file = "Classroom Info.csv";
std::string teacher_file = "Teacher Info.csv";
std::string class_file = "Class Info.csv";
std::string course_file = "Course Info.csv";

std::string lesson_file = "Lesson Info.csv";

std::vector<std::string> main_menu = { "�ļ�����","����Ԫ����Ϣ����","������Ϣ����","�ſ����������" };

std::vector<std::string> file_manage = { "�ſ��ļ�����","���浱ǰ��Ϣ","�˳�ϵͳ"};
std::vector<std::string> lesson_element_manage = {"������Ϣ����","��ʦ��Ϣ����","�༶��Ϣ����","�γ���Ϣ����"};
std::vector<std::string> lesson_manage = { "��ӿ�����Ϣ","ɾ��������Ϣ","�޸Ŀ�����Ϣ","��ѯ������Ϣ","����������Ϣ" };
std::vector<std::string> analysis_and_evaluate = { "���Ҳ�ѯ������","��ʦ�е����ú����Է���","�༶������ú����Է���" };

std::vector<std::string> file_input = { "�����ļ�����","��ʦ�ļ�����","�༶�ļ�����","�γ��ļ�����","�����ļ�����" };

std::vector<std::string> classroom_info_manage = { "��ӽ�����Ϣ","ɾ��������Ϣ","�޸Ľ�����Ϣ","��ѯ������Ϣ","����������Ϣ" };
std::vector<std::string> teacher_info_manage = { "��ӽ�ʦ��Ϣ","ɾ����ʦ��Ϣ","�޸Ľ�ʦ��Ϣ","��ѯ��ʦ��Ϣ","������ʦ��Ϣ" };
std::vector<std::string> class_info_manage = { "��Ӱ༶��Ϣ","ɾ���༶��Ϣ","�޸İ༶��Ϣ","��ѯ�༶��Ϣ","�����༶��Ϣ" };
std::vector<std::string> course_info_manage = { "��ӿγ���Ϣ","ɾ���γ���Ϣ","�޸Ŀγ���Ϣ","��ѯ�γ���Ϣ","�����γ���Ϣ" };

std::vector<std::string> classroom_manage = { "��ѯ�ս���","���������ʷ���","������Ч����" };

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


