#include "Scene.h"
#include "Enemy.h"
#include "Tower.h"

Scene::Scene(): QGraphicsScene(nullptr)
{
    mp=new Map(this);
    mp->Load("../test.map");
    mp->Draw();
}
Scene::~Scene(){
    mp->deleteLater();
}
// map
mapnode Scene::gridInfo(int i,int j) {return mp->M[i][j];}
vector<pii> Scene::startpos() {
    vector<pii> pos; int n=mp->n, m=mp->m;
    for(int i=1;i<=n;i++) for(int j=1;j<=m;j++)if(gridInfo(i,j).start) pos.push_back(pii(i,j));
    return pos;
}
pii Scene::whichGrid(double x,double y){
    x-=mp->offset_x; y-=mp->offset_y;
    if (!mapBound().in(x,y)) return pii(-1,-1);
    int i = ceil(y/grid_size)+0.0001, j = ceil(x/grid_size)+0.0001;
    return pii(i,j);
}
// list get&modify

void Scene::addEntity(Entity* e){
    addItem(e);
    enL.push_back(e);
}
void Scene::rmvEntity(Entity* e){
    removeItem(e);
    auto it = find(enL.begin(),enL.end(),e); if (it!=enL.end()) enL.erase(it);
}
vector<Enemy*> Scene::enemyL(){
    vector<Enemy*> ans; Enemy* e;
    for(auto x:enL)if (e=dynamic_cast<Enemy*>(x)) ans.push_back(e);
    return ans;
}
vector<Tower*> Scene::towerL(){
    vector<Tower*> ans; Tower* t;
    for(auto x:enL)if (t=dynamic_cast<Tower*>(x)) ans.push_back(t);
    return ans;
}
Entity* Scene::gridWho(int i,int j){
    auto enL = enemyL();
    auto twL = towerL();
    for(auto e:enL) if (e->getGridPos() == pii(i,j)) return e;
    for(auto t:twL) if (t->getGridPos() == pii(i,j)) return t;
    return nullptr;
}