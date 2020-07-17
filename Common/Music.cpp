#include "Music.h"
#include <QDir>
#include <QMediaPlayer>
#include <QMediaPlaylist>

AudioPlayer::AudioPlayer(QUrl BGMUrl, QObject *parent):
    QObject(parent),
    m_BGM(NULL),
    m_win(NULL),
    m_lose(NULL)
{
    m_win = new QMediaPlayer(this); m_lose = new QMediaPlayer(this);
    m_win ->setMedia(QUrl::fromLocalFile(s_curDir + "/Win.mp3"));
    m_lose->setMedia(QUrl::fromLocalFile(s_curDir + "/Lose.mp3"));

    if (QFile::exists(BGMUrl.toLocalFile()))
    {
        m_BGM = new QMediaPlayer(this);
        QMediaPlaylist *BGMList = new QMediaPlaylist();

        QMediaContent media(BGMUrl);
        BGMList->addMedia(media);
        BGMList->setCurrentIndex(0);
        BGMList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        m_BGM->setPlaylist(BGMList);
    }
}

void AudioPlayer::startBGM()
{
    if (m_BGM) m_BGM->play();
}

void AudioPlayer::stopBGM(){
    m_BGM->stop();
}

void AudioPlayer::playWinSound(){
    if(m_win) m_win->play();
}

void AudioPlayer::playLoseSound(){
    if(m_lose) m_lose->play();
}

void AudioPlayer::playSound(SoundType soundType)
{
    static const QUrl mediasUrls[] =
    {
        QUrl::fromLocalFile(s_curDir + "/tower_place.mp3"),
        QUrl::fromLocalFile(s_curDir + "/life_lose.mp3"),
        QUrl::fromLocalFile(s_curDir + "/normalBullet.mp3"),
        QUrl::fromLocalFile(s_curDir + "/iceBullet.mp3"),
        QUrl::fromLocalFile(s_curDir + "/laserBullet.mp3"),
        QUrl::fromLocalFile(s_curDir + "/fireBullet.mp3"),
        QUrl::fromLocalFile(s_curDir + "/normalEnemyDie.mp3"),
        QUrl::fromLocalFile(s_curDir + "/iceEnemyDie.mp3"),
        QUrl::fromLocalFile(s_curDir + "/fastEnemyDie.mp3"),
        QUrl::fromLocalFile(s_curDir + "/bossEnemyDie.mp3"),
        QUrl::fromLocalFile(s_curDir + "/cry.mp3"),
    };
    static QMediaPlayer player;

    if (QFile::exists(mediasUrls[soundType].toLocalFile()))
    {
        player.setMedia(mediasUrls[soundType]);
        player.play();
    }
}

QMediaPlayer * AudioPlayer::getMusic(){
    return m_BGM;
}


