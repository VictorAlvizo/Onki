#ifndef COBRAPICKUP_H
#define COBRAPICKUP_H
#include "pickupitem.h"
#include "cobra.h"

class CobraPickUp : public PickUpItem
{
    Q_OBJECT
public:
    CobraPickUp(QGraphicsItem * parent = nullptr);
};

#endif // COBRAPICKUP_H
