#include "GL\glew.h"
#include "GL\freeglut.h"
#include <iostream>
#include <ctype.h>
#include <ctime>
#include <math.h>
#include <sstream>
#include <string>

using namespace std;

//Jogadores
float movGol = 0, movDef = 0, movAta = 0;
float movGol2 = 0, movDef2 = 0, movAta2 = 0;
float posX[3] = { 0.75, 0, -0.75 };
float tamanho = 0.10;

//Bola
float movX = 0.0, movZ = 0.0;
float raio = 0.05;
float velocidadeBola = 0.075;
bool limiteX = true;
bool limiteZ = true;

//Gol
int golAzul = 0;
int golVermelho = 0;
bool gol = false;

GLfloat win;

void Starter()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void SetupRC(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void ChangeSize(GLsizei w, GLsizei h) {
	//Para prevenir uma divisão por zero
	if (h == 0)
		h = 1;
	//Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
	//Calcula o parâmetro "aspect" (w/h) utilizado na gluPerspective
	GLfloat aspect = w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Chama a função de projeção ortogonal, passando parâmetros
	//glOrtho(-1.0*70/60,1.0*70/60, -1.0,1.0, 0.1,100.0);
	//Chama a função de projeção perspectiva, passando parâmetros
	gluPerspective(50.0, aspect, 0.50, 7.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//Chama a câmera, passando parâmetros
	gluLookAt(4.0, 4.0, 0.0, 0.0, -0.5, 0.0, 0.0, 1.0, 0.0);
}

void DesenharJogadores() {
	//blue people

	//goleiro blue
	glPushMatrix();
	glTranslatef(0.0 + movGol, 0.1, 1.8);
	//glRotatef(ang[i], ay[i], 0, 0);
	//glRotatef(90.0, -1.0, 0.0, 0.0);
	glColor3f(0, 0, 1);
	glutSolidCube(tamanho);
	glPopMatrix();

	//defesa blue
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(posX[i] + movDef, 0.1, 0.4);
		glColor3f(0, 0, 1);
		glutSolidCube(tamanho);
		glPopMatrix();
	}

	//ataque blue
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(posX[i] + movAta, 0.1, -1.2);
		glColor3f(0, 0, 1);
		glutSolidCube(tamanho);
		glPopMatrix();
	}

	//red people

	//gol red
	glPushMatrix();
	glTranslatef(0 + movGol2, 0.1, -1.8);
	//glRotatef(ang[i], ay[i], 0, 0);
	//glRotatef(90.0, -1.0, 0.0, 0.0);
	glColor3f(1, 0, 0);
	glutSolidCube(tamanho);
	glPopMatrix();

	//defesa red
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(posX[i] + movDef2, 0.1, -0.4);
		glColor3f(1, 0, 0);
		glutSolidCube(tamanho);
		glPopMatrix();
	}
	//ataque red
	for (int i = 0; i < 3; i++)
	{
		glPushMatrix();
		glTranslatef(posX[i] + movAta2, 0.1, 1.2);
		glColor3f(1, 0, 0);
		glutSolidCube(tamanho);
		glPopMatrix();
	}
}

void DesenhaCampo() {
	//Funcão DesenhaCampo será chamada em RenderScene

	int m = 0;
	//Linha centro - ESQUERDA
	glColor3f(0.0, 0.9, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5 + m, -0, -0.25);
	glVertex3f(-1.5 + m, 0, -0.25);
	glVertex3f(-1.5 + m, 0, 0.25);
	glVertex3f(1.5 + m, 0, 0.25);
	glEnd();

	glColor3f(0.0, 0.8, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, -0, 0.25);
	glVertex3f(-1.5, 0, 0.25);
	glVertex3f(-1.5, 0, 0.75);
	glVertex3f(1.5, 0, 0.75);
	glEnd();

	glColor3f(0.0, 0.9, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, -0, 0.75);
	glVertex3f(-1.5, 0, 0.75);
	glVertex3f(-1.5, 0, 1.25);
	glVertex3f(1.5, 0, 1.25);
	glEnd();

	glColor3f(0.0, 0.8, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, -0, 1.25);
	glVertex3f(-1.5, 0, 1.25);
	glVertex3f(-1.5, 0, 1.75);
	glVertex3f(1.5, 0, 1.75);
	glEnd();

	glColor3f(0.0, 0.9, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, -0, 1.75);
	glVertex3f(-1.5, 0, 1.75);
	glVertex3f(-1.5, 0, 2);
	glVertex3f(1.5, 0, 2);
	glEnd();

	//DIREITA
	glColor3f(0.0, 0.8, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, -0, -0.25);
	glVertex3f(-1.5, 0, -0.25);
	glVertex3f(-1.5, 0, -0.75);
	glVertex3f(1.5, 0, -0.75);
	glEnd();

	glColor3f(0.0, 0.9, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, -0, -0.75);
	glVertex3f(-1.5, 0, -0.75);
	glVertex3f(-1.5, 0, -1.25);
	glVertex3f(1.5, 0, -1.25);
	glEnd();

	glColor3f(0.0, 0.8, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, -0, -1.25);
	glVertex3f(-1.5, 0, -1.25);
	glVertex3f(-1.5, 0, -1.75);
	glVertex3f(1.5, 0, -1.75);
	glEnd();

	glColor3f(0.0, 0.9, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, -0, -1.75);
	glVertex3f(-1.5, 0, -1.75);
	glVertex3f(-1.5, 0, -2);
	glVertex3f(1.5, 0, -2);
	glEnd();
}

void DesenhaParedes() {
	//Funcão DesenhaParedes será chamada em RenderScene

	//Barreiras baixo
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0, 2);
	glColor3f(1, 1, 1);
	glVertex3f(1.5, 0.2, 2);
	glVertex3f(1.5, 0.2, -2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(1.5, 0, -2);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.2, 2.2);
	glColor3f(1, 1, 1);
	glVertex3f(1.7, 0.2, 2.2);
	glVertex3f(1.7, 0.2, -2.2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(1.5, 0.2, -2.2);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(1.7, 0, 2.2);
	glColor3f(1, 1, 1);
	glVertex3f(1.7, 0.2, 2.2);
	glVertex3f(1.7, 0.2, -2.2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(1.7, 0, -2.2);
	glEnd();

	//alto
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-1.5, 0, 2);
	glColor3f(1, 1, 1);
	glVertex3f(-1.5, 0.2, 2);
	glVertex3f(-1.5, 0.2, -2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-1.5, 0, -2);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-1.5, 0.2, 2.2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-1.7, 0.2, 2.2);
	glVertex3f(-1.7, 0.2, -2.2);
	glColor3f(1, 1, 1);
	glVertex3f(-1.5, 0.2, -2.2);
	glEnd();

	//gol blue

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0, 2);
	glVertex3f(1.5, 0.2, 2);
	glColor3f(1, 1, 1);
	glVertex3f(0.6, 0.2, 2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0.6, 0, 2);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.2, 2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(1.5, 0.2, 2.2);
	glVertex3f(0.6, 0.2, 2.2);
	glColor3f(1, 1, 1);
	glVertex3f(0.6, 0.2, 2);
	glEnd();

	//-----------

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-1.5, 0, 2);
	glColor3f(1, 1, 1);
	glVertex3f(-1.5, 0.2, 2);
	glVertex3f(-0.6, 0.2, 2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.6, 0, 2);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-1.5, 0.2, 2);
	glVertex3f(-1.5, 0.2, 2.2);
	glVertex3f(-0.6, 0.2, 2.2);
	glVertex3f(-0.6, 0.2, 2);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-0.6, 0.0, 2.2);
	glColor3f(1, 1, 1);
	glVertex3f(-0.6, 0.2, 2.2);
	glVertex3f(-0.6, 0.2, 2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.6, 00, 2);
	glEnd();

	//gol red

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0, -2);
	glColor3f(1, 1, 1);
	glVertex3f(1.5, 0.2, -2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(0.6, 0.2, -2);
	glColor3f(1, 1, 1);
	glVertex3f(0.6, 0, -2);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(1.5, 0.2, -2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(1.5, 0.2, -2.2);
	glVertex3f(0.6, 0.2, -2.2);
	glColor3f(1, 1, 1);
	glVertex3f(0.6, 0.2, -2);
	glEnd();

	//----------------

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-1.5, 0, -2);
	glColor3f(1, 1, 1);
	glVertex3f(-1.5, 0.2, -2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.6, 0.2, -2);
	glColor3f(1, 1, 1);
	glVertex3f(-0.6, 0, -2);
	glEnd();

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex3f(-1.5, 0.2, -2);
	glVertex3f(-1.5, 0.2, -2.2);
	glVertex3f(-0.6, 0.2, -2.2);
	glVertex3f(-0.6, 0.2, -2);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex3f(-0.6, 0.0, -2.2);
	glColor3f(1, 1, 1);
	glVertex3f(-0.6, 0.2, -2.2);
	glVertex3f(-0.6, 0.2, -2);
	glColor3f(0.5, 0.5, 0.5);
	glVertex3f(-0.6, 00, -2);
	glEnd();
}

void DesenhaTexto(const char *text, int length, float x, float y, float z) {
	
	//Funcão DesenhaTexto será chamada em RenderScene

	glColor3f(0, 0, 0);
	//glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	//glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	//glLoadIdentity();
	//glOrtho(0, 800, 0, 600, -5, 5);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glPushMatrix();
	//glLoadIdentity();
	glRasterPos3i(x, y, z);
	for (int i = 0; i < length;i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);
	}
	//glPopMatrix();
	//glMatrixMode(GL_PROJECTION);
	//glLoadMatrixd(matrix);
	//glMatrixMode(GL_MODELVIEW);
}

void RenderScene(void) {
	//Trata oclusão de superfícies
	glEnable(GL_DEPTH_TEST);

	//Limpa a janela e habilita o teste para eliminar faces posteriores
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Habilita a iluminacao da cena
	glEnable(GL_LIGHTING);
	//Habilita a fonte de luz zero
	glEnable(GL_LIGHT0);
	//Posicao da luz

	GLfloat posicaoLuz[4] = { -1, -50, 50, -1 };
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	//Habilita a definicao da cor do material a partir da cor corrente

	glEnable(GL_COLOR_MATERIAL);

	//Chama função que desenha o campo
	DesenhaCampo();

	//Chama a função que desenha as paredes
	DesenhaParedes();

	//bola
	glPushMatrix();
	glTranslatef(movX, 0.2, movZ);
	glColor3f(1, 1, 1);
	glutSolidSphere(raio, 15, 15);
	glPopMatrix();

	//chama a função que desenha os jogadores
	DesenharJogadores();

	//text para desenhar o placar do jogo
	std::string text;
	text = "Azul " + std::to_string(golAzul) + " X " + std::to_string(golVermelho) + " Vermelho";
	
	//chama função para desenhar o placar com os parametros selecionados
	DesenhaTexto(text.data(), text.size(), 2.5, 3.0, 0.0);

	//Garante a execução dos comandos de desenho
	glFlush();
}

//Função de Colisão entre as goleiras
void ColisaoGol()
{
	//ColisãoGol será chamada em FuncaoAnima

	//Goleira Direita
	if (movZ > 1.9) {
		if (movX < 0.5 && movX > -0.5)
		{
			golVermelho = golVermelho + 1;
			movZ = 0.0;
			movX = 0.0;
			//cout << "Azul " << golAzul << " X " << golVermelho << " Vermelho" << endl;
		}
	}

	//Goleira Esquerda
	if (movZ < -1.9) {
		if (movX < 0.5 && movX > -0.5)
		{
			golAzul = golAzul + 1;
			movZ = 0.0;
			movX = 0.0;
			//cout << "Azul " << golAzul << " X " << golVermelho << " Vermelho" << endl;
		}
	}
}

//Função de colisão entre a bola e os jogadores
void Colisao()
{
	//Colisão será chamada em FuncaoAnima

	//distancias da bola em relação aos jogadores
	double distGol, distGol2;
	double distDef[3], distDef2[3];
	double distAta[3], distAta2[3];

	//Calcular a distancia entre o centro do goleiro e o centro da bola
	distGol = (double)sqrt(((0.0 + movGol) - movX)*((0.0 + movGol) - movX) + (1.8 - movZ)*(1.8 - movZ));
	distGol2 = (double)sqrt(((0.0 + movGol2) - movX)*((0.0 + movGol2) - movX) + (-1.8 - movZ)*(-1.8 - movZ));

	//Testes para ver se a bola colidiu com o goleiro
	if (distGol <= (double)(raio + tamanho)) {
		limiteZ = true;
	}

	if (distGol2 <= (double)(raio + tamanho)) {
		limiteZ = false;
	}

	//Calcular a distancia entre o centro dos jogadores e o centro da bola
	for (int i = 0; i < 3; i++)
	{
		distDef[i] = (double)sqrt(((posX[i] + movDef) - movX)*((posX[i] + movDef) - movX) + (0.4 - movZ)*(0.4 - movZ));
		distDef2[i] = (double)sqrt(((posX[i] + movDef2) - movX)*((posX[i] + movDef2) - movX) + (-0.4 - movZ)*(-0.4 - movZ));

		//Testes para ver se a bola colidiu com um defensor
		if (distDef[i] <= (double)(raio + tamanho)) {
			limiteZ = true;
		}

		if (distDef2[i] <= (double)(raio + tamanho)) {
			limiteZ = false;
		}

		distAta[i] = (double)sqrt(((posX[i] + movAta) - movX)*((posX[i] + movAta) - movX) + (-1.2 - movZ)*(-1.2 - movZ));
		distAta2[i] = (double)sqrt(((posX[i] + movAta2) - movX)*((posX[i] + movAta2) - movX) + (1.2 - movZ)*(1.2 - movZ));

		//Testes para ver se a bola colidiu com um atacante
		if (distAta[i] <= (double)(raio + tamanho)) {
			limiteZ = true;
		}

		if (distAta2[i] <= (double)(raio + tamanho)) {
			limiteZ = false;
		}
	}
}

void TeclasNormais(unsigned char tecla, int x, int y) {
	//comandos player 1
	if ((tecla == 'Q' || tecla == 'q') && movGol >= -1.4)
		movGol -= 0.1;
	else if ((tecla == 'A' || tecla == 'a') && movGol <= 1.4)
		movGol += 0.1;

	if ((tecla == 'W' || tecla == 'w') && posX[2] + movDef >= -1.4)
		movDef -= 0.1;
	else if ((tecla == 'S' || tecla == 's') && posX[0] + movDef <= 1.4)
		movDef += 0.1;

	if ((tecla == 'E' || tecla == 'e') && posX[2] + movAta >= -1.4)
		movAta -= 0.1;
	else if ((tecla == 'D' || tecla == 'd') && posX[0] + movAta <= 1.4)
		movAta += 0.1;

	//Comandos player 2

	if (tecla == '6' && movGol2 >= -1.4)
		movGol2 -= 0.1;
	else if (tecla == '3' && movGol2 <= 1.4)
		movGol2 += 0.1;

	if (tecla == '5' && posX[2] + movDef2 >= -1.4)
		movDef2 -= 0.1;
	else if (tecla == '2' && posX[0] + movDef2 <= 1.4)
		movDef2 += 0.1;

	if (tecla == '4' && posX[2] + movAta2 >= -1.4)
		movAta2 -= 0.1;
	else if (tecla == '1' && posX[0] + movAta2 <= 1.4)
		movAta2 += 0.1;


	glutPostRedisplay();
}

void FuncaoAnima(int valor)
{
	if (limiteX == true)
	{
		movX -= velocidadeBola;
		if (movX < -1.5)
		{
			movX += velocidadeBola;
			limiteX = false;
		}
	}
	else if (limiteX == false)
	{
		movX += velocidadeBola;
		if (movX > 1.5)
		{
			movX -= velocidadeBola;
			limiteX = true;
		}
	}

	if (limiteZ == true)
	{
		movZ -= velocidadeBola;
		if (movZ < -2)
		{
			movZ += velocidadeBola;
			limiteZ = false;
		}
	}
	else if (limiteZ == false)
	{
		movZ += velocidadeBola;
		if (movZ > 2)
		{
			movZ -= velocidadeBola;
			limiteZ = true;
		}
	}

	//chamar colisões
	Colisao();
	ColisaoGol();

	glutPostRedisplay();
	glutTimerFunc(50, FuncaoAnima, 1);
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(700, 600);
	glutCreateWindow("Cena sem iluminação e sombreamento");
	//Especifica para a OpenGL que funcao deve ser chamada para geracao da imagem
	glutDisplayFunc(RenderScene);
	//Chamada pela GLUT quando a janela é redimensionada
	glutReshapeFunc(ChangeSize);
	RenderScene();
	glutTimerFunc(50, FuncaoAnima, 1);
	//Executa a inicializacao de parametros de exibicao
	Starter();
	glutKeyboardFunc(TeclasNormais);
	glutMainLoop();

	return 0;
}