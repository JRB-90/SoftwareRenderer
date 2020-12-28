#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const double MOVE_AMT = 0.1;
const float FRAME_SIZE = 1.f;

double camX = 2.0;
double camY = 2.0;
double camZ = 2.0;

void MainLoop(int val);
void Render();
void HandleKeys(unsigned char key, int x, int y);
void PrintMat4(GLdouble* mat);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(2, 1);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("GLUT Test");

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)SCREEN_WIDTH / (double)SCREEN_HEIGHT, 0.1, 1000.0);

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
	//std::printf("%.3f\t\t%.3f\t\t%.3f\n", camX, camY, camZ);
	Render();
	glutTimerFunc(1000 / SCREEN_FPS, MainLoop, val);
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glLoadIdentity();
	gluLookAt(
		camX, camY, camZ,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0
	);
	glPushMatrix();

	GLdouble mat[16] = { 0 };
	glGetDoublev(GL_PROJECTION_MATRIX, mat);
	PrintMat4(mat);
	glGetDoublev(GL_MODELVIEW_MATRIX, mat);
	PrintMat4(mat);

	glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f); glVertex3f(0.f, 0.f, 0.f);
		glColor3f(1.f, 0.f, 0.f); glVertex3f(FRAME_SIZE, 0.f, 0.f);
		glColor3f(0.f, 1.f, 0.f); glVertex3f(0.f, 0.f, 0.f);
		glColor3f(0.f, 1.f, 0.f); glVertex3f(0.f, FRAME_SIZE, 0.f);
		glColor3f(0.f, 0.f, 1.f); glVertex3f(0.f, 0.f, 0.f);
		glColor3f(0.f, 0.f, 1.f); glVertex3f(0.f, 0.f, FRAME_SIZE);
	glEnd();

	glutSwapBuffers();
}

void HandleKeys(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		camZ += MOVE_AMT;
	}
	else if (key == 's')
	{
		camZ -= MOVE_AMT;
	}
	else if (key == 'd')
	{
		camX += MOVE_AMT;
	}
	else if (key == 'a')
	{
		camX -= MOVE_AMT;
	}
	else if (key == 'x')
	{
		camY += MOVE_AMT;
	}
	else if (key == 'z')
	{
		camY -= MOVE_AMT;
	}
}

void PrintMat4(GLdouble* mat)
{
	std::printf("%.3f\t%.3f\t%.3f\t%.3f\n", mat[0], mat[4], mat[8], mat[12]);
	std::printf("%.3f\t%.3f\t%.3f\t%.3f\n", mat[1], mat[5], mat[9], mat[13]);
	std::printf("%.3f\t%.3f\t%.3f\t%.3f\n", mat[2], mat[6], mat[10], mat[14]);
	std::printf("%.3f\t%.3f\t%.3f\t%.3f\n\n", mat[3], mat[7], mat[11], mat[15]);
}
