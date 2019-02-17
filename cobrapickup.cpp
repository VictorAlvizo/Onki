#include "cobrapickup.h"

CobraPickUp::CobraPickUp(QGraphicsItem *parent)
{
    QPixmap scaledGun(":/Sounds/CobraPickUp.png");
    scaledGun = scaledGun.scaled(QSize(40, 40));;
    setPixmap(scaledGun);

    droppedWeapon = new Cobra();

    itemName = "Cobra";
    textColor.setRgb(163,22,33);
    classType = Firearm;
}
