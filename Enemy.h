#include "Base.h"
#include "Unit.h"

class Tower;
class Enemy: public Unit{
    Q_OBJECT
private:
    int damage = 10;
    bool died = 0;
    bool frozen = 0; // 被冰冻
    QTimer *bTimer; int bcnt=0; int btot=10;
    // 词缀
    bool flash = 0; bool flash_enable = 1;
    bool quick = 0;
public:
    Enemy(Scene* parent, int i, int j);
    ~Enemy();
    void attack(Tower* t);
    void freeze();
    void startbleeding();
    void addPrefix(string p);
    void gridMove();
    void goDie() override;
signals:
    void End();
    void Died();
};