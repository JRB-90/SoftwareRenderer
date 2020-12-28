#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int COLOR_MODE_CYAN = 0;
const int COLOR_MODE_MULTI = 1;

int gColorMode = COLOR_MODE_CYAN;
GLfloat gProjectionScale = 1.f;

void MainLoop(int val);
void Render();
void HandleKeys(unsigned char key, int x, int y);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(2, 1);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("GLUT Test");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.f, 0.f, 0.f, 1.f);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		std::cerr << "Unable to initialize graphics library!" << std::endl;

		return 1;
	}

	glutKeyboardFunc(HandleKeys);
	glutDisplayFunc(Render);
	glutTimerFunc(1000 / SCREEN_FPS, MainLoop, 0);
	glutMainLoop();

	return 0;
}

void MainLoop(int val)
{
	Render();
	glutTimerFunc(1000 / SCREEN_FPS, MainLoop, val);
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 0.0f);

	if (gColorMode == COLOR_MODE_CYAN)
	{
		glBegin(GL_QUADS);
			glColor3f(0.f, 1.f, 1.f);
			glVertex2f(-50.f, -50.f);
			glVertex2f(50.f, -50.f);
			glVertex2f(50.f, 50.f);
			glVertex2f(-50.f, 50.f);
		glEnd();
	}
	else
	{
		glBegin(GL_QUADS);
			glColor3f(1.f, 0.f, 0.f); glVertex2f(-50.f, -50.f);
			glColor3f(1.f, 1.f, 0.f); glVertex2f(50.f, -50.f);
			glColor3f(0.f, 1.f, 0.f); glVertex2f(50.f, 50.f);
			glColor3f(0.f, 0.f, 1.f); glVertex2f(-50.f, 50.f);
		glEnd();
	}

	glutSwapBuffers();
}

void HandleKeys(unsigned char key, int x, int y)
{
	if (key == 'q')
	{
		if (gColorMode == COLOR_MODE_CYAN)
		{
			gColorMode = COLOR_MODE_MULTI;
		}
		else
		{
			gColorMode = COLOR_MODE_CYAN;
		}
	}
	else if (key == 'e')
	{
		if (gProjectionScale == 1.f)
		{
			gProjectionScale = 2.f;
		}
		else if (gProjectionScale == 2.f)
		{
			gProjectionScale = 0.5f;
		}
		else if (gProjectionScale == 0.5f)
		{
			gProjectionScale = 1.f;
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, SCREEN_WIDTH * gProjectionScale, SCREEN_HEIGHT * gProjectionScale, 0.0, 1.0, -1.0);
	}
}
