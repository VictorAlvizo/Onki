#ifndef M16PICKUP_H
#define M16PICKUP_H
#include "pickupitem.h"
#include "m16.h"

class M16PickUp : public PickUpItem
{
    Q_OBJECT
public:
    M16PickUp(QGraphicsItem * parent = nullptr);
};

#endif // M16PICKUP_H
