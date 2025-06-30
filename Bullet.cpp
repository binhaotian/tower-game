#include "Bullet.h"

Bullet::Bullet(Scene* parent, string model, QPointF from, QPointF to, int flyTime)
:Entity(parent) 
{
    if (model == "bullet") {setPic(":/bullet.png", 20);}
    else {puts("model not found"); return;}

    setPos(from); show();

    auto *anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(flyTime);
    anim->setStartValue(from);
    anim->setEndValue(to);
    anim->setEasingCurve(QEasingCurve::Linear);

    connect(anim, &QPropertyAnimation::finished, [=]() {
        parent->rmvEntity(this);
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}