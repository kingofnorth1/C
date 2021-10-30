/*
	课程内容:黑客帝国数学雨
	知识点:循环、条件判断、结构体
*/

#include <stdio.h>
#include <graphics.h>  //图形库头文件
#include <Windows.h>

#define WIDTH 960
#define HEIGTH 640
#define STR_SIZE 20  //数字雨数组最大储存
#define STR_NUM 128  //数字雨最大串数
#define STR_WIDTH 15  //字符串宽度
struct Rain {  //雨的结构
	int x;  //数字雨横向坐标
	int y;  //数字雨纵坐标
	int speed;  //下降速度
	char str[STR_SIZE];  //数字雨数组
}rain[STR_NUM];

char CreateCh() {
	char temp = 0;
	int flag = rand() % 3;  //产生 0 1 2 三个数字
	if (flag == 0) {
		temp = rand() % 26 + 'a';  //产生0~25然后加上a就是产生a~z
	}
	else if (flag == 1) {
		temp = rand() % 26 + 'A';
	}
	else {
		temp = rand() % 10 + '0';  //为什么要加上0呢？
	}

	return temp;
}

void GameInit() {
	//初始化基础数据
	for (int i = 0; i < STR_NUM; i++) {
		rain[i].x = i * STR_WIDTH;
		rain[i].y = rand() % WIDTH;
		rain[i].speed = rand() % 5 + 5;  //产生5~10的数字
	}
	//初始化字符串
	for (int i = 0; i < STR_NUM; i++) {
		for (int j = 0; j < STR_SIZE; j++) {
			rain[i].str[j] = CreateCh();
		}
	}
}

void GameDraw() {
	cleardevice();
	for (int i = 0; i < STR_NUM; i++) {
		for (int j = 0; j < STR_SIZE; j++) {
			outtextxy(rain[i].x, rain[i].y - STR_WIDTH * j, rain[i].str[j]);
			settextcolor(RGB(0, 255 - j * 13, 0));
		}
	}
}

void Gamespeed() {
	for (int i = 0; i < STR_NUM; i++) {
		rain[i].y += rain[i].speed;
		if (rain[i].y - STR_SIZE * STR_WIDTH > HEIGTH) {
			rain[i].y = 0;
		}
	}
}

void ChangeCh() {
	for (int i = 0; i < STR_NUM; i++) {
		rain[rand() % STR_NUM].str[rand() % STR_SIZE] = CreateCh();
	}
}

int main() {
	initgraph(WIDTH, HEIGTH);
	srand(GetTickCount());
	GameInit();
	DWORD t1, t2;
	t1 = t2 = GetTickCount();
	while (1) {
		BeginBatchDraw();
		GameDraw();
		ChangeCh();
		if (t2 - t1 > 20) {  //使游戏下落延时
			Gamespeed();
			t1 = t2;
		}
		t2 = GetTickCount();
		EndBatchDraw();
		//Sleep(20); //使整个程序延时
	}

	getchar();
	closegraph();
	return 0;
}