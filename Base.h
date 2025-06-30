#pragma once
#include <bits/stdc++.h>

#include <QApplication>
#include <QObject>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QElapsedTimer>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QtMath>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QGraphicsTextItem>
#include <QPointer>

using namespace std;

#define ptr QPointer
typedef pair<int,int> pii;
class Entity;

const int grid_size = 135;

string int2str(int x);

double randF(double l,double r);
int    randI(int l,   int r);
template<typename T>
T randPick(const vector<T>&v) {int n=v.size();int i=randI(0,n-1); return v[i];}

struct bRect{
    int xl,yl,xr,yr; 
    bRect(){xl=yl=xr=yr=0;} 
    bRect(int xl,int yl,int xr,int yr):xl(xl),yl(yl),xr(xr),yr(yr){}
    bool in(int x,int y){return (xl<=x && x<=xr) && (yl<=y && y<=yr);}
};

pii get_didj(char dir);
pii nextgrid(pii cur, char dir);

double dis(QPointF A,QPointF B);
double dis(Entity* A,Entity* B);

template<typename T> T fit_in(T a, T l, T r){return min(max(a,l),r);}

class Scene;
void Shoot(Scene* parent, string model, QPointF From, QPointF To, int flytime);