#ifndef GITHUBBUTTON_H
#define GITHUBBUTTON_H
#include <QGraphicsPixmapItem>
#include <QDesktopServices>
#include <QGraphicsSceneMouseEvent>
#include <QUrl>

class GithubButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    GithubButton(QGraphicsItem * parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

private:
    QPixmap githubLogo;
};

#endif // GITHUBBUTTON_H
