#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <QGraphicsRectItem>
#include <QTimer>
#include <QBrush>
#include <QColor>
#include "enemy.h"

class Projectile : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Projectile(QGraphicsItem * parent = nullptr);

    void ActivateBullet();

    void SetDamage(int newDamage);

public slots:
    virtual void DetectTarget();

    void MoveBullet();
    void DestroyProjectile();

protected:
    QTimer * moveTimer;
    QTimer * detectTimer;
    QTimer * destroyTimer;

    int projectileSpeed;
    int projectileDamage;
};

#endif // PROJECTILE_H
