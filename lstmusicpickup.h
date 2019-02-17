#ifndef LSTMUSICPICKUP_H
#define LSTMUSICPICKUP_H
#include "pickupitem.h"

class LSTMusicPickUp : public PickUpItem
{
    Q_OBJECT
public:
    LSTMusicPickUp(QGraphicsItem * parent = nullptr);
};

#endif // LSTMUSICPICKUP_H
