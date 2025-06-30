#pragma once
#include "Base.h"

class Scene;

struct mapnode{
    char dir=0; // direction
    bool start=0; // is start
};
class Map: public QObject{
private:
    Scene* parent;
    int n,m; mapnode M[60][60];
    int offset_x = 300, offset_y = 300;

public:
    Map(Scene* parent);
    pii gridPos(int i,int j);
    pii gridPosMid(int i,int j);
    void Load(string path);
    void Draw();
friend class Scene;
};