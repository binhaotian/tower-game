#include "GameView.h"

GameView::GameView(QWidget* parent): QGraphicsView(parent)
{
    // showFullScreen(); 
    const int WIN_W = 1440, WIN_H = 1080;
    resize(WIN_W, WIN_H);
    centerOn(WIN_W/2, WIN_H/2);
    setWindowTitle("Fight Blue!");
    setRenderHint(QPainter::Antialiasing);
    setMouseTracking(true);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate); // 强制每帧重绘整个视图
    setCacheMode(QGraphicsView::CacheNone); // 不缓存图像

    scene = new Scene();
    this->setScene(scene);
    
    tick = new QTimer(this);
    tick->start(1000);
    connect(tick, &QTimer::timeout, this, &GameView::gameMove);
}
GameView::~GameView(){
    scene->deleteLater();
}

void GameView::put(int i,int j,string type){
    // tower
    if (type=="meleeT"){
        if (scene->gridWho(i,j) != nullptr) return;
        meleeT *mt = new meleeT(scene, i, j);
    }
    if (type=="rangeT"){
        if (scene->gridWho(i,j) != nullptr) return;
        rangeT *mt = new rangeT(scene, i, j);
    }

    // enemy
    if (type=="enemy"){
        if (scene->gridWho(i,j) != nullptr) return;
        Enemy *e = new Enemy(scene, i, j);
    }
}
void GameView::gameMove(){
    puts("one tick");
    ++tc;

    auto enL = scene->enemyL();
    auto twL = scene->towerL();

    for(auto e:enL) {
        e->gridMove();
    }

    int turns = 40;
    if ((tc<turns && randI(1,100)<=45) || tc==1 || tc==turns){
        vector<pii> stpos = scene->startpos();
        pii e_pos = randPick(stpos);
        printf("new enemy pos: %d,%d\n",e_pos.first,e_pos.second);
        put(e_pos.first, e_pos.second, "enemy");
    }

    for(auto t:twL){
        meleeT *mt = dynamic_cast<meleeT*>(t);
        if (mt){
            mt->attack();
        }

        rangeT *rt = dynamic_cast<rangeT*>(t);
        if (rt){
            rt->attack();
        }
    }
}
void GameView::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        QPointF pos = mapToScene(event->pos());
        pii gridpos = scene->whichGrid(pos.x(),pos.y());
        int i = gridpos.first, j = gridpos.second;
        if (i>0 && j>0) {
            // put(i, j, "meleeT");
            put(i, j, "rangeT");
        }
    }

    QGraphicsView::mousePressEvent(event);
}