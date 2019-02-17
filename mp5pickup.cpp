#include "mp5pickup.h"

Mp5PickUp::Mp5PickUp(QGraphicsItem * parent)
{
    QPixmap scaledGun(":/Sprites/Mp5PickUp.png");
    scaledGun = scaledGun.scaled(QSize(40, 40));
    setPixmap(scaledGun);

    droppedWeapon = new Mp5();

    itemName = "MP5";
    textColor.setRgb(163,22,33);
    classType = Firearm;
}
