#include "ConsoleFunctions.h"

void setPos(int x, int y)
{
	COORD coord; // ��������� ��� �������� ���������
	coord.X = x; // �������������� ����������
	coord.Y = y; // ������������ ����������
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // ������������� �������
}

void clearLines(int startLine, int numLines)
{
	for (int i = 0; i < numLines; i++)
	{
		setPos(0, startLine + i);  // ������������ �� ������
		std::cout << "\033[K";  // ANSI-��� ��� ������� �� ����� ������
	}
	// ���������� ������ ������� �� ��������� �������
	setPos(0, startLine);
}
