#ifndef POND_H
#define POND_H
#include <QGraphicsPixmapItem>

class Pond : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Pond(QGraphicsItem * parent = nullptr);
};

#endif // POND_H
