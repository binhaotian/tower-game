#include "Follower.h"

Follower::Follower(Scene* parent, Entity* follow): Entity(parent), follow(follow) {}
Follower::Follower(Scene* parent, Entity* follow,int dx,int dy): Entity(parent), follow(follow), dx(dx), dy(dy) {}

void Follower::updatePosition(){
    if (!follow) return;

    QPointF fpos = follow->pos();
    setPos(fpos.x()+dx, fpos.y()+dy);
    update();
}