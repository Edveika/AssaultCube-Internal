#include "../../Includes.h"

// Opengl stuff that takes care of the 2D drawing using orthographic matrix, because game is runnin in 3D
void GL::SetupOrtho()
{
	glPushAttrib(GL_ALL_ATTRIB_BITS); // Get into orthographic state
	glPushMatrix(); // push matrix on the matrix stack
	GLint viewport[4]; // 4 ints x y pos of viewport and width & height of windw
	glGetIntegerv(GL_VIEWPORT, viewport); // Get viewport & store it in viewport
	glViewport(0, 0, viewport[2], viewport[3]); // Set viewport. x = 0 and y = 0 because thats how all games r setup. viewport 2 is width viewport 3 is height
	glMatrixMode(GL_PROJECTION); // Set matrix mode into projection mode
	glLoadIdentity(); // Loads blank view matrix
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1); // Creates ortho projection matrix(for 2D). left = 2, viwport 2 = width(far right), viewport 3 = y(height), top = 0, near = -1, far = 1. Frustrum definition.
	glMatrixMode(GL_MODELVIEW); // Set viewmatrix to model view, cus we about to draw onto screen
	glLoadIdentity(); // Blank matrix
	glDisable(GL_DEPTH_TEST); // So everything we draw is on the top layer
}

void GL::RestoreGL()
{
	glPopMatrix();
	glPopAttrib();
}

// Immediate mode of drawing
void GL::DrawFilledRect(float x, float y, float width, float height, const GLubyte color[3])
{
	// When you use GL_QUADS it knows to connect the last line back to first(bottom left to top left)
	// glBegin and End shows that this is emmediate mode.
	// 2f means its taking 2 varaibles & its floats
	// 3ub means 3 unsignes bytes

	glColor3ub(color[0], color[1], color[2]);
	glBegin(GL_QUADS); // Rectangle
	glVertex2f(x, y); // top left
	glVertex2f(x + width, y); // top right
	glVertex2f(x + width, y + height); // bottom right
	glVertex2f(x, y + height); // bottom left
	glEnd();
}

void GL::DrawOutline(float x, float y, float width, float height, float lineWidth, const GLubyte color[3])
{
	// glBegin and End shows that this is emmediate mode.
	// 2f means its taking 2 varaibles & its floats
	// 3ub means 3 unsignes bytes

	glLineWidth(lineWidth); // Line width
	glBegin(GL_LINE_STRIP); // Line. Everything (all vertecies) between glBegin and End will be connected w a line
	glColor3ub(color[0], color[1], color[2]);
	glVertex2f(x - 0.5f, y - 0.5f);
	glVertex2f(x + width + 0.5f, y - 0.5f); 
	glVertex2f(x + width + 0.5f, y + height + 0.5f); 
	glVertex2f(x - 0.5f, y + height + 0.5f); 
	glVertex2f(x - 0.5f, y - 0.5f); 
	glEnd();
}