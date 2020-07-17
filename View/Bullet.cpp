#include "Bullet.h"
#include "Enemy.h"
#include "../Model/mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>

const QSize Bullet::bs_fixedSize(26, 26);

Bullet::Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, const QPixmap &sprite, qreal slow):
    b_startPos(startPos),
    b_targetPos(targetPoint),
    b_sprite(sprite),
    b_currentPos(startPos),
    b_target(target),
    b_game(game),
    b_damage(damage),
    bulletKind(kind),
    slow_speed(slow){}

void Bullet::draw(QPainter *painter) const{
    painter->drawPixmap(b_currentPos, b_sprite);
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
    animation->setStartValue(b_startPos);
    animation->setEndValue(b_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));
    animation->start();
}

void Bullet::hitTarget(){
    if (b_game->enemyList().indexOf(b_target) != -1)
        b_target->getDamage(this);
    b_game->removedBullet(this);
}

void Bullet::setCurrentPos(QPoint pos){
    b_currentPos = pos;
}

QPoint Bullet::currentPos() const{
    return b_currentPos;
}

Tower1Bullet::Tower1Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, sprite){}


Tower2Bullet::Tower2Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, qreal slow, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, sprite, slow){}


Tower3Bullet::Tower3Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, sprite){}


Tower4Bullet::Tower4Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind, const QPixmap &sprite)
    :Bullet(startPos, targetPoint, damage, target, game, kind, sprite){}
