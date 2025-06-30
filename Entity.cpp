#include "Entity.h"

Entity::Entity(Scene* parent): parent(parent) {parent->addEntity(this); this->hide(); setZValue(0);}
Entity::~Entity() {parent->rmvEntity(this);}
void Entity::setPic(string pic, int size) {
    QPixmap pm; pm.load(pic.c_str());
    pm = pm.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(pm);
    setOffset(-pm.width() / 2, -pm.height() / 2);
}