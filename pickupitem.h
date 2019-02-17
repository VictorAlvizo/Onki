#ifndef PICKUPITEM_H
#define PICKUPITEM_H
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QBrush>
#include <QColor>
#include "weapon.h"
#include "pickuptext.h"

class PickUpItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    PickUpItem(QGraphicsItem * parent = nullptr);

    enum ItemClass{
        Firearm, Health, Skin, Music
    };

protected:
    QTimer * detectTimer;
    QTimer * deletePickUp;

    QString itemName;
    QColor textColor;

    QString musicLink;

    ItemClass classType;

    Weapon * droppedWeapon;

    QBrush droppedSkin;

    int healthGive;

public slots:
    void DetectPlayer();
    void DestroyPickUp();
};

#endif // PICKUPITEM_H
