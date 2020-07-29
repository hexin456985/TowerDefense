#ifndef TOWER_H
#define TOWER_H

#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>
#include <QPainter>
#include "../Common/utility.h"

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
    virtual int gettowertype();
    virtual int getlevel();

private slots://槽函数，对不同类的塔有不同的武器子弹，所以先在此用虚函数
    virtual void shootWeapon();

    protected:
    int             m_towertype;
    bool			m_attacking;
    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔
    qreal			m_rotationSprite;
    Enemy *			m_chooseEnemy;
    GameWindow *	m_game;
    QTimer *		m_fireRateTimer;
    const QPoint	m_pos;
    const QPixmap	m_sprite;
    static const QSize ts_fixedSize;
};
class Tower1 : public Tower     //弓弩塔 (基础塔）
{
    Q_OBJECT
public:
    Tower1(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Arrowtower1.png"));
    ~Tower1();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
    virtual void shootWeapon();

};
class Tower1_2 : public Tower1
{
    Q_OBJECT
public:
    Tower1_2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Arrowtower2.png"));
    ~Tower1_2();
    virtual int gettowertype();
    virtual int getlevel();
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
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};
class Tower2_2 : public Tower2
{
    Q_OBJECT
public:
    Tower2_2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Magictower2.png"));
    ~Tower2_2();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};


class Tower3 : public Tower   //惩戒塔 （近距离 高DPS）
{
    Q_OBJECT
public:
    Tower3(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Demontower1.png"));
    ~Tower3();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};
class Tower3_2 : public Tower3
{
    Q_OBJECT
public:
    Tower3_2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Demontower2.png"));
    ~Tower3_2();
    virtual int gettowertype();
    virtual int getlevel();
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
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();
};
class Tower4_2 : public Tower4
{
    Q_OBJECT
public:
    Tower4_2(QPoint pos, GameWindow *game, const QPixmap &sprite = QPixmap(":/Resource/images/Canontower2.png"));
    ~Tower4_2();
    virtual int gettowertype();
    virtual int getlevel();
protected slots:
   virtual void shootWeapon();

};



class TowerPosition
{
public:
    TowerPosition(QPoint pos, const QPixmap &sprite = QPixmap("://images/base.png"));

    void setHasTower(bool hasTower = true){m_hasTower=hasTower;}
    void setHasnotTower(bool hasTower = false){m_hasTower = hasTower;}
    bool hasTower() const;
    const QPoint centerPos() const;
    bool containPoint(const QPoint &pos) const;
    void draw(QPainter *painter) ;
    int Pos11x(){return m_pos.x();}
    int Pos11y(){return m_pos.y();}
    Tower * m_tower;

private:
    QPoint		m_pos;
    bool		m_hasTower;
    QPixmap		m_sprite;

    static const QSize ms_fixedSize;
};

#endif // TOWER_H
