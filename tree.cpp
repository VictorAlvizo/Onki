#include "tree.h"

Tree::Tree(QGraphicsItem * parent)
{
    QPixmap scaledTree(":/Sprites/Tree.png");
    scaledTree = scaledTree.scaled(QSize(150, 150));
    setPixmap(scaledTree);
}
