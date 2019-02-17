#ifndef LOTUS_H
#define LOTUS_H
#include "enemy.h"
#include "lotusprojectile.h"

class Lotus : public Enemy
{
    Q_OBJECT
public:
    Lotus(QGraphicsItem * parent = nullptr);

private:
    void PlayerDetected();
    void CleanupTimers();

    QTimer * fireTimer;

    QList<LotusProjectile *> bulletPool;

    int poolSize;
    int bulletIndex;

public slots:
    void Fire();

};

#endif // LOTUS_H
