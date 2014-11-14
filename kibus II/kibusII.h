#ifndef KIBUSI_H
#define KIBUSI_H

#include <iostream>
#include "punto.h"
#include "mundo.h"
#include "bressenham.h"
#include <thread>
#include <chrono>
#include <vector>
#include <random>


class kibusII{
	private:
	public:
		int orientacion;
		punto pos;
		punto posAnterior;
		punto posCasa;
		int frames[4];
		mundo m;
		bool volviendo;
		std::vector<punto> plan;

		void quitaBanderines(){
			random_device random;
			for(int i=0;i<m.rows();i++){
				for(int j=0;j<m.cols();j++){
					if(m[i][j].tipo>=3){
						m[i][j].tipo=0;
						m[i][j].frame=4+random()%2;
					}
				}
			}
		}

		void dibujarKibus();
		void desdibujarKibus();
		void redibuja(int, int);
		void ponBanderin(int x, int y){
			if(m[x][y].tipo==0){
				m[x][y].tipo=3;
				m[x][y].frame=9;
			}else if(m[x][y].tipo>=3){
				m[x][y].tipo++;
				m[x][y].frame=10;		
			}
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
				posAnterior=pos;
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
				posAnterior=pos;
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
				posAnterior=pos;
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
				posAnterior=pos;
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
				posAnterior=pos;
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
				posAnterior=pos;
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
				posAnterior=pos;
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
				posAnterior=pos;
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
			//cout<<pos.toString()<<endl;
			if(pos==posCasa){
				volviendo=false;
				return false;
			}
			desdibujarKibus();
			if(not volviendo){
				volviendo=true;
				plan = rectaBress(pos.x,pos.y,posCasa.x,posCasa.y);
			}
			punto paso = plan[0];
			plan.erase(plan.begin());
			int dx = paso.x - pos.x; 
			int dy = paso.y - pos.y;
			bool pasoLibre=camina(dx,dy);
			if(not pasoLibre){
				ponBanderin(pos.x,pos.y);
				redibuja(pos.x,pos.y);
				glFlush();
				glutSwapBuffers();
				std::vector<punto> opciones;
				int best=1<<20;
				for(int i=-1;i<2;i++){
					for(int j=-1;j<2;j++){
						if(i or j){
							int a=pos.x+i;
							int b=pos.y+j;
							if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and posAnterior!=punto(a,b) and m[a][b].tipo!=1 and m[a][b].tipo<=m[pos.x][pos.y].tipo){
								if(m[a][b].tipo < best)
									best=m[a][b].tipo;
							}
						}
					}
				}
				for(int i=-1;i<2;i++){
					for(int j=-1;j<2;j++){
						if(i!=0 or j!=0){
							int a=pos.x+i;
							int b=pos.y+j;
							if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and posAnterior!=punto(a,b) and m[a][b].tipo!=1 and m[a][b].tipo<=best){
								opciones.push_back(punto(a,b));
							}
						}
					}
				}
				if(opciones.empty()){
					for(int i=-1;i<2;i++){
						for(int j=-1;j<2;j++){
							if(i!=0 or j!=0){
								int a=pos.x+i;
								int b=pos.y+j;
								if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1){
									opciones.push_back(punto(a,b));
								}
							}
						}
					}
				}
				int idx=random()%opciones.size();
				paso = opciones[idx];
				dx = paso.x - pos.x; 
				dy = paso.y - pos.y;
				if(camina(dx,dy)){

				}else{
					posAnterior=pos;
					pos+=punto(dx,dy);
				}
				
				
				plan=rectaBress(pos.x,pos.y,posCasa.x,posCasa.y);
				dibujarKibus();
				glFlush();
				glutSwapBuffers();
				return true;
			}
			dibujarKibus();
			glFlush();
			glutSwapBuffers();
			//return not plan.empty();
			volviendo=pos!=posCasa;
			if(not volviendo){
				plan = std::vector<punto>();
			}
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
			posCasa = p;
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

		void cargaMundo(std::string s){
			cout<<"Cargando "<<s<<endl;
			random_device rnd;
			std::fstream f(s.c_str());
			if(!f.good()){
				std::cout<<"El archivo no existe"<<std::endl;
				return;
			}
			std::string lineas[20];
			punto casa2;
			bool error=false;
			bool casa=false;
			for(int i=0;i<20;i++){
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
				for(int i=0;i<20;i++){
					for(int j=0;j<30;j++){
						m[i][j].tipo=lineas[i][j]-'0';
						m[i][j].frame=(m[i][j].tipo==0?4+rnd()%2:m[i][j].tipo==1?6+rnd()%2:8);
					}
				}
				cout<<casa2.toString()<<endl;
				pos=casa2;
				posCasa=casa2;
				dibujar();
				dibujarKibus();
			}
		}

		void guardaMundo(std::string s){
			ofstream f(s.c_str());
			if(!f.good()){
				cout<<"Error al guardar"<<endl;
			}
			for(int i=0;i<20;i++){
				for(int j=0;j<30;j++){
					f.put(m[i][j].tipo+'0');
				}
				f.put('\n');
			}
			f.close();
		}
};

#endif