#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class Enemy1;
class Enemy2;
class MainWindow;
class GameWindow;


class Bullet : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 0, const QPixmap &sprite = QPixmap(":/Resource/images/Arrowbullet.png"), qreal slow = 1);
    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;
    friend class Enemy;

protected slots:
    void hitTarget();

protected:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    const QPixmap	m_sprite;
    QPoint			m_currentPos;
    Enemy *			m_target;
    GameWindow *    m_game;
    int				m_damage;
    int             bulletKind;
    qreal           slow_speed;
    static const QSize bs_fixedSize;
};

class Tower1Bullet: public Bullet   //弓弩塔子弹
{
    Q_OBJECT

public:
    Tower1Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 1, const QPixmap &sprite = QPixmap(":/Resource/images/Arrowbullet.png"));
};

class Tower2Bullet: public Bullet   //冰霜塔子弹
{
    Q_OBJECT

public:
    Tower2Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 2, qreal slow = 0.3, const QPixmap &sprite = QPixmap(":/Resource/images/Magicbullet.png"));

};

class Tower3Bullet: public Bullet   //惩戒塔子弹
{
    Q_OBJECT

public:
    Tower3Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 3, const QPixmap &sprite = QPixmap(":/Resource/images/Demonbullet.png"));

};

class Tower4Bullet: public Bullet   //迫炮塔子弹
{
    Q_OBJECT

public:
    Tower4Bullet(QPoint startPos, QPoint targetPoint, int damage, Enemy *target, GameWindow *game, int kind = 4, const QPixmap &sprite = QPixmap(":/Resource/images/Canonbullet.png"));

};

#endif // BULLET_H
