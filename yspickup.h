#ifndef YSPICKUP_H
#define YSPICKUP_H
#include "pickupitem.h"

class YSPickUp : public PickUpItem
{
    Q_OBJECT
public:
    YSPickUp(QGraphicsItem * parent = nullptr);
};

#endif // YSPICKUP_H
