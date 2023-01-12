#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;
bool Map::load(const char* path) {//从path加载地图,返回是否成功并输出失败原因
	ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		return false;
	}
	fin >> row >> col >> num_lights >> num_procs;//行 列 需要点亮的灯的个数 最多允许的过程数目 
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			fin >> cells[i][j].height;//输入各行各列的高度，零表示不存在 
			cells[i][j].robot = false;//一开始都没有机器人 
			cells[i][j].light_id = -1;//一开始都没有灯 
		}
	}
	for (int i = 0; i < num_lights; i++) {//map有修改 
		fin >> lights[i].pos.x >> lights[i].pos.y;//每一行都输入一个灯的横纵坐标 
		cells[lights[i].pos.y][lights[i].pos.x].light_id = i;//点亮对应块上的灯 
	}
	for (int i = 0; i < num_procs; i++) {
		fin >> op_limit[i];//输入各个过程的指令数目限制 
	}
	int dir_temp;//机器人的初始朝向--0 1 2 3  上下左右 
	fin >> robot.pos.x >> robot.pos.y >> dir_temp;
	robot.dir = (Direction)dir_temp;//强转成enum中的对应朝向-好阅读 
	cells[robot.pos.y][robot.pos.x].robot = true;//表示对应的块上有机器人
	fin.close();
	exist = true;
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
bool Map::robot_move() //地图中的robot向所朝向的方向移动，返回是否成功并输出失败原因
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
bool Map::robot_jump()//向前跳跃（高度差1），返回是否成功并输出失败原因
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
bool Map::robot_lit()//点亮灯，返回是否成功并输出失败原因
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
