/*
    名称:球球大作战
*/
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <graphics.h>  //第三方图形库
#include <windows.h>
#include <Mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
#define HEIGHT 640
#define WIDTH 1024  
#define MAP_HEIGHT (HEIGHT*3)
#define MAP_WIDTH (WIDTH*3) 
#define FOOD_NUM 100	//食物
//玩家 食物 ai    ->属性 坐标(x,y) 颜色  球:radius  flag 描述同类事物,那么用结构体

struct Ball {		//球的结构
	int x;
	int y;
	int r;  //半径
	bool flag;  //是否存活 true false
	DWORD color;
};
struct Ball player;
struct Ball food[FOOD_NUM];
//地图 图片
IMAGE map(MAP_WIDTH, MAP_HEIGHT);
//摄像机坐标
POINT g_camreaPos;

void createFood(int i) {
	food[i].x = rand() % MAP_WIDTH;
	food[i].y = rand() % MAP_HEIGHT;
	food[i].r = rand() % 5 + 1;  //1 2 3 4 5
	food[i].flag = true;
	food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);  //使用三原色合成一个颜色
}
void gameInit() {
	mciSendString(L"open 马赛克乐队《霓虹甜心》.mp3 alisa BGM", NULL, 0, NULL);
	mciSendString(L"play BGM", NULL, 0, NULL);
	PlaySound(TEXT("D:\\c语言\\C语言 软件设计\\球球大作战\\球球大作战\\马赛克乐队《霓虹甜心》.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//随机数种子
	srand((unsigned)time(NULL));
	//初始化玩家
	player.x = rand()%MAP_HEIGHT;
	player.y = rand()%MAP_WIDTH;
	player.r = 10;
	player.flag = true;
	//初始化食物
	for (int i = 0; i < FOOD_NUM; i++) {
		createFood(i);
	}
}

void gameDraw() {
	//设置绘制的设备(图片)  窗口也是一张图片
	SetWorkingImage(&map);
	//设置背景颜色
	setbkcolor(WHITE);
	cleardevice();  //清屏  针对图形框
	//画格子
	setlinecolor(RGB(230, 231, 239));
	for (int i = 0; i < MAP_WIDTH; i+=10) {
		line(i, 0, i, MAP_HEIGHT);  //竖线
		line(0, i, MAP_WIDTH, i);  //横线
	}

	//绘制食物
	for (int i = 0; i < FOOD_NUM; i++) {
		if (!food[i].flag)
			continue;
		setfillcolor(food[i].color);
		solidcircle(food[i].x, food[i].y, food[i].r);
	}
	//绘制玩家
	setfillcolor(RED);
	if (player.x<0)
		player.x = 0;
	if (player.y < 0)
		player.y = 0;
	if (player.x > MAP_WIDTH)
		player.x = MAP_WIDTH;
	if (player.y > MAP_HEIGHT)
		player.y = MAP_HEIGHT;
	solidcircle(player.x, player.y, player.r);
	SetWorkingImage();
	//把map输出到窗口上
	//putimage(0, 0, &map);
	//void putimage(int dstX, int dstY, const IMAGE * pSrcImg, DWORD dwRop = SRCCOPY);												// 绘制图像到屏幕
	//void putimage(int dstX, int dstY, int dstWidth, int dstHeight, const IMAGE * pSrcImg, int srcX, int srcY, DWORD dwRop = SRCCOPY);		// 绘制图像到屏幕(指定宽高)
	putimage(0, 0, WIDTH, HEIGHT, &map, g_camreaPos.x, g_camreaPos.y); {
		//以玩家为中心，计算摄像机的坐标
		g_camreaPos.x = player.x - WIDTH / 2;
		g_camreaPos.y = player.y - HEIGHT / 2;
		//防止摄像机越界
		if (g_camreaPos.x < 0) g_camreaPos.x = 0;
		if (g_camreaPos.y < 0)g_camreaPos.y = 0;
		if (g_camreaPos.x > MAP_WIDTH - WIDTH) g_camreaPos.x = MAP_WIDTH - WIDTH;
		if (g_camreaPos.y > MAP_HEIGHT - HEIGHT)g_camreaPos.y = MAP_HEIGHT - HEIGHT;
	}
}
//控制玩家移动
void movePlayer(int speed) {
#if 0
	//手动控制,获取键盘按键，getchar()  scanf gets  不合格，输入数据之后，需要按回车
	//_getch()	 按下即可触发，不需要回车  需要包含头文件conio.h
	char key = _getch();
	switch (key) {
	case 72:		//上
		player.y -= 2;
		break;
	case 80:		//下
		player.y += 2;
		break;
	case 75:		//左
		player.x -= 2;
		break;
	case 77:		//右
		player.x += 2;
		break;
	}
#else
	//getasynckeystate()	获取异步按键状态  这个函数比_getch()更流畅,而且可以支持同时按键
	if (GetAsyncKeyState(VK_UP)) {   //vk virtual key  虚拟键值
		player.y -= speed;
	}
	if (GetAsyncKeyState(VK_DOWN)) {   //vk virtual key  虚拟键值
		player.y += speed;
	}
	if (GetAsyncKeyState(VK_LEFT)) {   //vk virtual key  虚拟键值
		player.x -= speed;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {   //vk virtual key  虚拟键值
		player.x += speed;
	}
#endif
}
double distance(struct Ball *b1, struct Ball *b2) {
	return sqrt((b1->x - b2->x)* (b1->x - b2->x) + (b1->y - b2->y) * (b1->y - b2->y));
}
void PlayEatFood() {
	for (int i = 0; i < FOOD_NUM; i++) {
		if (food[i].flag && distance(&food[i],&player) < player.r) {
			food[i].flag = false;
			player.r += food[i].r / 2;
			//食物重新生成
			createFood(i);
		}
	}
}
/*
	ai:和玩家类似，主要是如何移动(让ai来追2玩家 吃食物 互相吃)
	初始化 绘制 ...

*/


int main() {
	//黑窗口->图形窗口
	initgraph(1024, 640, EW_SHOWCONSOLE);

	gameInit();
	printf("%d %d %d %d", player.x, player.y, player.r, player.flag);
	system("cls");  //清屏  针对控制台的
	//闪屏现象.双缓冲
	BeginBatchDraw();
	while (1) {
		gameDraw();
		movePlayer(5);
		PlayEatFood();

		FlushBatchDraw();  //刷新，把内存里面的数据先储存
		//Sleep(50);
	}
	closegraph();
	return 0;
}