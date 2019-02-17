#ifndef BORDER_H
#define BORDER_H
#include <QGraphicsRectItem>
#include <QColor>
#include <QBrush>
#include <QPixmap>
#include <QGraphicsPixmapItem>

class Border : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Border(QColor borderColor, int width, int height, QGraphicsItem * parent = nullptr);
};

#endif // BORDER_H
