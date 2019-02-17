#ifndef M16_H
#define M16_H
#include "weapon.h"

class M16 : public Weapon
{
    Q_OBJECT
public:
    M16(QGraphicsItem * parent = nullptr);
};

#endif // M16_H
