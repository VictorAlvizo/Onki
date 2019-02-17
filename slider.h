#ifndef SLIDER_H
#define SLIDER_H
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>
#include <QFont>
#include <QColor>

class Slider : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Slider(QGraphicsItem * parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

    int GetValue();

private:
    QGraphicsRectItem * sliderFill;

    int currentValue;

signals:
    void ValueChange();
};

#endif // SLIDER_H
