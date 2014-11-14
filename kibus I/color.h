#include<fstream>
#include<iostream>
#include<cmath>

class color{
	public:
		unsigned char r;
		unsigned char g;
		unsigned char b;
		
		color(){
			r=g=b=0;
		}
		
		color(char x, char y, char z){
			r=x;
			g=y;
			b=z;
		}

		color operator+(color o){
			int rn = r+o.r;
			int gn = g+o.g;
			int bn = b+o.b;
			if(rn > 255)
				rn=255;
			if(gn > 255)
				gn=255;
			if(bn > 255)
				bn=255;
			return color(rn, gn, bn);
		}

		color operator-(color o){
			int rn = r-o.r;
			int gn = g-o.g;
			int bn = b-o.b;
			if(rn < 0)
				rn=0;
			if(gn < 0)
				gn=0;
			if(bn < 0)
				bn=0;
			return color(rn, gn, bn);
		}
		
		inline bool operator==(color o){
			return r==o.r and g==o.g and b==o.b;
		}

		inline bool operator!=(color o){
			return r!=o.r and g!=o.g and b!=o.b;
		}

		color operator*(double s){
			int rn = s*r;
			int gn = s*g;
			int bn = s*b;
			if(rn < 0)
				rn=0;
			if(gn < 0)
				gn=0;
			if(bn < 0)
				bn=0;
			if(rn > 255)
				rn=255;
			if(gn > 255)
				gn=255;
			if(bn > 255)
				bn=255;
			return color(rn,gn,bn);
		}

		color aGris(){
			unsigned char c;
			c=(unsigned char)(0.30*r + 0.59*g + 0.11*b);
			return color(c,c,c);
		}


		unsigned char luz(){
			return (unsigned char)(0.30*r + 0.59*g + 0.11*b);
		}
		
				static color azul;
		static color rojo;
		static color blanco;
		static color verde;
		static color amarillo;
		static color morado;
		static color naranja;
		static color negro;
		static color cyan;
		static color cafe;
		static color rosa;
		static color gris;
};

color color::azul=color(0,0,255);
color color::rojo=color(255,0,0);
color color::blanco=color(255,255,255);
color color::verde=color(0,255,0);
color color::amarillo=color(255,255,0);
color color::morado=color(255,0,255);
color color::cyan=color(0,255,255);
color color::naranja=color(255,128,0);
color color::negro=color(0,0,0);
color color::cafe=color(153,76,0);
color color::rosa=color(255,153,204);
color color::gris=color(127,127,127);


std::istream& operator>>(std::istream& s, color& c){
	if(s==std::cin){
		int r,g,b;
		std::cin>>r;
		std::cin>>g;
		std::cin>>b;
		c.r=r;
		c.g=g;
		c.b=b;
		
	}else{
		c.b=s.get();
		c.g=s.get();
		c.r=s.get();
	}
	return s;
}



std::ostream& operator<<(std::ostream& s, color c){
	if(s==std::cout){
		std::cout<<"("<<(int)c.r<<","<<(int)c.g<<","<<(int)c.b<<")";
	}else{
		s.put(c.b);
		s.put(c.g);
		s.put(c.r);
	}
}

color max(color a, color b){
	color c;
	c.r=(a.r>b.r?a.r:b.r);
	c.g=(a.g>b.g?a.r:b.g);
	c.b=(a.r>b.b?a.b:b.b);
	return c;
}

color min(color a, color b){
	color c;
	c.r=(a.r<b.r?a.r:b.r);
	c.g=(a.g<b.g?a.r:b.g);
	c.b=(a.r<b.b?a.b:b.b);
	return c;	
}

color maxDif(color a, color b){
	return max(a,b)-min(a,b);
}


color hsl(int ang){
	int r, g, b;
	ang%=360;
	switch((ang)/60%6){
		case 0:
			r=(int)floor(255);
			g=int(floor(255*double(ang%60)/60.0));
			b=0;
			break;
		case 1:
			r=(int)floor((255-int(floor(255*double(ang%60)/60.0))));
			g=(int)floor(255);
			b=0;
			break;
		case 2:
			r=0;
			g=(int)floor(255);
			b=int(floor(255*double(ang%60)/60.0));
			break;
		case 3:
			r=0;
			g=(int)floor((255-int(floor(255*double(ang%60)/60.0))));
			b=(int)floor(255);
			break;
		case 4:
			r=int(floor(255*double(ang%60)/60.0));
			g=0;
			b=(int)floor(255);
			break;
		case 5:
			r=(int)floor(255);
			g=0;
			b=(int)floor((255-int(floor(255*double(ang%60)/60.0))));
	}
	return color(r, g, b);
}


	
