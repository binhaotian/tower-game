#include "Base.h"
#include "Entity.h"

class Follower: public Entity{
protected:
    Entity* follow; int dx,dy;
public:
    Follower(Scene* parent, Entity* follow);
    Follower(Scene* parent, Entity* follow, int dx, int dy);
    
    void setFollow(Entity* f){follow=f;}
    Entity* getFollow() {return follow;}
    virtual void updatePosition();
};