#include "Enemy.h"
#include "Map.h"
#include "Tower.h"

Enemy::Enemy(Scene* parent, int i, int j): Unit(parent)
{
    Entity::setPic(":/enemy.png",110); hb->setMaxHealth(110); hb->setHealth(110);
    setgPos(i,j); show();
    bTimer = new QTimer(nullptr);
}
Enemy::~Enemy(){bTimer->deleteLater();}
void Enemy::attack(Tower* t){
    t->decHealth(damage);
}
void Enemy::freeze(){
    frozen = 1;
    QTimer::singleShot(2000, [this]()->void {frozen=0;});
}
void Enemy::startbleeding(){
    bcnt = 0;
    bTimer->start(50); // 50ms per bleeding
    connect(bTimer, &QTimer::timeout, [this]()->void {
        ++bcnt;
        if (bcnt > btot){
            bTimer->stop();
        }
        else{
            decHealth(3);
        }
    });
}
void Enemy::addPrefix(string p){
    prefix.push_back(p);
    updateText();
    if (p=="Flash") flash=1;
    if (p=="Quick") quick=1;
}
void Enemy::gridMove(){
    if (frozen) return;

    char dir = parent->gridInfo(g_i,g_j).dir;
    pii mov = get_didj(dir);
    int di = mov.first, dj = mov.second;
    int dy = di*grid_size, dx=dj*grid_size;
    pii nx =  parent->nextGrid(getGridPos());
    pii nx2 = parent->nextGrid(nx);

    Entity* nex_who = parent->gridWho(nx.first, nx.second);
    Entity* nx2_who = parent->gridWho(nx2.first, nx2.second);
    Tower *t;
    if (t = dynamic_cast<Tower*>(nex_who)){ // 战斗
        if (flash && nx2_who == nullptr && flash_enable){
            flash_enable = 0;
            di = nx2.first-g_i, dj = nx2.second-g_j;
            g_i+=di; g_j+=dj; moveBy(dj*grid_size, di*grid_size); updateFollows();
            ptr<Enemy> tmp(this);
            QTimer::singleShot(4000, [tmp]()->void {if (tmp) tmp->flash_enable=1;});
        }
        else {
            attack(t); 
            return; // 不穿过
        }
    }
    // 如果前面是敌人, 也不穿过
    if (nex_who == nullptr){ // 空地, 穿过
        if (quick && nx2_who == nullptr && randI(1,100)<=50){
            di = nx2.first-g_i, dj = nx2.second-g_j;
            g_i+=di; g_j+=dj; moveBy(dj*grid_size, di*grid_size); updateFollows();
        }
        else{
            g_i+=di; g_j+=dj; moveBy(dx, dy); updateFollows();
        }
    }

    if (g_j<1){
        emit End();
    }
}
void Enemy::goDie(){
    if (died) return;
    emit Died(); died = 1; 
    QTimer::singleShot(950, [this]()->void {this->deleteLater();});
}