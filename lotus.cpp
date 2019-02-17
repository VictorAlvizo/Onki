#include "lotus.h"
#include "game.h"
#include <QDebug>

extern Game * game;

Lotus::Lotus(QGraphicsItem * parent)
{
    setRect(0, 0, 50, 50);

    QBrush lotusSkin;
    lotusSkin.setStyle(Qt::BrushStyle::SolidPattern);
    lotusSkin.setColor(QColor(66, 57, 64));
    setBrush(lotusSkin);

    dropAllowance = 10;

    damagePower = 40;
    scoreGive = 800;

    moveSpeed = 20;
    maxX = 150;
    maxY = 150;

    detectRange = new QGraphicsEllipseItem();
    detectRange->setRect(0, 0, 600, 600);
    detectRange->setPen(Qt::NoPen);

    enemyName = new QGraphicsTextItem("Lotus");
    QFont lotusFont("Footlight MT Light");
    lotusFont.setPointSize(20);
    enemyName->setDefaultTextColor(Qt::red);
    enemyName->setFont(lotusFont);

    connect(enemHealth, SIGNAL(Death()), this, SLOT(Death()));

    fireTimer = new QTimer();
    connect(fireTimer, SIGNAL(timeout()), this, SLOT(Fire()));

    poolSize = 10;
    bulletIndex = 0;

    for(int i = 0; i<poolSize; i++){
        LotusProjectile * newProjectile = new LotusProjectile();
        bulletPool.append(newProjectile);
    }
}

void Lotus::Fire(){
    if(playerAttack){
        bulletPool[bulletIndex]->setPos(x(), y());
        bulletPool[bulletIndex]->setRotation(GetDestRotation()); //Rotation used for bullet direction
        bulletPool[bulletIndex]->SetDamage(damagePower);

        game->scene->addItem(bulletPool[bulletIndex]);
        bulletPool[bulletIndex]->ActivateBullet();

        bulletIndex++;

        if(bulletIndex >= poolSize){
            bulletIndex = 0;
        }
    }else{
        fireTimer->stop();
    }
}

void Lotus::PlayerDetected()
{
    if(fireTimer->remainingTime() == -1){
        fireTimer->start(1000); //For fire rate | I should have really made a varible for this
    }
}

void Lotus::CleanupTimers()
{
    if(!enemActive){
        fireTimer->stop();
    }
}
