#include "witch.h"
#include "game.h"

extern Game * game;

Witch::Witch(QGraphicsItem * parent)
{
    setRect(0, 0, 50, 50);

    QBrush witchSkin; //Set default Witch skin
    witchSkin.setStyle(Qt::BrushStyle::SolidPattern);
    witchSkin.setColor(QColor(27,82,153));
    setBrush(witchSkin);

    dropAllowance = 4;

    damagePower = 25;
    scoreGive = 300;

    moveSpeed = 50; //Configure movement settings
    maxX = 50;
    maxY = 50;

    enemActive = false;

    detectRange = new QGraphicsEllipseItem(); //Configure range settings
    detectRange->setRect(0, 0, 400, 400);
    detectRange->setPen(Qt::NoPen);

    enemyName = new QGraphicsTextItem("Witch"); //Set the font for the Witch name
    QFont witchFont("Footlight MT Light");
    witchFont.setPointSize(20);
    enemyName->setDefaultTextColor(Qt::red);
    enemyName->setFont(witchFont);

    connect(enemHealth, SIGNAL(Death()), this, SLOT(Death()));

    fireTimer = new QTimer();
    connect(fireTimer, SIGNAL(timeout()), this, SLOT(Fire()));

    poolSize = 7;
    bulletIndex = 0;

    for(int i = 0; i<poolSize; i++){
        WitchProjectile * newProjectile = new WitchProjectile();
        bulletPool.append(newProjectile);
    }
}

void Witch::Fire(){
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

void Witch::PlayerDetected(){ //Start firing
    if(fireTimer->remainingTime() == -1){ //Timer is not running
        fireTimer->start(1500);
    }
}

void Witch::CleanupTimers()
{
    if(!enemActive){
        fireTimer->stop();
    }
}
