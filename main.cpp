#include "CubeRubic.h"
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

#define CUBE_SIZE 13
#define TIMER 30
// обозначаем цвета:
//                    (верх,      низ,   впереди,   сзади,    лево,      право)
unsigned int c[9] = { 0xFFFFFF, 0xFFFF00, 0x0000FF, 0x00FF00, 0xFF0000, 	0xCD853F };

int povorot = 1;
// кубик-рубик
CubeRubic cuber = CubeRubic();
// флаг того, крутится куб сам, или нет (будет переключаться правой кнопкой мыши)
int timerOn = 0;
//массив для заамены граней кубика визуал на грани кубика другого
int dfr[] = { 4,2,1,6,5,3 };

void display()
{
	//std::cout << "+ ";
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, cuber.lightPos);
	glTranslatef(0, 0, cuber.translateZ);
	glRotatef(cuber.xRot, 1, 0, 0);
	glRotatef(cuber.yRot, 0, 1, 0);
	glTranslatef(CUBE_SIZE / -2.0, CUBE_SIZE / -2.0, CUBE_SIZE / -2.0);
	cuber.cube.draw();
	glPopMatrix();
	glutSwapBuffers();
}



void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat fAspect = (GLfloat)w / (GLfloat)h;
	gluPerspective(60, fAspect, 1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	// инициализируем случайные числа
	srand(time(0));

	// освещение
	float mat_specular[] = { 0.3, 0.3, 0.3, 0 };
	float diffuseLight[] = { 0.2, 0.2, 0.2, 1 };
	float ambientLight[] = { 0.9, 0.9, 0.9, 1.0 };
	glShadeModel(GL_SMOOTH);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	// инициализируем куб
	cuber.cube.clear(CUBE_SIZE, c);
	//cuber.InputFromFile(s);
}

void specialKeys(int key, int, int)
{
	// клавиши влево/вправо вращают по Y
	// клавиши вверх/вниз вращают по X
	// F1 - возвращает в начальное положение
	if (key == GLUT_KEY_DOWN)
	{
		cuber.xRot += 3;
		if (cuber.xRot >= 360)
			cuber.xRot -= 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_UP)
	{
		cuber.xRot -= 3;
		if (cuber.xRot < 0)
			cuber.xRot += 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_RIGHT)
	{
		cuber.yRot += 3;
		if (cuber.yRot >= 360)
			cuber.yRot -= 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_LEFT)
	{
		cuber.yRot -= 3;
		if (cuber.yRot < 0)
			cuber.yRot += 360;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_HOME)
	{
		cuber.translateZ += 5;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_END)
	{
		cuber.translateZ -= 5;
		glutPostRedisplay();
	}

	if (key == GLUT_KEY_F1)
	{
		cuber.cube.clear(CUBE_SIZE, c);
		glutPostRedisplay();
	}
}
void timer(int)
{
	glutTimerFunc(TIMER, timer, 0);
	if (timerOn)
	{
		// если включен автоматический поворот, и смотрим
		// если сейчас никакая грань не крутится, то начинаем крутить случайную,
		// иначе крутим текущую
		if (cuber.cube.current == -1)
			cuber.r90cl(rand() % 6 + 1);
		else {
			cuber.cube.Rotate(cuber.cube.current, povorot*3);
		}
	}
	else
	{
		if (cuber.cube.current != -1)
			cuber.cube.Rotate(cuber.cube.current, povorot * 3);
	}
	display();
}

void keys(unsigned char key, int, int)
{
	// если нажали клавишу от 0 до 5 - начинаем поворот на 3 градуса
	if (cuber.cube.current == -1 && key >= '1' && key <= '6')
	{
		if (povorot == 1) {
			cuber.r90count(key - '0');
		}
		else {
			cuber.r90cl(key - '0');
		}
		display();
		
	}
	else if (key == 's') {
		std::string s;
		std::cout << "Path to file = ";
		std::cin >> s;
		cuber.OutputToFile(s);
	}
	else if (key == 'l') {
		povorot = povorot * (-1);
	}
	else if (key == 'd') {
		cuber.OutputToConsole();
	}
	else if (key == 'f') {
		std::string s;
		std::cout << "Path to file = ";
		std::cin >> s;
		cuber.InputFromFile(s);
	}
	else if (key == 'g') {
		cuber.InputFromConsole();
	}
	else if (key == 'q') {
		cuber.solve();
	}
}

void mouse(int key, int state, int, int)
{
	if (key == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		// переключаем флаг
		timerOn = 1 - timerOn;
	}
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 700);
	glutInitWindowPosition(1, 1);
	glutCreateWindow("Cube");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	glutTimerFunc(TIMER, timer, 0);
	glutSpecialFunc(specialKeys);
	glutMainLoop();
	return 0;
}