#include "weapon.h"
#include "game.h"

extern Game * game;

Weapon::Weapon(QGraphicsItem * parent)
{
    fireTimer = new QTimer();
    connect(fireTimer, SIGNAL(timeout()), this, SLOT(AllowFire()));

    readyFire = true;

    poolSize = 10;
    bulletIndex = 0;

    for(int i = 0; i<poolSize; i++){
        PlayerProjectile * newProjectile = new PlayerProjectile();
        bulletPool.append(newProjectile);
    }
}

void Weapon::Fire(QPointF playerPos, QPointF fireTarget){
    if(readyFire){
        bulletPool[bulletIndex]->setPos(playerPos);
        bulletPool[bulletIndex]->SetDamage(weaponDamage);
        bulletPool[bulletIndex]->setRotation(GetAngleRotation(playerPos, fireTarget));

        game->scene->addItem(bulletPool[bulletIndex]);
        bulletPool[bulletIndex]->ActivateBullet();

        bulletIndex++;

        if(bulletIndex >= poolSize){
            bulletIndex = 0;
        }

        readyFire = false;
        fireTimer->start(fireRate);
    }
}

double Weapon::GetAngleRotation(QPointF playerPos, QPointF dest)
{
    QLineF angleLine(playerPos, dest);
    return angleLine.angle() * -1;
}

void Weapon::AllowFire(){
    readyFire = true;
    fireTimer->stop();
}
