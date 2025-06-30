#include "Map.h"
#include "Scene.h"

Map::Map(Scene* parent): parent(parent) {}

pii Map::gridPos(int i,int j){
    int size = grid_size;
    int pos_x = (j-1)*size + offset_x;
    int pos_y = (i-1)*size + offset_y;
    return pii(pos_x,pos_y);
}
pii Map::gridPosMid(int i,int j){
    pii p = gridPos(i,j);
    return pii(p.first+grid_size/2, p.second+grid_size/2);
}

void Map::Load(string path){
    ifstream fin(path);
    if (!fin.is_open()){
        puts("fuck!");
        exit(0);
    }
    fin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            string tmp; fin>>tmp;
            if (tmp[0]=='0') continue;
            if (isalpha(tmp[0])){
                mapnode x; x.dir = tolower(tmp[0]);
                if (isupper(tmp[0])) x.start=1;
                M[i][j]=x;
            }
        }
    }
}

void Map::Draw(){
    int size = grid_size;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            printf("%c ",(M[i][j].dir)?(M[i][j].dir):'0');
            pii p = gridPos(i,j);
            parent->addRect(p.first, p.second, size, size, QPen(Qt::gray));
        }
        puts("");
    }
}