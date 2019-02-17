#include "button.h"

Button::Button(QString buttonText, QGraphicsItem * parent)
{
    setRect(0, 0, 130, 40);
    buttonX = 130;
    buttonY = 40;

    buttonTitle = new QGraphicsTextItem(buttonText, this);
    buttonTitle->setPos(45, 5);

    QBrush buttonStyle; //Set button default color
    buttonStyle.setColor(QColor(230,175,46));
    buttonStyle.setStyle(Qt::BrushStyle::SolidPattern);
    setBrush(buttonStyle);

    QFont buttonFont("Chrobot"); //Set button font
    buttonFont.setPointSize(15);
    buttonTitle->setDefaultTextColor(Qt::white);
    buttonTitle->setFont(buttonFont);

    increaseTimer = new QTimer();
    connect(increaseTimer, SIGNAL(timeout()), this, SLOT(IncreaseSize()));

    decreaseTimer = new QTimer();
    connect(decreaseTimer, SIGNAL(timeout()), this, SLOT(DecreaseSize()));

    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent * event) //Function enlarges button and changes color
{
    buttonTitle->setPos(60, 5);

    QBrush hoverBrush; //Button hover brush
    hoverBrush.setColor(QColor(49,57,60));
    hoverBrush.setStyle(Qt::BrushStyle::SolidPattern);
    setBrush(hoverBrush);

    increaseTimer->start(15);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) //Function reverts button to orignal settingss
{
    buttonTitle->setPos(45, 5);

    QBrush resetBrush; //Default brush
    resetBrush.setColor(QColor(230,175,46));
    resetBrush.setStyle(Qt::BrushStyle::SolidPattern);
    setBrush(resetBrush);

    decreaseTimer->start(15);
}

void Button::IncreaseSize()
{
    if(buttonX < 160){
        buttonX += 5;
        setRect(0, 0, buttonX, buttonY);
    }

    if(buttonY < 45){
        buttonY++;
        setRect(0, 0, buttonX, buttonY);
    }

    if(buttonX >= 160 && buttonY >= 45){
        setRect(0, 0, 160, 45); //Needed in order to resize to correct size if an error is to occur

        increaseTimer->stop();
    }
}

void Button::DecreaseSize(){
    if(buttonX > 130){
        buttonX -= 5;
        setRect(0, 0, buttonX, buttonY);
    }

    if(buttonY > 40){
        buttonY--;
        setRect(0, 0, buttonX, buttonY);
    }

    if(buttonX <= 130 && buttonY <= 40){
        setRect(0, 0, 130, 40);

        decreaseTimer->stop();
    }
}


