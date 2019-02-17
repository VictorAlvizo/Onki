#include "border.h"

Border::Border(QColor borderColor, int width, int height, QGraphicsItem * parent)
{
    setRect(0, 0, width, height);

    QBrush borderBrush;
    borderBrush.setStyle(Qt::BrushStyle::SolidPattern);
    borderBrush.setColor(borderColor);
    setBrush(borderBrush);
}
