#pragma once
#include "Base.h"
#include "Map.h"

class Map; struct mapnode;
class Entity; class Unit; class Enemy; class Tower;

class Scene: public QGraphicsScene{
    Map* mp;
    vector<Entity*> enL; // entity list
public:
    Scene();
    ~Scene();
    // map
    bRect mapBoundij() {return bRect(1,1,mp->n,mp->m);}
    bRect mapBound() {return bRect(1,1,(mp->m)*grid_size,(mp->n)*grid_size);}
    mapnode gridInfo(int i,int j);
    pii gridPos(int i,int j) {return mp->gridPos(i,j);}
    pii gridPosMid(int i,int j) {return mp->gridPosMid(i,j);}
    pii whichGrid(double x,double y);
    pii nextGrid(pii pos) {return nextgrid(pos,gridInfo(pos.first, pos.second).dir);}
    vector<pii> startpos();
    // list get&modify
    void addEntity(Entity* e);
    void rmvEntity(Entity* e);
    vector<Enemy*> enemyL(); // alive enemies
    vector<Tower*> towerL(); // alive towers
    Entity* gridWho(int i,int j);
};