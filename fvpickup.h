#ifndef FVPICKUP_H
#define FVPICKUP_H
#include "pickupitem.h"

class FVPickUp : public PickUpItem
{
    Q_OBJECT
public:
    FVPickUp(QGraphicsItem * parent = nullptr);
};

#endif // FVPICKUP_H
