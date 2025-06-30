#include "Tower.h"
#include "Enemy.h"

Tower::Tower(Scene* parent, int i, int j): Unit(parent)
{
    setgPos(i,j); hide();
}
Tower::~Tower(){}
void Tower::goDie(){this->deleteLater();}
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

void meleeT::addPrefix(string p){
    if (prefix.size() == 2) return;
    prefix.push_back(p);
    updateText();
    if (p=="Violent") violent=1;
    if (p=="Icy") icy=1;
    if (p=="Aoe") aoe=1;
}
void meleeT::attack1(ptr<Enemy> e){
    // 狂暴: 伤害*2 且 500ms 后再攻击一次 (相当于攻击频率*2)
    int dmg = violent?((int)(damage*1.5)):damage;
    e->decHealth(dmg); if (icy) e->freeze();
    // 冰冻: 冻住敌人 2s
    if (violent) QTimer::singleShot(500, [e,dmg]()->void {if (e) e->decHealth(dmg);});
}
void meleeT::attack(){
    if (!aoe){
        for(auto e:parent->enemyL())if(uNear(this,e)){
            attack1(e);
            return;
        }
    }
    else{
        // 群伤: 扩大攻击范围并且全部能攻击
        for(auto e:parent->enemyL())if(dis(this,e) < 2.5*grid_size){
            attack1(e);
        }
    }
}

rangeT::rangeT(Scene* parent, int i, int j): Tower(parent, i, j) {
    setPic(":/cannon.png"); show();
    hb->setMaxHealth(HP); hb->setHealth(HP);
}
rangeT::~rangeT(){}
void rangeT::addPrefix(string p){
    if (prefix.size() == 2) return;
    prefix.push_back(p);
    updateText();
    if (p=="Bleeding") bleeding=1;
}
void rangeT::attack(){
    puts("range tower attack");
    ptr<Enemy> e(NearEnemy()); if(!e) return;
    QPointF pos = e->pos();
    if (dis(this->pos(),pos) < 500){
        Shoot(parent, "bullet", this->pos(), e->pos(), 150);

        ptr<rangeT> tmp(this);
        QTimer::singleShot(150, [e,tmp]()->void {
            if (!tmp || !e) return;
            e->decHealth(tmp->damage);
            if (tmp->bleeding) e->startbleeding();
        });
    }
}