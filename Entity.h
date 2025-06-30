#pragma once
#include "Base.h"
#include "Scene.h"

class Entity: public QObject, public QGraphicsPixmapItem{
protected:
    Scene* parent;
public:
    Entity(Scene* parent);
    ~Entity();
    void setPic(string pic, int size);
};