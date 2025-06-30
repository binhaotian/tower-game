#include "Bar.h"

Rect::Rect(Scene*parent,int x,int y,int w,int h): QGraphicsRectItem(x,y,w,h) 
{
    QPen pen(Qt::black); pen.setWidth(1); QBrush brush(Qt::white);
    setPen(pen); setBrush(brush);
    parent->addItem(this); show();
}
void Rect::addText(string t){
    auto text = new QGraphicsTextItem(t.c_str(), this);
    text->setDefaultTextColor(Qt::black);
    // 居中
    QRectF r = rect();
    QFontMetricsF fm(text->font());
    qreal textWidth = fm.horizontalAdvance(t.c_str());
    qreal textHeight = fm.height();
    text->setPos(r.left() + (r.width() - textWidth) / 2, r.top() + (r.height() - textHeight) / 2);
}
void Rect::addPic(string src){
    QPixmap pixmap(src.c_str());
    // 居中
    QRectF r = this->rect();
    int size = min(r.width(), r.height());
    pixmap = pixmap.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QGraphicsPixmapItem *img = new QGraphicsPixmapItem(pixmap, this);
    QSizeF imgSize = img->boundingRect().size();
    img->setPos(r.left()+(r.width() - imgSize.width()) / 2, r.top()+(r.height() - imgSize.height()) / 2);
}

TextRect::TextRect(Scene*parent,int x,int y,int w,int h,string t): Rect(parent,x,y,w,h)
{
    text = new QGraphicsTextItem(t.c_str(), this);
    text->setDefaultTextColor(Qt::black);
    // 居中
    QRectF r = rect();
    QFontMetricsF fm(text->font());
    qreal textWidth = fm.horizontalAdvance(t.c_str());
    qreal textHeight = fm.height();
    text->setPos(r.left() + (r.width() - textWidth) / 2, r.top() + (r.height() - textHeight) / 2);
}
void TextRect::updateText(string t){
    text->setPlainText(t.c_str());
}

Bar::Bar(Scene*parent){
    puts("building bar");
    
    int size = 80;

    moneyR = new TextRect(parent,0,0,size,size,int2str(money));

    Rect* meleeT = new Rect(parent,size,0,size,size);
    meleeT -> addPic(":/tower.png");
    

    Rect* rangeT = new Rect(parent,2*size,0,size,size);
    rangeT -> addPic(":/cannon.png");
    

    cur = "meleeT";
    QPixmap picker_pic(":/picker.png"); picker_pic = picker_pic.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picker = new QGraphicsPixmapItem(picker_pic, nullptr); parent->addItem(picker);
    picker->setPos(meleeT->rect().left(),meleeT->rect().top());

    meleeT -> setMousePress([this,meleeT]()->void {this->cur = "meleeT"; picker->setPos(meleeT->rect().left(),meleeT->rect().top()); puts("set to melee");});
    rangeT -> setMousePress([this,rangeT]()->void {this->cur = "rangeT"; picker->setPos(rangeT->rect().left(),rangeT->rect().top()); puts("set to range");});
}
int  Bar::getMoney() {return money;}
void Bar::updateMoney() {moneyR->updateText(int2str(money));}
void Bar::addMoney(int x) {money+=x; updateMoney();}
void Bar::decMoney(int x) {money-=x; updateMoney();}