#include "lotusprojectile.h"

LotusProjectile::LotusProjectile(QGraphicsItem * parent)
{
    setRect(0, 0, 20, 20);

    QBrush projectileBrush;
    projectileBrush.setStyle(Qt::BrushStyle::SolidPattern);
    projectileBrush.setColor(QColor(236, 164, 0));
    setBrush(projectileBrush);

    projectileSpeed = 10;
}
