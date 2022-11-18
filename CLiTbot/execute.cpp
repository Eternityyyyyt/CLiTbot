#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;

extern Game game; //全局唯一的Game变量

int power10(int x, int time)
{
	for (int i = 0; i < time; i++)
	{
		x *= 10;
	}
	return x;
}
int string_to_int(string input) {
	int result = 0;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] > '9' || input[i] < '0')
		{
			return -1;
		}
		else
		{
			result += ((int)input[i] - '0') * power10(1, input.size() - i - 1);
		}
	}
	return result;
}
int check_P_string(string input) //对P开头的字符串进行判断，如果不合法输出-1，如果合法输出所调用的PROC序号
{
	if (input.size() > 100000000)
	{
		cout << "Error:Invalid Operation" << endl;
		return -1;
	}
	if (string_to_int(input.substr(1)) < 0) {
		cout << "Error:Invalid Operation" << endl;
	}
	return string_to_int(input.substr(1)) ;
}
void run_proc(OpSeq *p_seq, int num_of_proc,Result* p_result)
{
	for (int i = 0; i < p_seq->procs[num_of_proc].count; i++)
	{
		p_result->steps++;
		if (p_result->steps > game.limit)
		{
			cout << "Warning:Too Many Steps" << endl;
			return;
		}
		switch (p_seq->procs[num_of_proc].ops[i]) //执行第num_of_proc的第i个操作
		{
		case TL:
			game.map_run.robot.turn(0);
			auto_save();
			break;
		case TR:
			game.map_run.robot.turn(1);
			auto_save();
			break;
		case MOV:
			game.map_run.robot_move();
			auto_save();
			break;
		case JMP:
			game.map_run.robot_jump();
			auto_save();
			break;
		case LIT:
			game.map_run.robot_lit();
			auto_save();
			break;
		default:
			auto_save();
			if (p_seq->procs[num_of_proc].ops[i] - 4 > p_seq->count)
			{
				cout << "Warning:Called Process *Process" << p_seq->procs[num_of_proc].ops[i] - 5 << "* Does Not Exist" << endl;
			}
			else if (p_seq->procs[p_seq->procs[num_of_proc].ops[i] - 5].count == 0)
			{
				cout << "Warning:Called Process *Process" << p_seq->procs[num_of_proc].ops[i] - 5 << "* Does Not Contain Operation" << endl;
			}
			else
			{
				run_proc(p_seq, p_seq->procs[num_of_proc].ops[i] - 5, p_result);
			}
			break;
		}
		if (game.map_run.successed())
			return;
	}
	return;
}
Result robot_run(const char *path)
{
	ifstream fin;
	Result result_to_return={0,FAILED}; //准备返回的result
	fin.open(path);
	if (fin.is_open() == 0) {
		cout << "Error:Run Operation Sequence Failed:File Does Not Exist" << endl;
		result_to_return.result = FAILED;
		return result_to_return;
	}
	OpSeq seq;					  //创建一个操作序列的实例seq
	game.map_run = game.map_init; //这里可能会出问题，如果有问题就用上面的copy_map函数
	fin >> seq.count;	 //读取行数,同时也是有效过程数
	if (fin.good() == 0) //非法输入检测
	{
		cout << "Error:Wrong Format" << endl;
		result_to_return.result = FAILED;
		return result_to_return;
	}
	string temp;
	if (seq.count > MAX_PROCS)
	{
		cout << "Error:Too Many Processes" << endl;
		result_to_return.result = FAILED;
		return result_to_return;
	}
	for (int i = 0; i < seq.count; i++)//读取文件中的命令到seq里面
	{
		fin >> seq.procs[i].count; //输入过程i的操作数量
		if (fin.good() == 0)	   //非法输入检测
		{
			cout << "Error:Wrong Format" << endl;
			result_to_return.result = FAILED;
			return result_to_return;
		}
		for (int j = 0; j < seq.procs[i].count; j++)
		{
			fin >> temp;
			if (temp == "TL")
				seq.procs[i].ops[j] = TL;
			else if (temp == "TR")
				seq.procs[i].ops[j] = TR;
			else if (temp == "MOV")
				seq.procs[i].ops[j] = MOV;
			else if (temp == "JMP")
				seq.procs[i].ops[j] = JMP;
			else if (temp == "LIT")
				seq.procs[i].ops[j] = LIT;
			else if (temp == "MAIN")
				seq.procs[i].ops[j] = CALL;
			else if (temp[0] == 'P')
			{
				if (check_P_string(temp) < 0)
				{
					result_to_return.result = FAILED;
					return result_to_return;
				}
				else
				{
					seq.procs[i].ops[j] = (OpType)(check_P_string(temp) + 5);
				}
			}
			else
			{
				cout << "Error:Invalid Operation" << endl;
				result_to_return.result = FAILED;
				return result_to_return;
			}
		}
	}
	fin.close();
	run_proc(&seq, 0, &result_to_return);
	if(game.map_run.successed()){
		result_to_return.result = LIGHT;
		return result_to_return;
	}
	else if(result_to_return.steps>game.limit){
		result_to_return.result = LIMIT;
		return result_to_return;
	}
	else{
		result_to_return.result = DARK;
		return result_to_return;
	}
}

/*
将Game中的map_name和save_path的数据类型改为string
Robot增加了turn函数来执行转向操作
Map增加了robot_move函数来执行机器人的移动
Map增加了robot_jump函数来执行机器人的跳跃
Map增加了robot_lit函数来执行机器人的点灯
重载了Position中的"=="运算符
					y-
					UP
		(0,0)
			+————————ROW———————>  x+
			|
			|
x-  LEFT	|						RIGHT x+
			|
			C
			O
			L
			|
			\/
			y+

				   DOWN
					y+


*/