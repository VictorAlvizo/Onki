#include "m16pickup.h"

M16PickUp::M16PickUp(QGraphicsItem * parent)
{
    QPixmap scaledGun(":/Sprites/M16PickUp.png");
    scaledGun = scaledGun.scaled(QSize(40, 40));
    setPixmap(scaledGun);

    droppedWeapon = new M16();

    itemName = "M16";
    textColor.setRgb(163,22,33);
    classType = Firearm;
}
