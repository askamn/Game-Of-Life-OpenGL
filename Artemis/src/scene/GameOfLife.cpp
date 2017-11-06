#include "GameOfLife.h"

GameOfLife::GameOfLife(size_t width, size_t height) :
	m_Board(nullptr),
	m_WindowWidth(width),
	m_WindowHeight(height)
{
	width /= CELL_SIZE;
	height /= CELL_SIZE;
	
	m_BoardWidth = width;
	m_BoardHeight = height;

	m_Board = new uint32_t[width * height];
	memset(m_Board, 0, width * height);

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> state(0,1);

	int index = 0;
	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 1; j < width - 1; j++)
		{
			index = getIndex(i, j);
			this->m_Board[index] = state(mt);

			this->generateSprite(i, j, this->m_Board[index]);
		}
	}
}

void GameOfLife::generateSprites()
{
	// Delete old sprites
	for (auto& sprite : this->m_Sprites)
	{
		delete sprite;
		sprite = nullptr;
	}

	this->m_Sprites.clear();

	int index = 0;
	for (int x = 1; x < m_BoardHeight - 1; x++)
	{
		for (int y = 1; y < m_BoardWidth - 1; y++)
		{
			index = getIndex(x, y);
			this->generateSprite(x, y, this->m_Board[index]);
		}
	}
}

void GameOfLife::generateSprite(int x, int y, int state)
{
	// Position interpolation
	int _x = x;
	int _y = y;
	
	// This math because our rendering space has the origin at its center while the board begins at the top left (speaking hypothetically, because its a matrix)
	y = m_WindowHeight / 2 - CELL_SIZE / 2 - _x * 8;
	x = (-m_WindowWidth / 2 + CELL_SIZE / 2) + _y * 8;

	// If the cell is, alive, draw a sprite
	if (state == 1)
	{
		this->m_Sprites.push_back(new Sprite(glm::vec3(x, y, 0.0f), glm::vec2(CELL_SIZE, CELL_SIZE), Color(0x2980b9ff)));
	}
}

void GameOfLife::NextGeneration()
{
	int index = 0;
	uint32_t *nextGenerationBoard = new uint32_t[m_BoardHeight * m_BoardWidth];

	for (int x = 1; x < m_BoardHeight - 1; x++)
	{
		for (int y = 1; y < m_BoardWidth - 1; y++)
		{
			// Grab the number of neighbours
			int neighbours = 0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					index = getIndex(x + i, y + j);
					neighbours += this->m_Board[index];
				}
			}

			index = getIndex(x, y);
			neighbours -= this->m_Board[index];

			// If the cell is alive...
			if (this->m_Board[index] && ( neighbours >= 4 || neighbours <= 1))
			{
				nextGenerationBoard[index] = 0;
			}
			// If the cell is dead
			else if (this->m_Board[index] == 0 && neighbours == 3)
			{
				nextGenerationBoard[index] = 1;
			}
			else
			{
				nextGenerationBoard[index] = this->m_Board[index];
			}
		}
	}

	delete[] this->m_Board;
	this->m_Board = nextGenerationBoard;

	this->generateSprites();
}

GameOfLife::~GameOfLife()
{
	if (m_Board != nullptr)
	{
		delete[] m_Board;
		m_Board = nullptr;
	}

	for (auto& sprite : this->m_Sprites)
	{
		delete sprite;
		sprite = nullptr;
	}

	this->m_Sprites.clear();
}