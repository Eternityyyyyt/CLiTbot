#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;

void Robot::turn(int dir_to_turn) {
	if (dir_to_turn == 0)
	{
		switch (dir)
		{
		case UP:
			dir = LEFT;
			break;
		case DOWN:
			dir = RIGHT;
			break;
		case LEFT:
			dir = DOWN;
			break;
		case RIGHT:
			dir = UP;
			break;
		}
	}
	else if (dir_to_turn == 1)
	{
		switch (dir)
		{
		case UP:
			dir = RIGHT;
			break;
		case DOWN:
			dir = LEFT;
			break;
		case LEFT:
			dir = UP;
			break;
		case RIGHT:
			dir = DOWN;
			break;
		}
	}
}