#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QTimer>
#include <QMediaPlayer>

#include "../Viewmodel/LevelSelect.h"
#include "../Common/Button.h"
#include "../Common/Music.h"
#include "../Viewmodel/GameWindow.h"

class GameWindow;
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setFixedSize(1500,900);
    this->setWindowIcon(QIcon(":Resource/images/windowicon.jpg"));
    ui->setupUi(this);

    QUrl backgroundMusicUrl = QUrl::fromLocalFile(s_curDir + "/mainmusic.mp3");
    m_audioPlayer = new AudioPlayer(backgroundMusicUrl,this);
    m_audioPlayer->startBGM();

    Button * bin = new Button(":Resource/images/StartButton.png");
    bin->setParent(this);
    bin->move(550, 550);

    connect(bin,&QPushButton::clicked,this,[=](){
        bin->buttondown();
        bin->buttonup();
        LevelSelect * scene = new LevelSelect;
        QTimer::singleShot(500,this,[=](){
            m_audioPlayer->stopBGM();
            this->hide();
            scene->show();
            connect(scene, &LevelSelect::chooseBack,this,[=](){
                m_audioPlayer->startBGM();
                scene->hide();
                this->show();
            });
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pixmap(":Resource/images/MainMenu.jpg");
    QPixmap pixmaptitle(":Resource/images/title.png");

    painter.drawPixmap(0,0,this->width(),this->height(), pixmap);
    painter.drawPixmap(this->width()-pixmaptitle.width()-500, 60, pixmaptitle.width()*1.1, pixmaptitle.height()*1.1, pixmaptitle);
}


