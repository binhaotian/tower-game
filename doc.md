代码文件
[Base](./Base.cpp)
[Map](./Map.cpp)
[Scene](./Scene.cpp)
[Entity](./Entity.cpp)
[Unit](./Unit.cpp)
[Tower](./Tower.cpp)
[Enemy](./Enemy.cpp)
[GameView](./GameView.cpp)
[main](./main.cpp)

期望的class间关系: (->表示继承) (*表示todo)
Entity
    -> Unit
        -> Enemy
        -> Tower (我方单位, 近战或远程攻击塔)
    -> Follower
        -> HealthBar (血条)
        -> *Prefix (词缀)
    -> *弹幕之类的
Scene: 包含 Map, 和 Entity 列表
Map: 有一个 Scene* parent
GameView: 包含 Scene


地图 Map.cpp
地图的格式: 考虑到扩展性, 每一格用一个字符表示这一格的信息, 格子间用空格隔开, 这样后期也可以扩展成多字符
0 表示空白块, WASD 表示向上左下右走的路径块, 大写的 WASD 代表这里是路径的起点
地图大小不能超过 50*50
方法: 读取地图文件path存为地图 Load(string path)
方法: 在 scene 中画地图 Draw() 
方法: gridPos(i,j) // 获取i行j列格的左上角点 
方法: gridPosMid(i,j) // 获取i行j列格的中心点 

灵感: 把初始化的步骤也分为多步, 例如设置贴图, 如何如何
这样方便把初始化函数分解开, 找到共同与不同的部分

class Unit 单位, 基类, 我方和敌方的单位都是 Unit 的子类
Unit 是 Entity 子类, 因此也包含 Scene
初始化包含: 设置贴图, 设置位置, parent->add
方法: 获取格子位置 pii getGridPos()
方法: 获取绝对位置 QPointF pos() // 这是继承来的方法 // 考虑改成自己的 pointf 类, 并换个函数名

Enemy: 敌方单位, Unit 的子类
方法: 沿着地图的方向移动一格: gridMove()

做一个魔改 Scene: 继承自 QGraphicsScene
Scene 中包含 Map, 并且每个 Entity 里面都包含一个 Scene* parent, 这样大家就都可以获得整个地图信息了
Scene 中提供一些和 Map 有关的接口. 包括:
- gridPos, gridPosMid
- mapnode grid(i,j): 返回i,j格的信息
- vector<pii> startpos(): 返回开始点的列表
以及和全局信息有关的接口, 比如:
- 获取敌方和我方单位的列表 enemyL(), towerL()
- gridWho(i,j): i,j 位置格子上是谁, 没人在就 nullptr