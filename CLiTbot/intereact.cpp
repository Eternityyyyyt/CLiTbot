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
    int row;//�û�ʹ�õĹ�����
    int op_num[MAX_PROCS]={0};//�洢�û������ÿ�����̵�ָ����
    cin >> row;
    bool if_legal = true;//�ж��Ƿ�Ϸ�
    if (row > game.map_init.num_procs)
    {
        if_legal = false;
    }
    while (!if_legal)
    {
        cout << "<System>:Error:The Number Of Processes Exceeds The Limit Of This Map!Please Re-enter!" << endl;
        cin >> row;
        if (row > game.map_init.num_procs)
        {
            if_legal = false;
        }
        else {
            if_legal = true;
        }
    }
    fout << row << endl;
    string op_input;//��ȡ�û���ָ��
    for (int i = 0; i < row; i++)
    {
        cin >> op_num[i];
        if (op_num[i] > game.map_init.op_limit[i])
        {
            cout << "<System>:Error:This Input Is Illegal!Please Re-enter!" << endl;
            i--;
            continue;
        }
        else {
            getline(cin, op_input);
        }
        fout << op_num[i] << op_input << endl;
    }
    fout.close();
    return true;
};

bool output_status(void)
{
    ifstream fin;
    ofstream fout;
    fin.open(game.map_name);
    fin >> game.map_init.row >> game.map_init.col >> game.map_init.num_lights;
    fin >> game.map_init.num_procs;//!����ط��ǶԵ���
    for (int i = 0; i < game.map_init.row; i++)
    {
        for (int j = 0; j < game.map_init.col; j++)
        {
            fin >> game.map_init.cells[i][j].height;//�����Ԫ��ĳ���
            game.map_init.cells[i][j].light_id = -1;//�Ȱ����еĵ�Ԫ���ʼ��Ϊû�е�
            game.map_init.cells[i][j].robot = false;//ͬ��

        }
    }
    for (int k = 0; k < game.map_init.num_lights; k++)
    {
        fin >> game.map_init.lights->pos.x >> game.map_init.lights->pos.y;//�Ƶ�λ��
        game.map_init.lights->lighten = false;//��û�б�����
        game.map_init.cells[game.map_init.lights->pos.y][game.map_init.lights->pos.x].light_id = 1;//�ѵ�Ԫ��ĵƵı�ʶ����

    }
    for (int l = 0; l < game.map_init.num_procs; l++)
    {
        fin >> game.map_init.op_limit[l];//��ÿһ�����̵����ƴ����洢��ȥ
    }
    fin >> game.map_init.robot.pos.x >> game.map_init.robot.pos.y >> (int&)game.map_init.robot.dir;//�����˵�λ���Լ�����
    game.map_init.cells[game.map_init.robot.pos.y][game.map_init.robot.pos.x].robot = true;//�ѵ�Ԫ��Ļ����˵����ݽ��и���

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
                        cout << "\33[91;104;1m" << game.map_init.cells[i][j].height << "\33[0m";
                    }
                    else {//��ʾ�õ�Ԫ��û�л����� 
                        cout << "\33[92;104;1m" << game.map_init.cells[i][j].height << "\33[0m";
                    }
                }
                else {//��ʾ�õ�Ԫ��û�е�
                    if (game.map_init.cells[i][j].robot)//��ʾ�õ�Ԫ���л�����
                    {
                        cout << "\33[91;100;1m" << game.map_init.cells[i][j].height << "\33[0m";
                    }
                    else {//��ʾ�õ�Ԫ��û�л����� 
                        cout << "\33[92;100;1m" << game.map_init.cells[i][j].height << "\33[0m";
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
    fin.close();
    return true;
}