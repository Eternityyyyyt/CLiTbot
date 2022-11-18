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
    int row;//用户使用的过程数
    int op_num[MAX_PROCS]={0};//存储用户输入的每个过程的指令数
    cin >> row;
    bool if_legal = true;//判断是否合法
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
    string op_input;//获取用户的指令
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
    fin >> game.map_init.num_procs;//!这个地方是对的吗
    for (int i = 0; i < game.map_init.row; i++)
    {
        for (int j = 0; j < game.map_init.col; j++)
        {
            fin >> game.map_init.cells[i][j].height;//这个单元格的长度
            game.map_init.cells[i][j].light_id = -1;//先把所有的单元格初始化为没有灯
            game.map_init.cells[i][j].robot = false;//同上

        }
    }
    for (int k = 0; k < game.map_init.num_lights; k++)
    {
        fin >> game.map_init.lights->pos.x >> game.map_init.lights->pos.y;//灯的位置
        game.map_init.lights->lighten = false;//灯没有被点亮
        game.map_init.cells[game.map_init.lights->pos.y][game.map_init.lights->pos.x].light_id = 1;//把单元格的灯的标识更改

    }
    for (int l = 0; l < game.map_init.num_procs; l++)
    {
        fin >> game.map_init.op_limit[l];//把每一个进程的限制次数存储进去
    }
    fin >> game.map_init.robot.pos.x >> game.map_init.robot.pos.y >> (int&)game.map_init.robot.dir;//机器人的位置以及朝向
    game.map_init.cells[game.map_init.robot.pos.y][game.map_init.robot.pos.x].robot = true;//把单元格的机器人的内容进行更新

    cout << "Map Name: " << game.map_name << endl;
    cout << "Autosave: " << game.save_path << endl;
    cout << "Step Limit: " << game.limit << endl;
 
    for (int i = 0; i < game.map_init.row; i++)
    {
        for (int j = 0; j < game.map_init.col; j++)
        {
            if (game.map_init.cells[i][j].height == 0)//表示该单元格没有高度
            {
                cout << " ";
            }
            else {
                if (game.map_init.cells[i][j].light_id != -1)//表示该单元格有灯
                {
                    if (game.map_init.cells[i][j].robot)//表示该单元格有机器人
                    {
                        cout << "\33[91;104;1m" << game.map_init.cells[i][j].height << "\33[0m";
                    }
                    else {//表示该单元格没有机器人 
                        cout << "\33[92;104;1m" << game.map_init.cells[i][j].height << "\33[0m";
                    }
                }
                else {//表示该单元格没有灯
                    if (game.map_init.cells[i][j].robot)//表示该单元格有机器人
                    {
                        cout << "\33[91;100;1m" << game.map_init.cells[i][j].height << "\33[0m";
                    }
                    else {//表示该单元格没有机器人 
                        cout << "\33[92;100;1m" << game.map_init.cells[i][j].height << "\33[0m";
                    }
                }
            }
        }
        cout << endl;//每次完成一行的输入就换行
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