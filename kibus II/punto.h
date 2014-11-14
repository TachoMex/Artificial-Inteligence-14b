#ifndef PUNTO_H
#define PUNTO_H

#include<string>
#include<cstdlib>
#include<sstream>
#include<cmath>

using namespace std;

class punto{
	public:
		int x,y;
		punto(int,int);
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
		bool operator==(punto b){
			return x==b.x and y==b.y;
		}
		bool operator!=(punto b){
			return not this->operator==(b);
		}
};

punto::punto(int x ,int y){
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



#endif
