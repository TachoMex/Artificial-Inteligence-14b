#ifndef KIBUSI_H
#define KIBUSI_H

#include <iostream>
#include "punto.h"
#include "mundo.h"
#include "abeja.cpp"
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <algorithm>


class kibusIII{
	private:
	public:
		int orientacion;
		punto pos;
		punto posAuxiliar;
		int accion;
		punto posAnterior;
		int frames[4];
		mundo m;
		bool volviendo;
		std::vector<abeja> abejas;
		std::vector<punto> plan;

		void calculaCalor(){
			punto posCasa;
			posAuxiliar=pos;
			accion=0;
			for(int i=0;i<m.rows();i++){
				for(int j=0;j<m.cols();j++){
					if(m[i][j].tipo==2)
						posCasa=punto(i,j);
				}
			}
			for(int i=0;i<m.rows();i++){
				for(int j=0;j<m.cols();j++){
					m[i][j].temperatura=max(abs(posCasa.x-i),abs(posCasa.y-j));
				}
			}
			for(int i=0;i<m.rows();i++){
				for(int j=0;j<m.cols();j++){
					printf("%02d ",m[i][j].temperatura);
				}
				printf("\n");
			}
		}

		void dibujarKibus();
		void desdibujarKibus();
		void redibuja(int, int);
		void enfria(int x, int y){
			m[x][y].temperatura++;
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
			if(accion<5){
				for(int i=0;i<abejas.size();i++){
					m[abejas[i].posicion.x][abejas[i].posicion.y].dibujar(abejas[i].posicion.x,abejas[i].posicion.y);
				}
				random_device rnd;
				//cout<<pos.toString()<<endl;
				if(not volviendo){
					volviendo=true;
				}
				enfria(posAuxiliar.x,posAuxiliar.y);
				std::vector<abeja> libres;
				for(int i=-1;i<=1;i++){
					for(int j=-1;j<=1;j++){
						if(i or j){
							int a=posAuxiliar.x+i;
							int b=posAuxiliar.y+j;
							if(a>=0 and a<m.rows() and b>=0 and b<m.cols() and m[a][b].tipo!=1)
								libres.push_back(abeja(punto(a,b),m[a][b].temperatura));
						}
					}
				}
				abejas=std::vector<abeja>();
				for(int i=0;i<5;i++){
					if(not libres.empty()){
						int idx=rnd()%libres.size();
						abejas.push_back(libres[idx]);
						libres.erase(libres.begin()+idx);
					}
				}
				int idx=0;
				for(int i=0;i<abejas.size();i++){
					abejas[i].dibujar();
					if(abejas[i].temperatura<abejas[idx].temperatura){
						idx=i;
					}
				}
				if(abejas[idx].temperatura<m[posAuxiliar.x][posAuxiliar.y].temperatura)
					posAuxiliar=abejas[idx].posicion;
				plan.push_back(posAuxiliar);
				glFlush();
				glutSwapBuffers();
				dibujarKibus();
				accion++;
				//return not plan.empty();
				return volviendo;
			}else{
				desdibujarKibus();
				if(not plan.empty() and camina(plan[0].x-pos.x,plan[0].y-pos.y)){
					plan.erase(plan.begin());
				}else{
					if(not plan.empty())
					enfria(plan[0].x,plan[0].y);
					plan.erase(plan.begin(), plan.end());
					accion=0;
					posAuxiliar=pos;
				}

				dibujarKibus();
				glFlush();
				glutSwapBuffers();
				volviendo=m[pos.x][pos.y].tipo!=2;
				//return not plan.empty();
				return volviendo;
			}
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
				cout<<casa2.toString()<<endl;
				pos=casa2;
				dibujar();
				dibujarKibus();
			}
		}

		void guardaMundo(std::string s){
			ofstream f(s.c_str());
			if(!f.good()){
				cout<<"Error al guardar"<<endl;
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