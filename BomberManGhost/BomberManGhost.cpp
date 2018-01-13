// cubo3D.cpp: define el punto de entrada de la aplicación de consola.
#include "stdafx.h"
#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>

#include <assert.h>
#include <fstream>
#include "ImageLoader.h"

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

/* ==============TEXTURE VALUES=============================================================== */
#define M_PI 3.14159265358979323846

GLuint _text1;
GLuint _text2;

GLuint _text4;
GLuint _text5;
GLuint _text6;

GLuint loadTexture(Image* image) {
	GLuint idtextura;
	glGenTextures(1, &idtextura);
	glBindTexture(GL_TEXTURE_2D, idtextura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
	return idtextura;
}
void initRendering() {
	Image* lado1 = loadBMP("1.bmp");
	_text1 = loadTexture(lado1);
	delete lado1;

	Image* lado2 = loadBMP("2.bmp");
	_text2 = loadTexture(lado2);
	delete lado2;


	Image* lado4 = loadBMP("4.bmp");
	_text4 = loadTexture(lado4);
	delete lado4;

	Image* lado5 = loadBMP("5.bmp");
	_text5 = loadTexture(lado5);
	delete lado5;

	Image* lado6 = loadBMP("6.bmp");
	_text6 = loadTexture(lado6);
	delete lado6;
}
void cargarTextura(GLuint _textura) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
/* ============================================================================= */
void dibujarPlano() {
	cargarTextura(_text1);
	glBegin(GL_QUADS);
	glTexCoord2f(pA[0], pA[1]); glVertex3f(pA[0], pA[1],0);
	glTexCoord2f(7,7); glVertex3f(7, 7,0);
	glTexCoord2f(7,-7); glVertex3f(7, -7,0);
	glTexCoord2f(-7,-7); glVertex3f(-7, -7,0);
	glEnd();
}
void dibujarBordes() {
	cargarTextura(_text2);
	//Borde arriba
	glBegin(GL_QUADS);
	glTexCoord2f(-7,7); glVertex3f(-7, 7,0);
	glTexCoord2f(7,7); glVertex3f(7, 7,0);
	glTexCoord2f(7,6); glVertex3f(7, 6,0);
	glTexCoord2f(-7,6); glVertex3f(-7, 6,0);
	glEnd();
	
	cargarTextura(_text2);
	//Borde abajo
	glBegin(GL_QUADS);	
	glTexCoord2f(7,-7); glVertex3f(7, -7, 0);//A
	glTexCoord2f(-7,-7); glVertex3f(-7, -7, 0);//B
	glTexCoord2f(-7,-6); glVertex3f(-7, -6, 0);//C
	glTexCoord2f(7,-6); glVertex3f(7, -6, 0);//C
	glEnd();
	
	cargarTextura(_text2);
	//Borde izquierda
	glBegin(GL_QUADS);	
	glTexCoord2f(-7,6); glVertex3f(-7, 6, 0);//A
	glTexCoord2f(-6,6); glVertex3f(-6, 6, 0);//B
	glTexCoord2f(-6,-6); glVertex3f(-6, -6, 0);//A
	glTexCoord2f(-7,-6); glVertex3f(-7, -6, 0);//B
	glEnd();
	
	cargarTextura(_text2);
	//Borde derecha
	glBegin(GL_QUADS);
	glTexCoord2f(7,-6); glVertex3f(7, -6, 0);//A
	glTexCoord2f(6,-6); glVertex3f(6, -6, 0);//B
	glTexCoord2f(6,6); glVertex3f(6, 6, 0);//A
	glTexCoord2f(7,6); glVertex3f(7, 6, 0);//B
	glEnd();
}
void dibujar(int x,int y){
	glTexCoord2f(x,y); glVertex2f(x, y);
}
void dibujarCajas() {
	cargarTextura(_text1);
	glBegin(GL_QUADS);
	dibujar(-5, 5);
	dibujar(-4, 5);
	dibujar(-4, 2);
	dibujar(-5, 2);
	glEnd();
	//
	cargarTextura(_text1);
	glBegin(GL_QUADS);
	dibujar(-3, 5);//B
	dibujar(-1, 5);//B
	dibujar(-1, 2);//B
	dibujar(-3, 2);//B
	glEnd();
	//
	glBegin(GL_QUADS);
	//glColor3f(10, 0, 0);
	dibujar(1, 5);//B
	dibujar(3, 5);//B
	dibujar(3, 2);//B
	dibujar(1, 2);//B
	glEnd();
	//
	glBegin(GL_QUADS);
	//glColor3f(10, 0, 0);
	dibujar(5, 5);//A
	dibujar(4, 5);//B
	dibujar(4, 2);//C
	dibujar(5, 2);//d
	glEnd();
	//-------------------------------------
	//--En medio
	glBegin(GL_QUADS);
	//glColor3f(10, 0, 0);
	dibujar(-5, 1);//A
	dibujar(-4, 1);//B
	dibujar(-4, -1);//B
	dibujar(-5, -1);//A	
	glEnd();
	glBegin(GL_QUADS);
	//glColor3f(10, 0, 0);
	dibujar(-3, 1);//A
	dibujar(-1, 1);//B
	dibujar(-1, -1);//B
	dibujar(-3, -1);//A	
	glEnd();
	//-------------------------------------------
	//En medio Positivo
	glBegin(GL_QUADS);
	//glColor3f(10, 0, 0);
	dibujar(5, 1);//A
	dibujar(4, 1);//B
	dibujar(4, -1);//B
	dibujar(5, -1);//A	
	glEnd();
	glBegin(GL_QUADS);
	dibujar(3, 1);//A
	dibujar(1, 1);//B
	dibujar(1, -1);//B
	dibujar(3, -1);//A	
	glEnd();
	//-------------------------------------------
	//Abajo
	glBegin(GL_QUADS);
	dibujar(-5, -5);//A
	dibujar(-4, -5);//B
	dibujar(-4, -2);//C
	dibujar(-5, -2);//d
	glEnd();
	//
	glBegin(GL_QUADS);
	dibujar(-3, -5);//B
	dibujar(-1, -5);//B
	dibujar(-1, -2);//B
	dibujar(-3, -2);//B
	glEnd();
	//
	glBegin(GL_QUADS);
	dibujar(1, -5);//B
	dibujar(3, -5);//B
	dibujar(3, -2);//B
	dibujar(1, -2);//B
	glEnd();
	glBegin(GL_QUADS);
	dibujar(5, -5);//A
	dibujar(4, -5);//B
	dibujar(4, -2);//C
	dibujar(5, -2);//d
	glEnd();
}
void dibujarEnemigo() {
	cargarTextura(_text5);
	glBegin(GL_QUADS);	
	dibujar(enemigoA[0], enemigoA[1]);//A
	dibujar(enemigoB[0], enemigoB[1]);//A
	dibujar(enemigoC[0], enemigoC[1]);//A
	dibujar(enemigoD[0], enemigoD[1]);//A
	glEnd();
}
void eliminarRastroEnemigo() {
	glBegin(GL_QUADS);
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
		cargarTextura(_text4);
		glBegin(GL_QUADS);
		glTexCoord2f(bombaA[0], bombaA[1]); glVertex3f(bombaA[0], bombaA[1],0);//A
		glTexCoord2f(bombaB[0], bombaB[1]); glVertex3f(bombaB[0], bombaB[1],0);//A
		glTexCoord2f(bombaC[0], bombaC[1]); glVertex3f(bombaC[0], bombaC[1],0);//A
		glTexCoord2f(bombaD[0], bombaD[1]); glVertex3f(bombaD[0], bombaD[1],0);//A		
		glEnd();
	}
}
void dibujarBomber() {
	cargarTextura(_text6);
	glBegin(GL_QUADS);
	dibujar(bomberA[0], bomberA[1]);//A
	dibujar(bomberB[0], bomberB[1]);//A
	dibujar(bomberC[0], bomberC[1]);//A
	dibujar(bomberD[0], bomberD[1]);//A
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
	//dibujarPlano();
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	glPushMatrix();
	cargarEscenario();	
	dibujarBomba();
	/*2D*/
	gluLookAt(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f
	);
	glPopMatrix();
	glFlush();
	glutSwapBuffers();

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
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Texturas En 3D");
	glutSetCursor(GLUT_CURSOR_NONE);
	//glutFullScreen();
	initRendering();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);
	glutSpecialFunc(ArrowKey);
	glEnable(GL_DEPTH_TEST);
	//glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}