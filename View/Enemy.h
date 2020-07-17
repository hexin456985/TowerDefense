#ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "../Viewmodel/GameWindow.h"
#include "Bullet.h"

//待链接
class WayPoint;
class QPainter;
class MainWindow;
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
    void canRemove();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);
    bool collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2);
    QPoint pos() const;

    bool            e_active;
    int             ice;
    int             iceLevel; //冰冻效果持续时间
    int				e_maxHp;
    int				e_currentHp;
    int             e_damage; //对主塔的伤害
    int             enemyKind;
    int             e_money;
    //qreal = double
    qreal           e_speed; //设定速度
    qreal           e_walkingSpeed; //实际行走速度
    qreal			e_rotationSprite;
    QPoint			e_pos;
    WayPoint *		e_destinationWayPoint;
    GameWindow *    e_game;
    QList<Tower *>	e_attackedTowersList;
    const QPixmap	e_sprite;
    static const QSize es_fixedSize;
public slots:
    void doActivate();
};

class Enemy1:public Enemy{
    Q_OBJECT
public:
    //敌人图片先用"enemy1.png"
    Enemy1(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/Enemy1.png"));
};

class Enemy2:public Enemy{
    Q_OBJECT
public:
    //敌人图片先用"enemy2.png"
    Enemy2(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/Enemy2.png"));
};

class Enemy3:public Enemy{
    Q_OBJECT
public:
    //敌人图片先用"enemy3.png"
    Enemy3(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/Enemy3.png"));
};

class Enemy4:public Enemy{
    Q_OBJECT
public:
    //敌人图片先用"enemy4.png"
    Enemy4(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/Enemy4.png"));
};

class bossEnemy:public Enemy{
    Q_OBJECT
public:
    //敌人图片先用"monster1.png"
    bossEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/Enemy5.png"));
};

#endif // ENEMY_H
