#include "Scene.h"

Scene::Scene(const Window& window) :
	m_Window(window),
	m_GameOfLife(window.getWidth(), window.getHeight()),
	m_CameraX(0.0f),
	m_CameraY(0.0f),
	m_CameraSpeed(1.0f),
	LEFT(-window.getWidth() / 2), RIGHT(window.getWidth() / 2),
	TOP(window.getHeight() / 2), BOTTOM(-window.getHeight() / 2)
{
	m_ShaderProgram.AttachShader(Shader("Shaders/VertexShader.glsl", Shader::ShaderType::Vertex));
	m_ShaderProgram.AttachShader(Shader("Shaders/FragmentShader.glsl", Shader::ShaderType::Fragment));
	m_ShaderProgram.Link();
	m_ShaderProgram.Use();

	// Camera position
	m_ShaderProgram.SetUniform2f("input_position", m_CameraX, m_CameraY);

	// Set the Camera Projection Matrix
	glm::mat4 prMatrix = glm::ortho(-window.getWidth() / 2.0f, window.getWidth() / 2.0f, -window.getHeight() / 2.0f, window.getHeight() / 2.0f, -1.0f, 1.0f);
	m_ShaderProgram.SetMatrix4f("pr_matrix", &prMatrix[0][0]);
}

void Scene::Update()
{
	checkCameraInput();
}

void Scene::Render()
{
	m_Renderer.Begin();
	m_Renderer.AddSprites(m_GameOfLife.Sprites());
	m_Renderer.End();
	m_Renderer.Render();

	m_GameOfLife.NextGeneration();	// Proceed to the next generation
	checkSpriteOutOfBounds();		// Make sure no sprite is out of bounds
}

void Scene::checkSpriteOutOfBounds()
{
	std::vector<Sprite*> sprites = m_GameOfLife.Sprites();

	for (int i = 0; i < sprites.size(); i++)
	{
		glm::vec3 position = sprites[i]->getPosition();

		if (position.x + m_GameOfLife.getCellSize() / 2 > RIGHT)
		{
			position.x = RIGHT - m_GameOfLife.getCellSize() / 2;
		}
		if (-position.x - m_GameOfLife.getCellSize() / 2 < LEFT)
		{
			position.x = LEFT + m_GameOfLife.getCellSize() / 2;
		}
		if (position.y + m_GameOfLife.getCellSize() / 2 > TOP)
		{
			position.y = TOP - m_GameOfLife.getCellSize() / 2;
		}
		if (-position.y - m_GameOfLife.getCellSize() / 2 < BOTTOM)
		{
			position.y = BOTTOM + m_GameOfLife.getCellSize() / 2;
		}

		sprites[i]->setPosition(position);
	}
}

void Scene::checkCameraInput()
{
	if (m_Window.IsKeyDown(GLFW_KEY_A))
	{
		m_CameraX -= 1 * m_CameraSpeed;
	}
	else if (m_Window.IsKeyDown(GLFW_KEY_D))
	{
		m_CameraX += 1 * m_CameraSpeed;
	}
	else if (m_Window.IsKeyDown(GLFW_KEY_W))
	{
		m_CameraY += 1 * m_CameraSpeed;
	}
	else if (m_Window.IsKeyDown(GLFW_KEY_S))
	{
		m_CameraY -= 1 * m_CameraSpeed;
	}
	else if (m_Window.IsKeyPressed(GLFW_KEY_SPACE))
	{
		std::cout << "(x, y) : (" << m_CameraX << ", " << m_CameraY << ")" << std::endl;
	}
	else if (m_Window.IsKeyPressed(GLFW_KEY_Q))
	{
		m_CameraSpeed += 1.0f;
#ifdef _DEBUG
		std::cout << "Speed changed to: " << m_CameraSpeed << std::endl;
#endif
	}
	else if (m_Window.IsKeyPressed(GLFW_KEY_E))
	{
		if (m_CameraSpeed != 1.0f)
		{
			m_CameraSpeed -= 1.0f;
		}

#ifdef _DEBUG
		std::cout << "Speed changed to: " << m_CameraSpeed << std::endl;
#endif
	}
}

Scene::~Scene()
{

}