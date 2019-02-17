#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#include <QGraphicsRectItem>
#include <QColor>
#include <QBrush>

class HealthBar : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    HealthBar(QColor barOverlayColor, QGraphicsItem * parent = nullptr);

    QGraphicsRectItem * barOverlay;

    void DecreaseHealth(int decreaseAmount);
    void IncreaseHealth(int increaseAmount);
    void RestoreHealth();

    int GetHealth() const;

private:
    int currentHealth;

signals:
    void Death();
};

#endif // HEALTHBAR_H
