#ifndef PUNTO_H
#define PUNTO_H

#include<string>
#include<cstdlib>
#include<sstream>
#include<cmath>

using namespace std;

class punto{
	public:
		double x,y;
		punto(double,double);
		punto();
		string toString();
		punto operator+(punto b){
			return punto(x+b.x, y+b.y);
		}
		punto operator+=(punto b){
			*this=*this+b;
			return *this;
		}
		punto operator-(punto b){
			return punto(x-b.x, y-b.y);
		}
		punto operator-=(punto b){
			*this=*this-b;
			return *this;
		}
		punto operator*(double r){
			return punto(x*r, y*r);
		}
		double angulo(){
			return atan2(y, x);
		}
		double radio();
};

punto::punto(double x ,double y){
	this->x=x;
	this->y=y;
}

punto::punto(){
	this->x=this->y=0;
}

string punto::toString(){
	string ret="";
	ret+='(';
	ret+=to_string(this->x);
	ret+=',';
	ret+=to_string(this->y);
	ret+=')';
	return ret;
}

double distancia(punto a, punto b){
	double dx= std::abs(a.x-b.x);
	double dy= std::abs(a.y-b.y);
	return sqrt( dx*dx - dy*dy);
}

double punto::radio(){
	return sqrt(x*x+y*y);
}

#endif
