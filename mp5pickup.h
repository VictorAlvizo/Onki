#ifndef MP5PICKUP_H
#define MP5PICKUP_H
#include "pickupitem.h"
#include "mp5.h"

class Mp5PickUp : public PickUpItem
{
    Q_OBJECT
public:
    Mp5PickUp(QGraphicsItem * parent = nullptr);
};

#endif // MP5PICKUP_H
