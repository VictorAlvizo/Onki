#include "game.h"
#include "m1911pickup.h"
#include <QDebug>

Game::Game(QWidget * parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //Configure view
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(700, 600);

    scene = new QGraphicsScene(); //Configure scene
    scene->setSceneRect(0, 0, 700, 600);
    setScene(scene);

    QBrush bgColor; //Set orange background
    bgColor.setColor(QColor(255, 117, 79));
    bgColor.setStyle(Qt::BrushStyle::SolidPattern);
    scene->setBackgroundBrush(bgColor);

    currentSong = new QMediaPlayer(); //Play background mainmenu music
    currentSong->setMedia(QUrl("qrc:/Sounds/OnkiSong.wav"));
    connect(currentSong, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(LoopMusic()));
    currentSong->play();

    cursor = nullptr;
    setMouseTracking(true);

    srand(time(NULL));
}

void Game::MainMenu(){
    QGraphicsTextItem * onkiTitle = new QGraphicsTextItem("Onki"); //Create header text
    QFont headerFont;
    headerFont.setPointSize(50);
    headerFont.setFamily("Neou");
    onkiTitle->setFont(headerFont);
    onkiTitle->setPos(265, 50);
    onkiTitle->setDefaultTextColor(Qt::white);
    scene->addItem(onkiTitle);

    Button * playButton = new Button("Play"); //Create Play button
    playButton->setPos(287, 170);
    connect(playButton, SIGNAL(clicked()), this, SLOT(StartGame()));
    scene->addItem(playButton);

    Button * quitButton = new Button("Quit"); //Create Quit button
    quitButton->setPos(287, 260);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

    volumeSlider = new Slider(); //Create Slider
    volumeSlider->setPos(250, 350);
    scene->addItem(volumeSlider);
    connect(volumeSlider, SIGNAL(ValueChange()), this, SLOT(ChangeVolume()));

    volumeText = new QGraphicsTextItem("Volume: 100%"); //Create volume text
    QFont volumeFont;
    volumeFont.setPointSize(15);
    volumeFont.setFamily("Neou");
    volumeText->setFont(volumeFont);
    volumeText->setPos(280, 385);
    volumeText->setDefaultTextColor(QColor(23, 23, 56));
    scene->addItem(volumeText);

    GithubButton * gitButton = new GithubButton();
    gitButton->setPos(300, 475);
    scene->addItem(gitButton);

    inGame = false;
}

void Game::mousePressEvent(QMouseEvent * event)
{
    if(inGame && player->HasWeapon()){
        player->gun->Fire(player->pos(), mapToScene(event->pos()));
    }

    QGraphicsView::mousePressEvent(event);
}

void Game::mouseMoveEvent(QMouseEvent * event)
{
    if(inGame){
        QPointF cursorPos = QGraphicsView::mapToScene(event->pos());
        cursorPos = QPointF(cursorPos.x() - 12, cursorPos.y() - 9);

        cursor->setPos(cursorPos);
    }

    QGraphicsView::mouseMoveEvent(event);
}

void Game::keyPressEvent(QKeyEvent * event)
{
    if(inGame && !player->hasFocus()){ //Used to fix bug where player looses focus after mouse click, game is middleman
        player->keyPressEvent(event);
    }

    QGraphicsView::keyPressEvent(event);
}

void Game::SetCursor(QString fileName)
{
    if(cursor){
        scene->removeItem(cursor);
        delete cursor;
    }

    cursor = new QGraphicsPixmapItem();

    QPixmap scaledCursor(fileName);
    scaledCursor = scaledCursor.scaled(QSize(30, 30));
    cursor->setPixmap(scaledCursor);

    scene->addItem(cursor);
}

void Game::SetScore(int addScore)
{
    scoreText->setPlainText(QString::number(scoreNum + addScore));
    scoreNum += addScore;
}

int Game::GetScore()
{
    return scoreText->toPlainText().toInt();
}

void Game::StartGame()
{
    scene->clear(); //Prepare play area
    setBackgroundBrush(QColor(0, 0, 0));
    SetCursor(":/Sprites/Crosshair.png");

    currentSong->stop(); //Set new music
    currentSong->setMedia(QUrl("qrc:/Sounds/MainGameSong.wav"));

    scoreText = new QGraphicsTextItem("0");
    QFont scoreFont;
    scoreFont.setPointSize(50);
    scoreFont.setFamily("Neou");
    scoreText->setFont(scoreFont);
    scoreText->setPos(135, -150);
    scoreText->setDefaultTextColor(Qt::white);
    scene->addItem(scoreText);

    player = new Player(); //Create player and also focus player onto the scene
    player->setPos(150, 150);
    connect(player, SIGNAL(Moved()), this, SLOT(AdjustCamera()));
    scene->addItem(player);

    player->setFlag(QGraphicsItem::ItemIsFocusable, true);
    player->setFocus();
    AdjustCamera(); //Call just to focus camera correctly

    GenerateTerrain();
    SetupPool();

    M1911PickUp * startGun = new M1911PickUp();
    startGun->setPos(300, 150);
    scene->addItem(startGun);

    spawnTimer = new QTimer();
    connect(spawnTimer, SIGNAL(timeout()), this, SLOT(SpawnEnemy()));
    spawnTimer->start(8000);

    inGame = true;
    scoreNum = 0;
}

void Game::AdjustCamera(){ //Moves camera to center of player
    double camWidth = this->sceneRect().width();
    double camHeight = this->sceneRect().height();

    QPointF topLeft(player->x() - camWidth/2, player->y() - camHeight/2);
    this->setSceneRect(topLeft.x(), topLeft.y(), camWidth, camHeight);
}

void Game::GenerateTerrain()
{
    Border * worldBorder = new Border(QColor(119,173,120), 2000, 2000);
    scene->addItem(worldBorder);

    player->setZValue(1);
    cursor->setZValue(1);
    scoreText->setZValue(1);

    SpawnObjects();
}

void Game::SpawnObjects()
{
    int spawnX = 0; //Configure terrain settings
    int spawnY = 200;
    int pondMax = 3;
    int treeMax = 6;

    for(int i = 0; i<9; i++){
        for(int j = 0; j<10; j++){
            int spawnObject = rand() % 3;

            switch(spawnObject){
                case 0: {
                    if(treeMax > 0){
                        Tree * spawnTree = new Tree();
                        spawnTree->setPos(spawnX, spawnY);
                        scene->addItem(spawnTree);

                        treeMax--;
                    }

                    break;
               }

               case 1: {
                    if(pondMax > 0){
                        Pond * spawnPond = new Pond();
                        spawnPond->setPos(spawnX, spawnY);
                        scene->addItem(spawnPond);

                        pondMax--;
                    }

                    break;
               }

               case 2:{ //Spawn nothing
                    break;
               }
            }

            spawnX += 200;
        }

        spawnY += 200;
        spawnX = 0;

        pondMax = 3;
        treeMax = 6;
    }
}

void Game::SetupPool()
{
    goblinIndex = 0;
    witchIndex = 0;
    rampetIndex = 0;
    lotusIndex = 0;

    poolSize = 5; //Note: May need to enlarge pool

    for(int i = 0; i<poolSize; i++){
        Goblin * tempGoblin = new Goblin();
        Witch * tempWitch = new Witch();
        Rampet * tempRampet = new Rampet();
        Lotus * tempLotus = new Lotus();

        goblinPool.append(tempGoblin);
        witchPool.append(tempWitch);
        rampetPool.append(tempRampet);
        lotusPool.append(tempLotus);
    }
}

void Game::SpawnEnemy(){
    int spawnAllowance = 0;

    if(GetScore() >= 2000){
        spawnAllowance = 4;
    }else if(GetScore() >= 700){
        spawnAllowance = 3;
    }else if(GetScore() >= 300){
        spawnAllowance = 2;
    }else{
        spawnAllowance = 1;
    }

    int enemySpawn = rand() % spawnAllowance;
    QPointF spawnLocation = GetEnemySpawn();

    switch(enemySpawn){
        case 0: { //Spawn Goblin
            goblinPool[goblinIndex]->setPos(spawnLocation);
            goblinPool[goblinIndex]->detectRange->setPos(spawnLocation.x() - 100, spawnLocation.y() - 90);
            goblinPool[goblinIndex]->enemHealth->setPos(spawnLocation.x() - 25, spawnLocation.y() + 60);
            goblinPool[goblinIndex]->enemHealth->barOverlay->setPos(spawnLocation.x() - 25, spawnLocation.y() + 60);
            goblinPool[goblinIndex]->enemyName->setPos(spawnLocation.x() - 15, spawnLocation.y() - 40);

            scene->addItem(goblinPool[goblinIndex]);
            scene->addItem(goblinPool[goblinIndex]->detectRange);
            scene->addItem(goblinPool[goblinIndex]->enemHealth);
            scene->addItem(goblinPool[goblinIndex]->enemyName);
            goblinPool[goblinIndex]->StartMovement();

            while(!goblinPool[goblinIndex]->ValidMove()){ //Keep repositioning until in a valid spawn
                QPointF newSpawn = GetEnemySpawn();

                goblinPool[goblinIndex]->setPos(newSpawn);
                goblinPool[goblinIndex]->detectRange->setPos(newSpawn.x() - 100, newSpawn.y() - 90);
                goblinPool[goblinIndex]->enemHealth->setPos(newSpawn.x() - 25, newSpawn.y() + 60);
                goblinPool[goblinIndex]->enemHealth->barOverlay->setPos(newSpawn.x() - 25, newSpawn.y() + 60);
                goblinPool[goblinIndex]->enemyName->setPos(newSpawn.x() - 15, newSpawn.y() - 40);
            }

            goblinIndex++;

            if(goblinIndex >= poolSize){
                goblinIndex = 0;
            }

            break;
        }

        case 1: { //Spawn Witch
            witchPool[witchIndex]->setPos(spawnLocation);
            witchPool[witchIndex]->detectRange->setPos(spawnLocation.x() - 170, spawnLocation.y() - 160);
            witchPool[witchIndex]->enemHealth->setPos(spawnLocation.x() - 25, spawnLocation.y() + 60);
            witchPool[witchIndex]->enemHealth->barOverlay->setPos(spawnLocation.x() - 25, spawnLocation.y() + 60);
            witchPool[witchIndex]->enemyName->setPos(spawnLocation.x() - 15, spawnLocation.y() - 40);

            scene->addItem(witchPool[witchIndex]);
            scene->addItem(witchPool[witchIndex]->detectRange);
            scene->addItem(witchPool[witchIndex]->enemHealth);
            scene->addItem(witchPool[witchIndex]->enemyName);
            witchPool[witchIndex]->StartMovement();

            while(!witchPool[witchIndex]->ValidMove()){
                QPointF newSpawn = GetEnemySpawn();

                witchPool[witchIndex]->setPos(newSpawn);
                witchPool[witchIndex]->detectRange->setPos(newSpawn.x() - 170, newSpawn.y() - 160);
                witchPool[witchIndex]->enemHealth->setPos(newSpawn.x() - 25, newSpawn.y() + 60);
                witchPool[witchIndex]->enemHealth->barOverlay->setPos(newSpawn.x() - 25, newSpawn.y() + 60);
                witchPool[witchIndex]->enemyName->setPos(newSpawn.x() - 15, newSpawn.y() - 40);
            }

            witchIndex++;

            if(witchIndex >= poolSize){
                witchIndex = 0;
            }

            break;
        }

        case 2: { //Spawn Rampet
            rampetPool[rampetIndex]->setPos(spawnLocation);
            rampetPool[rampetIndex]->detectRange->setPos(spawnLocation.x() - 150, spawnLocation.y() - 145);
            rampetPool[rampetIndex]->enemHealth->setPos(spawnLocation.x() - 25, spawnLocation.y() + 60);
            rampetPool[rampetIndex]->enemHealth->barOverlay->setPos(spawnLocation.x() - 25, spawnLocation.y() + 60);
            rampetPool[rampetIndex]->enemyName->setPos(spawnLocation.x() - 20, spawnLocation.y() - 40);

            scene->addItem(rampetPool[rampetIndex]);
            scene->addItem(rampetPool[rampetIndex]->detectRange);
            scene->addItem(rampetPool[rampetIndex]->enemHealth);
            scene->addItem(rampetPool[rampetIndex]->enemyName);
            rampetPool[rampetIndex]->StartMovement();

            while(!rampetPool[rampetIndex]->ValidMove()){
                QPointF newSpawn = GetEnemySpawn();

                rampetPool[rampetIndex]->setPos(newSpawn);
                rampetPool[rampetIndex]->detectRange->setPos(newSpawn.x() - 150, newSpawn.y() - 145);
                rampetPool[rampetIndex]->enemHealth->setPos(newSpawn.x() - 25, newSpawn.y() + 60);
                rampetPool[rampetIndex]->enemHealth->barOverlay->setPos(newSpawn.x() - 25, newSpawn.y() + 60);
                rampetPool[rampetIndex]->enemyName->setPos(newSpawn.x() - 20, newSpawn.y() - 40);
            }

            rampetIndex++;

            if(rampetIndex >= poolSize){
                rampetIndex = 0;
            }

            break;
        }

        case 3: { //Spawn Lotus
            lotusPool[lotusIndex]->setPos(spawnLocation);
            lotusPool[lotusIndex]->detectRange->setPos(spawnLocation.x() - 270, spawnLocation.y() - 230);
            lotusPool[lotusIndex]->enemHealth->setPos(spawnLocation.x() - 25, spawnLocation.y() + 60);
            lotusPool[lotusIndex]->enemHealth->barOverlay->setPos(spawnLocation.x() - 25, spawnLocation.y() + 60);
            lotusPool[lotusIndex]->enemyName->setPos(spawnLocation.x() - 10, spawnLocation.y() - 40);
            scene->addItem(lotusPool[lotusIndex]);
            scene->addItem(lotusPool[lotusIndex]->detectRange);
            scene->addItem(lotusPool[lotusIndex]->enemHealth);
            scene->addItem(lotusPool[lotusIndex]->enemyName);
            lotusPool[lotusIndex]->StartMovement();

            while(!lotusPool[lotusIndex]->ValidMove()){
                QPointF newSpawn = GetEnemySpawn();

                lotusPool[lotusIndex]->setPos(newSpawn);
                lotusPool[lotusIndex]->detectRange->setPos(newSpawn.x() - 270, newSpawn.y() - 230);
                lotusPool[lotusIndex]->enemHealth->setPos(newSpawn.x() - 25, newSpawn.y() + 60);
                lotusPool[lotusIndex]->enemHealth->barOverlay->setPos(newSpawn.x() - 25, newSpawn.y() + 60);
                lotusPool[lotusIndex]->enemyName->setPos(newSpawn.x() - 10, newSpawn.y() - 40);
            }

            lotusIndex++;

            if(lotusIndex >= poolSize){
                lotusIndex = 0;
            }

            break;
        }
    }
}

QPointF Game::GetEnemySpawn(){
    QPointF spawnLocation;
    int spawnDirection = rand() % 4;

    switch(spawnDirection){
        case 0: //Spawn direction to the right of the player
            spawnLocation = QPointF(player->x() + rand() % 200 + 150, player->y() + rand());
            break;

        case 1: //Spawn direction to the left of the player
            spawnLocation = QPointF(player->x() - rand() % 200 + 150, player->y());
            break;

        case 2: //Spawn direction to the top of the player
            spawnLocation = QPointF(player->x() + rand(), player->y() - rand() % 200 + 150);
            break;

        case 3: //Spawn direction to the bottom of the player
            spawnLocation = QPointF(player->x() + rand(), player->y() + rand() % 200 + 150);
            break;
    }

    return spawnLocation;
}

void Game::EndGame()
{
    inGame = false;
    spawnTimer->stop();
    scene->clear();
    this->setSceneRect(0, 0, 700, 600);

    currentSong->stop();
    currentSong->setMedia(QUrl("qrc:/Sounds/Blues.wav"));

    EndGameGUI();
    SaveImage();

    scoreNum = 0;

    cursor = nullptr; //clear pointers (needed when starting again)
    player = nullptr;

    goblinPool.clear(); //Empty pool
    witchPool.clear();
    rampetPool.clear();
    lotusPool.clear();
}

void Game::EndGameGUI()
{
    setBackgroundBrush(QColor(186,31,51));

    QGraphicsTextItem * overText = new QGraphicsTextItem("Game Over");
    QFont overFont;
    overFont.setPointSize(50);
    overFont.setFamily("Neou");
    overText->setFont(overFont);
    overText->setPos(180, 0);
    overText->setDefaultTextColor(Qt::white);
    scene->addItem(overText);

    QGraphicsTextItem * finalScoreText = new QGraphicsTextItem();
    finalScoreText->setPlainText("Score:" + QString::number(scoreNum));
    QFont scoreFont;
    scoreFont.setPointSize(35);
    scoreFont.setFamily("Neou");
    finalScoreText->setFont(scoreFont);
    finalScoreText->setPos(270, 100);
    finalScoreText->setDefaultTextColor(Qt::white);
    scene->addItem(finalScoreText);

    Button * restartButton = new Button("Restart");
    restartButton->setPos(300, 250);
    connect(restartButton, SIGNAL(clicked()), this, SLOT(StartGame()));
    scene->addItem(restartButton);

    Button * quitButton = new Button("Quit");
    quitButton->setPos(300, 350);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

    TradeMarkAnim * finalAnimation = new TradeMarkAnim();
    finalAnimation->setPos(170, 300);
    scene->addItem(finalAnimation);
}

void Game::SaveImage()
{
    QPixmap scoreImage(":/Sprites/FinalImage.jpg");
    QString savePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "/OnkiScore.png"; //Get desktop path
    QFile fileSave(savePath);

    QPainter * imageEdit = new QPainter(&scoreImage);

    QFont editFont; //Set font needed for image editing
    editFont.setPointSize(20);
    editFont.setFamily("Neou");

    imageEdit->setPen(Qt::white);
    imageEdit->setFont(editFont);
    imageEdit->drawText(QPointF(160, 363), QString::number(scoreNum));

    if(!fileSave.open(QIODevice::WriteOnly)){
        return;
    }

    scoreImage.save(&fileSave, "PNG");
}

void Game::LoopMusic(){
    if(currentSong->state() == QMediaPlayer::StoppedState){ //Song has stopped rewind
        currentSong->play();
    }
}

void Game::ChangeVolume()
{
    currentSong->setVolume(volumeSlider->GetValue());
    volumeText->setPlainText("Volume: " + QString::number(volumeSlider->GetValue()) + "%");
}
