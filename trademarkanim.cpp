#include "trademarkanim.h"

TradeMarkAnim::TradeMarkAnim(QGraphicsItem * parent)
{
    animationFrames.append(QPixmap(":/Sprites/Victor.png"));
    animationFrames.append(QPixmap(":/Sprites/Alvizo.png"));
    animationFrames.append(QPixmap(":/Sprites/Onki.png"));

    currentFrame = 0;

    setPixmap(animationFrames[currentFrame]);

    frameSpeed = new QTimer();
    connect(frameSpeed, SIGNAL(timeout()), this, SLOT(NextFrame()));
    frameSpeed->start(500);
}

void TradeMarkAnim::NextFrame()
{
    setPixmap(animationFrames[currentFrame]);
    currentFrame++;

    if(currentFrame > (animationFrames.size() - 1)){
        currentFrame = 0;
    }
}
