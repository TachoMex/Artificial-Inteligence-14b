#define dl 28
#include <iostream>
#include "imagen.h"
imagen dibujos[11];
#include "kibusIV.h"
#include "mundo.h"
#include "grafo.h"
#include <random>

using namespace std;


int densidad=118;
int velocidad=118;

int slide=0;
int escribiendo;
string texto;

void ponerTexto(int x, int y, void* font, const char *string){
	glColor3f(0,0,0);
	glRasterPos2f(x, y);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(font, string[i]);
	}
}

void kibusIV::dibujar(){
	for(int i=0;i<m.rows();i++){
		for(int j=0;j<m.cols();j++){
			m[i][j].dibujar(i,j);
		}
	}
	dibujos[frames[orientacion]].drawAt(pos.x*dl,pos.y*dl);
	glBegin(GL_LINES);
		glColor(color::blanco);		
		glVertex2i(30*dl+50,0);
		glVertex2i(30*dl+50,21*dl);
		glColor(color::rojo);
		glVertex2i(30*dl+50,0);
		glVertex2i(30*dl+50,densidad);
		glColor(color::blanco);		
		glVertex2i(30*dl+10,0);
		glVertex2i(30*dl+10,21*dl);
		glColor(color::verde);
		glVertex2i(30*dl+10,0);
		glVertex2i(30*dl+10,velocidad);
	glEnd();
}



void casilla::dibujar(int i, int j){
	dibujos[frame].drawAt(i*dl,j*dl);
}


void kibusIV::redibuja(int x, int y){
	dibujos[m[x][y].frame].drawAt(x*dl,y*dl);
	glutSwapBuffers();
	glFlush();
}

kibusIV kib;

void renderFunc(){
	glClear(GL_COLOR_BUFFER_BIT);
	kib.dibujar();
	glFlush();
	glutSwapBuffers();
}

void regresa(int x){
	if(kib.regresa()){
		glutTimerFunc(velocidad,regresa,0);
		//cout<<"TIMER"<<endl;
	}else{
		kib.dibujar();
		glutSwapBuffers();
		glFlush();
	}
}
void entrenar(){
	kib.entrenar(20);
}


void tecladoFunc(unsigned char k, int x, int y){
	//cout<<(int)k<<endl;
	//cout<<(escribiendo==0?"Nada":(escribiendo==1?"Para cargar":"Para guardar"))<<endl;

	switch(escribiendo){
		case 2:
			for(int i=0;i<kib.m.cols();i++){
				kib.m[0][i].dibujar(0,i);
			}
			glFlush(); glutSwapBuffers(); 
			if(k==13){
				kib.cargaMundo(texto);
				renderFunc();
				glFlush(); glutSwapBuffers(); 
				escribiendo=0;
			}else if(k==8){
				texto=texto.substr(0,texto.size()-1);
				ponerTexto(0,0,GLUT_BITMAP_TIMES_ROMAN_24,texto.c_str());
				glFlush(); glutSwapBuffers(); 
			}else if(k==27){
				texto=string();
				escribiendo=0;
				kib.dibujar();
				glFlush(); glutSwapBuffers(); 
			}
			else{
				texto+=k;
				ponerTexto(0,0,GLUT_BITMAP_TIMES_ROMAN_24,texto.c_str());
				glFlush(); glutSwapBuffers(); 
			}
			return;
		case 1:
			for(int i=0;i<kib.m.cols();i++){
				kib.m[0][i].dibujar(0,i);
			}
			if(k==13){
				kib.guardaMundo(texto.c_str());
				escribiendo=0;
				texto=string();
				kib.dibujar();
				glFlush(); glutSwapBuffers();
			}else if(k==8){
				texto=texto.substr(0,texto.size()-1);
				ponerTexto(0,0,GLUT_BITMAP_TIMES_ROMAN_24,texto.c_str());
				glFlush(); glutSwapBuffers(); 
			}else if(k==27){
				texto=string();
				escribiendo=0;
				kib.dibujar();
				glFlush(); glutSwapBuffers(); 
			}
			else{
				texto+=k;
				ponerTexto(0,0,GLUT_BITMAP_TIMES_ROMAN_24,texto.c_str());
				glFlush(); glutSwapBuffers(); 
			}
			return;		
	}


	kib.desdibujarKibus();
	kib.m[kib.pos.x][kib.pos.y].dibujar(kib.pos.x,kib.pos.y);
	switch(k){
		case 'w': case 'W':
			kib.movN();
		break;
		case 'x': case 'X':
			kib.movS();
		break;
		case 'd': case 'D':
			kib.movE();
		break;
		case 'a': case 'A':
			kib.movO();
		break;
		case 'q': case 'Q':
			kib.movNO();
		break;
		case 'e': case 'E':
			kib.movNE();
		break;
		case 'z': case 'Z':
			kib.movSO();
		break;
		case 'c': case 'C':
			kib.movSE();
		break;
		case 'r': case 'R':
			glutTimerFunc(velocidad,regresa,0);
		break;
		case 'm': case 'M':
			kib.mapaAleatorio(densidad,21*dl);
			renderFunc();
		break;
		case 't': case 'T':
			entrenar();
		break;
		case 15:
			texto=string();
			escribiendo=2;
			break;
		case 19:
			texto=string();
			escribiendo=1;
		break;
	}
	kib.dibujarKibus();
	glBegin(GL_LINES);
		glColor(color::blanco);		
		glVertex2i(30*dl+50,0);
		glVertex2i(30*dl+50,21*dl);
		glColor(color::rojo);
		glVertex2i(30*dl+50,0);
		glVertex2i(30*dl+50,densidad);
		glColor(color::blanco);
		glVertex2i(30*dl+10,0);
		glVertex2i(30*dl+10,21*dl);
		glColor(color::verde);
		glVertex2i(30*dl+10,0);
		glVertex2i(30*dl+10,velocidad);
	glEnd();
	glFlush();
	glutSwapBuffers();
}

void mouseFunc(int b, int e, int x, int y){

	if(b==GLUT_LEFT_BUTTON and e==GLUT_DOWN){
		if(x>=30*dl+25){
			y=21*dl-y;
			y=(y>471?471:y);
			y=(y<118?128:y);
			densidad=y;
			glBegin(GL_LINES);
				glColor(color::blanco);		
				glVertex2i(30*dl+50,0);
				glVertex2i(30*dl+50,21*dl);
				glColor(color::rojo);
				glVertex2i(30*dl+50,0);
				glVertex2i(30*dl+50,densidad);
			glEnd();
			glFlush();
			glutSwapBuffers();
			slide=1;
			return;
		}else if(x>=30*dl){
			y=21*dl-y;
			velocidad=y;
			glBegin(GL_LINES);
			glColor(color::blanco);
			glVertex2i(30*dl+10,0);
			glVertex2i(30*dl+10,21*dl);
			glColor(color::verde);
			glVertex2i(30*dl+10,0);
			glVertex2i(30*dl+10,velocidad);
			glEnd();
			glFlush();
			glutSwapBuffers();
			slide=2;
			return;
		}
		if(kib.volviendo)
			return;
		x /= dl;
		y =21*dl-y;
		y/=dl;
		x^=y^=x^=y;
		random_device rnd;
		if(x<0 or y<0 or y>=kib.m.cols() or x>=kib.m.rows())
			return;
		if(kib.m[x][y].tipo==1){
			kib.m[x][y].tipo=0;
			kib.m[x][y].frame=4+rnd()%2;
		}else if(kib.m[x][y].tipo==0){
			kib.m[x][y].tipo=1;
			kib.m[x][y].frame=6+rnd()%2;
		}
	}else if(b==GLUT_RIGHT_BUTTON and e==GLUT_DOWN){
		random_device rnd;
		x /= dl;
		y =21*dl-y;
		y/=dl;
		cout<<x<<","<<y<<endl;
		x^=y^=x^=y;
		if(x<0 or y<0 or y>=kib.m.cols() or x>=kib.m.rows())
			return;
		if(kib.m[x][y].tipo!=1){
			kib.colocaCasa(punto(x,y));
		}
	}else{
		slide=0;
	}
	renderFunc();
}

void eventoArrastre(int x, int y){
	switch(slide){
		case 0:
		break;
		case 1:
			y=21*dl-y;
			y=(y>471?471:y);
			y=(y<118?128:y);
			densidad=y;
			glBegin(GL_LINES);
				glColor(color::blanco);		
				glVertex2i(30*dl+50,0);
				glVertex2i(30*dl+50,21*dl);
				glColor(color::rojo);
				glVertex2i(30*dl+50,0);
				glVertex2i(30*dl+50,densidad);
			glEnd();
			glFlush();
			glutSwapBuffers();
		break;
		case 2:
			y=21*dl-y;
			velocidad=y;
			glBegin(GL_LINES);
			glColor(color::blanco);
			glVertex2i(30*dl+10,0);
			glVertex2i(30*dl+10,21*dl);
			glColor(color::verde);
			glVertex2i(30*dl+10,0);
			glVertex2i(30*dl+10,velocidad);
			glEnd();
			glFlush();
			glutSwapBuffers();
		}
		return;

}
int mapa[][40]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,1,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,1,1,1,1,1,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,2,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};


int main(int argc, char**argv){




	random_device rnd;
	dibujos[0].leerBMP("kibusN.bmp");
	dibujos[1].leerBMP("kibusS.bmp");
	dibujos[2].leerBMP("kibusE.bmp");
	dibujos[3].leerBMP("kibusO.bmp");
	dibujos[4].leerBMP("pasto1.bmp");
	dibujos[5].leerBMP("pasto2.bmp");
	dibujos[6].leerBMP("arbol.bmp");
	dibujos[7].leerBMP("roca.bmp");
	dibujos[8].leerBMP("casa.bmp");
	dibujos[9].leerBMP("hada.bmp");

	kib.m = mundo(21,30);
	for(int i=0;i<kib.m.rows();i++){
		for(int j=0;j<kib.m.cols();j++){
			kib.m[i][j].tipo = mapa[i][j];
			kib.m[i][j].frame=(mapa[i][j]==0?4+rnd()%2:mapa[i][j]==1?6+rnd()%2:8);
		}
	}

	kib.frames[0]=0;
	kib.frames[1]=2;
	kib.frames[2]=1;
	kib.frames[3]=3;
	kib.pos=punto(18,26);
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(30*dl+60,21*dl);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Kibus IV");
	glClearColor(0,0,0, 0.0);
	glMatrixMode(GL_PROJECTION); 
	gluOrtho2D(0,30*dl+60,0,21*dl);  
	glLineWidth(10);
	glutKeyboardFunc(tecladoFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(eventoArrastre);
	glutDisplayFunc(renderFunc);
	glutMainLoop();   	
}

