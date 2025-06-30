#include "Enemy.h"
#include "Map.h"
#include "Tower.h"

Enemy::Enemy(Scene* parent, int i, int j): Unit(parent)
{
    Entity::setPic(":/enemy.png",110);
    setgPos(i,j); show();
}
Enemy::~Enemy(){

}

void Enemy::gridMove(){
    char dir = parent->gridInfo(g_i,g_j).dir;
    pii mov = get_didj(dir);
    int di = mov.first, dj = mov.second;
    int dy = di*grid_size, dx = dj*grid_size;
    pii nx =  parent->nextGrid(getGridPos()); Entity* who = parent->gridWho(nx.first, nx.second);
    
    if (dynamic_cast<Tower*>(who)){
        this -> deleteLater();
    }
    else{
        g_i+=di; g_j+=dj; moveBy(dx, dy);
    }
}