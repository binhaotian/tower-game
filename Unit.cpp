#include "Unit.h"

Unit::Unit(Scene* parent,int HP): Entity(parent),maxHP(HP) {
    hb = new HealthBar(parent, this, HP);
}
Unit::~Unit() {
    hb->deleteLater();
}
void Unit::setPic(string pic) {
    Entity::setPic(pic, 80);
}
void Unit::setgPos(int i,int j){
    g_i=i; g_j=j;
    pii t=parent->gridPosMid(i,j);
    setPos(t.first, t.second);
}

void Unit::updateFollows(){
    hb->updatePosition();
}

pii Unit::getGridPos() {return pii(g_i,g_j);}

int Unit::getHealth() {return hb->getHealth();}
void Unit::incHealth(int x) {hb->incHealth(x);}
void Unit::decHealth(int x) {bool die = hb->decHealth(x); if (die) goDie();}

bool uMeet(pii  a, pii  b){return a.first==b.first && a.second == b.second;}
bool uMeet(Unit*a, Unit*b){return uMeet(a->getGridPos(),b->getGridPos());}
bool uNear(pii  a, pii  b){return abs(a.first-b.first)+abs(a.second-b.second) == 1;}
bool uNear(Unit*a, Unit*b){return uNear(a->getGridPos(),b->getGridPos());}