#pragma once
#pragma comment(lib, "OpenGL32.lib")
#include <Windows.h>
#include <stdio.h>
#include <gl\GL.h>

namespace Colors
{
	const GLubyte red[3] = { 255, 0, 0 };
	const GLubyte green[3] = { 108, 255, 92 };
	const GLubyte blue[3] = { 48, 152, 255 };
	const GLubyte gray[3] = { 40, 40, 40 };
	const GLubyte darkGray[3] = { 30, 30, 30 };
	const GLubyte black[3] = { 0, 0, 0 };
	const GLubyte white[3] = { 255, 255, 255 };
}

namespace GL
{
	void SetupOrtho();
	void RestoreGL();

	void DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3]);
	void DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3]);
}