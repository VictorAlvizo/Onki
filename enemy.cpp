#include "enemy.h"
#include "player.h"
#include "m16pickup.h"
#include "m1911pickup.h"
#include "mp5pickup.h"
#include "cobrapickup.h"
#include "healthpotionpickup.h"
#include "healthpack.h"
#include "yspickup.h"
#include "wsshirtpickup.h"
#include "lstmusicpickup.h"
#include "fvpickup.h"
#include "game.h"
#include <QDebug>

extern Game * game;

Enemy::Enemy(QGraphicsItem * parent)
{
    enemHealth = new HealthBar(QColor(84, 29, 27));

    radiusTimer = new QTimer();
    connect(radiusTimer, SIGNAL(timeout()), this, SLOT(CheckRadius()));

    moveTimer = new QTimer();
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(MoveEnemy()));

    waitTimer = new QTimer();

    playerAttack = false;

    srand(time(NULL));
}

void Enemy::StartMovement(){
    NewDirection();

    enemActive = true;
    CleanupTimers();

    enemHealth->RestoreHealth();

    radiusTimer->start(200);
    moveTimer->start(moveSpeed);
}

void Enemy::WaitTime(){ //Set a new direction and restart timer
    NewDirection();
    moveTimer->start(moveSpeed);
}

void Enemy::NewDirection(){
    int directionSide = rand() % 4;

    switch(directionSide){
        case 0: //Set direction to the right
            destination = QPointF(x() + rand() % maxX, y());
            break;

        case 1: //Set direction to the left
            destination = QPointF(x() - rand() % maxX, y());
            break;

        case 2: //Set direction to the top
            destination = QPointF(x(), y() - rand() % maxY);
            break;

        case 3: //Set direction to the bottom
            destination = QPointF(x(), y() + rand() % maxY);
            break;
    }
}

void Enemy::MoveEnemy(){
    if(playerAttack){
        PlayerDetected();
    }else{
        QPointF orignalPos = this->pos();
        QPointF detectOrg = detectRange->pos();
        QPointF enemHealthOrg = enemHealth->pos();
        QPointF enemHealthOverlayOrg = enemHealth->barOverlay->pos();
        QPointF enemNameOrg = enemyName->pos();

        QLineF distanceLine(pos(), destination);

        if(distanceLine.length() <= 1){
            moveTimer->stop();
            waitTimer->singleShot((rand() % 2500) + 1000, this, SLOT(WaitTime())); //Wait time between 2.5 seconds - 1 second
        }

        setRotation(-1 * distanceLine.angle()); //Math to find the middle of the angle (I think)

        int stepSize = 1;
        double theta = rotation();

        double dx = stepSize * qCos(qDegreesToRadians(theta));
        double dy = stepSize * qSin(qDegreesToRadians(theta));

        setPos(x() + dx, y() + dy); //Move everything towards point
        detectRange->setPos(detectRange->x() + dx,detectRange->y() + dy);
        enemHealth->setPos(enemHealth->x() + dx, enemHealth->y() + dy);
        enemHealth->barOverlay->setPos(enemHealth->x(), enemHealth->y());
        enemyName->setPos(enemyName->x() + dx, enemyName->y() + dy);

        if(!ValidMove()){
            setPos(orignalPos);
            detectRange->setPos(detectOrg);
            enemHealth->setPos(enemHealthOrg);
            enemHealth->barOverlay->setPos(enemHealthOverlayOrg);
            enemyName->setPos(enemNameOrg);
        }
    }
}

bool Enemy::ValidMove()
{
    QList<QGraphicsItem *> collidedItems = collidingItems();
    bool inBorder = false;

    for(int i = 0; i<collidedItems.size(); i++){
        Tree * tempTree = dynamic_cast<Tree *>(collidedItems[i]);
        Pond * tempPond = dynamic_cast<Pond *>(collidedItems[i]);
        Border * insideBorder = dynamic_cast<Border *>(collidedItems[i]);

        if(tempTree){
            return false;
        }else if(tempPond){
            return false;
        }else if(insideBorder){
            inBorder = true;
        }
    }

    if(!inBorder){
        return false;
    }else{
        return true;
    }
}

double Enemy::GetDestRotation(){ //Used for projectiles to get the angle
    QLineF angleLine(pos(), destination);
    return angleLine.angle() * -1;
}

void Enemy::PlayerDetected(){ //Default PlayerDetected method used for chasing player
    QPointF orignalPos = this->pos();
    QPointF detectOrg = detectRange->pos();
    QPointF enemHealthOrg = enemHealth->pos();
    QPointF enemHealthOverlayOrg = enemHealth->barOverlay->pos();
    QPointF enemNameOrg = enemyName->pos();

    QLineF angleLine(pos(), destination);

    if(angleLine.length() <= 1){ //If met stop moving
        return;
    }

    setRotation(-1 * angleLine.angle()); //Math to find the middle of the angle (I think)

    int stepSize = 1;
    double theta = rotation();

    double dx = stepSize * qCos(qDegreesToRadians(theta));
    double dy = stepSize * qSin(qDegreesToRadians(theta));

    setPos(x() + dx, y() + dy); //Move everything towards point
    detectRange->setPos(detectRange->x() + dx,detectRange->y() + dy);
    enemHealth->setPos(enemHealth->x() + dx, enemHealth->y() + dy);
    enemHealth->barOverlay->setPos(enemHealth->x(), enemHealth->y());
    enemyName->setPos(enemyName->x() + dx, enemyName->y() + dy);

    if(!ValidMove()){
        setPos(orignalPos);
        detectRange->setPos(detectOrg);
        enemHealth->setPos(enemHealthOrg);
        enemHealth->barOverlay->setPos(enemHealthOverlayOrg);
        enemyName->setPos(enemNameOrg);
    }
}

void Enemy::CheckRadius(){
    QList<QGraphicsItem *> collidingItems = detectRange->collidingItems();
    bool playerFound = false; //Just needed as a temp varible to check if player was found during loop

    for(int i = 0 ; i<collidingItems.size(); i++){ //Check if player is inside the enemy range
        Player * tempPlayer = dynamic_cast<Player *>(collidingItems[i]);

        if(tempPlayer){ //If player is found set the destination to the player
            playerAttack = true;
            playerFound = true;
            destination = tempPlayer->pos();
            break;
        }
    }

    if(!playerFound && playerAttack){
        playerAttack = false;
        setRotation(0); //Reset rotation back to normal and a new direction
        NewDirection();
    }
}

void Enemy::DropItem()
{
    int droppedItem = rand() % dropAllowance;

    switch(droppedItem){
        case 0: { //Goblin pickups 0 - 0
            M1911PickUp * dropM1911 = new M1911PickUp();
            dropM1911->setPos(pos());
            game->scene->addItem(dropM1911);

            break;
        }

        case 1: { //Witch pickups 0 - 4
            HealthPotionPickUp * dropPotion = new HealthPotionPickUp();
            dropPotion->setPos(pos());
            game->scene->addItem(dropPotion);

            break;
        }

        case 2: {
            Mp5PickUp * dropMp5 = new Mp5PickUp();
            dropMp5->setPos(pos());
            game->scene->addItem(dropMp5);

            break;
        }

        case 3: {
            YSPickUp * yellowSkin = new YSPickUp();
            yellowSkin->setPos(pos());
            game->scene->addItem(yellowSkin);

            break;
        }

        case 4: { //Rampet pickups 0 - 7
            FVPickUp * funnyVal = new FVPickUp();
            funnyVal->setPos(pos());
            game->scene->addItem(funnyVal);

            break;
        }

        case 5: {
            M16PickUp * m16 = new M16PickUp();
            m16->setPos(pos());
            game->scene->addItem(m16);

            break;
        }

        case 6: {
            HealthPack * dropPack = new HealthPack();
            dropPack->setPos(pos());
            game->scene->addItem(dropPack);

            break;
        }

        case 7: { //Lotus pickups 0 - 10
            CobraPickUp * cobra = new CobraPickUp();
            cobra->setPos(pos());
            game->scene->addItem(cobra);

            break;
        }

        case 8: {
            WsshirtPickUp * whiteSkin = new WsshirtPickUp();
            whiteSkin->setPos(pos());
            game->scene->addItem(whiteSkin);

            break;
        }

        case 9: {
            LSTMusicPickUp * lonesome = new LSTMusicPickUp();
            lonesome->setPos(pos());
            game->scene->addItem(lonesome);

            break;
        }
    }
}

void Enemy::Death()
{
    DropItem();

    enemActive = false;
    CleanupTimers();

    radiusTimer->stop();
    moveTimer->stop();

    game->SetScore(scoreGive);
    game->scene->removeItem(enemHealth); //Delete everything thats in the game scene relating to enemy
    game->scene->removeItem(enemyName);
    game->scene->removeItem(detectRange);
    game->scene->removeItem(this);
}
