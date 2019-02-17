#include "pickupitem.h"
#include "player.h"
#include "game.h"
#include <QDebug>

extern Game * game;

PickUpItem::PickUpItem(QGraphicsItem * parent)
{
    detectTimer = new QTimer();
    connect(detectTimer, SIGNAL(timeout()), this, SLOT(DetectPlayer()));
    detectTimer->start(300);

    deletePickUp = new QTimer();
    connect(deletePickUp, SIGNAL(timeout()), this, SLOT(DestroyPickUp()));
    deletePickUp->start(5000);
}

void PickUpItem::DetectPlayer(){
    QList<QGraphicsItem *> itemCollided = collidingItems();

    for(int i = 0; i<itemCollided.size(); i++){
        Player * tempPlayer = dynamic_cast<Player *>(itemCollided[i]);

        if(tempPlayer){
            if(classType == Firearm){
                tempPlayer->NewWeapon(droppedWeapon);
            }else if(classType == Health){
                tempPlayer->playerHealth->IncreaseHealth(healthGive);
            }else if(classType == Skin){
                tempPlayer->setBrush(droppedSkin);
            }else{
                game->currentSong->stop();
                game->currentSong->setMedia(QUrl(musicLink));
            }

            PickUpText * itemText = new PickUpText(itemName, textColor);
            itemText->setPos(pos());
            game->scene->addItem(itemText);

            game->scene->removeItem(this);
            delete this;
        }
    }
}

void PickUpItem::DestroyPickUp()
{
    game->scene->removeItem(this);
    delete this;
}
