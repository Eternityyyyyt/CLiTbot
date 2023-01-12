#ifndef HEAD_H
#define HEAD_H
#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <cmath>
#define left_robot "src/robot.left.bmp"
#define right_robot "src/robot.right.bmp"
#define up_robot "src/robot.up.bmp"
#define down_robot "src/robot.down.bmp"
#define origin "imgs/map.bmp"

using namespace std;

const int MAX_OPS = 1000;
const int MAX_PROCS = 11+45+14;
const int MAX_ROW = 8;
const int MAX_COL = 8;
const int MAX_LIT = 100;
const int MAX_PATH_LEN = 114;
extern int time_;

//λ�����ͣ��������������˻������λ��
struct Position
{
	int x, y; // x��ʾ�кţ�y��ʾ�к�
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
//����ö�����ͣ��������������˳���ֻ������ȡֵ
enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
//����������
struct Robot
{
	Position pos;			   //������λ��
	Direction dir;			   //�����˳���
	void turn(int dir_to_turn); // 0��ʾ��ת��1��ʾ��ת
};
//������
struct Light
{
	Position pos; //�Ƶ�λ��
	bool lighten; //�Ƿ񱻵���
};
//��Ԫ������
struct Cell
{
	int height;	  //�߶�
	int light_id; //�Ʊ�ʶ��-1��ʾ�õ�Ԫ����û�е�
	bool robot;	  // true/false�ֱ��ʾ��������/���ڸõ�Ԫ����
};
//ָ������
enum OpType
{
	TL,
	TR,
	MOV,
	JMP,
	LIT,
	CALL,
};
// TLΪ��ת��TRΪ��ת��MOVΪ��ǰ���ߣ�JMPΪ��Ծ��LITΪ�����ƣ�
//ʹ��CALL��ʾ����MAIN��CALL + 1��ʾ����P1���Դ����ơ�

//��������
struct Proc
{
	OpType ops[MAX_OPS]; //ָ���¼��MAX_OPSΪ������
	int count;			 //��Чָ����
};

//ָ����������
struct OpSeq
{
	//���̼�¼��MAX_PROCSΪ������
	// procs[0]ΪMAIN���̣�procs[1]ΪP1���̣��Դ�����
	Proc procs[MAX_PROCS];
	int count; //��Ч������
};
//��ͼ״̬����
struct Map
{
	Cell cells[MAX_ROW][MAX_COL]; //��Ԫ����ɶ�ά���飬MAX_ROW��MAX_COLΪ������
	int row, col;				  //��Ч��������Ч����
	Light lights[MAX_LIT];		  //�Ƽ�¼��MAX_LITΪ������
	int num_lights;				  //��Ч����
	Robot robot;				  //��ͼ��ͬʱֻ��һ��������
	int num_procs;
	bool exist = false;
	int op_limit[MAX_PROCS];	  //ÿ�����̵�ָ��������
	bool load(const char* path);
	bool successed();
	bool robot_move(); //��ͼ�е�robot��������ķ����ƶ��������Ƿ�ɹ�
	bool robot_jump();
	bool robot_lit();
};//��Ϸ�����У���ͼ״̬���ܸı��ֻ�л����˵�λ���볯�򣬵Ʊ����������Ҫ�����ĵƣ� 
// ��Ϸ״̬����
struct Game
{
	string map_name; //��ǰ��ͼ���ļ�·����
	Map map_init;	 //��ͼ��ʼ״̬
	Map map_run;	 //ָ��ִ�й����еĵ�ͼ״̬
	//�Զ�������ļ�·������MAX_PATH_LENΪ������
	string save_path;
	int auto_save_id; //�Զ������ʶ
	int limit;		  //ִ��ָ�����ޣ������������޵ݹ飩
};
enum ResultType
{
	FAILED, //�����ļ���ȡʧ�ܣ�˵�������ļ����ڴ���
	LIGHT,	//�������е�
	LIMIT,	//�ﵽ��������
	DARK	//δ�������еƣ����ǲ����Ѿ�ִ�����
};
//һ����������ĵĽ��
struct Result
{
	int steps;		   //�ܲ���
	ResultType result; //���������,��enum��¼������ԭ�� 
	void output(string op);
};
# pragma pack(1)
struct BMPFileHeader{
	char id[2];//B,M 
	int size;//�ļ����� 
	short save1;//�����ֶΣ����ֽ� 
	short save2;
	int offset;//����ƫ�� 
};
# pragma pack(1)
struct BMPInfoHeader{
	   int headsize;//��Ϣͷ���� 
	   int wid;//x 
	   int hei;//y 
	   short image_pile;//ͼ�㣬û���� 
	   short pixel_position;//ÿ����λ 
	   int nothing;//ѹ���㷨 
	   int pixel_byte;
	   int x_fbl;
	   int y_fbl;
	   int board_colour;
	   int printer;
};	
struct pixel{
	unsigned char b,g,r;
};
 extern pixel content[900][1200];//content[y][x]---�ȶ�����-��Ӧ�ȶ�x ---ֻ�� 900*1200������������ 
//����Ĵ�С������ǵ�ͼ���ܳߴ�����ش�С   1200*900��С 
extern pixel Save[200][100];
Result robot_run(const char* path);//path��ָ�����е�·�������ú�����ȡָ�������ļ�������ִ�����е�ָ������ 
bool output_status();
int string_to_int(string input);//���ַ�ת��Ϊ���� 
int check_P_string(string input);
bool op_input(const char* path);
//����������Ҫ����Ĳ��� 
void save(string path);
void auto_save();
void chartlet_robot(int row,int col,int dir,int height);
void draw_a_normal_cell(int row,int col,int height,int exist_light);
//�ز����ٵĻ������岿�� 
void draw_the_original_map();
int get_digit(int number);
string to_string(int n);
void draw_a_lighted_cell(int row,int col,int height);
bool output_results(Result last_result, string path);
#endif
