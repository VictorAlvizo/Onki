#ifndef M1911PICKUP_H
#define M1911PICKUP_H
#include "pickupitem.h"
#include "m1911.h"

class M1911PickUp : public PickUpItem
{
    Q_OBJECT
public:
    M1911PickUp(QGraphicsItem * parent = nullptr);
};

#endif // M1911PICKUP_H
