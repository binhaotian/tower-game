#include "Base.h"
#include "Unit.h"

class Enemy;

class Tower: public Unit{
public:
    Tower(Scene* parent, int i, int j);
    ~Tower();
    Enemy* NearEnemy();
    void removePrefix() {if(!prefix.empty()) {prefix.pop_back(); updateText();}}
    void goDie() override;
};

class meleeT: public Tower{
private:
    int damage = 20;
    int HP = 180;
    // 词缀
    bool violent = 0; // 狂暴
    bool icy = 0; // 冰冻
    bool aoe = 0; // 群伤
public:
    meleeT(Scene* parent, int i, int j);
    ~meleeT();

    void addPrefix(string p);
    void attack1(ptr<Enemy> e);
    void attack();
};

class rangeT: public Tower{
private:
    int damage = 15;
    int HP = 50;
    // 词缀
    bool bleeding = 0; // 放血
public:
    rangeT(Scene* parent, int i, int j);
    ~rangeT();

    void addPrefix(string p);
    void attack();
};