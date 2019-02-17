#include "cobra.h"

Cobra::Cobra(QGraphicsItem * parent)
{
    QPixmap scaledGun(":/Sprites/Cobra.png");
    scaledGun = scaledGun.scaled(QSize(100, 60));
    setPixmap(scaledGun);

    weaponDamage = 50;
    fireRate = 2000;
}
