#ifndef TREE_H
#define TREE_H
#include <QGraphicsPixmapItem>

class Tree : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tree(QGraphicsItem * parent = nullptr);
};

#endif // TREE_H
