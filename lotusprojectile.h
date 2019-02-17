#ifndef LOTUSPROJECTILE_H
#define LOTUSPROJECTILE_H
#include "projectile.h"

class LotusProjectile : public Projectile
{
    Q_OBJECT
public:
    LotusProjectile(QGraphicsItem * parent = nullptr);
};

#endif // LOTUSPROJECTILE_H
