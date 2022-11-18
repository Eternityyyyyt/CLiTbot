#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;

extern Game game; //ȫ��Ψһ��Game����

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
int check_P_string(string input) //��P��ͷ���ַ��������жϣ�������Ϸ����-1������Ϸ���������õ�PROC���
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
		switch (p_seq->procs[num_of_proc].ops[i]) //ִ�е�num_of_proc�ĵ�i������
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
	Result result_to_return={0,FAILED}; //׼�����ص�result
	fin.open(path);
	if (fin.is_open() == 0) {
		cout << "Error:Run Operation Sequence Failed:File Does Not Exist" << endl;
		result_to_return.result = FAILED;
		return result_to_return;
	}
	OpSeq seq;					  //����һ���������е�ʵ��seq
	game.map_run = game.map_init; //������ܻ�����⣬�����������������copy_map����
	fin >> seq.count;	 //��ȡ����,ͬʱҲ����Ч������
	if (fin.good() == 0) //�Ƿ�������
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
	for (int i = 0; i < seq.count; i++)//��ȡ�ļ��е����seq����
	{
		fin >> seq.procs[i].count; //�������i�Ĳ�������
		if (fin.good() == 0)	   //�Ƿ�������
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
��Game�е�map_name��save_path���������͸�Ϊstring
Robot������turn������ִ��ת�����
Map������robot_move������ִ�л����˵��ƶ�
Map������robot_jump������ִ�л����˵���Ծ
Map������robot_lit������ִ�л����˵ĵ��
������Position�е�"=="�����
					y-
					UP
		(0,0)
			+����������������ROW��������������>  x+
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