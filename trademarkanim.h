#ifndef TRADEMARKANIM_H
#define TRADEMARKANIM_H
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>

class TradeMarkAnim : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    TradeMarkAnim(QGraphicsItem * parent = nullptr);

private:
    QList<QPixmap> animationFrames;

    QTimer * frameSpeed;

    int currentFrame;

public slots:
    void NextFrame();
};

#endif // TRADEMARKANIM_H
