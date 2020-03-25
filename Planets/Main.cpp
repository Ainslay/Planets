#include <Windows.h>
#include <GL\freeglut.h>
#include <iostream>

#include <math.h>

using namespace std;

int slices = 32;
int stacks = 32;

GLdouble scale = 1.0f;
GLdouble orbitDistance = 0.0f;

GLfloat PI = 3.14f;
GLfloat alpha = -PI / 2.0;
GLfloat jumpPoint = 1.0f;
GLfloat jumpEye = 1.0f;

GLfloat eyeX = 0;
GLfloat eyeY = 0;
GLfloat eyeZ = 0;

GLfloat pointX = jumpPoint * cos(alpha);
GLfloat pointY = 0.0f;
GLfloat pointZ = jumpPoint * sin(alpha);

void ChangeViewPort(int width, int height)
{
	const float aspectRatio = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-aspectRatio, aspectRatio, -1.0, 1.0, 2.0, 100.0);
}

void Render()
{
	const double time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	const double angle = time * 60.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	// The Sun
	glPushMatrix();
		gluLookAt(eyeX, eyeY, eyeZ, pointX, pointY, pointZ, 0.0, 1.0, 0.0);

		glColor3d(0.98, 0.73, 0.05);
		glTranslated(0, 0, -20);
		glRotated(angle, 0, 1, 0);
		glutSolidSphere(1.5 * scale, slices, stacks);
		// The Earth
		glPushMatrix();
			glColor3d(0.05, 0.3, 0.97);
			glTranslated(0, 0, 4 + orbitDistance);
			glRotated(23.44, 1, 0, 0);
			glutSolidSphere(0.3 * scale , slices, stacks);
			
			// The Moon
			glPushMatrix();
				glColor3d(0.5, 0.5, 0.5);
				glTranslated(0, 0, 0.5 * scale);
				glRotated(0, 1, 0, 0);
				glutSolidSphere(0.1 * scale, slices, stacks);
			glPopMatrix();

		glPopMatrix();

		// Jupiter
		glPushMatrix();
			glColor3d(0.7, 0.4, 0.08);
			glTranslated(0, 0, 8 + orbitDistance);
			glRotated(6.09, 1, 0, 0);
			glutSolidSphere(0.7 * scale, slices, stacks);
			
			glPushMatrix();
				glColor3d(0.5, 0.5, 0.5);
				glTranslated(0, 0.5, 1.2 * scale);
				glRotated(0, 1, 0, 0);
				glutSolidSphere(0.2 * scale, slices, stacks);
			glPopMatrix();

			glPushMatrix();
				glColor3d(0.5, 0.5, 0.5);
				glTranslated(0, -0.5, -0.7 * scale);
				glRotated(0, 1, 0, 0);
				glutSolidSphere(0.1 * scale, slices, stacks);
			glPopMatrix();
		
		glPopMatrix();

		// Saturn
		glPushMatrix();
			glColor3d(0.7, 0.6, 0.4);
			glTranslated(0, 0, 12 + orbitDistance);
			glRotated(63, 1, 0, 0);
			glutSolidSphere(0.45 * scale, slices, stacks);

			glPushMatrix();
				glColor3d(0.7, 0.7, 0.7);
				glScalef(1, 1, 0.1);
				glutSolidTorus(0.15 * scale, 1.0 * scale, slices, stacks);
				glColor3d(0.6, 0.6, 0.6);
				glutSolidTorus(0.05 * scale, 1.30 * scale, slices, stacks);
			glPopMatrix();

		glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();
}

void Menu()
{
	system("cls");
	cout << " ---=== Controls ===---\n";
	cout << " Ruch kamery: klawisze strzalek\n";
	cout << " Change detail: [-]/[+]\n";
	cout << " Change scale: [S]/[L]\n";
	cout << " Change orbit distance: [N]/[F]\n";
	cout << " Restore values: [R]\n";
	cout << " Exit: [E]\n\n";

	cout << " Scale: " << scale << endl;
	cout << " Orbit distance: " << orbitDistance << endl;
	cout << " Detail: " << slices << endl;
}

void Key(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '-':
		{
			if (slices > 3 && stacks > 3)
			{
				slices--;
				stacks--;
			}
		} break;
		case '+':
		{
			if (slices < 100 && stacks < 100)
			{
				slices++;
				stacks++;
			}
		} break;
		case 's':
		{
			if (scale >= 0.1)
				scale -= 0.1;
			if (scale < 0.1)
				scale = 0.1;
		} break;
		case 'l':
		{
			if (scale <= 4.0)
				scale += 0.1;
			if (scale > 4.0)
				scale = 4.0;
		} break;
		case 'n':
		{
			if (orbitDistance >= -3.0)
				orbitDistance -= 0.1;
			if (orbitDistance < -3.0)
				orbitDistance = -3.0;
		} break;
		case 'f':
		{
			if (orbitDistance <= 7.0)
				orbitDistance += 0.1;
			if (orbitDistance > 7.0)
				orbitDistance = 7.0;
		} break;
		case 'r':
		{
			scale = 1.0;
			orbitDistance = 0.0;
			stacks = 32;
			slices = 32;
		} break;
		case 'e':
		{
			cout << "\n ---=== Zakonczono prace z programem ===---\n";
			exit(0);
		}
	default:
		break;
	}

	Menu();
}

void SpecialKey(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_LEFT:
		{
			alpha -= PI / 32;
			pointX = jumpPoint * cos(alpha) + eyeX;
			pointZ = jumpPoint * sin(alpha) + eyeZ;
		} break;
		
		
		case GLUT_KEY_RIGHT:
		{
			alpha += PI / 32;
			pointX = jumpPoint * cos(alpha) + eyeX;
			pointZ = jumpPoint * sin(alpha) + eyeZ;
		} break;
		
		case GLUT_KEY_UP:
		{
			jumpEye += 10.0f;
			eyeX = jumpEye * cos(alpha) + eyeX;
			eyeZ = jumpEye * sin(alpha) + eyeZ;
			pointX = jumpPoint * cos(alpha) + eyeX;
			pointZ = jumpPoint * sin(alpha) + eyeZ;
			jumpEye = 0.0f;
		} break;
			 		case GLUT_KEY_DOWN:
		{
			jumpEye -= 10.0f;
			eyeX = jumpEye * cos(alpha) + eyeX;
			eyeZ = jumpEye * sin(alpha) + eyeZ;
			pointX = jumpPoint * cos(alpha) + eyeX;
			pointZ = jumpPoint * sin(alpha) + eyeZ;
			jumpEye = 0.0f;
		} break;
	}
	ChangeViewPort(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void Idle()
{
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(300, 150);

	glutCreateWindow("Planets assigment - Jakub Spalek Lab1 Gr1 INF II");
	//glEnable()
	glutReshapeFunc(ChangeViewPort);
	glutDisplayFunc(Render);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0, 0, 0, 0);

	Menu();

	glutMainLoop();
	return 0;
}