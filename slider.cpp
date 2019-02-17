#include "slider.h"
#include "game.h"

extern Game * game;

Slider::Slider(QGraphicsItem * parent)
{
    setRect(0, 0, 200, 25);

    QBrush sliderBrush; //Background slider
    sliderBrush.setColor(QColor(51, 51, 51));
    sliderBrush.setStyle(Qt::BrushStyle::SolidPattern);
    setBrush(sliderBrush);

    sliderFill = new QGraphicsRectItem();
    sliderFill->setRect(0, 0, 200, 25);
    sliderFill->setZValue(1); //Put overlay slider foward

    QBrush slideFillBrush; //Overlay slider configuring settings
    slideFillBrush.setColor(QColor(23, 23, 56));
    slideFillBrush.setStyle(Qt::BrushStyle::SolidPattern);
    sliderFill->setBrush(slideFillBrush);

    game->scene->addItem(sliderFill);
    sliderFill->setPos(250, 350); //250, 350
}

void Slider::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    //Function is needed in order to register the move event
}

void Slider::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    if(event->pos().x() <= 200 && event->pos().x() > -1){ //Makes moving it beyond valid number impossible
        sliderFill->setRect(0, 0, event->pos().x(), 25);
        currentValue = sliderFill->rect().width() / 2; //Adjust for the 100 range by dividing by /2. Since slider is 200
        emit ValueChange();
    }
}

int Slider::GetValue(){
    return currentValue;
}
