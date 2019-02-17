#ifndef WITCH_H
#define WITCH_H
#include "enemy.h"
#include "witchprojectile.h"

class Witch : public Enemy
{
    Q_OBJECT
public:
    Witch(QGraphicsItem * parent = nullptr);

protected:
    void PlayerDetected();
    void CleanupTimers();

    QTimer * fireTimer;

    QList<WitchProjectile *> bulletPool;

    int bulletIndex;
    int poolSize;

public slots:
    void Fire();
};

#endif // WITCH_H
