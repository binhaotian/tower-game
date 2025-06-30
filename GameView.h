#pragma once
#include "Base.h"
#include "Map.h"
#include "Scene.h"
#include "Bar.h"
#include "Unit.h"
#include "Enemy.h"
#include "Tower.h"

class GameView: public QGraphicsView{
    Scene* scene;
    QTimer* tick; int tc=0; bool stop=0;
    Bar* bar;
public:
    GameView(QWidget* parent);
    ~GameView();
    void put(int i,int j,string type);
    void gameMove();
    void gameStop();
    void Win();
    void Lose();
    void mousePressEvent(QMouseEvent* event) override;
};