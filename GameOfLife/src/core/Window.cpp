#include "Window.h"

Window::Window(int width, int height, std::string title) : 
	m_Width(width),
	m_Height(height),
	m_Title(title),
	m_Window(nullptr),
	m_StartTime(std::chrono::high_resolution_clock::now()),
	m_FPS(0)
{
	if (!glfwInit())
	{
		LOG_ERROR("Failed to initialize the required dependencies.");
		return;
	}

	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

	if (!m_Window)
	{
		LOG_ERROR("Failed to create window.");
		return;
	}

	memset(this->m_KeysPressed, 0, MAX_KEYS);
	memset(this->m_KeysDown, 0, MAX_KEYS);

	// Set the window user pointer to this for easier retreival from other functions
	glfwSetWindowUserPointer(m_Window, this);

	// Set the glfw Event Handlers
	glfwSetFramebufferSizeCallback(m_Window, &Window::setSize);
	glfwSetKeyCallback(m_Window, &Window::keyCallback);

	// Center the window on the screen
	const GLFWvidmode *videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwSetWindowPos(m_Window, videoMode->width / 2 - width / 2, videoMode->height / 2 - height / 2);

	// Initialize the opengl context
	glfwMakeContextCurrent(m_Window);

	if (glewInit() != GLEW_OK)
	{
		LOG_ERROR("Failed to initialize GLEW");
		return;
	}

	// Set the opengl viewport
	glViewport(0, 0, width, height);
}

void Window::update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();

	// FPS Counter
	auto current = std::chrono::high_resolution_clock::now();
	if (std::chrono::duration_cast<std::chrono::seconds>(current - m_StartTime).count() >= 1)
	{
		this->setTitle(this->m_Title + " (FPS: " + std::to_string(this->m_FPS) + ")");
		m_StartTime = current;
		m_FPS = 0;
	}

	m_FPS++;
}

void Window::setSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Window::LockFPS(float fps)
{
	_LockFPSa = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> work_time = _LockFPSa - _LockFPSb;

	if (work_time.count() < fps)
	{
		std::chrono::duration<double, std::milli> delta_ms(fps - work_time.count());
		auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
		std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
	}

	_LockFPSb = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> sleep_time = _LockFPSb - _LockFPSa;
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* windowClass = (Window*)glfwGetWindowUserPointer(window);

	if (action == GLFW_PRESS)
	{
#ifdef INPUT_DEBUG
		std::cout << glfwGetKeyName(key, scancode) << " was pressed." << std::endl;
#endif
		windowClass->m_KeysPressed[key] = 1;
		windowClass->m_KeysDown[key] = 1;
	}
	else if (action == GLFW_RELEASE)
	{
#ifdef INPUT_DEBUG
		std::cout << glfwGetKeyName(key, scancode) << " was released." << std::endl;
#endif
		// Release both key states
		windowClass->m_KeysDown[key] = 0;
		windowClass->m_KeysPressed[key] = 0;
	}
	else if(action == GLFW_REPEAT)
	{
#ifdef INPUT_DEBUG
		std::cout << glfwGetKeyName(key, scancode) << " was repeatedly pressed." << std::endl;
#endif
		// If the key is pressed, unset it
		if (windowClass->m_KeysPressed[key])
		{
			//windowClass->m_KeysPressed[key] = 0;
		}

		windowClass->m_KeysPressed[key] = 1;
		windowClass->m_KeysDown[key] = 1;
	}
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
	m_Window = nullptr;
}