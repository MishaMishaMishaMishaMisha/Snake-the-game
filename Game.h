#pragma once
#include "ConsoleFunctions.h"
#include "Field.h"
#include <conio.h>



class Game
{
private:
	enum Buttons {
		UP = 72, DOWN = 80, RIGHT = 77, LEFT = 75,
		W = 119, A = 97, S = 115, D = 100,
		w = 87, a = 65, s = 83, d = 68,
		NUMBER_ONE = 49, NUMBER_TWO = 50, NUMBER_THREE = 51, NUMBER_FOUR = 52,
		ESCAPE = 27
	};
	enum Difficulty {EASY, NORMAL, HARD};
	enum FieldSize {SMALL, MEDIUM, LARGE};

	int button;
	Difficulty difficulty = Difficulty::NORMAL;
	FieldSize size = FieldSize::MEDIUM;
	bool game_opened = true;

	Field field;

	void menu();
	void play();
	void settings();


public:
	Game() = default;

	void open();

};