#pragma once
#include "Base.h"
#include "Scene.h"

typedef function<void()> fvoid;
class Rect: public QGraphicsRectItem{
protected:
    fvoid mousepress = []()->void{}; // default: do nothing
public:
    Rect(Scene*parent,int x,int y,int w,int h);

    void setMousePress(fvoid func) {mousepress = func;}
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {mousepress();}

    void addText(string t);
    void addPic(string src);
};

class TextRect: public Rect{
protected:
    QGraphicsTextItem *text;
public:
    TextRect(Scene* parent, int x, int y, int w, int h, string t);
    void updateText(string t);
};

class Bar{
private:
    QGraphicsPixmapItem *picker;
    TextRect* moneyR; int money = 100;
public:
    string cur;
    Bar(Scene*parent);
    int  getMoney();
    void updateMoney();
    void addMoney(int x);
    void decMoney(int x);
};