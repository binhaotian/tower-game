#include "Base.h"
#include "Unit.h"

class Enemy;

class Tower: public Unit{
public:
    Tower(Scene* parent, int i, int j);
    ~Tower();

    Enemy* NearEnemy();
    
    void goDie() override;
};

class meleeT: public Tower{
    int damage = 20;
    int HP = 180;
public:
    meleeT(Scene* parent, int i, int j);
    ~meleeT();

    void attack();
};

class rangeT: public Tower{
private:
    int damage = 15;
    int HP = 50;
public:
    rangeT(Scene* parent, int i, int j);
    ~rangeT();

    void addPrefix(string p);
    void attack();
};