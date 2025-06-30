#include "HealthBar.h"

HealthBar::HealthBar(Scene *parent, Entity* f, int max): 
    Follower(parent,f,-16,-50), 
    maxHealth(max), curHealth(max)
{
    drawpic();

    // 等贴图画完 (疑似需要画一会)
    QTimer::singleShot(30, this, [this]() {updatePosition(); show(); puts("HealthBar show()");});
}
HealthBar::~HealthBar(){}

void HealthBar::drawpic() {
    QPixmap pixmap(barWidth, barHeight);
    pixmap.fill(Qt::transparent); // 透明背景

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::lightGray);
    painter.drawRect(0, 0, barWidth, barHeight);

    painter.setBrush(Qt::red);
    int filled = (barWidth * curHealth) / maxHealth;
    painter.drawRect(0, 0, filled, barHeight);

    setPixmap(pixmap); // 设置新贴图
}
void HealthBar::showDamage(int x){
    char num[10]; sprintf(num, "-%d", x);
    auto* text = new QGraphicsTextItem(num, this);
    text->setDefaultTextColor(Qt::red);

    text->setZValue(1); text->setPos(randI(-10,10),-20+randI(-20,5));
    
    QFont font; font.setBold(true); font.setPointSize(12);
    text->setFont(font);

    // 漂浮动画
    auto* animation = new QPropertyAnimation(text, "y");
    animation->setDuration(400);
    animation->setStartValue(-10);
    animation->setEndValue(-25);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    // 透明动画
    auto* effect = new QGraphicsOpacityEffect();
    text->setGraphicsEffect(effect);
    auto* fade = new QPropertyAnimation(effect, "opacity");
    fade->setDuration(400);
    fade->setStartValue(1.0);
    fade->setEndValue(0.0);
    fade->start(QAbstractAnimation::DeleteWhenStopped);

    QTimer::singleShot(400, this, [text]() {text->deleteLater();});
}

int HealthBar::getHealth(){
    return curHealth;
}
void HealthBar::setHealth(int value) {
    if (value==curHealth) return;
    curHealth = fit_in(value, 0, maxHealth);
    drawpic();
}
void HealthBar::setMaxHealth(int value){
    if (value==maxHealth) return;
    maxHealth = value; curHealth = fit_in(curHealth, 0, maxHealth);
    drawpic();
}
bool HealthBar::decHealth(int x){
    showDamage(x);
    setHealth(curHealth-x);
    return (curHealth <= 0); // return true if die
}
void HealthBar::incHealth(int x){
    setHealth(curHealth+x);
}