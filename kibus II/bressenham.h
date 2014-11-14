#include <vector>
#include <algorithm>
#include "punto.h"
punto referencia;
int distManhatan(punto a, punto b){
	return abs(a.x-b.x)+abs(a.y-b.y);
}

bool compManhatan(punto a, punto b){
	return distManhatan(referencia, a)<distManhatan(referencia,b);
}
std::vector<punto> rectaBress(int x1, int y1, int x2, int y2){
		referencia = punto(x1,y1);
		std::vector<punto> v;
		v.push_back(punto(x1,y1));
		v.push_back(punto(x2,y2));
		int dx=std::abs(x2-x1);
		int dy=std::abs(y2-y1);
		if(dy==0){
			if(x2<x1)
			std::swap(x1,x2);
			for(;x1<=x2;x1++)
			v.push_back(punto(x1,y1));
		}else if(dx==0){
			if(y1>y2)
			std::swap(y1,y2);
			for(;y1<=y2;y1++)
			v.push_back(punto(x1,y1));
			
		}else if(dx==dy){
			if(x1>x2){
				std::swap(x1,x2);
				std::swap(y1, y2);
			}
			int incremento=(y1<y2?1:-1);
			for(;x1<=x2;x1++,y1+=incremento){
				v.push_back(punto(x1,y1));
			}
		}
		else if(dy<dx){
			if(x1>x2){
				std::swap(x1,x2);
				std::swap(y1, y2);
			}
			int x=x1, y=y1;
			int incremento=(y1<y2?1:-1);
			int p=0;
			p=2*dy-dx;
			while(x!=x2 or y!=y2){
				v.push_back(punto(x,y));
				if(p>=0){
					x++;
					y+=incremento;
					p=p+2*dy-2*dx;
				}else{
					x++;
					p=p+2*dy;
				}
			}
		}else{	
			if(y1>y2){
				std::swap(x1,x2);
				std::swap(y1, y2);
			}
			int y=y1, x=x1;
			int incremento=(x1<x2?1:-1);
			int p=0;
			p=2*dx-dy;
			while(y!=y2 or x!=x2){
				v.push_back(punto(x,y));
				if(p>=0){
					y++;
					x+=incremento;
					p=p+2*dx-2*dy;
				}else{
					y++;
					p=p+2*dx;
				}
			}
		}
		sort(v.begin(), v.end(), compManhatan);
		v.erase(v.begin());
		return v;
}

