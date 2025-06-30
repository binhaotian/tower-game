#include "Base.h"
#include "Unit.h"

class Enemy;

class Tower: public Unit{
public:
    Tower(Scene* parent, int i, int j);
    ~Tower();

    void goDie() override;
};

class meleeT: public Tower{
    int damage = 20;
public:
    meleeT(Scene* parent, int i, int j);
    ~meleeT();

    void attack();
};