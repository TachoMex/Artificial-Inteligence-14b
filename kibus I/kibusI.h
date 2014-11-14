#ifndef KIBUSI_H
#define KIBUSI_H

#include <stack>
#include "punto.h"
#include "mundo.h"
#include <thread>
#include <chrono>
#include <random>


class kibusI{
	private:
	public:
		int orientacion;
		std::stack<int> movs;
		punto pos;
		int frames[4];
		mundo m;

		void dibujarKibus();
		void desdibujarKibus();
	
		void movN(){
			int a,b;
			a=pos.x+1;
			b=pos.y;
			orientacion=0;
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1){
				movs.push(orientacion);
				pos=punto(a,b);
			}
		}
		
		void movS(){
			int a,b;
			a=pos.x-1;
			b=pos.y;
			orientacion=2;
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1){
				movs.push(orientacion);
				pos=punto(a,b);
			}
		}
		
		void movE(){
			int a,b;
			a=pos.x;
			b=pos.y+1;
			orientacion=1;
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1){
				movs.push(orientacion);
				pos=punto(a,b);
			}
		}
		
		void movO(){
			int a,b;
			a=pos.x;
			b=pos.y-1;
			orientacion=3;
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1){
				movs.push(orientacion);
				pos=punto(a,b);
			}
		}
		void dibujar();
		
		bool regresa(){
			if(!movs.empty()){
				int paso=movs.top();
				desdibujarKibus();
				switch(paso){
					case 0:
						pos.x--;
						orientacion=2;
						break;
					case 1:
						pos.y--;
						orientacion=3;
						break;	
					case 2:
						pos.x++;
						orientacion=0;
						break;
					case 3:
						pos.y++;
						orientacion=1;
						break;
				}
				movs.pop();
				dibujarKibus();
				glFlush();
				glutSwapBuffers();
				return true;
			}
			return false;
		}
	
		
		void colocaKibus(punto p, int o){
			if(m[p.x][p.y].tipo==1)
				return;
			pos=p;
			orientacion=o;
			movs=std::stack<int>();
		}
		
		void colocaCasa(punto p){
			if(m[p.x][p.y].tipo==1)
				return;
			for(int i=0;i<m.rows();i++)
				for(int j=0;j<m.cols();j++)
					if(m[i][j].tipo==2){
						m[i][j].tipo=0;
						m[i][j].frame=5;
					}
			m[p.x][p.y].tipo=2;
			m[p.x][p.y].frame=8;
		}

		void reset(){
			movs = std::stack<int>();
			for(int i=0;i<m.rows();i++)
				for(int j=0;j<m.cols();j++)
					if(m[i][j].tipo==2){
						pos=punto(i,j);
						orientacion=2;
					}
		}

		void mapaAleatorio(int densidad,int total){
			random_device rnd;
			pos = punto(rnd()%m.rows(), rnd()%m.cols());

			for(int i=0;i<m.rows();i++){
				for(int j=0;j<m.cols();j++){
					m[i][j].tipo = rnd()%total<=densidad;
					m[i][j].frame=(m[i][j].tipo==0?4+rnd()%2:m[i][j].tipo==1?6+rnd()%2:8);
				}
			}
			m[pos.x][pos.y].tipo=2;
			m[pos.x][pos.y].frame=8;
			reset();
		}
};

#endif
