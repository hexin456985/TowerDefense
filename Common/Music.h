#ifndef MUSIC_H
#define MUSIC_H

#include <QObject>
#include <QDir>

// 记得要根据本地文件夹路径进行对应修改; '\'要改成'/'
static const QString s_curDir = "D:/summer_semester/tower_defense/tower_defense/music";


class QMediaPlayer;

enum SoundType
{
    TowerPlaceSound,
    LifeLoseSound,
    BulletSound1,
    BulletSound2,
    BulletSound3,
    BulletSound4,
    EnemyDestorySound1,
    EnemyDestorySound2,
    EnemyDestorySound3,
    EnemyDestorySound4,
    bossEnemyDestorySound,
    BaseAttackedSound,
};

class AudioPlayer : public QObject
{
public:
    explicit AudioPlayer(QUrl bgmUrl,QObject *parent = 0);
    void startBGM();
    void stopBGM();
    void playSound(SoundType soundType);
    void playWinSound();
    void playLoseSound();
    QMediaPlayer * getMusic();

private:
    QMediaPlayer *m_BGM; // 只用来播放背景音乐
    QMediaPlayer *m_win;
    QMediaPlayer *m_lose;
};

#endif // MUSIC_H
