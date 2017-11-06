#pragma once

#include <string>
#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <src/core/Common.h>

#define MAX_KEYS 1024

//#define INPUT_DEBUG

class Window
{
public:
	uint8_t m_KeysDown[MAX_KEYS];
	uint8_t m_KeysPressed[MAX_KEYS];

private:
	std::chrono::high_resolution_clock::time_point m_StartTime;
	std::chrono::high_resolution_clock::time_point _LockFPSa = std::chrono::high_resolution_clock::now();
	std::chrono::high_resolution_clock::time_point _LockFPSb = std::chrono::high_resolution_clock::now();

	uint32_t m_FPS;
	
	int m_Height;
	int m_Width;
	std::string m_Title;

	GLFWwindow* m_Window;

public:
	Window(int width, int height, std::string title);

	void LockFPS(float fps);

	static void setSize(GLFWwindow* window, int width, int height);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int actions, int mods);

	void setTitle(const std::string& title) const 
	{
		glfwSetWindowTitle(this->m_Window, title.c_str());
	}

	int getHeight()				const { return m_Height; }
	int getWidth()				const { return m_Width; }
	std::string getTitle()		const { return m_Title; }

	bool IsKeyPressed(uint8_t keycode)
	{
		if (this->m_KeysPressed[keycode] == 1)
		{
			// unset the key
			this->m_KeysPressed[keycode] = 0;
			return true;
		}

		return false;
	}

	bool IsKeyDown(uint8_t keycode)
	{
		return this->m_KeysDown[keycode] == 1;
	}
	
	bool IsKeyReleased(uint8_t keycode)
	{
		return this->m_KeysDown[keycode] == 0;
	}

	void update();

	bool shouldClose() const
	{
		return glfwWindowShouldClose(m_Window);
	}

	~Window();
};