#ifndef WEAPON_H
#define WEAPON_H
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QTimer>
#include <QLineF>
#include "playerprojectile.h"

class Weapon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Weapon(QGraphicsItem * parent = nullptr);

    virtual void Fire(QPointF playerPos, QPointF fireTarget);

public slots:
    void AllowFire();

protected:
    double GetAngleRotation(QPointF playerPos, QPointF dest);

    QList<PlayerProjectile *> bulletPool;

    QTimer * fireTimer;

    bool readyFire;

    int fireRate;
    int weaponDamage;

    int bulletIndex;
    int poolSize;
};

#endif // WEAPON_H
