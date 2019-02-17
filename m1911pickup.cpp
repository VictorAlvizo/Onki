#include "m1911pickup.h"

M1911PickUp::M1911PickUp(QGraphicsItem * parent)
{
    QPixmap scaledGun(":/Sprites/M1911PickUp.png");
    scaledGun = scaledGun.scaled(QSize(40, 40));
    setPixmap(scaledGun);

    droppedWeapon = new M1911();

    itemName = "M1911";
    textColor.setRgb(163,22,33);
    classType = Firearm;
}
