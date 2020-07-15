#include "mainscene.h"
#include "config.h"
#include "heroplane.h"
#include <QIcon>
#include <QPainter>
#include <ctime>
#include <QSound>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    initScene();
    playGame();
}

MainScene::~MainScene()
{

}

void MainScene::initScene()
{
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

    //设置图标资源
    setWindowIcon(QIcon(GAME_ICON));

    //定时器设置
    m_Timer.setInterval(GAME_RATE);

    m_recorder = 0;

    //随机数种子
    srand((unsigned int)time(NULL));
}

void MainScene::playGame()
{
    //启动背景音乐
    QSound::play(SOUND_BACKGROUND);
    //启动定时器
    m_Timer.start();

    //监听定时器
    connect(&m_Timer,&QTimer::timeout,[=](){
        //敌机出场
        enemyToScene();
        //更新游戏中元素的坐标
        updatePosition();
        //重新绘制图片
        update();
        //碰撞检测
        collisionDetection();


    });
}

void MainScene::updatePosition()
{

    //更新地图坐标
    m_map.mapPosition();

    //发射子弹
    m_hero.shoot();
    //计算子弹坐标
    for(int i=0; i<BULLET_NUM; i++){
        //如果子弹状态为非空闲，计算发射位置
        if(!m_hero.m_bullets[i].m_Free){
            m_hero.m_bullets[i].updatePosition();
        }
    }

    //敌机坐标计算
    for(int i=0; i<ENEMY_NUM; i++){
        //如果敌机状态为非空闲，更新坐标
        if(m_enemys[i].m_Free == false){
            m_enemys[i].updatePosition();
        }
    }

    //计算爆炸播放的图片
        for(int k = 0 ; k < BOMB_NUM;k++)
        {
            if(m_bombs[k].m_Free == false)
            {
               m_bombs[k].updateInfo();
            }
        }

}

void MainScene::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);


    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY , m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY , m_map.m_map2);
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);

    //绘制子弹
    for(int i=0; i<BULLET_NUM; i++){
        //如果子弹状态为非空闲，计算发射位置
        if(!m_hero.m_bullets[i].m_Free){
            painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
        }
    }

    //绘制敌机
    for(int i=0; i<ENEMY_NUM; i++){
        if(m_enemys[i].m_Free == false){
            painter.drawPixmap(m_enemys[i].m_X,m_enemys[i].m_Y,m_enemys[i].m_enemy);
        }
    }

    //绘制爆炸图片
    for(int k = 0 ; k < BOMB_NUM;k++)
        {
            if(m_bombs[k].m_Free == false)
            {
               painter.drawPixmap(m_bombs[k].m_X,m_bombs[k].m_Y,m_bombs[k].m_pixArr[m_bombs[k].m_index]);
            }
        }
}

void MainScene::keyPressEvent(QKeyEvent *e)
{
    int x = m_hero.m_X;
    int y = m_hero.m_Y;

    if(e->key() == Qt::Key_Left){
        x -= HERO_MOVE_SPEED;
    }else if(e->key() == Qt::Key_Right){
        x += HERO_MOVE_SPEED;
    }else if(e->key() == Qt::Key_Up){
        y -= HERO_MOVE_SPEED;
    }else if(e->key() == Qt::Key_Down){
        y += HERO_MOVE_SPEED;
    }

    if(x <= 0){
        x = 0;
    }
    if(x >= GAME_WIDTH - m_hero.m_Plane.width()){
        x = GAME_WIDTH - m_hero.m_Plane.width();
    }
    if(y >= GAME_HEIGHT - m_hero.m_Plane.height()){
        y = GAME_HEIGHT - m_hero.m_Plane.height();
    }
    if(y <= 0){
        y = 0;
    }

    m_hero.setPosition(x,y);

}

void MainScene::enemyToScene()
{
    m_recorder++;
    if(m_recorder < ENEMY_INTERVAL){
        return;
    }

    m_recorder = 0;

    for(int i=0; i<ENEMY_NUM; i++){
        if(m_enemys[i].m_Free)
        {
            //敌机空闲状态改为false
            m_enemys[i].m_Free = false;
            //设置坐标
            m_enemys[i].m_X = rand()%(GAME_WIDTH - m_enemys[i].m_Rect.width());
            m_enemys[i].m_Y = -m_enemys[i].m_Rect.height();
            break;
        }
    }
}

void MainScene::collisionDetection()
{
    //遍历所有非空闲敌机
    for(int i=0; i<ENEMY_NUM; i++){
        if(m_enemys[i].m_Free){
            //空闲飞机跳转下一次循环
            continue;
        }

        //遍历所有非空闲子弹
        for(int j=0; j<BULLET_NUM; j++){
            if(m_hero.m_bullets[j].m_Free){
                //空闲子弹跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态
            if(m_enemys[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect)){

                m_enemys[i].m_Free = true;
                m_hero.m_bullets[j].m_Free = true;
                //播放音效
                QSound::play(SOUND_BOMB);
                //播放爆炸效果
                for(int k=0; k < BOMB_NUM; k++){
                    if(m_bombs[k].m_Free){
                        //爆炸状态设置为非空闲
                        m_bombs[k].m_Free = false;


                        //更新坐标
                        m_bombs[k].m_X = m_enemys[i].m_X;
                        m_bombs[k].m_Y = m_enemys[i].m_Y;
                        break;
                    }
                }
            }
//            if(m_enemys[i].m_Rect.intersects(m_hero.m_Rect)){
//                 m_enemys[i].m_Free = true;
//                 m_hero.m_Free = true;
//            }

        }
    }

}
