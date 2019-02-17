#ifndef HEALTHPOTIONPICKUP_H
#define HEALTHPOTIONPICKUP_H
#include "pickupitem.h"

class HealthPotionPickUp : public PickUpItem
{
    Q_OBJECT
public:
    HealthPotionPickUp(QGraphicsItem * parent = nullptr);
};

#endif // HEALTHPOTIONPICKUP_H
