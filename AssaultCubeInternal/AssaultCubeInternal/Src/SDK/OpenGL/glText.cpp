#include "../../Includes.h"

void GL::Font::Build(int height)
{
	hdc = wglGetCurrentDC(); // Get current device context & store it in handle to device context (hdc)
	base = glGenLists(96); // Generate gl list of size 96
	HFONT hFont = CreateFontA(-height, 0, 0, 0, FW_MEDIUM, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FF_DONTCARE | DEFAULT_PITCH, "Consolas"); // Create consolas monospace font 
	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont); // Select the current font & sotre it in old font in case we need to restore it later
	wglUseFontBitmaps(hdc, 32, 96, base); // 32 to 96 defines the beggining and the end of list of characters that we want in our font(numbers, letters, some characters)
	SelectObject(hdc, hOldFont); // Select old font & make it the main font for the HDC
	DeleteObject(hFont); // Delete our font

	// Everything we need is already in base

	bBuilt = true; // set bBuilt to true

	// Everytime HDC changes, we need to rebuild the font
}

void GL::Font::Print(float x, float y, const unsigned char color[3], const char* format, ...)
{
	glColor3ub(color[0], color[1], color[2]); // Set the color to the color we chose
	glRasterPos2f(x, y); // Set the position we chose. Raster means where you are going to start drawin

	char text[100]; // Char of 100 characters. Hardcoded text value. If the value is bigger, it will not work
	va_list args; // Variable argument list

	// This is like a loop
	va_start(args, format);
	vsprintf_s(text, 100, format, args); // For each string apply formating using vsprintf_s. Stores in text[100]
	va_end(args);

	glPushAttrib(GL_LIST_BIT); // Push GL_LIST_BIT on glTribute stack
	glListBase(base - 32); // Set list base to base - 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text); // Call gl call lists
	glPopAttrib(); // Pop GL_LIST_BIT off the glTribute stack
}

// Centers text on x and y axis
Vector3 GL::Font::CenterText(float x, float y, float width, float height, float textWidth, float textHeight)
{
	Vector3 text;
	text.x = x + (width - textWidth) / 2;
	text.y = y + textHeight;
	return text;
}

// Center only text x axis
float GL::Font::CenterText(float x, float width, float textWidth)
{
	if (width > textWidth)
		return (x + ((width - textWidth) / 2));
	else
		return (x - ((textWidth - width) / 2));
}