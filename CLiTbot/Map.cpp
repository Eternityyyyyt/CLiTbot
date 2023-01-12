#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;
bool Map::load(const char* path) {//��path���ص�ͼ,�����Ƿ�ɹ������ʧ��ԭ��
	ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		return false;
	}
	fin >> row >> col >> num_lights >> num_procs;//�� �� ��Ҫ�����ĵƵĸ��� �������Ĺ�����Ŀ 
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fin >> cells[i][j].height;//������и��еĸ߶ȣ����ʾ������ 
			cells[i][j].robot = false;//һ��ʼ��û�л����� 
			cells[i][j].light_id = -1;//һ��ʼ��û�е� 
		}
	}
	for (int i = 0; i < num_lights; i++) {//map���޸� 
		fin >> lights[i].pos.x >> lights[i].pos.y;//ÿһ�ж�����һ���Ƶĺ������� 
		cells[lights[i].pos.y][lights[i].pos.x].light_id = i;//������Ӧ���ϵĵ� 
	}
	for (int i = 0; i < num_procs; i++) {
		fin >> op_limit[i];//����������̵�ָ����Ŀ���� 
	}
	int dir_temp;//�����˵ĳ�ʼ����--0 1 2 3  �������� 
	fin >> robot.pos.x >> robot.pos.y >> dir_temp;
	robot.dir = (Direction)dir_temp;//ǿת��enum�еĶ�Ӧ����-���Ķ� 
	cells[robot.pos.y][robot.pos.x].robot = true;//��ʾ��Ӧ�Ŀ����л�����
	fin.close();
	exist=true; 
	draw_the_original_map();//���ô˺������ɻ�����ʼ��ͼ�� 
	return true;
}


 
bool Map::successed()
{
	bool to_return = true;
	for (int i = 0; i < num_lights; i++)
	{
		if (lights[i].lighten == false)
		{
			to_return = false;
		}
	}
	return to_return;
}
bool Map::robot_move() //��ͼ�е�robot��������ķ����ƶ��������Ƿ�ɹ������ʧ��ԭ��
{
	switch (robot.dir)
	{
	case UP:
		if (robot.pos.y - 1 < 0)
		{
			cout << "Warning:Operation *Move* Unexecuted:Out Of The Map" << endl;
			return false;
		}
		if (cells[robot.pos.y - 1][robot.pos.x].height != cells[robot.pos.y][robot.pos.x].height)
		{
			cout << "Warning:Operation *Move* Unexecuted:Illegal Height" << endl;
			return false;
		}
		cells[robot.pos.y][robot.pos.x].robot = false;
		robot.pos.y--;
		cells[robot.pos.y][robot.pos.x].robot = true;
		break;
	case DOWN:
		if (robot.pos.y + 1 >= row)
		{
			cout << "Warning:Operation *Move* Unexecuted:Out Of The Map" << endl;
			return false;
		}
		if (cells[robot.pos.y + 1][robot.pos.x].height != cells[robot.pos.y][robot.pos.x].height)
		{
			cout << "Warning:Operation *Move* Unexecuted:Illegal Height" << endl;
			return false;
		}
		cells[robot.pos.y][robot.pos.x].robot = false;
		robot.pos.y++;
		cells[robot.pos.y][robot.pos.x].robot = true;
		break;
	case LEFT:
		if (robot.pos.x - 1 < 0)
		{
			cout << "Warning:Operation *Move* Unexecuted:Out Of The Map" << endl;
			return false;
		}
		if (cells[robot.pos.y][robot.pos.x - 1].height != cells[robot.pos.y][robot.pos.x].height)
		{
			cout << "Warning:Operation *Move* Unexecuted:Illegal Height" << endl;
			return false;
		}
		cells[robot.pos.y][robot.pos.x].robot = false;
		robot.pos.x--;
		cells[robot.pos.y][robot.pos.x].robot = true;
		break;
	case RIGHT:
		if (robot.pos.x + 1 >= col)
		{
			cout << "Warning:Operation *Move* Unexecuted:Out Of The Map" << endl;
			return false;
		}
		if (cells[robot.pos.y][robot.pos.x + 1].height != cells[robot.pos.y][robot.pos.x].height)
		{
			cout << "Warning:Operation *Move* Unexecuted:Illegal Height" << endl;
			return false;
		}
		cells[robot.pos.y][robot.pos.x].robot = false;
		robot.pos.x++;
		cells[robot.pos.y][robot.pos.x].robot = true;
		break;
	}
	return true;
}
bool Map::robot_jump()//��ǰ��Ծ���߶Ȳ�1���������Ƿ�ɹ������ʧ��ԭ��
{
	switch (robot.dir)
	{
	case UP:
		if (robot.pos.y - 1 < 0)
		{
			cout << "Warning:Operation *Jump* Unexecuted:Out Of The Map" << endl;
			return false;
		}
		if (cells[robot.pos.y - 1][robot.pos.x].height != cells[robot.pos.y][robot.pos.x].height + 1 && cells[robot.pos.y - 1][robot.pos.x].height != cells[robot.pos.y][robot.pos.x].height - 1)
		{
			cout << "Warning:Operation *Jump* Unexecuted:Illegal Height" << endl;
			return false;
		}
		cells[robot.pos.y][robot.pos.x].robot = false;
		robot.pos.y--;
		cells[robot.pos.y][robot.pos.x].robot = true;
		break;
	case DOWN:
		if (robot.pos.y + 1 >= row)
		{
			cout << "Warning:Operation *Jump* Unexecuted:Out Of The Map" << endl;
			return false;
		}
		if (cells[robot.pos.y + 1][robot.pos.x].height != cells[robot.pos.y][robot.pos.x].height + 1 && cells[robot.pos.y + 1][robot.pos.x].height != cells[robot.pos.y][robot.pos.x].height - 1)
		{
			cout << "Warning:Operation *Jump* Unexecuted:Illegal Height" << endl;
			return false;
		}
		cells[robot.pos.y][robot.pos.x].robot = false;
		robot.pos.y++;
		cells[robot.pos.y][robot.pos.x].robot = true;
		break;
	case LEFT:
		if (robot.pos.x - 1 < 0)
		{
			cout << "Warning:Operation *Jump* Unexecuted:Out Of The Map" << endl;
			return false;
		}
		if (cells[robot.pos.y][robot.pos.x - 1].height != cells[robot.pos.y][robot.pos.x].height + 1 && cells[robot.pos.y][robot.pos.x - 1].height != cells[robot.pos.y][robot.pos.x].height - 1)
		{
			cout << "Warning:Operation *Jump* Unexecuted:Illegal Height" << endl;
			return false;
		}
		cells[robot.pos.y][robot.pos.x].robot = false;
		robot.pos.x--;
		cells[robot.pos.y][robot.pos.x].robot = true;
		break;
	case RIGHT:
		if (robot.pos.x + 1 >= col)
		{
			cout << "Warning:Operation *Jump* Unexecuted:Out Of The Map" << endl;
			return false;
		}
		if (cells[robot.pos.y][robot.pos.x + 1].height != cells[robot.pos.y][robot.pos.x].height + 1 && cells[robot.pos.y][robot.pos.x + 1].height != cells[robot.pos.y][robot.pos.x].height - 1)
		{
			cout << "Warning:Operation *Jump* Unexecuted:Illegal Height" << endl;
			return false;
		}
		cells[robot.pos.y][robot.pos.x].robot = false;
		robot.pos.x++;
		cells[robot.pos.y][robot.pos.x].robot = true;
		break;
	}
	return true;
}
bool Map::robot_lit()//�����ƣ������Ƿ�ɹ������ʧ��ԭ��
{
	if (cells[robot.pos.y][robot.pos.x].light_id < 0)
	{
		cout << "Warning:Operation *LIT* Unexecuted:No Light In This Cell" << endl;
		return false;
	}
	if (lights[cells[robot.pos.y][robot.pos.x].light_id].lighten)
	{
		cout << "Warning:Operation *LIT* Unexecuted:Light Already Lit" << endl;
		return false;
	}
	lights[cells[robot.pos.y][robot.pos.x].light_id].lighten = true;
	return true;
}
