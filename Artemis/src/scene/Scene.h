#pragma once

#include <src/core/Common.h>
#include <src/core/Window.h>
#include <src/core/Shader.h>
#include <src/core/Renderer2D.h>
#include <src/core/ShaderProgram.h>

#include <src/scene/GameOfLife.h>
#include <glm/gtc/matrix_transform.hpp>

class Scene
{
private:
	GameOfLife m_GameOfLife;
	Renderer2D m_Renderer;
	ShaderProgram m_ShaderProgram;
	Window m_Window;

	// Camera Properties
	float m_CameraX;
	float m_CameraY;
	float m_CameraSpeed;

	const int LEFT;
	const int RIGHT;
	const int TOP;
	const int BOTTOM;

public:
	Scene(const Window& window);

	void Update();
	void Render();
	void checkSpriteOutOfBounds();
	void checkCameraInput();

	~Scene();
};