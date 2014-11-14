#include<cstring>
#include"color.h"
#include<GL/freeglut.h>
#include<GL/gl.h>
class imagen{
	private:
		color*pixels;
		int x, y;
	public:
		imagen(int a, int b){
			x=a;
			y=b;
			pixels= new color[x*y];
		}
		
		imagen(){
			pixels=NULL;
			x=y=0;
		}
		
		imagen(const imagen &i){
			x=i.x;
			y=i.y;
			pixels=new color[x*y];
			memcpy(pixels,i.pixels, x*y);
		}
		
		int filas(){
			return y;
		}
		
		int columnas(){
			return x;
		}
		
		color& en(int i, int j){
			if(i < 0 or i >= y or j < 0 or j >= x )
				throw 0;
			//std::cout<<i*x+j<<std::endl;
			return pixels[i*x+j];
		}
		
		imagen escalaDeGrises(){
			imagen ret(x,y);
			for(int i=0;i<y;i++)
				for(int j=0;j<x;j++)
					ret.en(i,j) = en(i,j).aGris();
			return ret;
		}

		imagen derivadax(){
			imagen ret(x,y);
			for(int i=0;i<y;i++){
				ret.en(i,0)=en(i,0);
				for(int j=1;j<x;j++)
					ret.en(i,j) =maxDif(en(i,j),en(i,j-1));
			}
			return ret;
		}

		imagen derivaday(){
			imagen ret(x,y);
			for(int i=0;i<x;i++){
				ret.en(0,i)=en(0,i);
				for(int j=1;j<y;j++)
					ret.en(j,i) = maxDif(en(j,i),en(j-1,i));
			}
			return ret;
		}

		imagen derivada(){
			imagen dx=derivadax();
			imagen dy=derivaday();
			imagen ret(x,y);

			for(int i=0;i<y;i++){
				for(int j=0;j<x;j++)
					ret.en(i,j) =max(dx.en(i,j),dy.en(i,j));
			}
			return ret;
		}


		imagen umbral(unsigned char min=128, color down=color()){
			imagen ret(x,y);
			for(int i=0;i<y;i++)
				for(int j=0;j<x;j++)
					ret.en(i,j) = (en(i,j).luz()>min?en(i,j):down);
			return ret;
		}

		imagen umbral(unsigned char min, color down, color up){
			imagen ret(x,y);
			for(int i=0;i<y;i++)
				for(int j=0;j<x;j++)
					ret.en(i,j) = (en(i,j).luz()>min?up:down);
			return ret;
		}

		void copiar(int h, int k, imagen &o){
			for(int i=0;i<o.y;i++)
				for(int j=0;j<o.x;j++){
					int p,q;
					p=h+i;
					q=k+j;
					try{
						en(p,q) = o.en(i,j);
					}catch(int e){
					
					}
				}
		}
		
		void drawAt(int h, int k){
			for(int i=0;i<y;i++)
				for(int j=0;j<x;j++){
					int p,q;
					p=h+i;
					q=k+j;
					try{
						color c=en(i,j);
						glColor3ub(c.r,c.g,c.b);
						glBegin(GL_QUADS);
							glVertex2i(q, p);
							glVertex2i(q, p+1);
							glVertex2i(q+1, p+1);
							glVertex2i(q+1, p);
						glEnd();
					}catch(int e){
					}
				}
				glFlush();
		}
		
		~imagen(){
			delete pixels;
		}
		
		imagen operator=(imagen i){
			delete pixels;
			x=i.x;
			y=i.y;
			pixels=new color[x*y];
			memcpy(pixels,i.pixels, x*y);
			return i;
		}

		
		imagen filtroMatriz(double coeficientes[3][3]){
			imagen ret(x,y);
			for(int i=0;i<y;i++){
				for(int j=0;j<x;j++){
					double sr=0;
					double sg=0;
					double sb=0;
					for(int k=-1;k<2;k++)
						for(int l=-1;l<2;l++){
							try{
								color aux=en(i+k,j+l);
								sr+=(double)aux.r*coeficientes[k+1][l+1];
								sg+=(double)aux.g*coeficientes[k+1][l+1];
								sb+=(double)aux.b*coeficientes[k+1][l+1];
							}catch(int e){
							}
						}

					if(sr>255)
						sr=255;
					if(sr<0)
						sr=0;
					if(sg>255)
						sg=255;
					if(sg<0)
						sg=0;
					if(sb>255)
						sb=255;
					if(sb<0)
						sb=0;
					ret.en(i,j) = color(sr,sg,sb);
				}
				//ret.guardaBMP("filtro.bmp");
			}
			return ret;
		}

		imagen filtroGauss(){
			double coeficientes[3][3]={
				{1.0/21,1.0/7,1.0/21},
				{1.0/7,5.0/21,1.0/7},
				{1.0/21,1.0/7,1.0/21}
			};
			return filtroMatriz(coeficientes);	
		}

		imagen filtroAfilador(){
			double coeficientes[3][3]={
			 {  0, -1,  0},
    		 {-1,  5, -1},
     		 {	0, -1,  0 }
     		};
     		return filtroMatriz(coeficientes);
		}

		imagen filtroMediana(){
			double coeficientes[3][3]={
				{1.0/9.0,1.0/9.0,1.0/9.0},
				{1.0/9.0,1.0/9.0,1.0/9.0},
				{1.0/9.0,1.0/9.0,1.0/9.0}
			};
			return filtroMatriz(coeficientes);
		}

		imagen erosionar(){
			imagen ret(x,y);
			int dx[] = {1,-1,0,0};
			int dy[] = {0,0,1,-1};
			for(int i=0;i<y;i++)
				for(int j=0;j<x;j++){
					color c=en(i,j);
					for(int k=0;k<4;k++){
						try{
							color z=en(i+dy[k],j+dx[k]);
							c=min(c,z); 
						}catch(int e){

						}
					}
					ret.en(i,j) = c;
				}
			return ret;
		}

		imagen dilatar(){
			imagen ret(x,y);
			int dx[] = {1,-1,0,0};
			int dy[] = {0,0,1,-1};
			for(int i=0;i<y;i++)
				for(int j=0;j<x;j++){
					color c=en(i,j);
					for(int k=0;k<4;k++){
						try{
							color z=en(i+dy[k],j+dx[k]);
							c=max(c,z); 
						}catch(int e){

						}
					}
					ret.en(i,j) = c;
				}
			return ret;
		}

		imagen laplace(){
			double coeficientes[3][3]={
			 {  -1, -1,  -1},
    		 {-1,  8, -1},
     		 {	-1, -1,  -1 }
     		};
     		return filtroMatriz(coeficientes);
		}

		void guardaBMP(const char *nombre){
			std::ofstream f(nombre);
			f.put('B'); f.put('M'); //Tipo
			int tam=54+x*y;
			f.write((char*)&tam,sizeof(int)); 
			int reservado=0;
			f.write((char*)&reservado,sizeof(int));  
			int offset=0x36;
			f.write((char*)&offset,sizeof(int));  
			int tamCabeceras=40;
			f.write((char*)&tamCabeceras,sizeof(int));
			f.write((char*)&(x),sizeof(int)); //ancho
			f.write((char*)&(y),sizeof(int)); //alto
			short planos=1;
			f.write((char*)&planos,sizeof(short));
			short bits=24;
			f.write((char*)&bits,sizeof(short));
			int compresion=0;
			f.write((char*)&compresion,sizeof(int));
			f.put(0); f.put(0); f.put(0); f.put(0); //Tamaño Paleta
			f.put(0); f.put(0); f.put(0); f.put(0); //BitsPorMetroX
			f.put(0); f.put(0); f.put(0); f.put(0); //BitsPorMetroY
			f.put(0); f.put(0); f.put(0); f.put(0); //Colores Usados
			f.put(0); f.put(0); f.put(0); f.put(0); //Colores Importantes
			int ajuste=(4-(x*3)%4)%4;
			//std::cout<<f.tellp()<<std::endl;
			for(int i=0;i<y;i++){
				for(int j=0;j<x;j++)
					try{f<<en(i,j);}catch(int t){f<<color();}
				for(int j=0;j<ajuste;j++)
					f<<color();
			}
			f.close();
		}
		
		void leerBMP(const char *nombre){
			delete pixels;
			std::ifstream f(nombre);
			if(f.get()!='B' or f.get()!='M'){
				std::cout<<"No es BMP"<<std::endl;
			}
			int tam;
			f.read((char*)&tam,sizeof(int));
			f.get(); f.get(); f.get(); f.get(); //Reservado
			f.get(); f.get(); f.get(); f.get(); //Offset
			f.get(); f.get(); f.get(); f.get(); //Tamaño cabecera
			f.read((char*)&x,sizeof(int)); //x++;
			f.read((char*)&y,sizeof(int)); //y++;
			f.get(); f.get(); //Planos
			short bits;
			f.read((char*)&bits,sizeof(short));
			f.get(); f.get(); f.get(); f.get(); //Compresion
			f.get(); f.get(); f.get(); f.get(); //Tamaño Paleta
			f.get(); f.get(); f.get(); f.get(); //BitsPorMetroX
			f.get(); f.get(); f.get(); f.get(); //BitsPorMetroY
			f.get(); f.get(); f.get(); f.get(); //Colores Usados
			f.get(); f.get(); f.get(); f.get(); //Colores Importantes
			pixels=new color[x*y];
			int ajuste=(4-(x*3)%4)%4;
			f.seekg(-((x+ajuste)*y*3),f.end);
			for(int i=0;i<y;i++){
				for(int j=0;j<x;j++){
					//std::cout<<x-j<<std::endl;
					f>>en(i,j);
				}
				for(int j=0;j<ajuste;j++)
					f.get();
			}
			f.close();
		}
		
		imagen region(int p, int q, int h, int k, imagen& r){
			delete r.pixels;
			r.x=h;
			r.y=k;
			r.pixels = new color[h*k];
			
			for(int i=0;i<k;i++)
				for(int j=0;j<h;j++)
					try{
						r.en(i,j) = en(q+i,p+j);
					}catch(int e){
					}
			
			
			return r;
		}

		
		imagen region(int p, int q, int h, int k){
			imagen r;
			r.x=h;
			r.y=k;
			r.pixels = new color[h*k];
			
			for(int i=0;i<k;i++)
				for(int j=0;j<h;j++)
					try{
						r.en(i,j) = en(q+i,p+j);
					}catch(int e){
					}
			
			
			return r;
		}


		void read(){
			delete pixels;
			x=glutGet(GLUT_WINDOW_WIDTH);
			y=glutGet(GLUT_WINDOW_HEIGHT);
			pixels = new color[x*y];
			glReadPixels(0,0,x,y,GL_RGB,GL_UNSIGNED_BYTE,pixels);
		}

		void read(int x2, int y2){
			delete pixels;
			x=x2;
			y=y2;
			pixels = new color[x*y];
			glReadPixels(0,0,x,y,GL_RGB, GL_UNSIGNED_BYTE, pixels);

		}
		
		void draw(){
			glDrawPixels(x,y,GL_RGB,GL_UNSIGNED_BYTE, pixels);
		}
};

void glColor(color c){
	glColor3ub(c.r,c.g,c.b);
}
