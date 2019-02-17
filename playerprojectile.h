#ifndef PLAYERPROJECTILE_H
#define PLAYERPROJECTILE_H
#include "projectile.h"
#include "witch.h"
#include "goblin.h"
#include "rampet.h"
#include "lotus.h"

class PlayerProjectile : public Projectile
{
    Q_OBJECT
public:
    PlayerProjectile(QGraphicsItem * parent = nullptr);

public slots:
    void DetectTarget();
};

#endif // PLAYERPROJECTILE_H
