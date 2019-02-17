#include "witchprojectile.h"

WitchProjectile::WitchProjectile(QGraphicsItem * parent)
{
    setRect(0, 0, 20, 20);

    QBrush projectileBrush; //Configure witch projectile color settings
    projectileBrush.setColor(QColor(131,33,97));
    projectileBrush.setStyle(Qt::BrushStyle::SolidPattern);
    setBrush(projectileBrush);

    projectileSpeed = 15;
}
