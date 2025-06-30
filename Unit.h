#pragma once
#include "Base.h"
#include "Scene.h"
#include "Entity.h"

class Unit: public Entity{
protected:
    int g_i, g_j; // grid pos
    int maxHP;
public:
    Unit(Scene* parent, int HP=100);
    ~Unit();

    void setPic(string pic);
    void setgPos(int i,int j);
    
    pii getGridPos();
    friend bool uMeet(Unit*a, Unit*b);
};

bool uMeet(pii  a, pii  b);
bool uMeet(Unit*a, Unit*b);
bool uNear(pii  a, pii  b);
bool uNear(Unit*a, Unit*b);