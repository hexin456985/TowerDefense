#include "../View/Enemy.h"
#include "TowerPosition.h"
#include "Tower.h"
#include "../Model/mainwindow.h"
#include "../Common/Music.h"

#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

static const int Health_Bar_Width = 100;
const QSize Enemy::es_fixedSize(10, 10);
Enemy::Enemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite):
     QObject(0),
     e_active(false),//决定painter是否显示enemy对象，不可通过m_active设置enemy暂停移动
     ice(0),
     e_maxHp(75),
     e_currentHp(75),
     enemyKind(1),
     e_money(100),
     e_speed(2.0),
     e_walkingSpeed(2.0),
     e_rotationSprite(0.0),
     e_pos(startWayPoint->pos()),
     e_destinationWayPoint(startWayPoint->nextWayPoint()),
     e_game(game),
     e_sprite(sprite){}

Enemy::~Enemy(){
    e_attackedTowersList.clear();
    e_destinationWayPoint = NULL;
    e_game = NULL;
}

void Enemy::doActivate(){
    e_active = true;
}

void Enemy::move()  //怪物移动
{
    if (!e_active)
        return;

    if (collisionWithCircle(e_pos, 1, e_destinationWayPoint->pos(), 1)){
        if (e_destinationWayPoint->nextWayPoint()){
            e_pos = e_destinationWayPoint->pos();
            e_destinationWayPoint = e_destinationWayPoint->nextWayPoint();
        } else {
            e_game->getHpDamage(e_damage);
            e_game->removedEnemy(this);
            return;
        }
    }
    QPoint targetPoint = e_destinationWayPoint->pos();

    // 向量标准化
    qreal movementSpeed = e_speed;
    QVector2D normalized(targetPoint - e_pos); //带方向性的数组？
    normalized.normalize();
    e_pos = e_pos + 0.8*normalized.toPoint() * movementSpeed;       //速度控制
}

bool Enemy::collisionWithCircle(QPoint point1, int radius1, QPoint point2, int radius2)   //判断是否碰撞
{
    const int xdif = point1.x() - point2.x();
    const int ydif = point1.y() - point2.y();
    const int distance = qSqrt(xdif * xdif + ydif * ydif);

    return ((distance <= radius1+radius2)? true: false);
}

void Enemy::draw(QPainter *painter) const   //绘制怪物及其血条
{
    if (!e_active)
        return;
    painter->save();

    //m_pos仍然是中心位置
    QPoint healthBarPoint = e_pos + QPoint(0, -es_fixedSize.height()/2 - 10);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)e_currentHp / e_maxHp * Health_Bar_Width, 5));
    painter->drawRect(healthBarRect);

    static const QPoint offsetPoint(-es_fixedSize.width() / 2, -es_fixedSize.height() / 2);
    painter->translate(e_pos);
    painter->rotate(e_rotationSprite);
    painter->drawPixmap(offsetPoint.x(),offsetPoint.y(),200,200, e_sprite);         //敌人绘制

    painter->restore();
}

void Enemy::getDamage(Bullet *bullet) //扣除怪物血量并播放音效
{
    e_currentHp -= bullet->b_damage;

    switch(bullet->bulletKind)
    {
        case 0://Tower1Bullet
            e_game->audioPlayer()->playSound(BulletSound1);
            break;
        case 1://Tower2Bullet
            e_game->audioPlayer()->playSound(BulletSound1);
            ice = iceLevel;
            e_walkingSpeed = e_speed * 0.3;
            break;
        case 2://Tower3Bullet
            e_game->audioPlayer()->playSound(BulletSound3);
            break;
        case 3://Tower4Bullet
            e_game->audioPlayer()->playSound(BulletSound3);
            break;
    }

    canRemove();
}

void Enemy::canRemove() //判断怪物是否死亡，死亡则将其移除
{
    if (e_currentHp <= 0){
        switch(enemyKind){
        case(1):
            e_game->audioPlayer()->playSound(EnemyDestorySound1);
            break;
        case(2):
            e_game->audioPlayer()->playSound(EnemyDestorySound2);
            break;
        case(3):
            e_game->audioPlayer()->playSound(EnemyDestorySound3);
            break;
        case(4):
            e_game->audioPlayer()->playSound(EnemyDestorySound4);
            break;
        case(5):
            e_game->audioPlayer()->playSound(bossEnemyDestorySound);
            break;
        }
        e_game->awardGold(e_money);

        if (!e_attackedTowersList.empty())
            foreach (Tower *attacker, e_attackedTowersList)
                attacker->targetKilled();
        e_game->removedEnemy(this);
    }
}

void Enemy::getAttacked(Tower *attacker){
    e_attackedTowersList.push_back(attacker);
}
void Enemy::gotLostSight(Tower *attacker){
    e_attackedTowersList.removeOne(attacker);
}
QPoint Enemy::pos() const{
    return e_pos;
}

//进击（普通怪）
Enemy1::Enemy1(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy1.png")*/):
    Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/Enemy1.png")*/)
{
    this->iceLevel = 20;
    this->e_damage = 1;
    this->e_rotationSprite = 0.0;
    this->e_pos=startWayPoint->pos();
    this->e_destinationWayPoint=startWayPoint->nextWayPoint();
}

//颚巨（小只高移速）
Enemy2::Enemy2(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy2.png")*/):
    Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/Enemy2.png")*/)
{
    this->enemyKind = 2;
    this->e_money = 120;
    this->e_maxHp = 50;
    this->e_currentHp = 50;
    this->iceLevel = 5;
    this->e_damage = 1;
    this->e_rotationSprite = 0.0;
    this->e_speed = 3.0;
    this->e_walkingSpeed = 3.0;
    this->e_pos=startWayPoint->pos();
    this->e_destinationWayPoint = startWayPoint->nextWayPoint();
}

//铠巨（肉盾低移速）
Enemy3::Enemy3(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy3.png")*/):
    Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/Enemy3.png")*/)
{
    this->enemyKind = 3;
    this->e_money = 150;
    this->e_maxHp = 200;
    this->e_currentHp = 200;
    this->e_speed = 1.2;
    this->e_walkingSpeed = 1.2;
    this->iceLevel = 5;
    this->e_damage = 2;
    this->e_rotationSprite = 0.0;
    this->e_pos = startWayPoint->pos();
    this->e_destinationWayPoint = startWayPoint->nextWayPoint();
}

//女巨 （高额赏金怪）
Enemy4::Enemy4(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy4.png")*/):
    Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/Enemy4.png")*/)
{
    this->enemyKind = 4;
    this->e_money = 220;
    this->e_maxHp = 90;
    this->e_currentHp = 130;
    this->e_speed = 2.5;
    this->e_walkingSpeed = 2.5;
    this->iceLevel=15;
    this->e_damage = 1;
    this->e_rotationSprite = 0.0;
    this->e_pos = startWayPoint->pos();
    this->e_destinationWayPoint = startWayPoint->nextWayPoint();
}

//超大巨 （Boss怪）
bossEnemy::bossEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy5.png")*/):
    Enemy(startWayPoint, game, sprite/* = QPixmap(":/images/Enemy5.png")*/)
{
    this->enemyKind = 5;
    this->e_money = 250;
    this->e_maxHp = 200;
    this->e_currentHp = 250;
    this->e_speed = 1.2;
    this->e_walkingSpeed = 1.2;
    this->iceLevel = 10;
    this->e_damage = 3;
    this->e_rotationSprite = 0.0;
    this->e_pos = startWayPoint->pos();
    this->e_destinationWayPoint = startWayPoint->nextWayPoint();
}






