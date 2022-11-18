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
	fin >> row >> col >> num_lights >> num_procs;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fin >> cells[i][j].height;
			cells[i][j].robot = false;
			cells[i][j].light_id = -1;
		}
	}
	for (int i = 0; i < num_lights; i++) {
		fin >> lights[i].pos.x >> lights[i].pos.y;
		cells[lights[i].pos.x][lights[i].pos.y].light_id = i;
	}
	for (int i = 0; i < num_procs; i++) {
		fin >> op_limit[i];
	}
	int dir_temp;
	fin >> robot.pos.x >> robot.pos.y >> dir_temp;
	robot.dir = (Direction)dir_temp;
	cells[robot.pos.x][robot.pos.y].robot = true;
	fin.close();
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
	if (cells[robot.pos.x][robot.pos.y].light_id < 0)
	{
		cout << "Warning:Operation *LIT* Unexecuted:No Light In This Cell" << endl;
		return false;
	}
	if (lights[cells[robot.pos.x][robot.pos.y].light_id].lighten)
	{
		cout << "Warning:Operation *LIT* Unexecuted:Light Already Lit" << endl;
		return false;
	}
	lights[cells[robot.pos.x][robot.pos.y].light_id].lighten = true;
	return true;
}