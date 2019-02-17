#ifndef PLAYER_H
#define PLAYER_H
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QColor>
#include <QBrush>
#include <QPointF>
#include "healthbar.h"
#include "m1911.h"
#include "m16.h"

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent = nullptr);

    void NewWeapon(Weapon * newGun);

    void keyPressEvent(QKeyEvent * event);

    bool HasWeapon() const;

    HealthBar * playerHealth;

    Weapon * gun;

private:
    bool ValidMove();

    bool weaponOccupied;

private slots:
    void PlayerDeath();

signals:
    void Moved();
};

#endif // PLAYER_H
