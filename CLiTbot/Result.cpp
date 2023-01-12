#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include "head.h"
using namespace std;

void Result::output(string op)
{
	cout << "<System>:" << op << ",Result:";
	switch (result)
	{
	case FAILED:
		cout << "Run Failed" << endl;
		break;
	case LIGHT:
		cout << "Congratulations!You Have Lit All The Lights!" << endl;
		break;
	case LIMIT:
		cout << "Reach The Max Step Limit" << endl;
		break;
	case DARK:
		cout << "Still Some Dark Lights!Try Again!" << endl;
		break;
	default:
		break;
	}
}
