#ifndef MATRIX_H
#define MATRIX_H 

#include"vector.h"

class matrix{
	private:
		int r,c;
		vector<double> *memoria;
	public:
		matrix();
		matrix(int a,int b);
		matrix(const matrix& o);
		matrix(const vector<double>& o);
		vector<double>& operator[](int n);
		vector<double> operator[](int n) const;
		~matrix();
		int rows() const;
		int cols() const;
		matrix operator=(const matrix& o);
		matrix operator+(const matrix& o)const;
		matrix operator+=(const matrix& o);
		matrix operator-(const matrix& o)const;
		matrix operator-=(const matrix& o);
		matrix operator*(double)const;
		matrix operator*=(double);
		matrix operator*(const matrix& o)const;
		matrix operator*=(const matrix& o);
};

std::ostream& operator<<(std::ostream& s, const matrix& m){
	if(m.rows()==0){
		s<<"NULL";
	}else{
	for(int i=0;i<m.rows();i++)
		s<<"|"<<m[i]<<"|"<<std::endl;
	}
	return s;
}

std::istream& operator>>(std::istream& s, matrix& m){
	int r, c;
	s>>r>>c;
	m=matrix(r,c);
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			s>>m[i][j];
	return s;
}

matrix::matrix(){
	memoria=NULL;
	r=0;
	c=0;
}

matrix::matrix(int a,int b){
	r=a;
	c=b;
	memoria=new vector<double>[r];
	for(int i=0;i<r;i++)
		memoria[i]=vector<double>(c);
}

matrix::matrix(const matrix& o){
	r=o.r;
	c=o.c;
	memoria=new vector<double>[r];
	for(int i=0;i<r;i++)
		memoria[i]=o[i];
}

matrix::matrix(const vector<double>& o){
	r=1;
	c=o.size();
	memoria =  new vector<double>(o);
}

vector<double>& matrix::operator[](int n){
	return memoria[n];
}

vector<double> matrix::operator[](int n) const{
	return memoria[n];
}

matrix::~matrix(){
	delete memoria;
}
int matrix::rows()const{
	return r;
}
int matrix::cols()const{
	return c;
}
matrix matrix::operator=(const matrix& o){
	r=o.r;
	c=o.c;
	memoria=new vector<double>[r];
	for(int i=0;i<r;i++)
		memoria[i]=o[i];
	return o;
}
matrix matrix::operator+(const matrix& o)const{
	matrix ret(r,c);
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			ret[i][j]=memoria[i][j]+o[i][j];
	return ret;
}
matrix matrix::operator+=(const matrix& o){
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			memoria[i][j]+=o[i][j];
	return *this;
}
matrix matrix::operator-(const matrix& o)const{
	matrix ret(r,c);
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			ret[i][j]=memoria[i][j]-o[i][j];
	return ret;
}
matrix matrix::operator-=(const matrix& o){
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			memoria[i][j]-=o[i][j];
	return *this;
}
matrix matrix::operator*(double k)const{
	matrix ret(r,c);
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			ret[i][j]=memoria[i][j]*k;
	return ret;
}
matrix matrix::operator*=(double k){
	for(int i=0;i<r;i++)
		for(int j=0;j<c;j++)
			memoria[i][j]*=k;
	return *this;
}
matrix matrix::operator*(const matrix& o)const{
	if(cols()!=o.rows())
		return matrix();
	matrix ret(rows(), o.cols());
	for(int k=0;k<ret.rows();k++){ 
		for(int j=0;j<ret.cols();j++){ 
			ret[k][j]=0;
			for (int i=0;i<cols();i++){
				ret[k][j]+=memoria[k][i]*o[i][j];
			}
		}
	}
	return ret;
}
matrix matrix::operator*=(const matrix& o){
	return *this=this->operator*(o);
}


matrix cofactor(const matrix& m, int ai, int aj){
	if(m.rows()!=m.cols() or ai<0 or aj<0 or ai>m.rows() or aj>m.rows())
		return matrix();
	matrix ret(m.rows()-1,m.cols()-1);
	for(int i=0;i<m.rows();i++){
		for(int j=0;j<m.cols();j++){
			if(ai!=i and aj!=j){
				ret[(i>ai?i-1:i)][(j>aj?j-1:j)]=m[i][j];
			}
		}
	}
	return ret;
}

double det(const matrix& m){
	if(m.rows()!=m.cols())
		return NAN;
	if(m.rows()==1){
		return m[0][0];
	}else{
		double ans=0.0;
		double x=1;
		for(int i=0;i<m.rows();i++){
			ans+=m[0][i]*det(cofactor(m,0,i))*x;
			x*=-1;
		}
		return ans;
	}
}

matrix cofactores(const matrix& m){
	if(m.rows()!=m.cols())
		return matrix();
	matrix ret(m.rows(),m.rows());
	for(int i=0;i<m.rows();i++){
		for(int j=0;j<m.cols();j++){
			ret[i][j]=det(cofactor(m,i,j))*((i+j)%2?-1:1);
		}
	}
	return ret;
}

matrix transpose(const matrix& m){
	matrix ret(m.cols(),m.rows());
	for(int i=0;i<ret.rows();i++)
		for(int j=0;j<ret.cols();j++)
			ret[i][j]=m[j][i];
	return ret;
}


matrix adj(const matrix& m){
	return transpose(cofactores(m));
}

matrix inverse(const matrix& m){
	return adj(m)*(1.0/det(m));
}

matrix lpse_inv(const matrix& m){
	matrix t=transpose(m);
	matrix tm=t*m;
	return inverse(tm)*t;
}

matrix rpse_inv(const matrix& m){
	matrix t = transpose(m);
	matrix mt=m*t;
	return t*inverse(mt);
}

#endif
