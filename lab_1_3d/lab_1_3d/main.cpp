/* Deplasarea observatorului intr-o scena 3D
SURSA:  lighthouse3D:  http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
Elemente de retinut:
- folosirea functiilor de desenare pentru a schita obiecte 3D
- schimbarea pozitiei observatorului se face in functia gluLookAt
- folosirea glutSpecialFunc si glutKeyboardFunc pentru interactiunea cu tastatura
*/

#include <iostream>
using namespace std;
#include<gl/freeglut.h>
#include<math.h>
// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;

int weather = 2;
int night = 1;

void callback_Main(int key)
{
	if (key == 0)
	{
		exit(0);
	}
}

void change_weather(int key) {
	if (key == 1) {
		weather = 1;
	}
	else {
		weather = 2;
	}
}

void change_night_day(int key) {
	if (key == 1) {
		night = 0;
		glClearColor(0.7, 0.7, 1, 1);
		glutPostRedisplay();
	}
	else {
		night = 1;
		glClearColor(0, 0, 0.01, 1);
		glutPostRedisplay();
	}
}

void changeSize(int w, int h)
{
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void drawSnowMan()
{
	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}

void drawTree() {
	// draw trunk
	glPushMatrix();
	glColor3f(0.2, 0.05, 0);
	glRotated(-90, 1, 0, 0);
	glutSolidCylinder(0.2, 2, 10, 10);
	glPopMatrix();

	glColor3f(0.05f, 0.6f, 0);
	glPushMatrix();
	glTranslated(-0.5, 2, 0);
	glutSolidSphere(0.7, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2, -0.5);
	glutSolidSphere(0.7, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.5, 2, 0);
	glutSolidSphere(0.7, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2, 0.5);
	glutSolidSphere(0.7, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 2.5, 0);
	glutSolidSphere(0.7, 10, 10);
	glPopMatrix();
}

void renderScene(void)
{
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 1.0f, z,
		x + lx, 1.0f, z + lz,
		0.0f, 1.0f, 0.0f);

	// Draw ground
	if (weather == 1) {
		glColor3f(0.8, 0.8, 0.8);
	}
	else {
		glColor3f(0, 0.7, 0);

	}
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	// Draw 36 SnowMen
	for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++)
		{
			glPushMatrix();
			glTranslatef(i * 10.0, 0, j * 10.0);
			if (weather == 1) {
				drawSnowMan();
			}
			else {
				drawTree();
			}
			
			glPopMatrix();
		}
	glPushMatrix();
	glPopMatrix();
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'l':
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	}
	if (key == 27)
		exit(0);
}

void processSpecialKeys(int key, int xx, int yy) {

	float fraction = 0.1f;

	switch (key)
	{
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}

void process_keys(unsigned char key, int x, int y) {
	float fraction = 0.1f;

	switch (key)
	{
	case 'a':
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case 'd':
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case 'w':
		x += lx * fraction;
		z += lz * fraction;
		break;
	case 's':
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	case 'l':
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	}
	if (key == 27)
		exit(0);
}

int main(int argc, char** argv)
{
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Scena 3D cu oameni de zapada");

	glClearColor(0.7, 0.7, 1, 1);

	int main_menu, weather_selection, night_day;

	weather_selection = glutCreateMenu(change_weather);
	glutAddMenuEntry("winter", 1);
	glutAddMenuEntry("spring", 2);

	night_day = glutCreateMenu(change_night_day);
	glutAddMenuEntry("day", 1);
	glutAddMenuEntry("night", 2);

	main_menu = glutCreateMenu(callback_Main);

	glutAddSubMenu("Iarna/Primavara ", weather_selection);
	glutAddSubMenu("Zi/Noapte", night_day);
	glutAddMenuEntry("Iesire ", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutKeyboardFunc(process_keys);
	glutSpecialFunc(processSpecialKeys);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

