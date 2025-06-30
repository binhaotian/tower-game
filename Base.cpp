#include "Base.h"
#include "Map.h"
#include "Scene.h"
#include "Entity.h"
#include "Unit.h"
#include "Tower.h"
#include "Enemy.h"

string int2str(int x){char t[12];sprintf(t,"%d",x); return string(t);}

mt19937 rand_gen(time(0));
auto rand01 = uniform_real_distribution<double> (0.0,1.0);
double randF(double l,double r){
	double t = rand01(rand_gen);
	return l+t*(r-l);
}
int randI(int l,int r){
	int ran = rand_gen(); if (ran<0) ran=-ran;
	return ran%(r-l+1)+l;
}

pii get_didj(char dir){
    dir = tolower(dir);
    if (dir=='w') return pii(-1,0);
    if (dir=='a') return pii(0,-1);
    if (dir=='s') return pii(1,0);
    if (dir=='d') return pii(0,1);
    return pii(0,0);
}
pii nextgrid(pii cur, char dir){
    pii d = get_didj(dir);
    return pii(cur.first+d.first, cur.second+d.second);
}

double dis(QPointF A,QPointF B){
    double dx = A.x()-B.x(), dy = A.y()-B.y();
    return sqrt(dx*dx+dy*dy);
}
double dis(Entity* A,Entity* B){
    return dis(A->pos(),B->pos());
}