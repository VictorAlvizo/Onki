#include "m16.h"

M16::M16(QGraphicsItem * parent)
{
    QPixmap scaledGun(":/Sprites/M16.png");
    scaledGun = scaledGun.scaled(QSize(100, 60));
    setPixmap(scaledGun);

    weaponDamage = 35;
    fireRate = 1000;
}
