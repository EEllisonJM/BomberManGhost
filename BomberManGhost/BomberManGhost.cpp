// cubo3D.cpp: define el punto de entrada de la aplicación de consola.
#include "stdafx.h"
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
using namespace std;

int bomberVidas = 3;
bool enemigoVive = true;
bool bomberVive = true;

float pA[] = { -7,7 };

bool bomba = false;
bool bombaActiva = false;
int tiempo = 0;

int bomberA[] = { -6,6 };
int bomberB[] = { -5,6 };
int bomberC[] = { -5,5 };
int bomberD[] = { -6,5 };

int enemigoA[] = { 3,-5 };
int enemigoB[] = { 4,-5 };
int enemigoC[] = { 4,-6 };
int enemigoD[] = { 3,-6 };

int bombaA[] = { -6,6 };
int bombaB[] = { -5,6 };
int bombaC[] = { -5,5 };
int bombaD[] = { -6,5 };

int bombaEnemigoA[] = { -6,6 };
int bombaEnemigoB[] = { -5,6 };
int bombaEnemigoC[] = { -5,5 };
int bombaEnemigoD[] = { -6,5 };

void dibujarPlano() {
	glBegin(GL_QUADS);
	glColor3f(0, 10, 0);
	glVertex2f(pA[0], pA[1]);//A
	glVertex2f(7, 7);//B
	glVertex2f(7, -7);//C
	glVertex2f(-7, -7);//D	
	glEnd();
}
void dibujarBordes() {
	//Borde arriba
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex3f(-7, 7, 0);//A
	glVertex3f(7, 7, 0);//B
	glVertex3f(7, 6, 0);//C
	glVertex3f(-7, 6, 0);//C
	glEnd();
	//Borde abajo
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex3f(7, -7, 0);//A
	glVertex3f(-7, -7, 0);//B
	glVertex3f(-7, -6, 0);//C
	glVertex3f(7, -6, 0);//C
	glEnd();
	//Borde izquierda
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex3f(-7, 6, 0);//A
	glVertex3f(-6, 6, 0);//B

	glVertex3f(-6, -6, 0);//A
	glVertex3f(-7, -6, 0);//B
	glEnd();
	//Borde derecha
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex3f(7, -6, 0);//A
	glVertex3f(6, -6, 0);//B

	glVertex3f(6, 6, 0);//A
	glVertex3f(7, 6, 0);//B
	glEnd();
}
void dibujarCajas() {
	//Z
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(-5, 5);//A
	glVertex2f(-4, 5);//B
	glVertex2f(-4, 2);//C
	glVertex2f(-5, 2);//d
	glEnd();
	//
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(-3, 5);//B
	glVertex2f(-1, 5);//B
	glVertex2f(-1, 2);//B
	glVertex2f(-3, 2);//B
	glEnd();
	//
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(1, 5);//B
	glVertex2f(3, 5);//B
	glVertex2f(3, 2);//B
	glVertex2f(1, 2);//B
	glEnd();
	//
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(5, 5);//A
	glVertex2f(4, 5);//B
	glVertex2f(4, 2);//C
	glVertex2f(5, 2);//d
	glEnd();
	//-------------------------------------
	//--En medio
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(-5, 1);//A
	glVertex2f(-4, 1);//B
	glVertex2f(-4, -1);//B
	glVertex2f(-5, -1);//A	
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(-3, 1);//A
	glVertex2f(-1, 1);//B
	glVertex2f(-1, -1);//B
	glVertex2f(-3, -1);//A	
	glEnd();
	//-------------------------------------------
	//En medio Positivo
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(5, 1);//A
	glVertex2f(4, 1);//B
	glVertex2f(4, -1);//B
	glVertex2f(5, -1);//A	
	glEnd();
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(3, 1);//A
	glVertex2f(1, 1);//B
	glVertex2f(1, -1);//B
	glVertex2f(3, -1);//A	
	glEnd();
	//-------------------------------------------
	//Abajo
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(-5, -5);//A
	glVertex2f(-4, -5);//B
	glVertex2f(-4, -2);//C
	glVertex2f(-5, -2);//d
	glEnd();
	//
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(-3, -5);//B
	glVertex2f(-1, -5);//B
	glVertex2f(-1, -2);//B
	glVertex2f(-3, -2);//B
	glEnd();
	//
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(1, -5);//B
	glVertex2f(3, -5);//B
	glVertex2f(3, -2);//B
	glVertex2f(1, -2);//B
	glEnd();
	//
	glBegin(GL_QUADS);
	glColor3f(10, 0, 0);
	glVertex2f(5, -5);//A
	glVertex2f(4, -5);//B
	glVertex2f(4, -2);//C
	glVertex2f(5, -2);//d
	glEnd();
}
void dibujarEnemigo() {
	glBegin(GL_QUADS);
	glColor3f(0, 0, 10);
	glVertex2f(enemigoA[0], enemigoA[1]);//A
	glVertex2f(enemigoB[0], enemigoB[1]);//A
	glVertex2f(enemigoC[0], enemigoC[1]);//A
	glVertex2f(enemigoD[0], enemigoD[1]);//A
	glEnd();
}
void eliminarRastroEnemigo() {
	glBegin(GL_QUADS);
	glColor3f(0, 10, 0);
	glVertex2f(enemigoA[0], enemigoA[1]);//A
	glVertex2f(enemigoB[0], enemigoB[1]);//A
	glVertex2f(enemigoC[0], enemigoC[1]);//A
	glVertex2f(enemigoD[0], enemigoD[1]);//A
	glEnd();
}
void posicionBombaEnemigo() {
	bombaEnemigoA[0] = enemigoA[0];
	bombaEnemigoA[1] = enemigoA[1];

	bombaEnemigoB[0] = enemigoB[0];
	bombaEnemigoB[1] = enemigoB[1];

	bombaEnemigoC[0] = enemigoC[0];
	bombaEnemigoC[1] = enemigoC[1];

	bombaEnemigoD[0] = enemigoD[0];
	bombaEnemigoD[1] = enemigoD[1];
}
void traslacionEnemigo(int f0, int f1) {
	enemigoA[0] += f0;
	enemigoB[0] += f0;
	enemigoC[0] += f0;
	enemigoD[0] += f0;
	enemigoA[1] += f1;
	enemigoB[1] += f1;
	enemigoC[1] += f1;
	enemigoD[1] += f1;
}
void moverEnemigo() {
	int v1 = rand() % 4;         // v1 in the range 0 to 99
	if (v1 == 0) {//Derecha
		if ((enemigoA[1] == 2 || enemigoA[1] == 6 || enemigoA[1] == -1 || enemigoA[1] == -5) &&
			enemigoA[0] + 1 <= 5)
		{
			eliminarRastroEnemigo();
			traslacionEnemigo(1, 0);
			dibujarEnemigo();
		}if ((enemigoA[0] == -1) && (
			((enemigoA[1] >= 2 && enemigoA[1] <= 5) ||
			(enemigoA[1] >= -1 && enemigoA[1] <= 1) ||
				(enemigoA[1] >= -5 && enemigoA[1] <= -2))
			))
		{
			traslacionEnemigo(1, 0);
			dibujarEnemigo();
		}
	}
	if (v1 == 1) {//Izquierda		
		if ((enemigoA[1] == 2 || enemigoA[1] == 6 || enemigoA[1] == -1 || enemigoA[1] == -5) &&
			enemigoA[0] - 1 >= -6) {
			eliminarRastroEnemigo();
			traslacionEnemigo(-1, 0);
			dibujarEnemigo();
		}
	}
	if (v1 == 2) {//Arriba		
		if ((enemigoA[0] == -1 || enemigoA[0] == -4 || enemigoA[0] == -6 || enemigoA[0] == 0 ||
			enemigoA[0] == 3 || enemigoA[0] == 5) && enemigoA[1] + 1 <= 6)
		{
			eliminarRastroEnemigo();
			traslacionEnemigo(0, 1);
			dibujarEnemigo();
		}
	}
	if (v1 == 3) {//Abajo		
		if ((enemigoA[0] == -1 || enemigoA[0] == -4 || enemigoA[0] == -6 || enemigoA[0] == 0 ||
			enemigoA[0] == 3 || enemigoA[0] == 5) && enemigoA[1] - 1 >= -5)
		{
			eliminarRastroEnemigo();
			traslacionEnemigo(0, -1);
			dibujarEnemigo();
		}
	}
}
void posicionBomba() {
	bombaA[0] = bomberA[0];
	bombaA[1] = bomberA[1];

	bombaB[0] = bomberB[0];
	bombaB[1] = bomberB[1];

	bombaC[0] = bomberC[0];
	bombaC[1] = bomberC[1];

	bombaD[0] = bomberD[0];
	bombaD[1] = bomberD[1];
}
void dibujarBomba() {
	if (bomba == true)
	{
		//posicionBomba ya debe de estar asignada
		glBegin(GL_QUADS);
		glColor3f(5, 5, 10);//Parece ser blanco
		glVertex2f(bombaA[0], bombaA[1]);//A
		glVertex2f(bombaB[0], bombaB[1]);//A
		glVertex2f(bombaC[0], bombaC[1]);//A
		glVertex2f(bombaD[0], bombaD[1]);//A
		glEnd();
	}
}
void dibujarBomber() {
	glBegin(GL_QUADS);
	glColor3f(10, 5, 0);
	glVertex2f(bomberA[0], bomberA[1]);//A
	glVertex2f(bomberB[0], bomberB[1]);//A
	glVertex2f(bomberC[0], bomberC[1]);//A
	glVertex2f(bomberD[0], bomberD[1]);//A
	glEnd();
}
void traslacionBomber(int a0, int a1) {
	bomberA[0] += a0;
	bomberB[0] += a0;
	bomberC[0] += a0;
	bomberD[0] += a0;

	bomberA[1] += a1;
	bomberB[1] += a1;
	bomberC[1] += a1;
	bomberD[1] += a1;
}
void mover(char lado[]) {
	if (lado == "Arriba") {
		if ((bomberA[0] == -1 || bomberA[0] == -4 || bomberA[0] == -6 || bomberA[0] == 0 ||
			bomberA[0] == 3 || bomberA[0] == 5) && bomberA[1] + 1 <= 6)
		{
			traslacionBomber(0, 1);
			dibujarBomber();
		}
	}
	if (lado == "Abajo") {
		if ((bomberA[0] == -1 || bomberA[0] == -4 || bomberA[0] == -6 || bomberA[0] == 0 ||
			bomberA[0] == 3 || bomberA[0] == 5) && bomberA[1] - 1 >= -5)
		{
			traslacionBomber(0, -1);
			dibujarBomber();
		}
	}
	if (lado == "Derecha") {
		if ((bomberA[1] == 2 || bomberA[1] == 6 || bomberA[1] == -1 || bomberA[1] == -5) &&
			bomberA[0] + 1 <= 5)
		{
			traslacionBomber(1, 0);
			dibujarBomber();
		}if ((bomberA[0] == -1) && (
			((bomberA[1] >= 2 && bomberA[1] <= 5) ||
			(bomberA[1] >= -1 && bomberA[1] <= 1) ||
				(bomberA[1] >= -5 && bomberA[1] <= -2))
			))
		{
			traslacionBomber(1, 0);
			dibujarBomber();
		}
	}
	if (lado == "Izquierda") {
		if ((bomberA[1] == 2 || bomberA[1] == 6 || bomberA[1] == -1 || bomberA[1] == -5) &&
			bomberA[0] - 1 >= -6)
		{
			traslacionBomber(-1, 0);
			dibujarBomber();
		}if ((bomberA[0] == 0) &&
			((bomberA[1] >= 2 && bomberA[1] <= 5) ||
			(bomberA[1] >= -1 && bomberA[1] <= 1) ||
				(bomberA[1] >= -5 && bomberA[1] <= -2))
			)
		{
			traslacionBomber(-1, 0);
			dibujarBomber();
		}
	}
}
void cargarEscenario() {
	dibujarPlano();
	dibujarBordes();
	dibujarCajas();
	if (enemigoVive == true)
	{
		dibujarEnemigo();
	}
	if (bomberVive == true && bomberVidas >= 0)
	{
		dibujarBomber();
	}
	else {//Cerrar ventana al perder todas las vidas
		exit(0);
	}
	moverEnemigo();
}
void impactoBomba() {
	if ((bombaA[0] - 1 == bomberA[0]) ||//Izquierda
		(bombaA[0] + 1 == bomberA[0]) ||//Derecha
		(bombaA[1] + 1 == bomberA[1]) ||//Arriba
		(bombaA[1] - 1 == bomberA[1])) {//Abajo
		bomberVive == false;
		cout << "--------BOMBER IS DEAD--------------------";
		bomberVidas--;
	}
	if ((enemigoA[0] - 1 == enemigoA[0]) ||
		(enemigoA[0] + 1 == enemigoA[0]) ||
		(enemigoA[1] + 1 == enemigoA[1]) ||
		(enemigoA[1] - 1 == enemigoA[1])) {
		enemigoVive == false;
		cout << "--------GHOST IS DEAD--------------------";
	}
}
static void display(void) {
	cargarEscenario();
	dibujarBomba();
	glFlush();
	Sleep(120);
	tiempo += 1;
	if (tiempo == 30 && bomba == true)
	{
		bomba = false;
		tiempo = 0;
		bombaActiva = false;//No hay bomba, ya que PUM explotó!!!
		impactoBomba();
	}
	cout << tiempo << "-";
}

void reshape(int w, int h) {
	glViewport(0.0, 0.0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10, 10, -10, 10, 0, 20);
	glMatrixMode(GL_MODELVIEW);
}

void ArrowKey(int Key, int e, int y) {
	switch (Key) {
	case GLUT_KEY_PAGE_UP:
		break;
	case GLUT_KEY_PAGE_DOWN://Avanzar Página
		if (bombaActiva == false)
		{
			bomba = true;//Entonces -> dibujarBomba();
			posicionBomba();//La posicion en la que se dibujara la bomba
			bombaActiva = true;
			tiempo = 0;
		}
		break;
	case GLUT_KEY_HOME:
		break;
	case GLUT_KEY_END:
		break;
	case GLUT_KEY_DOWN:
		mover("Abajo");
		break;
	case GLUT_KEY_UP:
		mover("Arriba");
		break;
	case GLUT_KEY_RIGHT:
		mover("Derecha");
		break;
	case GLUT_KEY_LEFT:
		mover("Izquierda");
		break;
	case GLUT_KEY_F1:
		break;
	case GLUT_KEY_F2:
		break;
	case GLUT_KEY_F3:
		break;
	case GLUT_KEY_F4:
		break;
	case GLUT_KEY_F5:
		break;
	case GLUT_KEY_F6:
		break;
	case GLUT_KEY_F7:
		break;
	case GLUT_KEY_F8:
		break;
	case GLUT_KEY_F9:
		break;
	case GLUT_KEY_F10:
		break;
	case GLUT_KEY_F11:
		break;
	case GLUT_KEY_F12:
		break;
	}
	glutPostRedisplay();
}
void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(320, 37);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutCreateWindow("Polígonos");
	glutDisplayFunc(display);
	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
	/* glutIdleFunc sets the global idle callback to be func so a GLUT program can perform background
	processing tasks or continuous animation when window system events are not being received. If enabled,
	the idle callback is continuously called when events are not being received. The callback routine
	has no parameters. The current window and current menu will not be changed before the idle callback.
	Programs with multiple windows and/or menus should explicitly set the current window and/or current
	menu and not rely on its current setting.
	The amount of computation and rendering done in an idle callback should be minimized to avoid affecting
	the program's interactive response. In general, not more than a single frame of rendering should be
	done in an idle callback. */
	glutIdleFunc(display);
	/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*/
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(ArrowKey);

	glutMainLoop();

	return 0;
}

