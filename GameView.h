#pragma once
#include "Base.h"
#include "Map.h"
#include "Scene.h"
#include "Unit.h"
#include "Enemy.h"
#include "Tower.h"

class GameView: public QGraphicsView{
    Scene* scene;
    QTimer* tick; int tc=0;
public:
    GameView(QWidget* parent);
    ~GameView();
    void put(int i,int j,string type);
    void gameMove();
    void mousePressEvent(QMouseEvent* event) override;
};