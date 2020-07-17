#include "Tower.h"
#include "Enemy.h"
#include "Bullet.h"
#include "../Model/mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>

const QSize Tower::ts_fixedSize(107, 95);

Tower::Tower(QPoint pos, GameWindow *game, const QPixmap &sprite):
    t_attacking(false),
    t_attackRange(400),
    t_damage(20),
    t_fireRate(800),
    t_rotationSprite(0.0),
    t_chooseEnemy(NULL),
    t_game(game),
    t_pos(pos),
    t_sprite(sprite)
{
    t_fireRateTimer = new QTimer(this);
    connect(t_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::~Tower()
{
    delete t_fireRateTimer;
    t_fireRateTimer = NULL;
}

bool Tower::collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2)   //判断是否碰撞
{
    const int xdif = point1.x() - point2.x();
    const int ydif = point1.y() - point2.y();
    const int distance = qSqrt(xdif * xdif + ydif * ydif);

    return ((distance <= radius1+radius2)? true: false);
}

void Tower::checkEnemyInRange()
{
    if (t_chooseEnemy)
    {
        QVector2D normalized(t_chooseEnemy->pos() - t_pos);
        normalized.normalize();
        t_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90; //角度转为弧度

        if (!collisionWithCircle(t_pos, t_attackRange, t_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        QList<Enemy *> enemyList = t_game->enemyList();
        foreach (Enemy *enemy, enemyList)
        {
            if (collisionWithCircle(t_pos, t_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
    }
}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    painter->drawEllipse(t_pos, t_attackRange, t_attackRange);
    static const QPoint offsetPoint(-ts_fixedSize.width() / 2, -ts_fixedSize.height() / 2);
    painter->translate(t_pos);
    painter->rotate(t_rotationSprite);
    painter->drawPixmap(offsetPoint, t_sprite);
    painter->restore();
}

int Tower::gettowertype()
{
    return 1;
}

void Tower::attackEnemy()
{
    t_fireRateTimer->start(t_fireRate);
}

void Tower::chooseEnemyForAttack(Enemy *enemy)
{
    t_chooseEnemy = enemy;
    attackEnemy();
    t_chooseEnemy->getAttacked(this);
}

void Tower::shootWeapon()
{
    Bullet *bullet = new Bullet(t_pos, t_chooseEnemy->pos(), t_damage, t_chooseEnemy, t_game);
    bullet->move();
    t_game->addBullet(bullet);
}

void Tower::targetKilled()
{
    if (t_chooseEnemy)
        t_chooseEnemy = NULL;

    t_fireRateTimer->stop();
    t_rotationSprite = 0.0;
}

void Tower::lostSightOfEnemy()
{
    t_chooseEnemy->gotLostSight(this);
    if (t_chooseEnemy)
        t_chooseEnemy = NULL;

    t_fireRateTimer->stop();
    t_rotationSprite = 0.0;
}


Tower1::Tower1(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    t_attackRange=300;
    t_damage=20;
}
Tower1::~Tower1()
{
}
void Tower1::shootWeapon()
{
    Bullet *bullet = new Bullet(t_pos, t_chooseEnemy->pos(), t_damage, t_chooseEnemy, t_game);
    bullet->move();
    t_game->addBullet(bullet);
}
int Tower1::gettowertype()
{
    return 1;
}


Tower2::Tower2(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    t_attackRange = 300;
    t_damage      = 25;
    t_fireRate    = 1000;
}
Tower2::~Tower2()
{
}
void Tower2::shootWeapon()
{
    Tower2Bullet *bullet2 = new Tower2Bullet(t_pos, t_chooseEnemy->pos(), t_damage, t_chooseEnemy, t_game);
    bullet2->move();
    t_game->addBullet(bullet2);
}
int Tower2::gettowertype()
{
    return 2;
}


Tower3::Tower3(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    t_attackRange = 200;
    t_damage      = 25;
    t_fireRate    = 300;
}
Tower3::~Tower3()
{
}
void Tower3::shootWeapon()
{
    Tower3Bullet *bullet3 = new Tower3Bullet(t_pos, t_chooseEnemy->pos(), t_damage, t_chooseEnemy, t_game);
    bullet3->move();
    t_game->addBullet(bullet3);
}
int Tower3::gettowertype()
{
    return 3;
}


Tower4::Tower4(QPoint pos, GameWindow *game, const QPixmap &sprite)
    : Tower(pos, game, sprite)
{
    t_attackRange = 400;
    t_damage      = 50;
    t_fireRate    = 2500;
}
Tower4::~Tower4()
{
}
void Tower4::shootWeapon()
{
    Tower4Bullet *bullet4 = new Tower4Bullet(t_pos, t_chooseEnemy->pos(), t_damage, t_chooseEnemy, t_game);
    bullet4->move();
    t_game->addBullet(bullet4);
}
int Tower4::gettowertype()
{
    return 4;
}
