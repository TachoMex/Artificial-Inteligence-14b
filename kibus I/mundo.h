#ifndef MUNDO_H
#define MUNDO_H 
#include "vector.h"
#include "casilla.h"
class mundo{
	private:
		int r, c;
		vector<casilla>* memoria;
	public:
		mundo(){
			r=0;
			c=0;
			memoria=0;
		}
		mundo(int a, int b){
			r=a;
			c=b;
			memoria = new vector<casilla>[r];
			for(int i=0;i<r;i++){
				memoria[i]=vector<casilla>(c);
			}
		}
		mundo(const mundo& o);
		mundo(const vector<casilla>& o);
		vector<casilla>& operator[](int n);
		vector<casilla> operator[](int n) const;
		mundo operator=(const mundo& o);
		~mundo();
		int rows() const;
		int cols() const;
		
};




mundo::mundo(const mundo& o){
	r=o.r;
	c=o.c;
	memoria=new vector<casilla>[r];
	for(int i=0;i<r;i++)
		memoria[i]=o[i];
}

mundo::mundo(const vector<casilla>& o){
	r=1;
	c=o.size();
	memoria =  new vector<casilla>(o);
}

vector<casilla>& mundo::operator[](int n){
	return memoria[n];
}

vector<casilla> mundo::operator[](int n) const{
	return memoria[n];
}

mundo::~mundo(){
	delete[] memoria;
}
int mundo::rows()const{
	return r;
}
int mundo::cols()const{
	return c;
}
mundo mundo::operator=(const mundo& o){
	r=o.r;
	c=o.c;
	memoria=new vector<casilla>[r];
	for(int i=0;i<r;i++)
		memoria[i]=o[i];
	return o;
}




#endif