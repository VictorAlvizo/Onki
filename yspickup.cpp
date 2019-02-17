#include "yspickup.h"

YSPickUp::YSPickUp(QGraphicsItem *parent)
{
    QPixmap scaledSkin(":/Sprites/YellowShirtPickUp.png");
    scaledSkin = scaledSkin.scaled(QSize(40, 40));
    setPixmap(scaledSkin);

    droppedSkin.setStyle(Qt::BrushStyle::SolidPattern);
    droppedSkin.setColor(QColor(215,207,7));

    itemName = "Banane";
    textColor = Qt::white;
    classType = Skin;
}
