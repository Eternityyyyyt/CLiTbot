#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;

extern Game game;
bool output_results(Result last_result ,string path){
	ifstream fin;
	fin.open(path);
	if (fin.is_open() == 0) {
		return false;
	}
	cout<<"Run "<< path <<", result: ";
	if(last_result.result==0)
	{
		cout<<"FAILED"<<endl;
	}
	else if(last_result.result==1)
	{
		cout<<"LIGHT"<<endl;
	}
	else if(last_result.result==2)
	{
		cout<<"LIMIT"<<endl;
	}
	else{
		cout<<"DARK"<<endl;
	}
	cout<<"Step(s) used: "<<last_result.steps<<endl;
	for(int i=0;i<game.map_run.row;i++)
    {
        for(int j=0;j<game.map_run.col;j++)
        {
            if(game.map_run.cells[i][j].height==0)//表示该单元格没有高度
            {
                cout<<" ";
            }
            else{
                if(game.map_run.cells[i][j].light_id!=-1)//表示该单元格有灯
                {
					if(game.map_run.lights[game.map_run.cells[i][j].light_id].lighten)//表示灯已经被点亮
					{
						if(game.map_run.cells[i][j].robot)//表示该单元格有机器人
						{
							cout<<"\033[91;103;1m"<<game.map_run.cells[i][j].height<<"\033[0m";
						}
						else{//表示该单元格没有机器人 
							cout<<"\033[92;103;1m"<<game.map_run.cells[i][j].height<<"\033[0m";
						}
					}
					else{
						if(game.map_run.cells[i][j].robot)//表示该单元格有机器人
						{
							cout<<"\033[91;104;1m"<<game.map_run.cells[i][j].height<<"\033[0m";
						}
						else{//表示该单元格没有机器人 
							cout<<"\033[92;104;1m"<<game.map_run.cells[i][j].height<<"\033[0m";
						}
					}
               }
                else{//表示该单元格没有灯
                    if(game.map_run.cells[i][j].robot)//表示该单元格有机器人
                    {
                        cout<<"\033[91;100;1m"<<game.map_run.cells[i][j].height<<"\033[0m";
                    }
                    else{//表示该单元格没有机器人 
                        cout<<"\033[92;100;1m"<<game.map_run.cells[i][j].height<<"\033[0m";
                    }
                }
            }
        }
        cout<<endl;//每次完成一行的输入就换行
    }
	cout<<"Robot is facing ";
	switch (game.map_run.robot.dir)
    {
    case UP:
        cout<<"UP";
        break;
    case DOWN:
        cout<<"DOWN";
        break;
    case LEFT:
        cout<<"LEFT";
        break;
    case RIGHT:
        cout<<"RIGHT";
        break;
    }
	cout<<endl;
	return true;
} 
