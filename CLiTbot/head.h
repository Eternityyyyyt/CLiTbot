#include <iostream>
#include <cstring>
#include <algorithm>
#include <fstream>
#include <cmath>
using namespace std;

const int MAX_OPS = 1000;
const int MAX_PROCS = 11 + 45 + 14;
const int MAX_ROW = 8;
const int MAX_COL = 8;
const int MAX_LIT = 100;
const int MAX_PATH_LEN = 114;

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
	int op_limit[MAX_PROCS];	  //ÿ�����̵�ָ��������
	bool load(const char* path);
	bool successed();
	bool robot_move(); //��ͼ�е�robot��������ķ����ƶ��������Ƿ�ɹ�
	bool robot_jump();
	bool robot_lit();
};
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
	ResultType result; //���������
};
Result robot_run(const char* path);
bool output_status();