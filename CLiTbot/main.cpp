#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;

Game game; //全局唯一的Game变量

int main() {
	game.limit = 100;
	//*  used for test
	//game.map_init.load("maps/testmap1.txt");
	//ofstream fout;
	//fout.open("testop2.txt");
	//cout << fout.is_open() << endl;
	//cout <<(int) robot_run("ops/testop1.txt").result << endl;
	//*

	string input_op;//输入的命令
	while (cout << "<User>:", getline(cin, input_op), input_op != "EXIT") {//输入命令，EXIT退出
		if ((input_op.substr(0, 4) == "LOAD" && input_op.size() == 4) || (input_op.substr(0, 5) == "LOAD " && input_op.size() == 5)) {
			cout << "<System>:Command Format:*LOAD <MAP_PATH>*" << endl;
		}
		else if (input_op.substr(0, 5) == "LOAD ") {//加载地图
			if (game.map_init.load(input_op.substr(5).c_str())) {
				cout << "<System>:Successfully Load Map From <" << input_op.substr(5) << ">" << endl;
			}
			else {
				cout << "Error:Load Map Failed:File Does Not Exist" << endl;
			}
		}
		else if ((input_op.substr(0, 4) == "RUN" && input_op.size() == 3) || (input_op.substr(0, 4) == "RUN " && input_op.size() == 4)) {
			cout << "<System>:Command Format:*RUN <OP_PATH>*" << endl;
		}
		else if (input_op.substr(0, 4) == "RUN ") {
			robot_run(input_op.substr(4).c_str()).output();
		}
		else if (input_op.substr(0, 6) == "STATUS" && input_op.size() == 6) {
			output_status();
		}
		else if (input_op.substr(0, 5) == "LIMIT" && input_op.size() == 5) {
			cout << "<System>:Command Format:LIMIT <OPS>" << endl;
		}
		else if (input_op.substr(0, 6) == "LIMIT ") {
			if (string_to_int(input_op.substr(6)) > 0) {
				game.limit = string_to_int(input_op.substr(6));
				cout << "<System>:Successfully Set Step Limit To " << game.limit << endl;
			}
			else {
				cout << "<System>:Unknown Command;Input *HELP* For Help" << endl;
			}
		}
		else if (input_op.substr(0, 4) == "HELP" && input_op.size() == 4) {//帮助
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