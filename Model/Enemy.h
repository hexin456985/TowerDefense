#ifndef ENEMY_H
#define ENEMY_H

#include "Bullet.h"
#include "../Common/utility.h"
#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class WayPoint;
class QPainter;
class Tower;
class GameWindow;
class Bullet;

class Enemy : public QObject{
    Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/Enemy1.png"));
    virtual ~Enemy();
    void draw(QPainter *painter) const;
    void move();
    void getDamage(Bullet *bullet);
    void getRemoved();
    void canRemove();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    QPoint pos() const;

    bool            m_active;
    int             ice;
    int             iceLevel; //冰冻效果持续时间
    int				m_maxHp;
    int				m_currentHp;
    int             m_damage; //对主塔的伤害
    int             enemyKind;
    int             award;
    //qreal = double
    qreal           m_speed; //设定速度
    qreal           m_walkingSpeed; //实际行走速度
    qreal			m_rotationSprite;
    QPoint			m_pos;
    WayPoint *		m_destinationWayPoint;
    GameWindow *    m_game;
    QList<Tower *>	m_attackedTowersList;
    const QPixmap	m_sprite;
    static const QSize es_fixedSize;
public slots:
    void doActivate();
};

class Enemy1:public Enemy{
    Q_OBJECT
public:
    Enemy1(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Enemy1.png"));
};

class Enemy2:public Enemy{
    Q_OBJECT
public:
    Enemy2(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Enemy2.png"));
};

class Enemy3:public Enemy{
    Q_OBJECT
public:
    Enemy3(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Enemy3.png"));
};

class Enemy4:public Enemy{
    Q_OBJECT
public:
    Enemy4(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Enemy4.png"));
};

class bossEnemy:public Enemy{
    Q_OBJECT
public:
    bossEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Enemy5.png"));
};

#endif // ENEMY_H
