#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;

Game game; //ȫ��Ψһ��Game����

int main() {
	game.limit = 100;
	game.auto_save_id = 0;
	//*  used for test
	//game.map_init.load("maps/testmap1.txt");
	//ofstream fout;
	//fout.open("testop2.txt");
	//cout << fout.is_open() << endl;
	//cout <<(int) robot_run("ops/testop1.txt").result << endl;
	//*
	
	string input_op;//���������
	while (cout << "<User>:", getline(cin, input_op), input_op != "EXIT") {//�������ֱ������EXIT�˳�
		//�������LOAD
		if ((input_op.substr(0, 4) == "LOAD" && input_op.size() == 4) || (input_op.substr(0, 5) == "LOAD " && input_op.size() == 5)) {
			cout << "<System>:Command Format:*LOAD <MAP_PATH>*" << endl;
		}
		else if (input_op.substr(0, 5) == "LOAD ") {//���ص�ͼ
			if (game.map_init.load(input_op.substr(5).c_str())) {
				cout << "<System>:Successfully Load Map From <" << input_op.substr(5) << ">" << endl;
				game.map_name = input_op.substr(5);
			}
			else {//�ļ�������
				cout << "Error:Load Map Failed:File Does Not Exist" << endl;
			}
		}
		//�������RUN
		else if ((input_op.substr(0, 4) == "RUN" && input_op.size() == 3) || (input_op.substr(0, 4) == "RUN " && input_op.size() == 4)) {
			cout << "<System>:Command Format:*RUN <OP_PATH>*" << endl;
		}
		else if (input_op.substr(0, 4) == "RUN ") {
			Result run_result;
			run_result = robot_run(input_op.substr(4).c_str());
			output_results(run_result, input_op.substr(4).c_str());
		}
		//�������STATUS
		else if (input_op.substr(0, 6) == "STATUS" && input_op.size() == 6) {
			output_status();
		}
		//�������LIMIT
		else if (input_op.substr(0, 5) == "LIMIT" && input_op.size() == 5) {
			cout << "<System>:Command Format:LIMIT <OPS>" << endl;
		}
		else if (input_op.substr(0, 6) == "LIMIT ") {
			if (string_to_int(input_op.substr(6)) > 0) {//�����������
				game.limit = string_to_int(input_op.substr(6));
				cout << "<System>:Successfully Set Step Limit To " << game.limit << endl;
			}
			else {//����Ĳ�������
				cout << "<System>:Unknown Command;Input *HELP* For Help" << endl;
			}
		}
		//�������AUTOSAVE
		else if (input_op.substr(0, 9) == "AUTOSAVE ") {
			if (input_op.substr(9) == "OFF") {//�������AUTOSAVE OFF
				game.save_path = "";
			}
			else {//������ǵ�ַ
				game.save_path = input_op.substr(9);
			}
		}
		//�������OP
		else if (input_op.substr(0, 2) == "OP" && input_op.size() == 2) {
			cout << "<System>:Command Format:*OP <OP_PATH>*" << endl;
		}
		else if (input_op.substr(0, 3) == "OP ") {
			if (game.map_init.exist) {
				if (op_input(input_op.substr(3).c_str())) {
					cout << "<System>:Successfully Store Operation Sequence To <" << input_op.substr(3) << ">" << endl;
				}
			}
			else {
				cout << "<System>:Failed! Please Load Map First!" << endl;
			}
		}
		//�������HELP
		else if (input_op.substr(0, 4) == "HELP" && input_op.size() == 4) {//����
			cout << "<System>:<Help>" << endl;
			cout << "    LOAD <MAP_PATH>:Load Map From <MAP_PATH>" << endl;
			cout << "    RUN <OP_PATH>:Run Operation From <OP_PATH>" << endl;
			cout << "    STATUS:Output Current Game Status" << endl;
			cout << "    AUTOSAVE <SAVE_PATH>:Turn On Autosae Map Images And Set Save Path As <MAP_PATH>" << endl;
			cout << "    AUTOSAVE <OFF>:Turn Off Autosave Map Images" << endl;
			cout << "    LIMIT <OPS>:Set Step Limit As <OPS>" << endl;
			cout << "    OP <OP_PATH>:Start Input Operation Sequence And Store It To <OP_PATH>" << endl;
			cout << "    EXIT:Exit Program" << endl;
			cout << "    HELP:Get Help" << endl;
		}
		else {
			cout << "<System>:Unknown Command;Input *HELP* For Help" << endl;
		}
	}
	system("pause");
	return 0;
}