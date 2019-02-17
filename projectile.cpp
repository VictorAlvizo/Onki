#include "projectile.h"
#include "game.h"
#include "player.h"

extern Game * game;

Projectile::Projectile(QGraphicsItem * parent)
{
    detectTimer = new QTimer();
    connect(detectTimer, SIGNAL(timeout()), this, SLOT(DetectTarget()));

    moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(MoveBullet()));

    destroyTimer = new QTimer();
}

void Projectile::ActivateBullet()
{
    detectTimer->start(200);
    moveTimer->start(projectileSpeed);
    destroyTimer->singleShot(6000, this, SLOT(DestroyProjectile()));
}

void Projectile::MoveBullet(){
    int stepSize = 1;
    double theta = rotation();

    double dx = stepSize * qCos(qDegreesToRadians(theta));
    double dy = stepSize * qSin(qDegreesToRadians(theta));

    setPos(x() + dx, y() + dy);
}

void Projectile::DetectTarget(){ //Default target detector which looks for player
    QList<QGraphicsItem *> bulletContact = collidingItems();

    for(int i = 0; i<bulletContact.size(); i++){
        Player * tempPlayer = dynamic_cast<Player *>(bulletContact[i]);

        if(tempPlayer){ //Player has been hit decrease health and destroy bullet
            DestroyProjectile();
            tempPlayer->playerHealth->DecreaseHealth(projectileDamage);
            break;
        }
    }
}

void Projectile::DestroyProjectile(){
    game->scene->removeItem(this);

    moveTimer->stop(); //Stop all the timers in order to be reset once bullet activates
    detectTimer->stop();
    destroyTimer->stop();
}

void Projectile::SetDamage(int newDamage){
    projectileDamage = newDamage;
}
