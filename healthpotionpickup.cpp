#include "healthpotionpickup.h"

HealthPotionPickUp::HealthPotionPickUp(QGraphicsItem * parent)
{
    QPixmap scaledPotion(":/Sprites/HealthPotionPickUp");
    scaledPotion = scaledPotion.scaled(QSize(40, 40));
    setPixmap(scaledPotion);

    healthGive = 35;

    itemName = "Kidor";
    textColor.setRgb(80, 114, 60);
    classType = Health;
}
