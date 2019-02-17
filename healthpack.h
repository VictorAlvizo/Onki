#ifndef HEALTHPACK_H
#define HEALTHPACK_H
#include "pickupitem.h"

class HealthPack : public PickUpItem
{
    Q_OBJECT
public:
    HealthPack(QGraphicsItem * parent = nullptr);
};

#endif // HEALTHPACK_H
