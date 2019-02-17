#include "fvpickup.h"

FVPickUp::FVPickUp(QGraphicsItem *parent)
{
    QPixmap scaledDisc(":/Sprites/FVPickUp.png");
    scaledDisc = scaledDisc.scaled(QSize(40, 40));
    setPixmap(scaledDisc);

    musicLink = "qrc:/Sounds/FVSong.wav";

    itemName = "My Funny Valentine";
    textColor = Qt::blue;
    classType = Music;
}
