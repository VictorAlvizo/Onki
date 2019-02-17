#include "m1911.h"

M1911::M1911(QGraphicsItem * parent)
{
    QPixmap scaledGun(":/Sprites/M1911.png");
    scaledGun = scaledGun.scaled(QSize(60, 60));
    setPixmap(scaledGun);

    weaponDamage = 20;
    fireRate = 1200;
}
