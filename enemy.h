#ifndef ENEMY_H
#define ENEMY_H
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QColor>
#include <QPainter>
#include <QFont>
#include <QTimer>
#include <QPointF>
#include <QLineF>
#include <cstdlib>
#include <ctime>
#include <qmath.h>
#include "healthbar.h"
#include "tree.h"
#include "border.h"
#include "pond.h"

class Enemy : public QObject, public QGraphicsRectItem //TODO: After enemy is finished add sound
{
    Q_OBJECT
public:
    Enemy(QGraphicsItem * parent = nullptr);

    void StartMovement();
    void NewDirection();

    bool ValidMove();

    QGraphicsEllipseItem * detectRange;

    QGraphicsTextItem * enemyName;

    HealthBar * enemHealth;

    int damagePower;

    bool enemActive;

public slots:
    void MoveEnemy();
    void WaitTime();

    void CheckRadius();

    void Death();

protected:
    virtual void PlayerDetected();
    virtual void CleanupTimers() = 0;

    void DropItem();

    double GetDestRotation();

    int dropAllowance;

    int moveSpeed;

    int scoreGive;

    int maxX;
    int maxY;

    bool playerAttack;

    QTimer * moveTimer;
    QTimer * waitTimer;
    QTimer * radiusTimer;

    QPointF destination;
};

#endif // ENEMY_H
