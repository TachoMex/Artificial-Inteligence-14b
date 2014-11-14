#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

#ifndef NULL 
#define NULL 0
#endif

template<class Tipo>
class vector{
	protected:
		int tam;
		Tipo *memoria;
	public:
		vector<Tipo>();
		vector<Tipo>(int t);
		vector<Tipo>(int t, Tipo *ptr);
		vector<Tipo>(const vector<Tipo>& o);
		Tipo& operator[](int n);
		Tipo operator[](int n) const;
		~vector();
		int size() const;
		vector<Tipo> operator=(const vector<Tipo>& o);
		vector<Tipo> operator+(const vector<Tipo>& o);
		vector<Tipo> operator+=(const vector<Tipo>& o);
		vector<Tipo> operator-(const vector<Tipo>& o);
		vector<Tipo> operator-=(const vector<Tipo>& o);
		vector<Tipo> operator*(Tipo);
		vector<Tipo> operator*=(Tipo);
};

template<class Tipo>
std::ostream& operator<<(std::ostream& s, const vector<Tipo>& v){
	s<<"[ "<<v[0];
	for(int i=1;i<v.size();i++)
		s<<" "<<v[i];
	s<<" ]";
	return s;
}

template<class Tipo>
std::istream& operator>>(std::istream& s, vector<Tipo>& v){
	int n;
	s>>n;
	v=vector<Tipo>(n);
	for(int i=0;i<n;i++)
		s>>v[i];
	return s;
}



template<class Tipo>
vector<Tipo>::vector(){
	tam=0;
	memoria=NULL;
}

template<class Tipo>
vector<Tipo>::vector(int t){
	tam=t;
	memoria=new Tipo[tam];
}


template<class Tipo>
vector<Tipo>::vector(int t, Tipo *ptr){
	memoria = new Tipo[t];
	tam=t;
	for(int i=0;i<tam;i++)
		memoria[i]=ptr[i];
}

template<class Tipo>
vector<Tipo>::vector(const vector<Tipo>& o){
	tam=o.tam;
	memoria = new Tipo[tam];
	for(int i=0;i<tam;i++){
		memoria[i]=o.memoria[i];
	}
}

template<class Tipo>
Tipo& vector<Tipo>::operator[](int n){		
	return memoria[n];
}

template<class Tipo>
Tipo vector<Tipo>::operator[](int n) const{
	return memoria[n];
}

template<class Tipo>
vector<Tipo>::~vector(){
	delete memoria;
}


template<class Tipo>
int vector<Tipo>::size() const{
	return tam;
}

template<class Tipo>
vector<Tipo> vector<Tipo>::operator=(const vector<Tipo>& o){
	if(memoria!=NULL)
		delete memoria;
	tam=o.tam;
	memoria = new Tipo[tam];
	for(int i=0;i<tam;i++){
		memoria[i]=o.memoria[i];
	}
	return o;	
}
template<class Tipo>
vector<Tipo> vector<Tipo>::operator+(const vector<Tipo>& o){
	if(tam!=o.tam)
		return vector<Tipo>();
	vector<Tipo> ret(tam);
	for(int i=0;i<tam;i++)
		ret[i]=memoria[i]+o.memoria[i];
	return ret;
}

template<class Tipo>
vector<Tipo> vector<Tipo>::operator+=(const vector<Tipo>& o){
	if(tam!=o.tam){
		*this = vector<Tipo>();
		return *this;
	}
	for(int i=0;i<tam;i++)
		memoria[i]+=o.memoria[i];
	return *this;
}

template<class Tipo>
vector<Tipo> vector<Tipo>::operator-(const vector<Tipo>& o){
	if(tam!=o.tam)
		return vector<Tipo>();
	vector<Tipo> ret(tam);
	for(int i=0;i<tam;i++)
		ret[i]=memoria[i]-o.memoria[i];
	return ret;
}

template<class Tipo>
vector<Tipo> vector<Tipo>::operator-=(const vector<Tipo>& o){
	if(tam!=o.tam){
		*this = vector<Tipo>();
		return *this;
	}
	for(int i=0;i<tam;i++)
		memoria[i]-=o.memoria[i];
	return *this;
}

template<class Tipo>
vector<Tipo> vector<Tipo>::operator*(Tipo k){
	vector<Tipo> ret(tam);
	for(int i=0;i<tam;i++)
		ret[i]=memoria[i]*k;
	return ret;
}

template<class Tipo>
vector<Tipo> vector<Tipo>::operator*=(Tipo k){
	for(int i=0;i<tam;i++)
		memoria[i]*=k;
	return *this;
}

double dot(vector<double> a, vector<double> b){
	if(a.size()!=b.size())
		return NAN;
	double k=0;
	for(int i=0;i<a.size();i++)
		k+=a[i]*b[i];
	return k;
}

double norm2(vector<double> v){
	return dot(v,v);
}

double norm(vector<double> v){
	return sqrt(dot(v,v));
}

#endif