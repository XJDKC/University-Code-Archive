#pragma once

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERRFLOW -2
#define NOTEXIST -3
#define EXIST -4

typedef int status;
typedef int ElemType;
typedef std::set<int, std::greater<int> > UD_SET;
typedef std::map<int, int, std::greater<int> > UD_MAP;
typedef std::map<int, std::map<int, int, std::greater<int> >, std::greater<int> > UD_M_MAP;

UD_SET V_set;
UD_MAP V_map;
UD_M_MAP E_map;
std::queue<int> V_queue;

extern void Deal_Mention(int interface_type, int op_type, int mention_type, int info);

class Map;

class Edge
{	
	friend class Map;
	friend class Vertax;
private:
	int next_no;
	int weight;
	Edge *E_next;
public:
	Edge()
	{
		next_no=0;
		E_next = NULL;
	}
	~Edge()
	{
	}

	friend std::ifstream &operator>>(std::ifstream &inFile, Map &MM);
	friend std::ofstream &operator<<(std::ofstream &outFile, Map &MM);
};

class Vertax
{
	friend class Map;
private:
	int no;
	int value;
	int edge_num;
	Edge *E_head;
	Vertax *V_next;
public:
	Vertax()
	{
		no = 0;
		value = -1;
		edge_num = 0;
		E_head = NULL;
	}
	~Vertax()
	{
		Edge *pcur = E_head,*temp;
		while (pcur)
		{
			temp = pcur->E_next;
			delete(pcur);
			pcur = temp;
		}
	}

	int GetNo();
	void GetNextto();

	friend std::ifstream &operator>>(std::ifstream &inFile, Map &MM);
	friend std::ofstream &operator<<(std::ofstream &outFile, Map &MM);
};

class Map
{
	friend class Multimap;
private:
	int msize;
	Vertax *V_head;
public:
	bool saved;
	int map_type;
	Map *M_next;
	std::string name;
	Map()
	{
		saved = false;
		msize = 0;
		map_type = 0;
		V_head = NULL;
	}
	~Map()
	{
		Vertax *pcur=V_head, *temp;
		while (pcur)
		{
			temp = pcur->V_next;
			delete(pcur);
			pcur = temp;
		}
	}

	bool IsAdjust(int from,int to);
	status DFS();

	status CreateGraph(UD_MAP &V_map,UD_M_MAP &E_map);
	status DestroyGraph();
	Vertax *LocateVex(int v);
	status GetVex(int v);
	status PutVex(int v,int value);
	Vertax *FirstAdjVex(int v);
	Vertax *NextAdjVex(int v,int w);
	status InsertVex(int v, int value = -1);
	status DeleteVex(int v);
	status InsertArc(std::tuple<int,int,int> new_edge);
	status DeleteArc(std::tuple<int,int,int> del_edge);
	status DFSTraverse(Vertax *pcur=NULL);
	status BFSTraverse();

	friend std::ifstream &operator>>(std::ifstream &inFile, Map &MM);
	friend std::ofstream &operator<<(std::ofstream &outFile, Map &MM);
};

class Multimap
{
public:
	int num;
	int untitle_no;
	Map *M_head;

	Multimap()
	{
		num = 0;
		untitle_no = 0;
		M_head = NULL;
	}
	~Multimap()
	{
		Map *pcur=M_head,*temp;
		while (pcur)
		{
			temp=pcur->M_next;
			delete(pcur);
			pcur = temp;
		}
	}

	status DeleteMap(Map *workon);
	status FindMap(std::string find_name);

	friend std::ifstream &operator>>(std::ifstream &inFile, Multimap &MM);
	friend std::ofstream &operator<<(std::ofstream &outFile, Multimap &MM);
};


int Vertax::GetNo()
{
	return no;
}

void Vertax::GetNextto()
{
	Edge *pcur = E_head;
	while (pcur)
	{
		std::cout << pcur->next_no;
		pcur = pcur->E_next;
		if (pcur) std::cout << " ";
		else std::cout << std::endl;
	}
}



bool Map::IsAdjust(int from, int to)
{
	Vertax *pcur = V_head;
	while (pcur)
	{
		if (pcur->no == from)
		{
			break;
		}
		pcur = pcur->V_next;
	}
	if (pcur)
	{
		Edge *pedge = pcur->E_head;
		while (pedge)
		{
			if (pedge->next_no == to)
				return TRUE;
			pedge = pedge->E_next;
		}
	}
	return FALSE;
}

status Map::DFS()
{
	Vertax *pcur = V_head;
	std::cout << "\n---------------DFSTraverse-------------------\n";
	while (pcur)
	{
		if (V_set.find(pcur->no) == V_set.end())
		{
			if (pcur != V_head) std::cout << std::endl << std::endl;
			DFSTraverse(pcur);
		}
		pcur = pcur->V_next;
	}
	std::cout << "\n---------------------------------------------\n";
	return OK;
}

status Map::CreateGraph(UD_MAP &V_map,UD_M_MAP &E_map)
{
	UD_M_MAP::iterator i;
	UD_MAP::iterator j;
	UD_MAP::iterator k;
	DestroyGraph();
	for (k = V_map.begin(); k != V_map.end(); k++)
	{
		Vertax *pcur;
		pcur = LocateVex(k->first);
		if (pcur == NULL)
		{
			InsertVex(k->first,k->second);
			pcur=LocateVex(k->first);
		}
		if ((i = E_map.find(k->first)) != E_map.end())
		{
			for (j = i->second.begin(); j != i->second.end(); j++)
			{
				if (!IsAdjust(i->first, j->second))
				{
					InsertArc(std::make_tuple(i->first, j->first, j->second));
					if (map_type % 2 == 0)
					{
						Vertax *to;
						to = LocateVex(j->first);
						if (to == NULL)
						{
							InsertVex(j->first);
							to=LocateVex(j->first);
						}
						InsertArc(std::make_tuple(j->first, i->first, j->second));
					}
				}

			}
		}
	}
	return OK;
}

status Map::DestroyGraph()
{
	delete(V_head);
	V_head = NULL;
	msize = 0;
	return OK;
}

Vertax *Map::LocateVex(int v)
{
	Vertax *pcur = V_head;
	while (pcur)
	{
		if (pcur->no == v)
			return pcur;
		pcur = pcur->V_next;
	}
	return NULL;
}

status Map::GetVex(int v)
{
	Vertax *pcur = LocateVex(v);
	if (pcur == NULL) return NOTEXIST;
	else return pcur->value;
}

status Map::PutVex(int v,int value)
{
	Vertax *pcur = LocateVex(v);
	if (pcur == NULL) return NOTEXIST;
	else
	{
		pcur->value = value;
		return OK;
	}
}

Vertax *Map::FirstAdjVex(int v)
{
	Vertax *pcur = LocateVex(v);
	if (pcur == NULL) return NULL;
	else
	{
		if (pcur->E_head == NULL) return NULL;
		else return LocateVex(pcur->E_head->next_no);
	}
}

Vertax *Map::NextAdjVex(int v,int w)
{
	Vertax *pcur = LocateVex(v);
	if (pcur == NULL) return NULL;
	else
	{
		Edge *pedge = pcur->E_head;
		while (pedge)
		{
			if (pedge->next_no == w)
			{
				return pedge->E_next?LocateVex(pedge->E_next->next_no):NULL;
			}
			pedge = pedge->E_next;
		}
		return NULL;
	}
}

status Map::InsertVex(int v,int value)
{
	if (LocateVex(v) != NULL) return EXIST;
	else
	{
		Vertax *pnew = new(Vertax);
		pnew->no = v;
		pnew->value = value;
		msize++;
		if (V_head == NULL || V_head && V_head->no > v)
		{
			pnew->V_next = V_head;
			V_head = pnew;
		}
		else
		{
			Vertax *pinsert = V_head;
			while (pinsert)
			{
				if (pinsert->V_next == NULL || pinsert->V_next->no > v)
					break;
				pinsert = pinsert->V_next;
			}
			pnew->V_next = pinsert->V_next;
			pinsert->V_next = pnew;
		}
		return OK;
	}
}

status Map::DeleteVex(int v)
{
	Vertax *pcur = V_head, *pprev = NULL;
	Edge *pedge,*temp;
	bool mark = false;
	while (pcur)
	{
		if (pcur->no == v)
		{
			if (pprev == NULL)
				V_head = pcur->V_next;
			else
				pprev->V_next=pcur->V_next;
			msize--;
			delete(pcur);
			mark = true;
			pcur = pprev == NULL ? V_head : pprev->V_next;
			continue;
		}
		else 
		{
			if (pcur->E_head&&pcur->E_head->next_no == v)
			{
				temp = pcur->E_head->E_next;
				delete(pcur->E_head);
				pcur->E_head = temp;
				pcur->edge_num--;
			}
			else
			{
				pedge = pcur->E_head;
				while (pedge)
				{
					if (pedge->E_next&&pedge->E_next->next_no == v)
					{
						temp = pedge->E_next->E_next;
						delete(pedge->E_next);
						pedge->E_next = temp;
						pcur->edge_num--;
						break;
					}
					pedge = pedge->E_next;
				}
			}
		}
		pprev = pcur;
		pcur = pcur->V_next;
	}
	return mark?OK:NOTEXIST;
}

status Map::InsertArc(std::tuple<int, int, int> new_edge)
{
	Vertax *from,*to;
	if ((from = LocateVex(std::get<0>(new_edge))) == NULL
		||(to = LocateVex(std::get<1>(new_edge))) == NULL) return NOTEXIST;
	else
	{
		if (!IsAdjust(std::get<0>(new_edge), std::get<1>(new_edge)))
		{
			Edge *pnew = new(Edge),*pinsert;
			from->edge_num++;
			if (map_type>2) 
				pnew->weight = std::get<2>(new_edge);
			pnew->next_no = std::get<1>(new_edge);
			if (!from->E_head || from->E_head->next_no > to->no)
			{
				pnew->E_next = from->E_head;
				from->E_head = pnew;
			}
			else
			{
				pinsert = from->E_head;
				while (pinsert)
				{
					if (!pinsert->E_next || pinsert->next_no > to->no)
						break;
					pinsert = pinsert->E_next;
				}
				pnew->E_next = pinsert->E_next;
				pinsert->E_next = pnew;
			}

			if (map_type % 2 == 0)
			{
				pnew = new(Edge);
				to->edge_num++;
				if (map_type > 2)
					pnew->weight = std::get<2>(new_edge);
				pnew->next_no = std::get<0>(new_edge);
				if (!to->E_head || to->E_head->next_no > from->no)
				{
					pnew->E_next = to->E_head;
					to->E_head = pnew;
				}
				else
				{
					pinsert = to->E_head;
					while (pinsert)
					{
						if (!pinsert->E_next || pinsert->next_no > from->no)
							break;
						pinsert = pinsert->E_next;
					}
					pnew->E_next = pinsert->E_next;
					pinsert->E_next = pnew;
				}
			}
			return OK;
		}
		else return EXIST;
	}
}

status Map::DeleteArc(std::tuple<int, int, int> del_edge)
{
	Vertax *from, *to;
	if ((from = LocateVex(std::get<0>(del_edge))) == NULL
		|| (to = LocateVex(std::get<1>(del_edge))) == NULL) return NOTEXIST;
	else
	{
		if (IsAdjust(std::get<0>(del_edge), std::get<1>(del_edge)))
		{
			Vertax *pcur = LocateVex(std::get<0>(del_edge));
			Edge *pedge = pcur->E_head,*pprev=NULL;
			pcur->edge_num--;
			while (pedge)
			{
				if (pedge->next_no == std::get<1>(del_edge))
				{
					if (pprev == NULL)
						pcur->E_head = pedge->E_next;
					else
						pprev->E_next = pedge->E_next;
					delete(pedge);
					break;
				}
				pprev = pedge;
				pedge = pedge->E_next;
			}
			if (map_type % 2 == 0)
			{
				pcur = LocateVex(std::get<1>(del_edge));
				pedge = pcur->E_head, pprev = NULL;
				pcur->edge_num--;
				while (pedge)
				{
					if (pedge->next_no == std::get<0>(del_edge))
					{
						if (pprev == NULL)
							pcur->E_head = pedge->E_next;
						else
							pprev->E_next = pedge->E_next;
						delete(pedge);
						break;
					}
					pprev = pedge;
					pedge = pedge->E_next;
				}
			}
			return OK;
		}
		else return ERROR;
	}
}

status Map::DFSTraverse(Vertax *pcur)
{
	std::cout << pcur->no << '\t';
	V_set.insert(pcur->no);
	Edge *pedge = pcur?pcur->E_head:NULL;
	while (pedge)
	{
		if (V_set.find(pedge->next_no) == V_set.end())
		{
			DFSTraverse(LocateVex(pedge->next_no));
		}
		pedge = pedge->E_next;
	}
	return OK;
}

status Map::BFSTraverse()
{
	Vertax *pcur;
	Edge *pedge;
	V_set.clear();
	while (!V_queue.empty()) V_queue.pop();	
	std::cout << "\n---------------BFSTraverse-------------------\n";
	while ((int)V_set.size() < msize)
	{
		pcur = V_head;
		while (pcur)
		{
			if (V_set.find(pcur->no) == V_set.end())
			{
				V_queue.push(pcur->no);
				break;
			}
			pcur = pcur->V_next;
		}
		while (!V_queue.empty())
		{
			pcur = LocateVex(V_queue.front());
			V_queue.pop();
			std::cout << pcur->no << "\t";
			V_set.insert(pcur->no);
			pedge = pcur->E_head;
			while (pedge)
			{
				if (V_set.find(pedge->next_no) == V_set.end())
				{
					V_set.insert(pedge->next_no);
					V_queue.push(pedge->next_no);
				}
				pedge = pedge->E_next;
			}
		}
		if ((int)V_set.size() < msize) std::cout << std::endl << std::endl;
	}
	V_set.clear();
	std::cout << "\n---------------------------------------------\n";
	return OK;
}


status Multimap::DeleteMap(Map *workon)
{
	Map *pcur = M_head, *pprev = NULL;
	while (pcur)
	{
		if (pcur->name == workon->name)
		{
			if (pprev == NULL)
				M_head = M_head->M_next;
			else
				pprev = pprev->M_next;
			delete(workon);
			num--;
			return OK;
		}
		pprev = pcur;
		pcur = pcur->M_next;
	}
	return NOTEXIST;
}

status Multimap::FindMap(std::string find_name)
{
	Map *pcur = M_head;
	while (pcur)
	{
		if (find_name == pcur->name)
			return TRUE;
		pcur = pcur->M_next;
	}
	return FALSE;
}


std::ifstream &operator>>(std::ifstream &inFile, Map &MM)
{
	V_map.clear();
	E_map.clear();
	int count = 0;
	UD_MAP *temp;
	inFile >> MM.map_type;
	inFile >> MM.msize >> count;
	for (int i = 1, x, y; i <= MM.msize; i++)
	{
		inFile >> x >> y;
		V_map[x] = y;
	}
	for (int i = 1, x, y, z; i <= count; i++)
	{
		inFile >> x >> y >> z;
		if (E_map.find(x) == E_map.end())
		{
			temp = new(UD_MAP);
			(*temp)[y] = z;
			E_map[x] = *temp;
		}
		else
			E_map[x][y] = z;
	}
	MM.CreateGraph(V_map, E_map);
	return inFile;
}

std::ofstream &operator<<(std::ofstream &outFile, Map &MM)
{
	outFile << MM.map_type << std::endl;
	int count = 0;
	Vertax *pcur;
	Edge *pedge;
	for (pcur = MM.V_head; pcur; pcur = pcur->V_next)
	{
		count += pcur->edge_num;
	}
	outFile << MM.msize << " " << count << std::endl;
	for (pcur = MM.V_head; pcur; pcur = pcur->V_next)
		outFile << pcur->no << " " << pcur->value << std::endl;
	for (pcur = MM.V_head; pcur; pcur = pcur->V_next)
		for (pedge = pcur->E_head; pedge; pedge = pedge->E_next)
		{
			outFile << pcur->no << " " << pedge->next_no << " " << pedge->weight << std::endl;
		}
	return outFile;
}

std::ifstream &operator>>(std::ifstream &inFile, Multimap &MM)
{
	std::ifstream inMap;
	Map *pcur;
	inFile >> MM.num >> MM.untitle_no;
	for (int i = 0; i < MM.num; i++)
	{
		pcur = new(Map);
		inFile >> pcur->name;
		pcur->saved = true;
		inMap.open(pcur->name + ".txt");
		if (!inMap.is_open())
		{
			Deal_Mention(0, -2, 1, 0);
			MM.num = i;
			break;
		}
		inMap >> *pcur;
		inMap.close();
		pcur->M_next = MM.M_head;
		MM.M_head = pcur;
	}
	return inFile;
}

std::ofstream &operator<<(std::ofstream &outFile, Multimap &MM)
{
	std::ofstream outMap;
	int count = 0;
	Map *pcur=MM.M_head;
	outFile << MM.num << " " << MM.untitle_no << std::endl;
	while (pcur)
	{
		if (pcur->saved)
		{
			count++;
			outFile << pcur->name << std::endl;
			outMap.open(pcur->name + ".txt");
			if (!outMap.is_open())
			{
				Deal_Mention(0, -2, 1, 0);
				break;
			}
			outMap << *pcur;
			outMap.close();
		}
		pcur = pcur->M_next;
	}
	return outFile;
}
