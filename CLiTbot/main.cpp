#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;

Game game; //ȫ��Ψһ��Game����

int main(){
	game.limit = 100;
	//*  used for test
	//game.map_init.load("maps/testmap1.txt");
	//ofstream fout;
	//fout.open("testop2.txt");
	//cout << fout.is_open() << endl;
	//cout <<(int) robot_run("ops/testop1.txt").result << endl;
	//*

	string input_op;//���������
	while (cout << "User>:", getline(cin, input_op), input_op != "EXIT") {//�������EXIT�˳�
		if ((input_op.substr(0, 4) == "LOAD" && input_op.size() == 4) || (input_op.substr(0, 5) == "LOAD " && input_op.size() == 5)) {
			cout << "System:Command Format:*LOAD <MAP_PATH>*" << endl;
		}
		else if(input_op.substr(0,5)=="LOAD "){
			if(game.map_init.load(input_op.substr(5).c_str())){
				cout << "System:Successfully Load Map From <" << input_op.substr(5) << ">" << endl;
			}
			else{
				cout << "Error:Load Map Failed:File Does Not Exist" << endl;
			}
		}
		else if ((input_op.substr(0, 4) == "RUN" && input_op.size() == 3) || (input_op.substr(0, 4) == "RUN " && input_op.size() == 4)) {
			cout << "System:Command Format:*RUN <OP_PATH>*" << endl;
		}
		else if (input_op.substr(0, 4) == "RUN ") {
			cout << robot_run(input_op.substr(4).c_str()).result << endl;
		}
		else if (input_op.substr(0, 6) == "STATUS" && input_op.size() == 6) {
			output_status();
		}
		else if (input_op.substr(0, 4) == "HELP" && input_op.size() == 4) {
			cout << "Help Information" << endl;
		}
		else {
			cout << "System:Unknown Command;Input *HELP* For Help" << endl;
		}
		
	}

	system("pause");
	return 0;
}