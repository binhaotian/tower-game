#include "Entity.h"

class Bullet: public Entity{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Bullet(Scene* parent, string model, QPointF from, QPointF to, int flyTime);
};