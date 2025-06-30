#include "Base.h"
#include "Unit.h"

class Tower;
class Enemy: public Unit{
    Q_OBJECT
    int damage = 10;
public:
    Enemy(Scene* parent, int i, int j);
    ~Enemy();
    void attack(Tower* t);
    void gridMove();
    void goDie() override;
signals:
    void Died();
    void End();
};