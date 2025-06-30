#pragma once
#include "Base.h"
#include "Scene.h"
#include "Entity.h"
#include "HealthBar.h"

class Unit: public Entity{
protected:
    int g_i, g_j; // grid pos
    int maxHP; HealthBar *hb;
    // 词缀
    vector<string> prefix;
    QGraphicsTextItem* ptext;
public:
    Unit(Scene* parent, int HP=100);
    ~Unit();

    void setPic(string pic);
    void setgPos(int i,int j);

    void updateFollows();
    void updateText();

    int getHealth();
    void incHealth(int x);
    void decHealth(int x);
    virtual void goDie() {}
    
    pii getGridPos();
    friend bool uMeet(Unit*a, Unit*b);
};

bool uMeet(pii  a, pii  b);
bool uMeet(Unit*a, Unit*b);
bool uNear(pii  a, pii  b);
bool uNear(Unit*a, Unit*b);