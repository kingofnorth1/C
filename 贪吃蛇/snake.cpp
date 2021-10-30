#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <mmsystem.h>//多媒体
#pragma comment(lib,"winmm.lib")//多媒体接口
/*
	课程内容：贪吃蛇
	课程讲师：顽石老师
	知识点：结构体，循环，函数,easyx,数组
*/
//做界面1，创建一个窗口，图形窗口
#define SNAKE_NUM 500//蛇的最大节数
enum DIR {  //表示蛇的方向
	UP,
	DOWN,
	LEFT,
	RIGHT
};
//蛇的结构
struct Snake {
	int size;//蛇的节数
	int dir;//蛇的方向
	int speed;//移动速度
	POINT coor[SNAKE_NUM];//坐标
}snake;
//食物结构
struct Food {
	int x;
	int y;
	int r;			//食物大小
	bool flag;		//食物是否被吃
	DWORD color;	//食物颜色
}food;
//数据的初始化
void GameInit() {
	//播放背景音乐
	mciSendString("open ./res/snake_bgm.mp3 alias BGM",0,0,0);
	mciSendString("play BGM repeat", 0, 0, 0);
	//init 初始化 graph图形窗口
	initgraph(640, 480/*,SHOWCONSOLE*/);
	//设置随机数种植 GetTickCount(),获取系统开机，到现在所经历的毫秒数
	srand(GetTickCount());
	//初始化蛇 一开始有三节
	snake.size = 10;
	snake.speed = 10;
	snake.dir=RIGHT;
	for (int i = 0; i < snake.size; i++) {
		snake.coor[i].x = 10*(snake.size-1-i)+20;
		snake.coor[i].y = 10;
	}
	//初始化食物  rand()随机产生一个整数，如果没有设置随机数种子，每次产生的都是固定的整数 2 % 5 == 2
	//设置种子需要头文件stdlib.h 一般把时间作为种子，因为时间是在不断变化的
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}
void GameDraw() {
	//双缓冲绘图
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//绘制蛇
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//绘制食物
	if (food.flag) {
		solidcircle(food.x, food.y,food.r);
	}
	EndBatchDraw();

}
//移动蛇
void snakeMove() {
	//让身体跟着3头移动
	for (int i = snake.size-1; i >0; i--) {
		snake.coor[i] = snake.coor[i-1];
	}
	//移动是什么发生改变
	switch (snake.dir) {
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y+10 <= 0) {//超出了上面的边界
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y+=snake.speed;
		if (snake.coor[0].y-10 >= 480) {
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x-=snake.speed;
		if (snake.coor[0].x+10 <= 0) {
			snake.coor[0].x=640;
		}
		break;
	case RIGHT:
		snake.coor[0].x+=snake.speed;
		if (snake.coor[0].x-10 >= 640) {
			snake.coor[0].x=0;
		}
		break;
	}
}
//通过按键改变蛇的移动方向
void keyControl() {
	//判断有没有按键，如果有按键返回真
	if (_kbhit()) {	
		//72 80 75 77 上下左右键值
		switch (_getch()) {
		case 'w':
		case 'W':
		case 72:
			//改变方向
			if (snake.dir != DOWN) {
				snake.dir = UP;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != UP) {
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT) {
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT) {
				snake.dir = RIGHT;
			}
			break;
		case ' ': //游戏暂停逻辑
			while (1) {
				if (_getch() == ' ')
					return;
			}
		}
	}
}
void EatFood() {
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r) {

		food.flag = false;
		snake.size++;
	}
	//如果食物消失，则重新生成一个食物
	if (!food.flag) {
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}
//游戏暂停
bool snakebool(){   //自己写的东西
	for (int i = snake.size; i>0; i--) {
		if (snake.coor[0].x == snake.coor[i].x || snake.coor[0].y == snake.coor[i].y) {
			return true;
		}
		else
			return false;
	}
} 
int main() {
	GameInit();

	while (1) {
		snakeMove();
		GameDraw();
		keyControl();
		EatFood();
		/*if (snakebool()) {
			break;
		}*/
		Sleep(200);
	}
	//printf("游戏结束");
	return 0;
}