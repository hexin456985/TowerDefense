#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QMainWindow>
#include <QList>
#include "../Model/Game.h"

class LevelSelect: public QMainWindow
{
    Q_OBJECT
public:
    explicit LevelSelect(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *);
    GameWindow * game = NULL;
    AudioPlayer* audioPlayer() const;
    void updateScene();

private:
    QList<Tower*> tower_list;
    AudioPlayer * m_audioPlayer;

signals:
    void chooseBack();
};

#endif // LEVELSELECT_H
