#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Tower.h"
#include "../Common/utility.h"
#include "../Common/EnemyPath.h"
#include "../Common/Music.h"
#include "../Common/plistreader.h"

#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QPixmap>
#include <QMouseEvent>
#include <QMessageBox>
#include <QtGlobal>
#include <QMediaPlayer>
#include <QPropertyAnimation>

static const int TowerCost1 = 150;
static const int TowerCost2 = 220;
static const int TowerCost3 = 260;
static const int TowerCost4 = 300;//设定每安置一个炮塔花费的金币
static const int UpdateTowerCost = 200;//设定升级炮塔花费200金币
static const int RemoveTowerGet = 100;//设定拆除炮塔得到100金币


GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    m_waves(0),
    m_playerHp(15),
    m_playrGold(600),
    m_gameEnded(false),
    m_gameWin(false)
{
    this->setWindowIcon(QIcon(":/Resource/images/windowicon.jpg"));
    this->setFixedSize(1500,900);

    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/bgmusic2.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();


    gButton * back_bin = new gButton(":/Resource/images/Backbutton.png");
    back_bin->setParent(this);
    back_bin->setIconSize(QSize(160,160));
    back_bin->move(1290, -40);
    connect(back_bin,&gButton::clicked,this,[=](){
        back_bin->buttondown();
        back_bin->buttonup();
        m_audioPlayer->stopBGM();
        QTimer::singleShot(200,this,[=](){
         emit chooseBack();
        });
    });


    gButton * tower1 = new gButton(":/Resource/images/Arrowtower0.png");
    tower1->setParent(this);
    tower1->setIconSize(QSize(150,150));
    tower1->move(800,650);
    connect(tower1,&gButton::clicked,this,[=](){
        tower1->buttondown();
        tower1->buttonup();
        towertype=1;
        up=0;
        del=0;
    });

    gButton * tower2 = new gButton(":/Resource/images/Magictower0.png");
    tower2->setParent(this);
    tower2->setIconSize(QSize(150,150));
    tower2->move(980,684);
    connect(tower2,&gButton::clicked,this,[=](){
        tower2->buttondown();
        tower2->buttonup();
        towertype=2;
        up=0;
        del=0;
    });

    gButton * tower3 = new gButton(":/Resource/images/Demontower0.png");
    tower3->setParent(this);
    tower3->setIconSize(QSize(150,150));
    tower3->move(1152,704);
    connect(tower3,&gButton::clicked,this,[=](){
        tower3->buttondown();
        tower3->buttonup();
        towertype=3;
        up=0;
        del=0;
    });

    gButton * tower4 = new gButton(":/Resource/images/Canontower0.jpg");
    tower4->setParent(this);
    tower4->setIconSize(QSize(130,150));
    tower4->move(1233,640);
    connect(tower4,&gButton::clicked,this,[=](){
        tower4->buttondown();
        tower4->buttonup();
        towertype=4;
        up=0;
        del=0;
    });

    gButton * play = new gButton(":/Resource/images/Button.png");
    play->setParent(this);
    play->move(1100,1010);

    gButton * upgrade_bin = new gButton(":/Resource/images/Upgrade.png");
    upgrade_bin->setParent(this);
    upgrade_bin->setIconSize(QSize(120,120));
    upgrade_bin->move(900,-85);
    connect(upgrade_bin,&gButton::clicked,this,[=](){
        upgrade_bin->buttondown();
        upgrade_bin->buttonup();
        towertype=0;
        up=1;
        del=0;
    });

    gButton * deletetower_bin = new gButton(":/Resource/images/Deletetower.png");
    deletetower_bin->setParent(this);
    deletetower_bin->setIconSize(QSize(120,120));
    deletetower_bin->move(1105,-30);
    connect(deletetower_bin,&gButton::clicked,this,[=](){
        deletetower_bin->buttondown();
        deletetower_bin->buttonup();
        towertype=0;
        up=0;
        del=1;
    });

    preLoadWavesInfo();
    loadTowerPositions();
    addWayPoints();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(10);

    // 设置10000ms后游戏启动
    QTimer::singleShot(10000, this, SLOT(gameStart()));
}


void GameWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/Resource/images/Window1.jpeg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);

    painter.setRenderHint(QPainter::Antialiasing, true);
    if (m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "Defeat!!!" : "Victory!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        QFont font1("微软雅黑",64,QFont::Bold, true) ;
        painter.setFont(font1);
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    QPixmap castle5(":/Resource/images/Maintower0.png");
    QPixmap castle4(":/Resource/images/Maintower1.png");
    QPixmap castle3(":/Resource/images/Maintower2.png");
    QPixmap castle2(":/Resource/images/Maintower3.png");
    QPixmap castle1(":/Resource/images/Maintower4.png");
    if(m_playerHp>=13){
        painter.drawPixmap(20,600,150,200,castle1);
    }
    else if(m_playerHp<13&&m_playerHp>=9){
       painter.drawPixmap(20,600,150,200,castle2);
    }
    else if(m_playerHp<9&&m_playerHp>=6){
       painter.drawPixmap(20,600,150,200,castle3);
    }
    else if(m_playerHp<6&&m_playerHp>=3){
       painter.drawPixmap(20,600,150,200,castle4);
    }
    else{
        painter.drawPixmap(20,600,150,200,castle5);
    }

    for(int i=0;i<=19;++i)
    {
        painter.drawPixmap(m_towerPositionsList[i].Pos11x(),m_towerPositionsList[i].Pos11y(),90,90,QPixmap(":/Resource/images/towerbase.png"));
    }

    foreach (const Tower *tower, m_towersList)
        tower->draw(&painter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&painter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);


    drawPlayerGold(&painter);
    drawWave(&painter);
    drawHP(&painter);
}

GameWindow::~GameWindow()
{
    delete this->audioPlayer();

}

void GameWindow::addWayPoints()
{
    WayPoint *wayPoint1 = new WayPoint(QPoint(150-80, 690-80));
    m_wayPointsList.push_back(wayPoint1);

    WayPoint *wayPoint2 = new WayPoint(QPoint(220-80, 690-80));
    m_wayPointsList.push_back(wayPoint2);
    wayPoint2->setNextWayPoint(wayPoint1);

    WayPoint *wayPoint3 = new WayPoint(QPoint(220-80, 490-80));
    m_wayPointsList.push_back(wayPoint3);
    wayPoint3->setNextWayPoint(wayPoint2);

    WayPoint *wayPoint4 = new WayPoint(QPoint(440-80, 490-80));
    m_wayPointsList.push_back(wayPoint4);
    wayPoint4->setNextWayPoint(wayPoint3);

    WayPoint *wayPoint5 = new WayPoint(QPoint(440-80, 690-80));
    m_wayPointsList.push_back(wayPoint5);
    wayPoint5->setNextWayPoint(wayPoint4);

    WayPoint *wayPoint6 = new WayPoint(QPoint(710-80, 690-80));
    m_wayPointsList.push_back(wayPoint6);
    wayPoint6->setNextWayPoint(wayPoint5);

    WayPoint *wayPoint7 = new WayPoint(QPoint(710-80, 590-80));
    m_wayPointsList.push_back(wayPoint7);
    wayPoint7->setNextWayPoint(wayPoint6);

    WayPoint *wayPoint8 = new WayPoint(QPoint(1440-80, 590-80));
    m_wayPointsList.push_back(wayPoint8);
    wayPoint8->setNextWayPoint(wayPoint7);

    WayPoint *wayPoint9 = new WayPoint(QPoint(1440-80, 380-80));
    m_wayPointsList.push_back(wayPoint9);
    wayPoint9->setNextWayPoint(wayPoint8);

    WayPoint *wayPoint10 = new WayPoint(QPoint(1320-80, 380-80));
    m_wayPointsList.push_back(wayPoint10);
    wayPoint10->setNextWayPoint(wayPoint9);

    WayPoint *wayPoint11 = new WayPoint(QPoint(1320-80, 250-80));
    m_wayPointsList.push_back(wayPoint11);
    wayPoint11->setNextWayPoint(wayPoint10);

    WayPoint *wayPoint12 = new WayPoint(QPoint(710-80, 250-80));
    m_wayPointsList.push_back(wayPoint12);
    wayPoint12->setNextWayPoint(wayPoint11);

    WayPoint *wayPoint13 = new WayPoint(QPoint(710-80, 130-80));
    m_wayPointsList.push_back(wayPoint13);
    wayPoint13->setNextWayPoint(wayPoint12);

    WayPoint *wayPoint14 = new WayPoint(QPoint(450-80, 130-80));
    m_wayPointsList.push_back(wayPoint14);
    wayPoint14->setNextWayPoint(wayPoint13);

    WayPoint *wayPoint15 = new WayPoint(QPoint(450-80, 250-80));
    m_wayPointsList.push_back(wayPoint15);
    wayPoint15->setNextWayPoint(wayPoint14);

    WayPoint *wayPoint16 = new WayPoint(QPoint(240-80, 250-80));
    m_wayPointsList.push_back(wayPoint16);
    wayPoint16->setNextWayPoint(wayPoint15);

    WayPoint *wayPoint17 = new WayPoint(QPoint(220-80, 90-80));
    m_wayPointsList.push_back(wayPoint17);
    wayPoint17->setNextWayPoint(wayPoint16);
}

void GameWindow::updateScene()
{
   update();
}

void GameWindow::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(270, 128),

        QPoint(160, 350),
        QPoint(260, 350),
        QPoint(360, 350),

        QPoint(750, 340),
        QPoint(850, 340),
        QPoint(950, 340),
        QPoint(1050, 340),
        QPoint(1150, 340),

        QPoint(760, 470),
        QPoint(860, 470),
        QPoint(960, 470),
        QPoint(1060, 470),
        QPoint(1160, 470),
        QPoint(1260, 470),

        QPoint(265, 580),
        QPoint(265, 690),

        QPoint(440, 800),
        QPoint(540, 800),
        QPoint(640, 800)
    };
    int len	= sizeof(pos) / sizeof(pos[0]);

    for (int i = 0; i < len; ++i)
        m_towerPositionsList.push_back(pos[i]);
}

bool GameWindow::canBuyTower1() const
{
    return (((m_playrGold >= TowerCost1))? true: false);
}

bool GameWindow::canBuyTower2() const
{
    return (((m_playrGold >= TowerCost2))? true: false);
}

bool GameWindow::canBuyTower3() const
{
    return (((m_playrGold >= TowerCost3))? true: false);
}

bool GameWindow::canBuyTower4() const
{
    return (((m_playrGold >= TowerCost4))? true: false);
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {
        if (canBuyTower1() && it->containPoint(pressPos) && !it->hasTower() && towertype==1 && up==0 && del==0)
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost1;
            it->setHasTower();

            it->m_tower = new Tower1(it->centerPos(), this);
            m_towersList.push_back(it->m_tower);
            update();
            break;
        }
        if (canBuyTower2() && it->containPoint(pressPos) && !it->hasTower() && towertype==2 && up==0 && del==0)
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost2;
            it->setHasTower();

            it->m_tower = new Tower2(it->centerPos(), this);//构建的同时直接在mainwindow上作画
            m_towersList.push_back(it->m_tower);//把新构建的塔放入towerlist中储存，方便管理
            update();
            break;
        }
        if (canBuyTower3() && it->containPoint(pressPos) && !it->hasTower() && towertype==3 && up==0 && del==0)
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost3;
            it->setHasTower();

            it->m_tower = new Tower3(it->centerPos(), this);//构建的同时直接在mainwindow上作画
            m_towersList.push_back(it->m_tower);//把新构建的塔放入towerlist中储存，方便管理
            update();
            break;
        }
        if (canBuyTower4() && it->containPoint(pressPos) && !it->hasTower() && towertype==4 && up==0 && del==0)
        {
            m_audioPlayer->playSound(TowerPlaceSound);
            m_playrGold -= TowerCost4;
            it->setHasTower();

            it->m_tower = new Tower4(it->centerPos(), this);//构建的同时直接在mainwindow上作画
            m_towersList.push_back(it->m_tower);//把新构建的塔放入towerlist中储存，方便管理
            update();
            break;
        }
        //删除的鼠标事件
        if( it->containPoint(pressPos) && it->hasTower() && towertype==0 && up==0 && del==1)
        {
            m_towersList.removeOne(it->m_tower);
            it->setHasnotTower();
            m_playrGold+=RemoveTowerGet;
            m_audioPlayer->playSound(TowerPlaceSound);
            update();
            break;
        }
        //升级的鼠标事件
        if( it->containPoint(pressPos) && it->hasTower() && towertype==0 && up==1 && del==0)
        {
             if(it->m_tower->gettowertype()==1 && m_playrGold>=UpdateTowerCost)
             {
                 m_towersList.removeOne(it->m_tower);
                 it->m_tower = new Tower1_2(it->centerPos(), this);
                 m_towersList.push_back(it->m_tower);
                 m_playrGold -= UpdateTowerCost;

                 update();
             }
             if(it->m_tower->gettowertype()==2 && m_playrGold>=UpdateTowerCost)
             {
                 m_towersList.removeOne(it->m_tower);
                 it->m_tower = new Tower2_2(it->centerPos(), this);
                 m_towersList.push_back(it->m_tower);
                 m_playrGold -= UpdateTowerCost;
                 update();

             }
             if(it->m_tower->gettowertype()==3 && m_playrGold>=UpdateTowerCost)
             {
                 m_towersList.removeOne(it->m_tower);
                 it->m_tower = new Tower3_2(it->centerPos(), this);
                 m_towersList.push_back(it->m_tower);
                 m_playrGold -= UpdateTowerCost;
                 update();

             }
             if(it->m_tower->gettowertype()==4 && m_playrGold>=UpdateTowerCost)
             {
                 m_towersList.removeOne(it->m_tower);
                 it->m_tower = new Tower4_2(it->centerPos(), this);
                 m_towersList.push_back(it->m_tower);
                 m_playrGold -= UpdateTowerCost;
                 update();

             }
            m_audioPlayer->playSound(TowerPlaceSound);
            break;
        }


        ++it;
    }
}

void GameWindow::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    QFont font1("黑体",20,QFont::Bold, false) ;
    painter->setFont(font1);
    painter->drawText(QRect(8, 3, 800, 800), QString("GOLD:%1").arg(m_playrGold));
}

void GameWindow::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::white));
    QFont font1("黑体",20,QFont::Bold, false) ;
    painter->setFont(font1);
    painter->drawText(QRect(8, 100, 300, 500), QString("WAVE:%1").arg(m_waves + 1));
}

void GameWindow::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    QFont font1("黑体",20,QFont::Bold, false) ;
    painter->setFont(font1);
    painter->drawText(QRect(8, 200, 500, 500), QString("HP:%1").arg(m_playerHp));
}

void GameWindow::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        m_gameWin = false;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理

        m_audioPlayer->stopBGM();
        m_audioPlayer->playLoseSound();
    }
}

void GameWindow::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

AudioPlayer *GameWindow::audioPlayer() const
{
    return m_audioPlayer;
}

void GameWindow::getHpDamage(int damage)
{
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void GameWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
            m_audioPlayer->stopBGM();

            m_audioPlayer->playWinSound();
        }
    }
}


void GameWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void GameWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.push_back(bullet);
}

void GameWindow::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

gButton::gButton(QString pix): QPushButton(0)
{
    QPixmap pixmap(pix);
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:Opx;}");
    this->setIcon(pixmap);
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
}

void gButton::buttondown(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+7,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void gButton::buttonup(){
    QPropertyAnimation * animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()+7,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

void GameWindow::preLoadWavesInfo()
{
    QFile file(":/config/Waves.plist");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
        return;
    }

    PListReader reader;
    reader.read(&file);
    // 获取波数信息
    m_wavesInfo = reader.data();

    file.close();
}

bool GameWindow::loadWave()
{
    if (m_waves >= m_wavesInfo.size())
        return false;

    WayPoint *startWayPoint = m_wayPointsList.back();
    QList<QVariant> curWavesInfo = m_wavesInfo[m_waves].toList();

    for (int i = 0; i < curWavesInfo.size(); ++i)
    {
        QMap<QString, QVariant> dict = curWavesInfo[i].toMap();
        int spawnTime = dict.value("spawnTime").toInt();

        Enemy *enemy;
        int j=i%5;
        switch(j){
        case 0:
            enemy = new Enemy1(startWayPoint, this);
            break;
        case 1:
            enemy=new Enemy2(startWayPoint, this);
            break;
        case 2:
            enemy=new Enemy3(startWayPoint, this);
            break;
        case 3:
            enemy=new Enemy4(startWayPoint, this);
            break;
        case 4:
            enemy=new bossEnemy(startWayPoint, this);
            break;
        }
        m_enemyList.push_back(enemy);
        QTimer::singleShot(spawnTime, enemy, SLOT(doActivate()));
    }

    return true;
}


QList<Enemy *> GameWindow::enemyList() const
{
    return m_enemyList;
}

void GameWindow::gameStart()
{
    loadWave();
}

bool GameWindow::canUpgradeTower() const
{
    if(m_playrGold >= UpdateTowerCost)
        return true;
    return false;
}



