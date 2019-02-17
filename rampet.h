#ifndef RAMPET_H
#define RAMPET_H
#include "enemy.h"

class Rampet : public Enemy
{
    Q_OBJECT
public:
    Rampet(QGraphicsItem * parent = nullptr);

private:
    QTimer * collideTimer;

    void CleanupTimers();

public slots:
    void PlayerCollide();
};

#endif // RAMPET_H
