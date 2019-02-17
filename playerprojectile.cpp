#include "playerprojectile.h"
#include "game.h"

extern Game * game;

PlayerProjectile::PlayerProjectile(QGraphicsItem *parent)
{
    setRect(0, 0, 20, 20);

    QBrush projectileBrush;
    projectileBrush.setStyle(Qt::BrushStyle::SolidPattern);
    projectileBrush.setColor(QColor(222,239,183));
    setBrush(projectileBrush);

    projectileSpeed = 9;
}

void PlayerProjectile::DetectTarget()
{
    QList<QGraphicsItem *> bulletContact = collidingItems();

    for(int i = 0; i<bulletContact.size(); i++){
        Witch * tempWitch = dynamic_cast<Witch *>(bulletContact[i]);
        Goblin * tempGoblin = dynamic_cast<Goblin *>(bulletContact[i]);
        Rampet * tempRampet = dynamic_cast<Rampet *>(bulletContact[i]);
        Lotus * tempLotus = dynamic_cast<Lotus *>(bulletContact[i]);

        if(tempWitch){
            tempWitch->enemHealth->DecreaseHealth(projectileDamage);
            DestroyProjectile();
        }else if(tempGoblin){
            tempGoblin->enemHealth->DecreaseHealth(projectileDamage);
            DestroyProjectile();
        }else if(tempRampet){
            tempRampet->enemHealth->DecreaseHealth(projectileDamage);
            DestroyProjectile();
        }else if(tempLotus){
            tempLotus->enemHealth->DecreaseHealth(projectileDamage);
            DestroyProjectile();
        }
    }
}
