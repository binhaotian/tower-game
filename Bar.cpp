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

    Rect* Violent = new Rect(parent,3*size,0,size,size);
    Violent -> addText("Violent");

    Rect* Icy = new Rect(parent,4*size,0,size,size);
    Icy -> addText("Icy");

    Rect* Aoe = new Rect(parent,5*size,0,size,size);
    Aoe -> addText("Aoe");

    Rect* Bleeding = new Rect(parent,6*size,0,size,size);
    Bleeding -> addText("Bleeding");

    Rect* Remove = new Rect(parent,7*size,0,size,size);
    Remove -> addText("Remove");
    

    cur = "meleeT";
    QPixmap picker_pic(":/picker.png"); picker_pic = picker_pic.scaled(size, size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    picker = new QGraphicsPixmapItem(picker_pic, nullptr); parent->addItem(picker);
    picker->setPos(meleeT->rect().left(),meleeT->rect().top());

    meleeT -> setMousePress([this,meleeT]()->void {this->cur = "meleeT"; picker->setPos(meleeT->rect().left(),meleeT->rect().top()); puts("set to melee");});
    rangeT -> setMousePress([this,rangeT]()->void {this->cur = "rangeT"; picker->setPos(rangeT->rect().left(),rangeT->rect().top()); puts("set to range");});
    Violent -> setMousePress([this,Violent]()->void {this->cur = "Violent"; picker->setPos(Violent->rect().left(),Violent->rect().top()); puts("set to Violent");});
    Icy -> setMousePress([this,Icy]()->void {this->cur = "Icy"; picker->setPos(Icy->rect().left(),Icy->rect().top()); puts("set to Icy");});
    Aoe -> setMousePress([this,Aoe]()->void {this->cur = "Aoe"; picker->setPos(Aoe->rect().left(),Aoe->rect().top()); puts("set to Aoe");});
    Bleeding -> setMousePress([this,Bleeding]()->void {this->cur = "Bleeding"; picker->setPos(Bleeding->rect().left(),Bleeding->rect().top()); puts("set to Bleeding");});
    Remove -> setMousePress([this,Remove]()->void {this->cur = "Remove"; picker->setPos(Remove->rect().left(),Remove->rect().top()); puts("set to Remove");});
}
int  Bar::getMoney() {return money;}
void Bar::updateMoney() {moneyR->updateText(int2str(money));}
void Bar::addMoney(int x) {money+=x; updateMoney();}
void Bar::decMoney(int x) {money-=x; updateMoney();}