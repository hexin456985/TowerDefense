#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"
#include "Tower.h"
#include "../Common/utility.h"

#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::bs_fixedSize(26, 26);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, const QPixmap &sprite, qreal slow):
    m_startPos(startPos),
    m_targetPos(targetPoint),
    m_sprite(sprite),
    m_currentPos(startPos),
    m_target(target),
    m_game(game),
    m_damage(damage),
    bulletKind(kind),
    slow_speed(slow){}

void Bullet::draw(QPainter *painter) const{
    painter->drawPixmap(m_currentPos, m_sprite);
}

void Bullet::move(){
    static int duration;
    switch(bulletKind){
    case(1):
        duration = 250; break;
    case(2):
        duration = 250; break;
    case(3):
        duration = 180; break;
    case(4):
        duration = 500; break;
    }

    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
    animation->start();
}

void Bullet::hitTarget(){
    if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamage(this);
    m_game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos){
    m_currentPos = pos;
}

QPoint Bullet::currentPos() const{
    return m_currentPos;
}

Tower1Bullet::Tower1Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, sprite){}


Tower2Bullet::Tower2Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, qreal slow, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, sprite, slow){}


Tower3Bullet::Tower3Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, sprite){}


Tower4Bullet::Tower4Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, sprite){}
