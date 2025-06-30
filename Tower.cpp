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
Enemy* Tower::NearEnemy(){
    double min_d = 0.00; Enemy* min_e = nullptr;
    for(auto e:parent->enemyL())if((min_e==nullptr or dis(e,this)<min_d)){
        min_d = dis(e,this);
        min_e = e;
    }
    return min_e;
}

meleeT::meleeT(Scene* parent, int i, int j): Tower(parent, i, j) {
    setPic(":/tower.png"); show();
    hb->setMaxHealth(HP); hb->setHealth(HP);
}
meleeT::~meleeT(){}
void meleeT::attack(){
    for(auto e:parent->enemyL())if(uNear(this,e)){
        e->decHealth(damage);
        return;
    }
}

rangeT::rangeT(Scene* parent, int i, int j): Tower(parent, i, j) {
    setPic(":/cannon.png"); show();
    hb->setMaxHealth(HP); hb->setHealth(HP);
}
rangeT::~rangeT(){

}
void rangeT::attack(){
    puts("range tower attack");
    ptr<Enemy> e(NearEnemy()); if(!e) return;
    QPointF pos = e->pos();
    if (dis(this->pos(),pos) < 500){
        Shoot(parent, "bullet", this->pos(), e->pos(), 150);

        ptr<rangeT> tmp(this);
        // 这个是为了防止自己过会死了
        QTimer::singleShot(150, [e,tmp]()->void {
            if (!tmp || !e) return;
            e->decHealth(tmp->damage);
        });
    }
}