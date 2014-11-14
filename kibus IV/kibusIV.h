#ifndef KIBUSI_H
#define KIBUSI_H

#include <iostream>
#include "grafo.h"
#include "punto.h"
#include "mundo.h"
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>


class kibusIV{
	private:
	public:
		int orientacion;
		punto pos;
		punto posAux;
		punto posAnt;
		int frames[4];
		mundo m;
		grafo conocimiento;
		bool volviendo;
		bool entrenado;
		bool refrescarEnEntrenamiento;

		void dibujarKibus(bool aux=false){
			if(aux)
				dibujos[frames[orientacion]].drawAt(posAux.x*dl,posAux.y*dl);
			else	
				dibujos[frames[orientacion]].drawAt(pos.x*dl,pos.y*dl);
		}

		void desdibujarKibus(bool aux=false){
			if(aux)
			m[posAux.x][posAux.y].dibujar(posAux.x,posAux.y);
			else
			m[pos.x][pos.y].dibujar(pos.x,pos.y);
		}
		void redibuja(int, int);

		punto caminaAlAzar(){
			std::vector<punto> disponibles;
			for(int i=-1;i<2;i++){
				for(int j=-1;j<2;j++){
					if(i or j){
						int a=posAux.x+i;
						int b=posAux.y+j;
						//std::cout<<a<<"::"<<b<<std::endl;
						if(a>=0 and b>=0 and a<m.rows() and b<m.cols() and m[a][b].tipo!=1 and a!=posAnt.x and b!=posAnt.y){
							disponibles.push_back(punto(a,b));
						}
					}
				}
			}
			std::random_device rnd;
			return disponibles.size()==0?posAnt:disponibles[rnd()%disponibles.size()];
		}

		void entrenar(int iteraciones){
			refrescarEnEntrenamiento=false;
			std::cout<<"Iniciando entrenamiento..."<<std::endl;
			int mejor=-1;
			int peor=-1;
			for(int i=0;i<iteraciones;i++){
				std::vector<punto> camino;
				if(refrescarEnEntrenamiento){
					orientacion=2;
					desdibujarKibus(1);
					posAux=pos;
					dibujarKibus(1);
					glFlush();
					glutSwapBuffers();
				}
				posAux=posAnt=pos;
				std::cout<<"Recorrido numero:\t"<<i+1<<std::endl;
				while(m[posAux.x][posAux.y].tipo!=2){
					camino.push_back(posAux);
					if(refrescarEnEntrenamiento){
						//std::cout<<posAux.toString()<<std::endl;
						desdibujarKibus(1);
						punto sig;
						//std::cout<<sig.toString()<<std::endl;
						sig=caminaAlAzar();
						//std::cout<<":v"<<std::endl;
						posAnt=posAux;
						posAux=sig;
						dibujarKibus(1);
						glFlush();
						glutSwapBuffers();
					}else{
						punto sig=caminaAlAzar();
						posAnt=posAux;
						posAux=sig;
					}
				}
				if(mejor==-1 and peor==-1){
					mejor=peor=camino.size();
				}else{
					int media=(mejor+peor)/2;
					int actual=camino.size();
					mejor=std::min(mejor,actual);
					peor=std::max(peor,actual);
					int factor=abs(media-actual);
					std::cout<<"Mejor:\t"<<mejor<<std::endl;
					std::cout<<"Peor:\t"<<peor<<std::endl;
					std::cout<<"Media:\t"<<media<<std::endl;
					std::cout<<"Actual:\t"<<actual<<std::endl;
					if(actual<media){	
							
					}else if(actual>media){
						factor*=-1;
					}else{
						factor=0;
					}
					if(factor){
						for(int i=1;i<actual;i++){
						//	std::cout<<"Ajustando pesos: "<<i<<"/"<<actual<<std::endl;
							conocimiento.ajustaPesos(camino[i-1],camino[i],factor);
						}
					}
				}
			}
			entrenado=true;
		}
			
		bool movN(){
			int a,b;
			a=pos.x+1;
			b=pos.y;
			orientacion=0;
			if(a<0 or b<0 or a>=m.rows() or b>=m.cols()){
				return false;
			}
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1 and (m[a][b].tipo<=m[pos.x][pos.y].tipo or m[a][b].tipo==2)){
				pos=punto(a,b);
				return true;
			}
			return false;
		}
		bool movS(){
			int a,b;
			a=pos.x-1;
			b=pos.y;
			orientacion=2;
			if(a<0 or b<0 or a>=m.rows() or b>=m.cols()){
				return false;
			}
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1 and (m[a][b].tipo<=m[pos.x][pos.y].tipo or m[a][b].tipo==2)){
				pos=punto(a,b);
				return true;
			}
			return false;
		}
		bool movE(){
			int a,b;
			a=pos.x;
			b=pos.y+1;
			orientacion=1;
			if(a<0 or b<0 or a>=m.rows() or b>=m.cols()){
				return false;
			}
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1 and (m[a][b].tipo<=m[pos.x][pos.y].tipo or m[a][b].tipo==2)){
				pos=punto(a,b);
				return true;
			}
			return false;
		}
		bool movO(){
			int a,b;
			a=pos.x;
			b=pos.y-1;
			orientacion=3;
			if(a<0 or b<0 or a>=m.rows() or b>=m.cols()){
				return false;
			}
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1 and (m[a][b].tipo<=m[pos.x][pos.y].tipo or m[a][b].tipo==2)){
				pos=punto(a,b);
				return true;
			}
			return false;
		}
		bool movNO(){
			int a,b;
			a=pos.x+1;
			b=pos.y-1;
			orientacion=0;
			if(a<0 or b<0 or a>=m.rows() or b>=m.cols()){
				return false;
			}
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1 and (m[a][b].tipo<=m[pos.x][pos.y].tipo or m[a][b].tipo==2)){
				pos=punto(a,b);
				return true;
			}
			return false;
		}
		bool movSE(){
			int a,b;
			a=pos.x-1;
			b=pos.y+1;
			orientacion=2;
			if(a<0 or b<0 or a>=m.rows() or b>=m.cols()){
				return false;
			}
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1 and (m[a][b].tipo<=m[pos.x][pos.y].tipo or m[a][b].tipo==2)){
				pos=punto(a,b);
				return true;
			}
			return false;
		}
		bool movNE(){
			int a,b;
			a=pos.x+1;
			b=pos.y+1;
			orientacion=1;
			if(a<0 or b<0 or a>=m.rows() or b>=m.cols()){
				return false;
			}
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1 and (m[a][b].tipo<=m[pos.x][pos.y].tipo or m[a][b].tipo==2)){
				pos=punto(a,b);
				return true;
			}
			return false;
		}
		bool movSO(){
			int a,b;
			a=pos.x-1;
			b=pos.y-1;
			orientacion=3;
			if(a<0 or b<0 or a>=m.rows() or b>=m.cols()){
				return false;
			}
			if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1 and (m[a][b].tipo<=m[pos.x][pos.y].tipo or m[a][b].tipo==2)){
				pos=punto(a,b);
				return true;
			}
			return false;
		}

		bool camina(int dx, int dy){
			if(dx==-1){
				if(dy==-1){
					return movSO();
				}else if(dy==0){
					return movS();
				}else if(dy==1){
					return movSE();
				}
			}else if(dx==0){
				if(dy==-1){
					return movO();
				}else if(dy==0){
					return true;
				}else if(dy==1){
					return movE();
				}
			}else{
				if(dy==-1){
					return movNO();
				}else if(dy==0){
					return movN();
				}else if(dy==1){
					return movNE();
				}
			}
			return false;
		}

		bool regresa(){
			if(not entrenado)
				return true;
			desdibujarKibus();
			punto sig=conocimiento.mejor(pos);
			
			dibujarKibus();
			pos=sig;
			glFlush();
			glutSwapBuffers();
			volviendo=m[pos.x][pos.y].tipo!=2;
			return volviendo;
		}


	
		void dibujar();		
		void colocaKibus(punto p, int o){
			if(m[p.x][p.y].tipo==1)
				return;
			pos=p;
			orientacion=o;
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
			volviendo = false;
			for(int i=0;i<m.rows();i++)
				for(int j=0;j<m.cols();j++)
					if(m[i][j].tipo==2){
						pos=punto(i,j);
						orientacion=2;
					}
		}

		void mapaAleatorio(int densidad,int total){
			std::random_device rnd;
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

		void cargaMundo(std::string s){
			std::cout<<"Cargando "<<s<<std::endl;
			std::random_device rnd;
			std::fstream f(s.c_str());
			if(!f.good()){
				std::cout<<"El archivo no existe"<<std::endl;
				return;
			}
			std::string lineas[21];
			punto casa2;
			bool error=false;
			bool casa=false;
			for(int i=0;i<21;i++){
				std::getline(f,lineas[i]);
				for(int j=0;j<30;j++){
					char c;
					if(j>=lineas[i].size()){
						c='0';
					}else{
						c=lineas[i][j];
					}
					switch(c){
						case '0': case '1':
						break;
						case '2':
							if(casa){
								error=true;
							}else{
								casa2=punto(i,j);
								casa=true;
							}
						break;
						default:
							error=true;
					}
				}
			}
			f.close();
			if(error){
				std::cout<<"El archivo no es correcto"<<std::endl;
			}else if(not casa){
				std::cout<<"No se encontro la casa en el archivo"<<std::endl;
			}else{
				for(int i=0;i<21;i++){
					for(int j=0;j<30;j++){
						m[i][j].tipo=lineas[i][j]-'0';
						m[i][j].frame=(m[i][j].tipo==0?4+rnd()%2:m[i][j].tipo==1?6+rnd()%2:8);
					}
				}
				std::cout<<casa2.toString()<<std::endl;
				pos=casa2;
				dibujar();
				dibujarKibus();
			}
		}

		void guardaMundo(std::string s){
			std::ofstream f(s.c_str());
			if(!f.good()){
				std::cout<<"Error al guardar"<<std::endl;
			}
			for(int i=0;i<21;i++){
				for(int j=0;j<30;j++){
					f.put(m[i][j].tipo+'0');
				}
				f.put('\n');
			}
			f.close();
		}
};

#endif