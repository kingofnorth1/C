#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>
#include <mmsystem.h>//��ý��
#pragma comment(lib,"winmm.lib")//��ý��ӿ�
/*
	�γ����ݣ�̰����
	�γ̽�ʦ����ʯ��ʦ
	֪ʶ�㣺�ṹ�壬ѭ��������,easyx,����
*/
//������1������һ�����ڣ�ͼ�δ���
#define SNAKE_NUM 500//�ߵ�������
enum DIR {  //��ʾ�ߵķ���
	UP,
	DOWN,
	LEFT,
	RIGHT
};
//�ߵĽṹ
struct Snake {
	int size;//�ߵĽ���
	int dir;//�ߵķ���
	int speed;//�ƶ��ٶ�
	POINT coor[SNAKE_NUM];//����
}snake;
//ʳ��ṹ
struct Food {
	int x;
	int y;
	int r;			//ʳ���С
	bool flag;		//ʳ���Ƿ񱻳�
	DWORD color;	//ʳ����ɫ
}food;
//���ݵĳ�ʼ��
void GameInit() {
	//���ű�������
	mciSendString("open ./res/snake_bgm.mp3 alias BGM",0,0,0);
	mciSendString("play BGM repeat", 0, 0, 0);
	//init ��ʼ�� graphͼ�δ���
	initgraph(640, 480/*,SHOWCONSOLE*/);
	//�����������ֲ GetTickCount(),��ȡϵͳ�������������������ĺ�����
	srand(GetTickCount());
	//��ʼ���� һ��ʼ������
	snake.size = 10;
	snake.speed = 10;
	snake.dir=RIGHT;
	for (int i = 0; i < snake.size; i++) {
		snake.coor[i].x = 10*(snake.size-1-i)+20;
		snake.coor[i].y = 10;
	}
	//��ʼ��ʳ��  rand()�������һ�����������û��������������ӣ�ÿ�β����Ķ��ǹ̶������� 2 % 5 == 2
	//����������Ҫͷ�ļ�stdlib.h һ���ʱ����Ϊ���ӣ���Ϊʱ�����ڲ��ϱ仯��
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = rand() % 10 + 5;
	food.flag = true;
}
void GameDraw() {
	//˫�����ͼ
	BeginBatchDraw();
	//���ñ�����ɫ
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//������
	setfillcolor(GREEN);
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//����ʳ��
	if (food.flag) {
		solidcircle(food.x, food.y,food.r);
	}
	EndBatchDraw();

}
//�ƶ���
void snakeMove() {
	//���������3ͷ�ƶ�
	for (int i = snake.size-1; i >0; i--) {
		snake.coor[i] = snake.coor[i-1];
	}
	//�ƶ���ʲô�����ı�
	switch (snake.dir) {
	case UP:
		snake.coor[0].y-=snake.speed;
		if (snake.coor[0].y+10 <= 0) {//����������ı߽�
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
//ͨ�������ı��ߵ��ƶ�����
void keyControl() {
	//�ж���û�а���������а���������
	if (_kbhit()) {	
		//72 80 75 77 �������Ҽ�ֵ
		switch (_getch()) {
		case 'w':
		case 'W':
		case 72:
			//�ı䷽��
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
		case ' ': //��Ϸ��ͣ�߼�
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
	//���ʳ����ʧ������������һ��ʳ��
	if (!food.flag) {
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}
//��Ϸ��ͣ
bool snakebool(){   //�Լ�д�Ķ���
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
	//printf("��Ϸ����");
	return 0;
}