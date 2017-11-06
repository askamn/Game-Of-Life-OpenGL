#pragma once

#include <src/core/Common.h>
#include <src/core/Color.h>
#include <src/scene/Sprite.h>

#include <random>
#include <vector>

class GameOfLife
{
private:
	// Cell size
	const int CELL_SIZE = 8;

	// Sprites
	std::vector<Sprite*> m_Sprites;

	// The board
	uint32_t *m_Board;

	size_t m_BoardWidth;
	size_t m_BoardHeight;

	// We need these to interpolate the position of the sprites
	int m_WindowWidth;
	int m_WindowHeight;

	// Cell Colors... just for fun
	

public:
	GameOfLife(size_t width, size_t height);

	void generateSprite(int x, int y, int state);
	void generateSprites();
	void NextGeneration();

	// For traversing our 1D heap as a 2D array
	inline uint32_t getIndex(int x, int y)	const { return x * m_BoardHeight + y; }
	inline uint32_t Size()					const { return m_BoardWidth * m_BoardHeight; }
	inline std::vector<Sprite*> Sprites()	const { return this->m_Sprites; }
	inline const int getCellSize()			const { return this->CELL_SIZE; }

	~GameOfLife();
};