#pragma once

#define OK 1
#define ERROR 0
#define ILLEGALITY -1
#define EXIST 2
#define NOTEXIST 3
#define CANCEL -2

#define MAX_WEEK 25

class CLASSROOM;
class TEACHER;
class CLASS;
class COURSE;
class LESSON;

struct lesson_set_comp
{
	bool operator()(const LESSON *a, const LESSON *b)const;
};

struct classroom_set_comp
{
	bool operator()(const CLASSROOM *a, const CLASSROOM *b)const;
};

struct course_set_comp
{
	bool operator()(const COURSE *a, const COURSE *b)const;
};

typedef int Status;

typedef std::map<CLASSROOM *, LESSON *> PLACE;								//表示地点
typedef std::map<std::string, PLACE> PERIOD;								//表示节数
typedef std::map<int, PERIOD> DAY;											//表示星期几的课堂
typedef std::map<int, DAY> TIME_MAP;										//时间映射

typedef std::set<CLASSROOM *, classroom_set_comp> CLASSROOM_SET;			//教室集合
typedef std::set<TEACHER *> TEACHER_SET;									//教师集合
typedef std::set<CLASS *> CLASS_SET;										//课堂上上课班级集合
typedef std::set<COURSE *,course_set_comp> COURSE_SET;										//课程集合

typedef std::set<class LESSON *,lesson_set_comp> LESSON_SET;				//课堂集合

class LESSON						//课堂
{
public:
	bool weeks[MAX_WEEK];			//课程上课时间 表示周数的字符串
	int day;						//课程上课事件 表示星期的整形
	std::string period;				//课程上课时间 表示节数的字符串
	class CLASSROOM* classroom;		//上课地点 指向 教室 类
	class TEACHER* teacher;			//上课老师信息 包括哪个老师 负责哪几节课 
	CLASS_SET classes;				//班级信息 集合 该课程哪几个班上 	
	class COURSE* course;			//课程信息 指向 课程 类

	LESSON()
	{
		std::fill(weeks, weeks + MAX_WEEK, false);
		classroom = NULL;
		teacher = NULL;
		course = NULL;
	}

	Status getWeeks(std::string);
	LESSON *conflictDetection(TIME_MAP&);
	Status insertTimeMap(TIME_MAP&);
	Status insertLessonSet(TIME_MAP &,LESSON_SET &);
	Status deleteLessonSet(TIME_MAP &,LESSON_SET &);

	friend std::ostream &operator<<(std::ostream &outPut, LESSON &lesson);
	friend std::ifstream &operator>>(std::ifstream &inFile, LESSON &lesson);
	friend std::ofstream &operator<<(std::ofstream &outFile, LESSON &lesson);
};

class CLASSROOM
{
public:
	std::string building;			//教学楼名称
	std::string room;				//教室编号
	int max_capacity;
	LESSON_SET lessons;				//与该教室有关的课堂集合

	CLASSROOM()
	{
		building = "";
		room = "";
		max_capacity = 0;
	}

	std::string firstElem()
	{
		return building;
	}
	std::string secondElem()
	{
		return room;
	}

	friend std::ostream &operator<<(std::ostream &outPut, CLASSROOM &classroom);

	friend std::ifstream &operator>>(std::ifstream &inFile, CLASSROOM &classroom);
	friend std::ofstream &operator<<(std::ofstream &outFile, CLASSROOM &classroom);
};

class TEACHER
{
public:
	std::string t_name;				//教师名字
	std::string institute;			//学院名称
	LESSON_SET lessons;				//与该教师有关的课堂集合

	TEACHER()
	{
		t_name = "";
		institute = "";
	}

	std::string firstElem()
	{
		return t_name;
	}
	std::string secondElem()
	{
		return institute;
	}

	friend std::ostream &operator<<(std::ostream &outPut, TEACHER &teacher);
	friend std::ifstream &operator>>(std::ifstream &inFile, TEACHER &teacher);
	friend std::ofstream &operator<<(std::ofstream &outFile, TEACHER &teacher);
};

class CLASS
{
public:
	std::string c_name;				//班级名称
	std::string institute;			//所在学院
	int student_num;				//学生人数
	COURSE_SET learned;				//该班级已经学过的课程				
	LESSON_SET lessons;				//与该班级有关的课堂集合

	CLASS()
	{
		c_name = "";
		institute = "";
		student_num = 0;
	}

	std::string firstElem()
	{
		return c_name;
	}
	std::string secondElem()
	{
		return institute;
	}

	friend std::ostream &operator<<(std::ostream &outPut, CLASS &Class);
	friend std::ifstream &operator>>(std::ifstream &inFile, CLASS &Class);
	friend std::ofstream &operator<<(std::ofstream &outFile, CLASS &Class);
};

class COURSE						//课程
{
public:
	std::string ID;					//课程ID
	std::string name;				//课程名称
	std::string institute;			//该课程属于哪个学院专业课
	COURSE_SET require;				//该门课程需要的基础课程
	LESSON_SET lessons;				//与该课程有关的课堂

	COURSE()
	{
		ID = "";
		name = "";
		institute = "";
	}

	std::string firstElem()
	{
		return ID;
	}
	std::string secondElem()
	{
		return name;
	}

	friend std::ostream &operator<<(std::ostream &outPut, COURSE &course);
	friend std::ifstream &operator>>(std::ifstream &inFile, COURSE &course);
	friend std::ofstream &operator<<(std::ofstream &outFile, COURSE &course);
};


template<class TYPE_ITERATOR>
TYPE_ITERATOR my_find_if(TYPE_ITERATOR begin,TYPE_ITERATOR end,std::string firstelem,std::string secondelem,int comp_type)
{
	TYPE_ITERATOR it;
	for (it = begin; it != end; it++)
	{
		switch (comp_type)
		{
			case 0:if ((*it)->firstElem() == firstelem && (*it)->secondElem() == secondelem) return it; break;
			case 1:if ((*it)->firstElem() == firstelem) return it; break;
			case 2:if ((*it)->secondElem() == secondelem) return it; break;
			case 3:if (((*it)->firstElem() == firstelem || (*it)->secondElem() == secondelem)) return it; break;
			default:return end;
		}
	}
	return it;
}

template<class TYPE_ITERATOR>
Status my_file_out(std::string out_file,TYPE_ITERATOR begin,TYPE_ITERATOR end, std::string first_line)
{
	TYPE_ITERATOR it;
	std::ofstream outFile;
	outFile.open(out_file);
	if (!outFile.is_open())
	{
		outFile.close();
		return ERROR;
	}
	outFile << first_line << endl;
	for (it = begin;it != end; it++)
	{
		outFile << *(*it);
	}
	outFile.close();
	return OK;
}

Status LESSON::getWeeks(std::string info)
{
	std::fill(weeks, weeks + MAX_WEEK, false);

	int left, right, next=-1;
	std::string temp1,temp2;
	for (left = 0, right = 0; right < info.length(); right++)
	{
		if (info[right] == '-')
		{
			next = info.find(',', right + 1);
			if (next == -1) next = info.length();
			temp1 = info.substr(left, right - left);
			temp2 = info.substr(right + 1, next - right - 1);
			for (int i = atoi(temp1.c_str()), max_i = atoi(temp2.c_str()); i <= max_i; i++)
			{
				weeks[i] = true;
			}
			left = right = next + 1;
		}
		else if (info[right] == ',')
		{
			temp1 = info.substr(left, right - left);
			weeks[atoi(temp1.c_str())] = true;
			left = right = right + 1;
		}
	}
	if (left < info.length()) weeks[atoi(info.substr(left, right - left).c_str())] = true;

	return OK;
}

bool lesson_set_comp::operator()(const LESSON *a,const LESSON *b)const 
{
	if (a->course->name != b->course->name)return a->course->name < b->course->name;
	for (int i = 0; i < MAX_WEEK; i++)
	{
		if (a->weeks[i] != b->weeks[i])
		{
			return a->weeks[i] < b->weeks[i];
		}
	}
	if (a->day != b->day)	return a->day < b->day;
	if (a->period != b->period) return a->period < b->period;
	if (a->classroom->building != b->classroom->building) return a->classroom->building < b->classroom->building;
	if (a->classroom->room != b->classroom->room) return a->classroom->room < b->classroom->room;
	if (a->teacher->t_name != b->teacher->t_name)return a->teacher->t_name < b->teacher->t_name;
	if (a->classes.size() != b->classes.size())return a->classes.size() < b->classes.size();
	return false;
}

bool classroom_set_comp::operator()(const CLASSROOM *a, const CLASSROOM *b)const
{
	if (a->building != b->building) return a->building < b->building;
	if (a->room != b->room) return a->room < b->room;
	return false;
}

bool course_set_comp::operator()(const COURSE *a, const COURSE *b)const
{
	if (a->ID != b->ID) return a->ID < b->ID;
	if (a->institute != b->institute) return a->institute < b->institute;
	if (a->name != b->name) return a->name < b->name;
	return false;
}


