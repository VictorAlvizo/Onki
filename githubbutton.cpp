#include "githubbutton.h"
#include <QDebug>

GithubButton::GithubButton(QGraphicsItem * parent)
{
    githubLogo.load(":/Sprites/GithubLogo.png");
    githubLogo = githubLogo.scaled(QSize(100, 100));

    setPixmap(githubLogo);

    setAcceptHoverEvents(true);
}

void GithubButton::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    QString githubLink = "http://github.com/VictorAlvizo";
    QDesktopServices::openUrl(QUrl(githubLink));
}

void GithubButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    githubLogo = githubLogo.scaled(QSize(110, 110));
    setPixmap(githubLogo);
}

void GithubButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    githubLogo = githubLogo.scaled(QSize(100, 100));
    setPixmap(githubLogo);
}
