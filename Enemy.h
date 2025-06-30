#include "Base.h"
#include "Unit.h"

class Tower;
class Enemy: public Unit{
    Q_OBJECT
public:
    Enemy(Scene* parent, int i, int j);
    ~Enemy();
    void gridMove();
signals:
    void End();
    void Died();
};