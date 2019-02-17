#include "pond.h"

Pond::Pond(QGraphicsItem * parent)
{
    QPixmap scaledPond(":/Sprites/Pond.png");
    scaledPond = scaledPond.scaled(QSize(150, 150));
    setPixmap(scaledPond);
}
