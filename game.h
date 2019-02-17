#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QPointF>
#include <QPainter>
#include <QFile>
#include <QTimer>
#include <QMouseEvent>
#include <cstdlib>
#include <ctime>
#include "button.h"
#include "slider.h"
#include "player.h"
#include "goblin.h"
#include "witch.h"
#include "rampet.h"
#include "lotus.h"
#include "tree.h"
#include "border.h"
#include "pond.h"
#include "githubbutton.h"
#include "trademarkanim.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget * parent = nullptr);

    void MainMenu();

    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);

    void SetCursor(QString fileName);
    void SetScore(int addScore);

    void EndGame();
    void EndGameGUI();
    void SaveImage();

    int GetScore();

    QGraphicsScene * scene;

    QGraphicsTextItem * scoreText;

    QMediaPlayer * currentSong;

private:
    void GenerateTerrain();
    void SpawnObjects();
    void SetupPool();

    int goblinIndex;
    int witchIndex;
    int rampetIndex;
    int lotusIndex;
    int scoreNum; //Needed for game over

    int poolSize;

    QList<Goblin *> goblinPool;
    QList<Witch *> witchPool;
    QList<Rampet *> rampetPool;
    QList<Lotus *> lotusPool;

    QPointF GetEnemySpawn();

    QGraphicsRectItem * backgroundFiller;

    QTimer * spawnTimer;

    Slider * volumeSlider;

    QGraphicsTextItem * volumeText;

    QGraphicsPixmapItem * cursor;

    Player * player;

    bool inGame;

private slots:
    void StartGame();
    void ChangeVolume();
    void LoopMusic();
    void AdjustCamera();
    void SpawnEnemy();
};

#endif // GAME_H
