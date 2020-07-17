#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include "../Viewmodel/GameWindow.h"

class QPainter;
class Enemy;
class Enemy1;
class Enemy2;
class MainWindow;
class GameWindow;


class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint b_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 0, const QPixmap &sprite = QPixmap(":/images/tower4bullet.png"), qreal slow = 1);
    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;
    friend class Enemy;

protected slots:
    void hitTarget();

protected:
    const QPoint	b_startPos;
    const QPoint	b_targetPos;
    const QPixmap	b_sprite;
    QPoint			b_currentPos;
    Enemy *			b_target;
    GameWindow *    b_game;
    int				b_damage;
    int             bulletKind;
    qreal           slow_speed;
    static const QSize bs_fixedSize;
};

class Tower1Bullet: public Bullet   //弓弩塔子弹
{
    Q_OBJECT

public:
    Tower1Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 1, const QPixmap &sprite = QPixmap(":/images/	Arrorbullet.png"));
};

class Tower2Bullet: public Bullet   //冰霜塔子弹
{
    Q_OBJECT

public:
    Tower2Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 2, qreal slow = 0.3, const QPixmap &sprite = QPixmap(":/images/Magicbullet.png"));

};

class Tower3Bullet: public Bullet   //惩戒塔子弹
{
    Q_OBJECT

public:
    Tower3Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 3, const QPixmap &sprite = QPixmap(":/images/Demonbullet.png"));

};

class Tower4Bullet: public Bullet   //迫炮塔子弹
{
    Q_OBJECT

public:
    Tower4Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 4, const QPixmap &sprite = QPixmap(":/images/Canonbullet.png"));

};

#endif // BULLET_H
