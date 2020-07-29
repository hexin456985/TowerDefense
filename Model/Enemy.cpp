#include "Enemy.h"
#include "Tower.h"
#include "Game.h"
#include "../Common/utility.h"
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
     m_active(false),//决定painter是否显示enemy对象，不可通过m_active设置enemy暂停移动
     ice(0),
     m_maxHp(75),
     m_currentHp(75),
     enemyKind(1),
     award(100),
     m_speed(1.5),
     m_walkingSpeed(2.0),
     m_rotationSprite(0.0),
     m_pos(startWayPoint->pos()),
     m_destinationWayPoint(startWayPoint->nextWayPoint()),
     m_game(game),
     m_sprite(sprite){}

Enemy::~Enemy(){
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

void Enemy::doActivate(){
    m_active = true;
}

void Enemy::move()  //怪物移动
{
    if (!m_active)
        return;

    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1)){
        if (m_destinationWayPoint->nextWayPoint()){
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        } else {
            m_game->getHpDamage(m_damage);
            m_game->removedEnemy(this);
            return;
        }
    }
    QPoint targetPoint = m_destinationWayPoint->pos();

    // 向量标准化
    qreal movementSpeed = m_speed;
    QVector2D normalized(targetPoint - m_pos); //带方向性的数组？
    normalized.normalize();
    m_pos = m_pos + 0.8*normalized.toPoint() * movementSpeed;       //速度控制
}

void Enemy::draw(QPainter *painter) const   //绘制怪物及其血条
{
    if (!m_active)
        return;
    painter->save();

    //m_pos仍然是中心位置
    QPoint healthBarPoint = m_pos + QPoint(0, -es_fixedSize.height()/2 - 10);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 5));
    painter->drawRect(healthBarRect);

    static const QPoint offsetPoint(-es_fixedSize.width() / 2, -es_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    painter->drawPixmap(offsetPoint.x(),offsetPoint.y(),140,140, m_sprite);         //敌人绘制

    painter->restore();
}


void Enemy::getRemoved(){
    if (!m_attackedTowersList.empty())
        foreach (Tower *attacker, m_attackedTowersList)
            attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    m_game->removedEnemy(this);
}

void Enemy::getDamage(Bullet *bullet){
    m_currentHp -= bullet->m_damage;
    switch(bullet->bulletKind)
    {
        case 0://Tower1Bullet
            m_game->audioPlayer()->playSound(BulletSound1);
            break;
        case 1://Tower2Bullet
            m_game->audioPlayer()->playSound(BulletSound2);
            m_walkingSpeed *= 0.6;
            break;
        case 2://Tower3Bullet
            m_game->audioPlayer()->playSound(BulletSound3);
            break;
        case 3://Tower4Bullet
            m_game->audioPlayer()->playSound(BulletSound4);
            break;
    }
    // 阵亡,需要移除
    canRemove();
}

void Enemy::canRemove()
{
    if (m_currentHp <= 0){
        switch(enemyKind){
        case 1:
            m_game->audioPlayer()->playSound(EnemyDestroySound1);
            break;
        case 2:
            m_game->audioPlayer()->playSound(EnemyDestroySound2);
            m_walkingSpeed = m_walkingSpeed * 0.5;
            break;
        case 3:
            m_game->audioPlayer()->playSound(EnemyDestroySound3);
            break;
        case 4:
            m_game->audioPlayer()->playSound(EnemyDestroySound4);
            break;
        case 5:
            m_game->audioPlayer()->playSound(bossEnemyDestorySound);
            break;
        }

        m_game->awardGold(award);
        getRemoved();
    }
}

void Enemy::getAttacked(Tower *attacker){
    m_attackedTowersList.push_back(attacker);
}
void Enemy::gotLostSight(Tower *attacker){
    m_attackedTowersList.removeOne(attacker);
}
QPoint Enemy::pos() const{
    return m_pos;
}

//进击（普通怪）
Enemy1::Enemy1(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy1.png")*/):
    Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/Enemy1.png")*/)
{
    this->enemyKind= 1;
    this->iceLevel = 20;
    this->m_damage = 1;
    this->m_rotationSprite = 0.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint=startWayPoint->nextWayPoint();
}

//颚巨（小只高移速）
Enemy2::Enemy2(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy2.png")*/):
    Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/Enemy2.png")*/)
{
    this->enemyKind = 2;
    this->award = 120;
    this->m_maxHp = 100;
    this->m_currentHp = 100;
    this->iceLevel = 5;
    this->m_damage = 1;
    this->m_rotationSprite = 0.0;
    this->m_speed = 2.2;
    this->m_walkingSpeed = 3.0;
    this->m_pos=startWayPoint->pos();
    this->m_destinationWayPoint = startWayPoint->nextWayPoint();
}

//铠巨（肉盾低移速）
Enemy3::Enemy3(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy3.png")*/):
    Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/Enemy3.png")*/)
{
    this->enemyKind = 3;
    this->award = 150;
    this->m_maxHp = 300;
    this->m_currentHp = 300;
    this->m_speed = 1.2;
    this->m_walkingSpeed = 1.2;
    this->iceLevel = 5;
    this->m_damage = 2;
    this->m_rotationSprite = 0.0;
    this->m_pos = startWayPoint->pos();
    this->m_destinationWayPoint = startWayPoint->nextWayPoint();
}

//女巨 （高额赏金怪）
Enemy4::Enemy4(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy4.png")*/):
    Enemy(startWayPoint, game,sprite/* = QPixmap(":/images/Enemy4.png")*/)
{
    this->enemyKind = 4;
    this->award = 220;
    this->m_maxHp = 190;
    this->m_currentHp = 190;
    this->m_speed = 2.0;
    this->m_walkingSpeed = 2.5;
    this->iceLevel=15;
    this->m_damage = 1;
    this->m_rotationSprite = 0.0;
    this->m_pos = startWayPoint->pos();
    this->m_destinationWayPoint = startWayPoint->nextWayPoint();
}

//超大巨 （Boss怪）
bossEnemy::bossEnemy(WayPoint *startWayPoint, GameWindow *game, const QPixmap &sprite/* = QPixmap(":/images/Enemy5.png")*/):
    Enemy(startWayPoint, game, sprite/* = QPixmap(":/images/Enemy5.png")*/)
{
    this->enemyKind = 5;
    this->award = 250;
    this->m_maxHp = 350;
    this->m_currentHp = 350;
    this->m_speed = 1.2;
    this->m_walkingSpeed = 1.2;
    this->iceLevel = 10;
    this->m_damage = 3;
    this->m_rotationSprite = 0.0;
    this->m_pos = startWayPoint->pos();
    this->m_destinationWayPoint = startWayPoint->nextWayPoint();
}






