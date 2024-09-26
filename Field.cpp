#include "Field.h"

void Field::setSize(uint8_t size)
{
	if (!field.empty() || size >= 5 && size <= 50)
	{
		this->reset();
	}	

	this->size = size;
}

void Field::changeDifficulty(std::chrono::milliseconds dif)
{
	if (!field.empty())
	{
		this->reset();
	}
	this->speed = dif;
}

void Field::initField()
{
	if (field.empty())
	{
		field.resize(size);
		for (int i = 0; i < size; i++)
		{
			field[i].resize(size, ' ');
		}

		int middle = size / 2;
		field[middle][0] = '>';
		field[middle][1] = '>';
		field[middle][2] = 'o';
		field[middle][middle + middle / 2] = '@';

		tail.first = middle;
		tail.second = 0;
		head.first = middle;
		head.second = 2;

		srand(time(0));
	}
}

void Field::reset()
{
	if (!field.empty())
	{
		snake_length = 3;
		direction = RIGHT;
		is_game_over = false;
		is_pause = false;
		for (int i = 0; i < size; i++)
		{
			field[i].clear();
		}
		field.clear();
	}
}

void Field::dispayField()
{
	for (int i = 0; i < size * 2 + 3; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;

	for (int i = 0; i < size; i++)
	{
		std::cout << "#";
		for (int j = 0; j < size; j++)
		{
			std::cout << "|" << field[i][j];
		}
		std::cout << "|#" << std::endl;
	}

	for (int i = 0; i < size * 2 + 3; i++)
	{
		std::cout << "#";
	}
	std::cout << std::endl;
}



void Field::start()
{
	bool temp = true;
	while (temp)
	{
		{
			std::unique_lock<std::mutex> lock(mtx);
			// if paused, wait ffor signal
			cv.wait(lock, [this]() { return !is_pause; });
		}


		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		temp = makeMove();
	}
	std::cout << "Game over" << std::endl;
	std::cout << "Your score: " << snake_length - 3 << std::endl;
	is_game_over = true;
}

bool Field::makeMove()
{
	coords next = head;
	char arrow;
	if (direction == RIGHT)
	{
		next.second++;
		arrow = '>';
	}
	else if (direction == LEFT)
	{
		next.second--;
		arrow = '<';
	}
	else if (direction == UP)
	{
		next.first--;
		arrow = '^';
	}
	else
	{
		next.first++;
		arrow = 'v';
	}

	int check = checkMove(next.first, next.second);

	if (check == 0)
	{
		updateField(next, arrow, false, true);
		return false;
	}
	else
	{
		bool isGrow = false;
		if (check == 2)
		{
			isGrow = true;
		}
		updateField(next, arrow, isGrow);
		return true;
	}

}

int Field::checkMove(uint16_t x, uint16_t y)
{	
	if (x >= size || y >= size || x <= -1 || y <= -1)
	{
		return 0;
	}
	else if (field[x][y] == ' ')
	{
		return 1;
	}
	else if (field[x][y] == '@')
	{
		snake_length++;
		generateApple();
		return 2;
	}
	// snake hit itself 
	else
	{
		return 0;
	}
}

void Field::updateField(coords next, char arrow, bool isGrow, bool isHit)
{
	if (isHit)
	{
		setPos(next.second * 2 + 2, next.first + 1);
		std::cout << 'X';
		setPos(head.second * 2 + 2, head.first + 1);
		std::cout << arrow;
		setPos(0, size + 2);
		return;
	}
	
	field[next.first][next.second] = 'o';
	field[head.first][head.second] = arrow;
	// display on console
	setPos(next.second * 2 + 2, next.first + 1);
	std::cout << 'o';
	setPos(head.second * 2 + 2, head.first + 1);
	std::cout << arrow;
	setPos(0, size + 2);
	head = next;

	if (!isGrow)
	{
		setPos(tail.second * 2 + 2, tail.first + 1);
		std::cout << ' ';
		setPos(0, size + 2);
		char tail_arrow = field[tail.first][tail.second];
		field[tail.first][tail.second] = ' ';
		if (tail_arrow == '>')
		{
			tail.second++;
		}
		else if (tail_arrow == '<')
		{
			tail.second--;
		}
		else if (tail_arrow == '^')
		{
			tail.first--;
		}
		else
		{
			tail.first++;
		}
	}
}

void Field::changeDirection(Direction direction)
{
	this->direction = direction;
}

void Field::generateApple()
{
	int x, y;
	while (true)
	{
		x = rand() % (size - 1);
		y = rand() % (size - 1);
		if (field[x][y] == ' ')
		{
			break;
		}
	}
	
	field[x][y] = '@';
	// display on console
	setPos(y * 2 + 2, x + 1);
	std::cout << '@';
	setPos(0, size + 2);
}

void Field::pause()
{
	std::unique_lock<std::mutex> lock(mtx);
	std::cout << "          PAUSE";
	is_pause = true;
}

void Field::resume() {
	std::unique_lock<std::mutex> lock(mtx);
	is_pause = false;

	setPos(0, size + 2);
	std::cout << "\033[K";  // clear line "PAUSE"

	cv.notify_one();
}