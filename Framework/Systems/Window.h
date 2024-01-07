#pragma once

class Scene;

class Window
{
private:
	Window() = default;
	~Window() = default;

public:
	static WPARAM Run(Scene* main);

private:
	static void Create();
	static void Destroy();

	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	static void MainRender();

private:
	static class Scene* MainScene;
};

