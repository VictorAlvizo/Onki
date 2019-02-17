#include "pickuptext.h"
#include "game.h"

extern Game * game;

PickUpText::PickUpText(QString itemName, QColor textColor, QGraphicsItem * parent)
{
    setPlainText(itemName);
    setDefaultTextColor(textColor);

    QFont textfont;
    textfont.setPointSize(30);
    textfont.setFamily("Neou");
    setFont(textfont);

    moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(MoveUp()));
    moveTimer->start(50);

    destroyTimer = new QTimer();
    connect(destroyTimer, SIGNAL(timeout()), this, SLOT(DestroyText()));
    destroyTimer->start(2000);
}

void PickUpText::MoveUp(){
    this->setPos(x(), y()-15);
    this->setOpacity(opacity() - .1);
}

void PickUpText::DestroyText()
{
    game->scene->removeItem(this);
    delete this;
}
