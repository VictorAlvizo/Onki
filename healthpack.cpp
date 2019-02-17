#include "healthpack.h"

HealthPack::HealthPack(QGraphicsItem *parent)
{
    QPixmap scaledPack(":/Sprites/AidPack.png");
    scaledPack = scaledPack.scaled(QSize(60, 60));
    setPixmap(scaledPack);

    healthGive = 50;

    itemName = "Health Pack";
    textColor.setRgb(80, 114, 60);
    classType = Health;
}
