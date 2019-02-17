#include "wsshirtpickup.h"

WsshirtPickUp::WsshirtPickUp(QGraphicsItem * parent)
{
    QPixmap scaledSkin(":/Sprites/WhiteShirtPickUp");
    scaledSkin = scaledSkin.scaled(QSize(40, 40));
    setPixmap(scaledSkin);

    droppedSkin = Qt::white;

    itemName = "Yeti";
    textColor = Qt::white;
    classType = Skin;
}
