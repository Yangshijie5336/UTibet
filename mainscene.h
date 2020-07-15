#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "map.h"
#include "heroplane.h"
#include "enemyplane.h"
#include "bomb.h"

#include <QWidget>
#include <QTimer>
#include <QPaintEvent>
#include <QKeyEvent>

class MainScene : public QWidget
{
    Q_OBJECT
    void initScene();
    QTimer m_Timer;
    //启动游戏 用于启动定时器对象
    void playGame();

    //更新坐标
    void updatePosition();

    //绘图事件
    void paintEvent(QPaintEvent *event);

    //地图对象
    Map m_map;

    //飞机对象
    HeroPlane m_hero;

    //键盘移动事件
    void keyPressEvent(QKeyEvent *event);

    //敌机出场
    void enemyToScene();

    //敌机数组
    EnemyPlane m_enemys[ENEMY_NUM];

    //敌机出场间隔
    int m_recorder;

    //碰撞检测函数
    void collisionDetection();

    //爆炸数组
    Bomb m_bombs[BOMB_NUM];

public:
    MainScene(QWidget *parent = 0);
    ~MainScene();
};



#endif // MAINSCENE_H
