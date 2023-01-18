#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include  "head.h"
using namespace std;

extern Game game;

bool op_input(const char* path)
{
    ifstream fin;
    ofstream fout;
    string path_string(path);
    fout.open(path);
    int user_proc_num;//�û�ʹ�õĹ�����
    int op_num[MAX_PROCS]={0};//�洢�û������ÿ�����̵�ָ����
    bool input_legal = false;//�ж��Ƿ�Ϸ�
    while (!input_legal) {
        cout << "<System>:Please Input The Number Of Processes:";
        cin >> user_proc_num;
        if (cin.rdstate()) {
            cout << "<System>:Error:This Input Is Illegal!Please Input a Number!" << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<int>::max(), '\n');
            input_legal = false;
        }
        else
        {
            if (user_proc_num > game.map_init.num_procs)
            {
                input_legal = false;
                cout << "<System>:The Number Of The Processes Exceeds The Limit Of The Map!Please Re-input!" << endl;
            }
            else {
                input_legal = true;
            }     
        }
    }
    fout << user_proc_num << endl;
    string op_input;//��ȡ�û���ָ��
    for (int i = 0; i < user_proc_num; i++)
    {
        cout << "<System>:Please Input Process "<<i<<":";
        cin >> op_num[i];
        if (cin.rdstate()) {
            cout << "<System>:Error:This Input Is Illegal!Please Input a Number!" << endl;
            i--;
            cin.clear();
            cin.ignore(std::numeric_limits<int>::max(), '\n');
            continue;
        }
        else
        {
            if (op_num[i] > game.map_init.op_limit[i])
            {
                cout << "<System>:The Number Of The Operations In Process "<<i<<" Exceeds The Limit Of The Map!Please Re-input!" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<int>::max(), '\n');
                i--;
                continue;
            }
            else {
                getline(cin, op_input);
            }
            fout << op_num[i] << op_input << endl;
        }
    }
    fout.close();
    return true;
};

bool output_status()
{
    cout << "Map Name: " << game.map_name << endl;
    cout << "Autosave: " << game.save_path << endl;
    cout << "Step Limit: " << game.limit << endl;
    for (int i = 0; i < game.map_init.row; i++)
    {
        for (int j = 0; j < game.map_init.col; j++)
        {
            if (game.map_init.cells[i][j].height == 0)//��ʾ�õ�Ԫ��û�и߶�
            {
                cout << " ";
            }
            else {
                if (game.map_init.cells[i][j].light_id != -1)//��ʾ�õ�Ԫ���е�
                {
                    if (game.map_init.cells[i][j].robot)//��ʾ�õ�Ԫ���л�����
                    {
                        cout << "\033[91;104;1m" << game.map_init.cells[i][j].height << "\033[0m";
                    }
                    else {//��ʾ�õ�Ԫ��û�л����� 
                        cout << "\033[92;104;1m" << game.map_init.cells[i][j].height << "\033[0m";
                    }
                }
                else {//��ʾ�õ�Ԫ��û�е�
                    if (game.map_init.cells[i][j].robot)//��ʾ�õ�Ԫ���л�����
                    {
                        cout << "\033[91;100;1m" << game.map_init.cells[i][j].height << "\033[0m";
                    }
                    else {//��ʾ�õ�Ԫ��û�л����� 
                        cout << "\033[92;100;1m" << game.map_init.cells[i][j].height << "\033[0m";
                    }
                }
            }
        }
        cout << endl;//ÿ�����һ�е�����ͻ���
    }
    cout << "Proc Limit : [";
    for (int i = 0; i < game.map_init.num_procs - 1; i++)
    {
        cout << game.map_init.op_limit[i] << ", ";
    }
    cout << game.map_init.op_limit[game.map_init.num_procs - 1] << "]" << endl;
    cout << "Robot is facing ";
    switch (game.map_init.robot.dir)
    {
    case UP:
        cout << "UP";
        break;
    case DOWN:
        cout << "DOWN";
        break;
    case LEFT:
        cout << "LEFT";
        break;
    case RIGHT:
        cout << "RIGHT";
        break;
    }
    cout << endl;
    return true;
}
