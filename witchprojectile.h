#ifndef WITCHPROJECTILE_H
#define WITCHPROJECTILE_H
#include "projectile.h"

class WitchProjectile : public Projectile
{
    Q_OBJECT
public:
    WitchProjectile(QGraphicsItem * parent = nullptr);
};

#endif // WITCHPROJECTILE_H
