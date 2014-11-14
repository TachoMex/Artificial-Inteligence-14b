#ifndef PUNTO_H
#define PUNTO_H

#include <string>
#include <cstdlib>
#include <cmath>


class punto{
	public:
		int x,y;
		punto(int,int);
		punto();
		std::string toString();
		punto operator+(const punto& b)const{
			return punto(x+b.x, y+b.y);
		}
		punto operator+=(const punto& b){
			*this=*this+b;
			return *this;
		}
		punto operator-(const punto& b)const{
			return punto(x-b.x, y-b.y);
		}
		punto operator-=(const punto& b){
			*this=*this-b;
			return *this;
		}
		bool operator==(const punto& b)const {
			return x==b.x and y==b.y;
		}
		bool operator!=(const punto& b)const {
			return not this->operator==(b);
		}
		bool operator<(const punto& b)const {
			return (x==b.x?y<b.y:x<b.x);
		}
};

punto::punto(int x ,int y){
	this->x=x;
	this->y=y;
}

punto::punto(){
	this->x=this->y=0;
}
std::string punto::toString(){
	std::string ret="";
	ret+='(';
	ret+=std::to_string(this->x);
	ret+=',';
	ret+=std::to_string(this->y);
	ret+=')';
	return ret;
}

#if __cplusplus <= 199711L
#endif



#endif
