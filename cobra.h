#ifndef COBRA_H
#define COBRA_H
#include "weapon.h"

class Cobra : public Weapon
{
    Q_OBJECT
public:
    Cobra(QGraphicsItem * parent = nullptr);
};

#endif // COBRA_H
