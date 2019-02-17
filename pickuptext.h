#ifndef PICKUPTEXT_H
#define PICKUPTEXT_H
#include <QGraphicsTextItem>
#include <QTimer>
#include <QFont>

class PickUpText : public QGraphicsTextItem
{
    Q_OBJECT
public:
    PickUpText(QString itemName, QColor textColor, QGraphicsItem * parent = nullptr);

private:
    QTimer * moveTimer;
    QTimer * destroyTimer;

public slots:
    void MoveUp();
    void DestroyText();
};

#endif // PICKUPTEXT_H
