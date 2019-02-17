#include "lstmusicpickup.h"

LSTMusicPickUp::LSTMusicPickUp(QGraphicsItem *parent)
{
    QPixmap scaledDisc(":/Sprites/LSTPickUp.png");
    scaledDisc = scaledDisc.scaled(QSize(40, 40));
    setPixmap(scaledDisc);

    musicLink = "qrc:/Sounds/Lonesome.wav";

    itemName = "Lonesome Town";
    textColor = Qt::blue;
    classType = Music;
}
