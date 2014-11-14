#ifndef GRAFO_H
#define GRAFO_H 

#include <map>
#include "punto.h"
class nodo;
class conexion;

class nodo{
	public:
		conexion *hilos[8];	
		nodo(){
			hilos[0]=hilos[1]=hilos[2]=hilos[3]=hilos[4]=hilos[5]=hilos[6]=hilos[7]=nullptr;
		}
};


class conexion{
	public:
		nodo* globo;
		int peso;
};


class grafo{
	public:
		std::map<punto,nodo*> nodos;
		grafo(){
		}
		void ajustaPesos(const punto& a, const punto& b, int peso){
			if(nodos.count(a)==0){
				nodos[a]=new nodo();
			}
			if(nodos.count(b)==0){
				nodos[b]=new nodo();
			}
			int dx=a.x-b.x+1;
			int dy=a.y-b.y+1;
			int idx=dx*3+dy;
			idx-=idx>3;
			if(nodos[a]->hilos[idx]==nullptr){
				nodos[a]->hilos[idx]=new conexion();
				nodos[a]->hilos[idx]->globo=nodos[b];
			}
			nodos[a]->hilos[idx]+=peso;
		}

		punto mejor(const punto& a){
			std::cout<<"Mejor"<<std::endl;
			nodo* desde = nodos[a];
			conexion * mejor=nullptr;
			int idx;
			for(int i=0;i<8;i++){
				if(desde->hilos[i]!=nullptr){
					if(mejor==nullptr){
						mejor=desde->hilos[i];
						idx=i;
					}else if(mejor->peso<desde->hilos[i]->peso){
						mejor=desde->hilos[i];
						idx=i;
					}
				}
			}	
			std::cout<<idx<<std::endl;
			idx+=idx>=4;
			int dx=idx/3-1;
			int dy=idx%3-1;
			return punto(dx,dy)+a;
		}

};

#endif
