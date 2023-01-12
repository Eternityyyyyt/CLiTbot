#ifndef HEAD_H
#define HEAD_H
#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <cmath>
#define left_robot "robot.left.bmp"
#define right_robot "robot.right.bmp"
#define up_robot "robot.up.bmp"
#define down_robot "robot.down.bmp"
#define origin "map.bmp"
using namespace std;

const int MAX_OPS = 1000;
const int MAX_PROCS = 11 + 45 + 14;
const int MAX_ROW = 8;
const int MAX_COL = 8;
const int MAX_LIT = 100;
const int MAX_PATH_LEN = 114;
extern int time;
//位置类型，可用来表达机器人或灯所在位置
struct Position
{
	int x, y; // x表示列号，y表示行号
	bool operator==(const Position p)
	{
		if (x == p.x && y == p.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
//方向枚举类型，可用来表达机器人朝向，只有四种取值
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
//机器人类型
struct Robot
{
	Position pos;			   //机器人位置
	Direction dir;			   //机器人朝向
	void turn(int dir_to_turn); // 0表示左转，1表示右转
};
//灯类型
struct Light
{
	Position pos; //灯的位置
	bool lighten; //是否被点亮
};
//单元格类型
struct Cell
{
	int height;	  //高度
	int light_id; //灯标识，-1表示该单元格上没有灯
	bool robot;	  // true/false分别表示机器人在/不在该单元格上
};
//指令类型
enum OpType
{
	TL,
	TR,
	MOV,
	JMP,
	LIT,
	CALL,
};
// TL为左转，TR为右转，MOV为向前行走，JMP为跳跃，LIT为点亮灯；
//使用CALL表示调用MAIN，CALL + 1表示调用P1，以此类推。

//过程类型
struct Proc
{
	OpType ops[MAX_OPS]; //指令记录，MAX_OPS为合理常数
	int count;			 //有效指令数
};

//指令序列类型
struct OpSeq
{
	//过程记录，MAX_PROCS为合理常数
	// procs[0]为MAIN过程，procs[1]为P1过程，以此类推
	Proc procs[MAX_PROCS];
	int count; //有效过程数
};
//地图状态类型
struct Map
{
	Cell cells[MAX_ROW][MAX_COL]; //单元格组成二维数组，MAX_ROW、MAX_COL为合理常数
	int row, col;				  //有效行数、有效列数
	Light lights[MAX_LIT];		  //灯记录，MAX_LIT为合理常数
	int num_lights;				  //有效灯数
	Robot robot;				  //地图上同时只有一个机器人
	int num_procs;
	bool exist = false;
	int op_limit[MAX_PROCS];	  //每个过程的指令数限制
	bool load(const char* path);
	bool successed();
	bool robot_move(); //地图中的robot向所朝向的方向移动，返回是否成功
	bool robot_jump();
	bool robot_lit();
};
// 游戏状态类型
struct Game
{
	string map_name; //当前地图的文件路径名
	Map map_init;	 //地图初始状态
	Map map_run;	 //指令执行过程中的地图状态
	//自动保存的文件路径名，MAX_PATH_LEN为合理常数
	string save_path;
	int auto_save_id; //自动保存标识
	int limit;		  //执行指令上限（用来避免无限递归）
};
enum ResultType
{
	FAILED, //命令文件读取失败，说明命令文件存在错误
	LIGHT,	//点亮所有灯
	LIMIT,	//达到步数限制
	DARK	//未点亮所有灯，但是操作已经执行完毕
};
//一次运行命令的的结果
struct Result
{
	int steps;		   //总步数
	ResultType result; //结果的类型
	void output(string op);
};
# pragma pack(1)
struct BMPFileHeader{
	char id[2];//B,M 
	int size;//文件长度 
	short save1;//保留字段，四字节 
	short save2;
	int offset;//像素偏移 
};
# pragma pack(1)
struct BMPInfoHeader{
	   int headsize;//信息头长度 
	   int wid;//x 
	   int hei;//y 
	   short image_pile;//图层，没有用 
	   short pixel_position;//每像素位 
	   int nothing;//压缩算法 
	   int pixel_byte;
	   int x_fbl;
	   int y_fbl;
	   int board_colour;
	   int printer;
};	
struct pixel{
	unsigned char b,g,r;
};
 extern pixel content[900][1200];//content[y][x]---先读里层的-对应先读x ---只在 900*1200的区域内作画 
//这个的大小定义的是地图的总尺寸的像素大小   1200*900大小 
extern pixel Save[200][100];
Result robot_run(const char* path);
bool output_status();
int string_to_int(string input);
int check_P_string(string input);
bool op_input(const char* path);
void save(string path);
void auto_save();
void chartlet_robot(int row,int col,int dir,int height);
void draw_a_normal_cell(int row,int col,int height,int exist_light);
//必不可少的基础定义部分 
void draw_the_original_map();
int get_digit(int number);
string to_string(int n);
void draw_a_lighted_cell(int row,int col,int height);
bool output_results(Result last_result, string path);
#endif
