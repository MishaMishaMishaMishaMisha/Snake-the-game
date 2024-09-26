#pragma once
#include "Windows.h"
#include "iostream"

// переместить курор на другую позицию
void setPos(int x, int y);

// Функция для очистки строк с использованием ANSI escape codes
void clearLines(int startLine, int numLines);