#include "player.h"
#include "game.h"
#include <QDebug>

extern Game * game;

Player::Player(QGraphicsItem * parent)
{
    setRect(0, 0, 50, 50);

    QBrush playerDesign; //Set player default skin
    playerDesign.setColor(QColor(138,48,51));
    playerDesign.setStyle(Qt::BrushStyle::SolidPattern);
    setBrush(playerDesign);

    playerHealth = new HealthBar(QColor(40,150,90)); //Configure player health settings
    connect(playerHealth, SIGNAL(Death()), this, SLOT(PlayerDeath()));
    game->scene->addItem(playerHealth);
    playerHealth->setPos(-130, -130);
    playerHealth->barOverlay->setPos(-130, -130);

    weaponOccupied = false;
}

void Player::NewWeapon(Weapon * newGun){
    if(weaponOccupied){
        game->scene->removeItem(gun);
        delete gun;
    }

    gun = newGun;
    gun->setPos(x()-280, y()-250);
    game->scene->addItem(gun);

    weaponOccupied = true;
}

bool Player::HasWeapon() const{
    return weaponOccupied;
}

void Player::keyPressEvent(QKeyEvent * event)
{   
    QPointF originalPos = this->pos();
    QPointF healthOriginalPos = playerHealth->pos();
    QPointF healthOverlayOrignalPos = playerHealth->barOverlay->pos();
    QPointF scoreOrgPos = game->scoreText->pos();
    QPointF gunOriginalPos;

    if(weaponOccupied){
        gunOriginalPos = gun->pos();
    }

    if(event->key() == Qt::Key_Right || event->key() == Qt::Key_D){ //Code section controls for input
        setPos(x()+10, y());
        playerHealth->setPos(playerHealth->x() + 10, playerHealth->y());
        playerHealth->barOverlay->setPos(playerHealth->x(), playerHealth->y());
        game->scoreText->setPos(game->scoreText->x() + 10, game->scoreText->y());

        if(weaponOccupied){
            gun->setPos(gun->x()+10, gun->y());
        }

        emit Moved();
    }else if(event->key() == Qt::Key_Left || event->key() == Qt::Key_A){
        setPos(x()-10, y());
        playerHealth->setPos(playerHealth->x() - 10, playerHealth->y());
        playerHealth->barOverlay->setPos(playerHealth->x(), playerHealth->y());
        game->scoreText->setPos(game->scoreText->x() - 10, game->scoreText->y());

        if(weaponOccupied){
            gun->setPos(gun->x()-10, gun->y());
        }

        emit Moved();
    }else if(event->key() == Qt::Key_Down || event->key() == Qt::Key_S){
        setPos(x(), y()+10);
        playerHealth->setPos(playerHealth->x(), playerHealth->y() + 10);
        playerHealth->barOverlay->setPos(playerHealth->x(), playerHealth->y());
        game->scoreText->setPos(game->scoreText->x(), game->scoreText->y() + 10);

        if(weaponOccupied){
            gun->setPos(gun->x(), gun->y()+10);
        }

        emit Moved();
    }else if(event->key() == Qt::Key_Up || event->key() == Qt::Key_W){
        setPos(x(), y()-10);
        playerHealth->setPos(playerHealth->x(), playerHealth->y() - 10);
        playerHealth->barOverlay->setPos(playerHealth->x(), playerHealth->y());
        game->scoreText->setPos(game->scoreText->x(), game->scoreText->y() - 10);

        if(weaponOccupied){
            gun->setPos(gun->x(), gun->y()-10);
        }

        emit Moved();
    }

    if(!ValidMove()){
        setPos(originalPos);
        playerHealth->setPos(healthOriginalPos);
        playerHealth->barOverlay->setPos(healthOverlayOrignalPos);
        game->scoreText->setPos(scoreOrgPos);

        if(weaponOccupied){
            gun->setPos(gunOriginalPos);
        }
    }
}

bool Player::ValidMove()
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

void Player::PlayerDeath(){
    game->EndGame();
}
