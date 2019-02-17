#include "mp5.h"

Mp5::Mp5(QGraphicsItem * parent)
{
    QPixmap scaledGun(":/Sprites/Mp5.png");
    scaledGun = scaledGun.scaled(QSize(80, 60));
    setPixmap(scaledGun);

    weaponDamage = 15;
    fireRate = 500;
}
