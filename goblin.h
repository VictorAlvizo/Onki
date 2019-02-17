#ifndef GOBLIN_H
#define GOBLIN_H
#include "enemy.h"

class Goblin : public Enemy
{
    Q_OBJECT
public:
    Goblin(QGraphicsItem * parent = nullptr);

private:
    QTimer * collideTimer;

    void CleanupTimers();

public slots:
    void PlayerCollide();
};

#endif // GOBLIN_H
