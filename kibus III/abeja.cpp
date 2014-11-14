#ifndef ABEJA_H
#include"punto.h"

class abeja{
public:
	int frame;
	punto posicion;
	int temperatura;
	abeja(const punto& p, int t){
		posicion=p;
		frame=9;
		temperatura=t;
	}
	void dibujar();
};
#define ABEJA_H 
#endif