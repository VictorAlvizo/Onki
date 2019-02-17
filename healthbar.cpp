#include "healthbar.h"
#include "game.h"

extern Game * game;

HealthBar::HealthBar(QColor barOverlayColor, QGraphicsItem * parent)
{
    setRect(0, 0, 100, 10);
    currentHealth = 100;

    QBrush healthBrush; //Background settings
    healthBrush.setColor(QColor(51, 51, 51));
    healthBrush.setStyle(Qt::BrushStyle::SolidPattern);
    setBrush(healthBrush);

    barOverlay = new QGraphicsRectItem(); //Prepare overlay
    barOverlay->setRect(0, 0, 100, 10);
    setZValue(.9);
    barOverlay->setZValue(1);

    QBrush overlayBrush; //Change overlay style
    overlayBrush.setColor(barOverlayColor);
    overlayBrush.setStyle(Qt::BrushStyle::SolidPattern);
    barOverlay->setBrush(overlayBrush);

    game->scene->addItem(barOverlay);
}

int HealthBar::GetHealth() const{
    return currentHealth;
}

void HealthBar::DecreaseHealth(int decreaseAmount)
{
    currentHealth -= decreaseAmount;

    if(currentHealth <= 0){ //If healthbar is >0 emit death signal; if not just adjust the bar overlay
        barOverlay->setRect(0, 0, 0, 10);
        emit Death();
    }else{
        barOverlay->setRect(0, 0, currentHealth, 10);
    }
}

void HealthBar::IncreaseHealth(int increaseAmount){ //Similar to Decrease health without the emitting
    currentHealth += increaseAmount;

    if(currentHealth > 100){
        barOverlay->setRect(0, 0, 100, 10);
    }else{
        barOverlay->setRect(0, 0, currentHealth, 10);
    }
}

void HealthBar::RestoreHealth()
{
    currentHealth = 100;
    barOverlay->setRect(0, 0, 100, 10);
}
