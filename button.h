#ifndef BUTTON_H
#define BUTTON_H
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QFont>
#include <QTimer>

class Button : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Button(QString buttonText, QGraphicsItem * parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

private:
    QTimer * increaseTimer;
    QTimer * decreaseTimer;

    int buttonX;
    int buttonY;

signals:
    void clicked();

private:
    QGraphicsTextItem * buttonTitle;

private slots:
    void IncreaseSize();
    void DecreaseSize();
};

#endif // BUTTON_H
