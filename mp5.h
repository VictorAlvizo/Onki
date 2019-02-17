#ifndef MP5_H
#define MP5_H
#include "weapon.h"

class Mp5 : public Weapon
{
    Q_OBJECT
public:
    Mp5(QGraphicsItem * parent = nullptr);
};

#endif // MP5_H
