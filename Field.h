#pragma once
#include "iostream"


#include "ConsoleFunctions.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

#include <conio.h>

enum Direction{UP, DOWN, RIGHT, LEFT};
typedef std::pair<uint16_t, uint16_t> coords;

class Field
{
private:
	std::vector<std::vector<char>> field;
	uint8_t size = 15; // field 15x15
	uint16_t snake_length = 3;
	Direction direction = Direction::RIGHT;

	coords head;
	coords tail;

	std::mutex mtx;
	std::condition_variable cv;
	std::chrono::milliseconds speed = std::chrono::milliseconds(200);

public:
	Field() = default;
	void setSize(uint8_t size);
	void changeDifficulty(std::chrono::milliseconds dif); // speed
	void reset(); // clear field and make parameters default
	void dispayField();
	void initField(); // initialization of field

	bool makeMove(); // return: false - game over; true - successful move
	int checkMove(uint16_t x, uint16_t y); // return: 0 - snake hit wall or itself; 1 - just move; 2 - snake pick up apple
	void changeDirection(Direction direction);
	void updateField(coords pred_head, char arrow, bool isGrow = false, bool isHit = false);
	void generateApple();
	void start();

	bool is_game_over;
	bool is_pause;

	void pause();
	void resume();
};

