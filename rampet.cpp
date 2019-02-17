#include "rampet.h"
#include "player.h"

Rampet::Rampet(QGraphicsItem *parent)
{
    setRect(0, 0, 50, 50);

    QBrush rampetSkin;
    rampetSkin.setColor(QColor(83, 25, 29));
    rampetSkin.setStyle(Qt::BrushStyle::SolidPattern);
    setBrush(rampetSkin);

    dropAllowance = 7;

    damagePower = 15;
    scoreGive = 500;

    moveSpeed = 15;
    maxX = 300;
    maxY = 300;

    enemActive = false;

    detectRange = new QGraphicsEllipseItem();
    detectRange->setRect(0, 0, 350, 350);
    detectRange->setPen(QPen(Qt::NoPen));

    enemyName = new QGraphicsTextItem("Rampet");
    QFont rampetFont("Footlight MT Light");
    rampetFont.setPointSize(20);
    enemyName->setDefaultTextColor(Qt::red);
    enemyName->setFont(rampetFont);

    connect(enemHealth, SIGNAL(Death()), this, SLOT(Death()));

    collideTimer = new QTimer();
    connect(collideTimer, SIGNAL(timeout()), this, SLOT(PlayerCollide()));
}

void Rampet::PlayerCollide()
{
    QList<QGraphicsItem *> collideList = collidingItems();

    for(int i = 0; i<collideList.size(); i++){
        Player * tempPlayer = dynamic_cast<Player *>(collideList[i]);

        if(tempPlayer){ //Player found damage player
            tempPlayer->playerHealth->DecreaseHealth(damagePower);
            break;
        }
    }
}

void Rampet::CleanupTimers()
{
    if(enemActive){
        collideTimer->start(200);
    }else{
        collideTimer->stop();
    }
}
