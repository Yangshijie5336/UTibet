#ifndef CONFIG_H
#define CONFIG_H

//游戏数据配置
#define GAME_WIDTH 512
#define GAME_HEIGHT 768
#define GAME_TITLE "飞机大战v10.0"
#define GAME_ICON "://res/app.ico"

//地图数据配置
#define MAP_PATH "://res/img_bg_level_1.jpg"
#define MAP_SCROLL_SPEED 2
#define GAME_RATE 10   //刷新间隔，帧率，单位毫秒

//飞机数据配置
#define HERO_PATH "://res/hero2.png"
#define HERO_MOVE_SPEED 40

//子弹数据配置
#define BULLET_PATH "://res/bullet_12.png"
#define BULLET_SPEED 5
#define BULLET_NUM 30   //弹匣中子弹总数
#define BULLET_INTERVAL 30   //发射子弹时间间隔

//敌机数据配置
#define ENEMY_PATH "://res/img-plane_7.png"
#define ENEMY_SPEED 5 
#define ENEMY_NUM 20
#define ENEMY_INTERVAL 30

//爆炸数据配置
#define BOMB_PATH "://res/bomb-%1.png"
#define BOMB_NUM 20
#define BOMB_MAX 7
#define BOMB_INTERVAL 20

//音效数据配置
#define SOUND_BACKGROUND "://res/bg.wav"
#define SOUND_BOMB "://res/bomb.wav"



#endif // CONFIG_H
