#include "Base.h"
#include "Follower.h"

class HealthBar : public Follower{
    Q_OBJECT
protected:
    int maxHealth, curHealth; // 满血, 当前血
    const int barWidth=40, barHeight=6; // 血条长宽
public:
    HealthBar(Scene *parent, Entity* follow, int maxHealth = 100);
    ~HealthBar();

    void drawpic();
    void showDamage(int x);

    int getHealth();
    void setHealth(int value);
    void setMaxHealth(int value);
    bool decHealth(int x);
    void incHealth(int x);
};