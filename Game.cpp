#include "Game.h"


void Game::open()
{
	while (game_opened)
	{
		menu();
	}
	system("cls");
	std::cout << "\n\n======Bye!=======\n";
}

void Game::menu()
{
	system("cls");
	std::cout << "======Snake======" << std::endl;
	std::cout << "    1. Start" << std::endl;
	std::cout << "    2. Settings" << std::endl;
	std::cout << "    3. Exit" << std::endl;
	std::cout << std::endl << "Enter (1,2 or 3)...";

	button = 0;
	while (button != Buttons::NUMBER_ONE && button != Buttons::NUMBER_TWO && button != Buttons::NUMBER_THREE)
	{
		button = _getch();
	}

	if (button == Buttons::NUMBER_THREE)
	{
		game_opened = false;
	}
	else if (button == Buttons::NUMBER_TWO)
	{
		settings();
	}
	else
	{
		play();
	}

}

void Game::settings()
{
	system("cls");

	std::cout << "======Settings======" << std::endl;
	while (true) 
	{
		switch (difficulty) 
		{
		case Difficulty::NORMAL:
			setPos(0, 1);
			std::cout << "\033[K";
			std::cout << "1. Difficulty - normal" << std::endl;
			break;
		case Difficulty::HARD:
			setPos(0, 1);
			std::cout << "\033[K";
			std::cout << "1. Difficulty - hard" << std::endl;
			break;
		case Difficulty::EASY:
			setPos(0, 1);
			std::cout << "\033[K";
			std::cout << "1. Difficulty - easy" << std::endl;
			break;
		}

		switch (size)
		{
		case FieldSize::MEDIUM:
			setPos(0, 2);
			std::cout << "\033[K";
			std::cout << "2. Field Size - medium" << std::endl;
			break;
		case FieldSize::SMALL:
			setPos(0, 2);
			std::cout << "\033[K";
			std::cout << "2. Field Size - small" << std::endl;
			break;
		case FieldSize::LARGE:
			setPos(0, 2);
			std::cout << "\033[K";
			std::cout << "2. Field Size - large" << std::endl;
			break;
		}

		std::cout << "3. Save" << std::endl;
		std::cout << "4. Back to menu" << std::endl;
		std::cout << std::endl << "Enter (1, 2, 3 or 4)...";

		button = _getch();
		if (button == Buttons::NUMBER_ONE) 
		{
			difficulty = static_cast<Difficulty>((difficulty + 1) % 3);
		}
		else if (button == Buttons::NUMBER_TWO)
		{
			size = static_cast<FieldSize>((size + 1) % 3);
		}
		else if (button == Buttons::NUMBER_TWO)
		{
			size = static_cast<FieldSize>((size + 1) % 3);
		}
		else if (button == Buttons::NUMBER_THREE)
		{
			if (size == FieldSize::SMALL) field.setSize(7);
			else if (size == FieldSize::LARGE) field.setSize(25);
			else field.setSize(15);

			if (difficulty == Difficulty::EASY) field.changeDifficulty(std::chrono::milliseconds(500));
			else if (difficulty == Difficulty::NORMAL) field.changeDifficulty(std::chrono::milliseconds(200));
			else field.changeDifficulty(std::chrono::milliseconds(100));
		}
		else if (button == Buttons::NUMBER_FOUR)
		{
			break;
		}
	}

}

void Game::play()
{
	system("cls");

	field.reset();
	field.initField();
	field.dispayField();
	std::thread th(&Field::start, std::ref(field));

	int button;
	Direction current_direction = Direction::RIGHT;
	while (!field.is_game_over)
	{
		if (_kbhit())
		{
			button = _getch();
			if (button == 224)
			{
				button = _getch();
			}
			if ((button == UP || button == W || button == w) && current_direction != Direction::DOWN)
			{
				field.changeDirection(Direction::UP);
				current_direction = Direction::UP;
			}
			else if ((button == DOWN || button == S || button == s) && current_direction != Direction::UP)
			{
				field.changeDirection(Direction::DOWN);
				current_direction = Direction::DOWN;
			}
			else if ((button == RIGHT || button == D || button == d) && current_direction != Direction::LEFT)
			{
				field.changeDirection(Direction::RIGHT);
				current_direction = Direction::RIGHT;
			}
			else if ((button == LEFT || button == A || button == a) && current_direction != Direction::RIGHT)
			{
				field.changeDirection(Direction::LEFT);
				current_direction = Direction::LEFT;
			}
			// pause
			else if (button == ESCAPE)
			{
				if (field.is_pause)
				{
					field.resume();
				}
				else
				{
					field.pause();
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}

	th.join();

	std::cout << "Press any button...";
	button = _getch();
	system("cls");
}