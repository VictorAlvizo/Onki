#ifndef M1911_H
#define M1911_H
#include "weapon.h"

class M1911 : public Weapon
{
    Q_OBJECT
public:
    M1911(QGraphicsItem * parent = nullptr);
};

#endif // M1911_H
