#include "Tower.h"
#include "Enemy.h"

Tower::Tower(Scene* parent, int i, int j): Unit(parent)
{
    setgPos(i,j); hide();
}
Tower::~Tower(){
    
}
void Tower::goDie(){
    this->deleteLater();
}

meleeT::meleeT(Scene* parent, int i, int j): Tower(parent, i, j) {
    setPic(":/tower.png"); show();
}
meleeT::~meleeT(){}
void meleeT::attack(){
    for(auto e:parent->enemyL())if(uNear(this,e)){
        e->decHealth(damage);
        return;
    }
}