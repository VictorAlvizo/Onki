#include "goblin.h"
#include "player.h"
#include <QDebug>

Goblin::Goblin(QGraphicsItem * parent)
{
    setRect(0, 0, 50, 50);

    QBrush goblinSkin; //Set default goblin skin
    goblinSkin.setColor(QColor(77, 170, 87));
    goblinSkin.setStyle(Qt::BrushStyle::SolidPattern);
    setBrush(goblinSkin);

    dropAllowance = 1;

    damagePower = 5;
    scoreGive = 200;

    moveSpeed = 20; //Configure movement settings
    maxX = 200;
    maxY = 200;

    enemActive = false;

    detectRange = new QGraphicsEllipseItem(); //Configure the range settings for Goblin class
    detectRange->setRect(0, 0, 250, 250);
    detectRange->setPen(QPen(Qt::NoPen)); //Make range invisble

    enemyName = new QGraphicsTextItem("Goblin"); //Set the font for the Goblin name
    QFont goblinFont("Footlight MT Light");
    goblinFont.setPointSize(20);
    enemyName->setDefaultTextColor(Qt::red);
    enemyName->setFont(goblinFont);

    connect(enemHealth, SIGNAL(Death()), this, SLOT(Death()));

    collideTimer = new QTimer();
    connect(collideTimer, SIGNAL(timeout()), this, SLOT(PlayerCollide()));
}

void Goblin::PlayerCollide(){
    QList<QGraphicsItem *> collideList = collidingItems();

    for(int i = 0; i<collideList.size(); i++){
        Player * tempPlayer = dynamic_cast<Player *>(collideList[i]);

        if(tempPlayer){ //Player found damage player
            tempPlayer->playerHealth->DecreaseHealth(damagePower);
            break;
        }
    }
}

void Goblin::CleanupTimers()
{
    if(enemActive){
        collideTimer->start(200);
    }else{
        collideTimer->stop();
    }
}
