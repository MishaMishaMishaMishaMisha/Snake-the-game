#include "ConsoleFunctions.h"

void setPos(int x, int y)
{
	COORD coord; // Структура для хранения координат
	coord.X = x; // Горизонтальная координата
	coord.Y = y; // Вертикальная координата
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Устанавливаем позицию
}

void clearLines(int startLine, int numLines)
{
	for (int i = 0; i < numLines; i++)
	{
		setPos(0, startLine + i);  // Перемещаемся на строку
		std::cout << "\033[K";  // ANSI-код для очистки до конца строки
	}
	// Возвращаем курсор обратно на начальную позицию
	setPos(0, startLine);
}
