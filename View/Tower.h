#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class Enemy;
class GameWindow;
class QTimer;

class Tower : public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/images/Arrowtower1.png"));
    ~Tower();

    void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(Enemy *enemy);
    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();
    bool collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2);
    virtual int gettowertype();

private slots://槽函数，对不同类的塔有不同的武器子弹，所以先在此用虚函数
    virtual void shootWeapon();

    protected:
    int             t_towertype;
    bool			t_attacking;
    int				t_attackRange;	// 代表塔可以攻击到敌人的距离
    int				t_damage;		// 代表攻击敌人时造成的伤害
    int				t_fireRate;		// 代表再次攻击敌人的时间间隔
    qreal			t_rotationSprite;
    Enemy *			t_chooseEnemy;
    GameWindow *	t_game;
    QTimer *		t_fireRateTimer;
    const QPoint	t_pos;
    const QPixmap	t_sprite;
    static const QSize ts_fixedSize;
};
class Tower1 : public Tower     //弓弩塔 (基础塔）
{
    Q_OBJECT
public:
    Tower1(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Arrowtower1.png"));
    ~Tower1();
    virtual int gettowertype();
protected slots:
    virtual void shootWeapon();

};

class Tower2 : public Tower     //冰霜塔（缓速塔）
{
    Q_OBJECT
public:
    Tower2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Magictower1.png"));
    ~Tower2();
    virtual int gettowertype();
protected slots:
   virtual void shootWeapon();

};

class Tower3 : public Tower     //惩戒塔 （近距离 高DPS）
{
    Q_OBJECT
public:
    Tower3(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Demontower1.png"));
    ~Tower3();
    virtual int gettowertype();
protected slots:
   virtual void shootWeapon();

};

class Tower4 : public Tower     //迫炮塔 （远程高伤害）
{
    Q_OBJECT
public:
    Tower4(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Canontower1.png"));
    ~Tower4();
    virtual int gettowertype();
protected slots:
   virtual void shootWeapon();

};

#endif // TOWER_H
