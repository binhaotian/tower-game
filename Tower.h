#include "Base.h"
#include "Unit.h"

class Enemy;

class Tower: public Unit{
public:
    Tower(Scene* parent, int i, int j);
    ~Tower();
};

class meleeT: public Tower{
public:
    meleeT(Scene* parent, int i, int j);
    ~meleeT();
};