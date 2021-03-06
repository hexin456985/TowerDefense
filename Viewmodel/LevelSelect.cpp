#include "LevelSelect.h"
#include "Button.h"
#include "../Common/Music.h"

#include <QPainter>
#include <QTimer>
#include <QPushButton>
#include <QMediaPlayer>

LevelSelect:: LevelSelect(QWidget *parent): QMainWindow(parent)
{
    this->setFixedSize(1500,900);
    this->setWindowIcon(QIcon(":/Resource/images/windowicon.jpg"));


    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/mainmusic.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl, this);
    m_audioPlayer->startBGM();

    Button * back_bin = new Button(":/Resource/images/Backbutton.png");
    back_bin->setParent(this);
    back_bin->setIconSize(QSize(180,180));
    back_bin->move(1240, 640);

    connect(back_bin, &Button::clicked, this,[=](){
        back_bin->buttonup();
        back_bin->buttondown();
        m_audioPlayer->stopBGM();
        QTimer::singleShot(200,this,[=](){
        emit chooseBack();
        });
    });

    Button * levelbtn1 = new Button(":/Resource/images/level1.png");
    levelbtn1->setParent(this);
    levelbtn1->setIconSize(QSize(150,150));
    levelbtn1->move(160,150);

    Button * levelbtn2 = new Button(":/Resource/images/levellocked.png");
    levelbtn2->setParent(this);
    levelbtn2->setIconSize(QSize(155,150));
    levelbtn2->move(680,270);

    Button * levelbtn3 = new Button(":/Resource/images/levellocked.png");
    levelbtn3->setParent(this);
    levelbtn3->setIconSize(QSize(150,150));
    levelbtn3->move(1170,120);

    Button * levelbtn4 = new Button(":/Resource/images/levellocked.png");
    levelbtn4->setParent(this);
    levelbtn4->setIconSize(QSize(150,150));
    levelbtn4->move(370,500);

    Button * levellocked = new Button(":/Resource/images/levellocked.png");
    levellocked->setParent(this);
    levellocked->setIconSize(QSize(150,150));
    levellocked->move(940,540);


    //点击关卡，显示对应主题游戏界面
    connect(levelbtn1, &Button::clicked, [=](){
        levelbtn1-> buttondown();
        levelbtn1-> buttonup();
        GameWindow * scene1 = new GameWindow;
        QTimer::singleShot(300,this,[=](){
            m_audioPlayer->stopBGM();
            this->hide();
            scene1->show();

            connect(scene1, &GameWindow::chooseBack, this, [=](){
                scene1->hide();
                this->show();
                m_audioPlayer->startBGM();
            });
        });
    });

    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LevelSelect::updateScene);
    timer->start(10);
}

void LevelSelect::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":/Resource/images/MainMenu.jpg");
    painter.drawPixmap(0,0,this->width(),this->height(),pixmap);
}

AudioPlayer * LevelSelect::audioPlayer() const
{
    return m_audioPlayer;
}

void LevelSelect::updateScene()
{
   update();
}
