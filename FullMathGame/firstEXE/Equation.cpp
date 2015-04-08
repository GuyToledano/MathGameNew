#include "Equation.h"
#include "io_utils.h"
#include <iostream>

using namespace std;
//TODO: לבצע תיעוד לקוד

Equation::Equation(const unsigned int currentlevel)
{
	num1 = rand() % (currentlevel + 10) + 1;
	num2 = rand() % (currentlevel + 10) + 1;
	oper = rand() % 4;
	switch (oper)
	{
	case PLUS:
		result = num1 + num2;
		hiddenNum = rand() % 2;
		if (hiddenNum)
			targetNum = num2;
		else
			targetNum = num1;
		break;
	case MULT:
		result = num1*num2;
		hiddenNum = rand() % 2;
		if (hiddenNum)
			targetNum = num2;
		else
			targetNum = num1;
		break;
	case MINUS:
		result = num1 + num2;
		hiddenNum = rand() % 2;
		if (hiddenNum)
			targetNum = num2;
		else
			targetNum = num1;
		break;
	case DIV:
		result = num1*num2;
		hiddenNum = rand() % 2;
		if (hiddenNum)
			targetNum = num2;
		else
			targetNum = num1;
		break;
	}
}
void Equation::printEquation(int x, int y)
{
	char op;
	gotoxy(x, y);

	op = getOperator(oper);
	if (op == NULL)
	{
		cout << "invalid operator!" << endl;
		return;
	}
	if (targetNum == num1)
	{
		if (op == '+' || op == '*')
			cout << "__ " << op << " " << num2 << " = " << result;
		else
			cout << result << " " << op << "__ = " << num2;
	}
	else
	{
		if (op == '+' || op == '*')
			cout << num1 << " " << op << " __" << " = " << result;
		else
			cout << result << " " << op << " " << num1 << " = __";
	}

}
char Equation::getOperator(int oper)
{
	switch (oper)
	{
	case PLUS:
		return '+';

	case MINUS:
		return '-';

	case DIV:
		return '/';

	case MULT:
		return '*';
	}

	return NULL;
}