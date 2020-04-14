#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <Windows.h>
//#include <GL/freeglut.h>
#include <iostream>

#include <math.h>

using namespace std;

int slices = 32;
int stacks = 32;

GLdouble scale = 1.0f;
GLdouble orbitDistance = 1.0f;

GLdouble PI = 3.14f;
GLdouble alpha = -PI / 2.0;
GLdouble jumpPoint = 1.0f;
GLdouble jumpEye = 1.0f;

GLdouble eyeX = 0;
GLdouble eyeY = 0;
GLdouble eyeZ = 20;

GLdouble pointX = jumpPoint * cos(alpha);
GLdouble pointY = 0.0f;
GLdouble pointZ = jumpPoint * sin(alpha);

void ChangeViewPort(int width, int height)
{
	const float aspectRatio = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0, 2.0, 400.0);
}

void Render()
{
	const double time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	const double angle = time * 60.0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// The Sun
	glPushMatrix();
		gluLookAt(eyeX, eyeY, eyeZ, pointX, pointY, pointZ, 0.0, 1.0, 0.0);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		glColor3d(0.98, 0.73, 0.05);
		glTranslated(0, 0, -20);
		glRotated(angle * 0.3, 0, 0, 1);
		glutSolidSphere(3.0 * scale, slices, stacks);

		// The Earth
		glColor3d(0.05, 0.3, 0.97);
		glTranslated(8 * orbitDistance * cos(time) * 1.5, 8 * orbitDistance * sin(time), 0);
		glRotated(angle, 0, 0, 1);
		glutSolidSphere(0.3 * scale, slices, stacks);
			
			// The Moon
			glColor3d(0.5, 0.5, 0.5);
			glTranslated(1 * orbitDistance * cos(time), 1 * orbitDistance * sin(time), 0);
			glRotated(time, 0, 0, 1);
			glutSolidSphere(0.1 * scale, slices, stacks);

		glLoadIdentity();
		glTranslated(0, 0, -20);

	// Jupiter
		glColor3d(0.7, 0.4, 0.08);
		glTranslated(14 * orbitDistance * cos(time/3) * 2.0, 14 * orbitDistance * sin(time / 3), 0);
		glRotated(angle * 0.5, 0, 0, 1);
		glutSolidSphere(0.7 * scale, slices, stacks);
			
			// First moon
			glColor3d(0.5, 0.5, 0.5);
			glTranslated(1.5 * orbitDistance * cos(time), 1.5 * orbitDistance * sin(time), 0);
			glRotated(time, 1, 0, 0);
			glutSolidSphere(0.2 * scale, slices, stacks);

			// Second moon
			glColor3d(0.5, 0.5, 0.5);
			glTranslated(2 * orbitDistance * cos(time / 2), 2 * orbitDistance * sin(time / 2), 0);
			glRotated(time, 1, 0, 0);
			glutSolidSphere(0.1 * scale, slices, stacks);
		
		glLoadIdentity();
		glTranslated(0, 0, -20);

		// Saturn
		glColor3d(0.7, 0.6, 0.4);
		glTranslated(22 * orbitDistance * cos(time / 5) * 1.5, 22 * orbitDistance * sin(time / 5), 0);
		glRotated(angle * 0.4, 0, 0, 1);
		glutSolidSphere(0.45 * scale, slices, stacks);

		glPushMatrix();
			glColor3d(0.7, 0.7, 0.7);
			glScalef(1, 1, 0.1);
			glutSolidTorus(0.15 * scale, 1.0 * scale, slices, stacks);
			glColor3d(0.6, 0.6, 0.6);
			glutSolidTorus(0.05 * scale, 1.30 * scale, slices, stacks);
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
	cout << " Change scale: [s]/[l]\n";
	cout << " Change orbit distance: [n]/[f]\n";
	cout << " Restore values: [r]\n";
	cout << " Exit: [e]\n\n";

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
			if (orbitDistance >= 1.0)
				orbitDistance -= 0.1;
			if (orbitDistance < 1.0)
				orbitDistance = 1.0;
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
			orbitDistance = 1.0;
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
	
	glutReshapeFunc(ChangeViewPort);
	glutDisplayFunc(Render);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Key);
	glutSpecialFunc(SpecialKey);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0, 0, 0, 0);

	Menu();

	glutMainLoop();
	return 0;
}