#ifndef WSSHIRTPICKUP_H
#define WSSHIRTPICKUP_H
#include "pickupitem.h"

class WsshirtPickUp : public PickUpItem
{
    Q_OBJECT
public:
    WsshirtPickUp(QGraphicsItem * parent = nullptr);
};

#endif // WSSHIRTPICKUP_H
