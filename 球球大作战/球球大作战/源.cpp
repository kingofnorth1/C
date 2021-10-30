/*
    ����:�������ս
*/
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <graphics.h>  //������ͼ�ο�
#include <windows.h>
#include <Mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
#define HEIGHT 640
#define WIDTH 1024  
#define MAP_HEIGHT (HEIGHT*3)
#define MAP_WIDTH (WIDTH*3) 
#define FOOD_NUM 100	//ʳ��
//��� ʳ�� ai    ->���� ����(x,y) ��ɫ  ��:radius  flag ����ͬ������,��ô�ýṹ��

struct Ball {		//��Ľṹ
	int x;
	int y;
	int r;  //�뾶
	bool flag;  //�Ƿ��� true false
	DWORD color;
};
struct Ball player;
struct Ball food[FOOD_NUM];
//��ͼ ͼƬ
IMAGE map(MAP_WIDTH, MAP_HEIGHT);
//���������
POINT g_camreaPos;

void createFood(int i) {
	food[i].x = rand() % MAP_WIDTH;
	food[i].y = rand() % MAP_HEIGHT;
	food[i].r = rand() % 5 + 1;  //1 2 3 4 5
	food[i].flag = true;
	food[i].color = RGB(rand() % 256, rand() % 256, rand() % 256);  //ʹ����ԭɫ�ϳ�һ����ɫ
}
void gameInit() {
	mciSendString(L"open �������ֶӡ��޺����ġ�.mp3 alisa BGM", NULL, 0, NULL);
	mciSendString(L"play BGM", NULL, 0, NULL);
	PlaySound(TEXT("D:\\c����\\C���� ������\\�������ս\\�������ս\\�������ֶӡ��޺����ġ�.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//���������
	srand((unsigned)time(NULL));
	//��ʼ�����
	player.x = rand()%MAP_HEIGHT;
	player.y = rand()%MAP_WIDTH;
	player.r = 10;
	player.flag = true;
	//��ʼ��ʳ��
	for (int i = 0; i < FOOD_NUM; i++) {
		createFood(i);
	}
}

void gameDraw() {
	//���û��Ƶ��豸(ͼƬ)  ����Ҳ��һ��ͼƬ
	SetWorkingImage(&map);
	//���ñ�����ɫ
	setbkcolor(WHITE);
	cleardevice();  //����  ���ͼ�ο�
	//������
	setlinecolor(RGB(230, 231, 239));
	for (int i = 0; i < MAP_WIDTH; i+=10) {
		line(i, 0, i, MAP_HEIGHT);  //����
		line(0, i, MAP_WIDTH, i);  //����
	}

	//����ʳ��
	for (int i = 0; i < FOOD_NUM; i++) {
		if (!food[i].flag)
			continue;
		setfillcolor(food[i].color);
		solidcircle(food[i].x, food[i].y, food[i].r);
	}
	//�������
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
	//��map�����������
	//putimage(0, 0, &map);
	//void putimage(int dstX, int dstY, const IMAGE * pSrcImg, DWORD dwRop = SRCCOPY);												// ����ͼ����Ļ
	//void putimage(int dstX, int dstY, int dstWidth, int dstHeight, const IMAGE * pSrcImg, int srcX, int srcY, DWORD dwRop = SRCCOPY);		// ����ͼ����Ļ(ָ�����)
	putimage(0, 0, WIDTH, HEIGHT, &map, g_camreaPos.x, g_camreaPos.y); {
		//�����Ϊ���ģ����������������
		g_camreaPos.x = player.x - WIDTH / 2;
		g_camreaPos.y = player.y - HEIGHT / 2;
		//��ֹ�����Խ��
		if (g_camreaPos.x < 0) g_camreaPos.x = 0;
		if (g_camreaPos.y < 0)g_camreaPos.y = 0;
		if (g_camreaPos.x > MAP_WIDTH - WIDTH) g_camreaPos.x = MAP_WIDTH - WIDTH;
		if (g_camreaPos.y > MAP_HEIGHT - HEIGHT)g_camreaPos.y = MAP_HEIGHT - HEIGHT;
	}
}
//��������ƶ�
void movePlayer(int speed) {
#if 0
	//�ֶ�����,��ȡ���̰�����getchar()  scanf gets  ���ϸ���������֮����Ҫ���س�
	//_getch()	 ���¼��ɴ���������Ҫ�س�  ��Ҫ����ͷ�ļ�conio.h
	char key = _getch();
	switch (key) {
	case 72:		//��
		player.y -= 2;
		break;
	case 80:		//��
		player.y += 2;
		break;
	case 75:		//��
		player.x -= 2;
		break;
	case 77:		//��
		player.x += 2;
		break;
	}
#else
	//getasynckeystate()	��ȡ�첽����״̬  ���������_getch()������,���ҿ���֧��ͬʱ����
	if (GetAsyncKeyState(VK_UP)) {   //vk virtual key  �����ֵ
		player.y -= speed;
	}
	if (GetAsyncKeyState(VK_DOWN)) {   //vk virtual key  �����ֵ
		player.y += speed;
	}
	if (GetAsyncKeyState(VK_LEFT)) {   //vk virtual key  �����ֵ
		player.x -= speed;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {   //vk virtual key  �����ֵ
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
			//ʳ����������
			createFood(i);
		}
	}
}
/*
	ai:��������ƣ���Ҫ������ƶ�(��ai��׷2��� ��ʳ�� �����)
	��ʼ�� ���� ...

*/


int main() {
	//�ڴ���->ͼ�δ���
	initgraph(1024, 640, EW_SHOWCONSOLE);

	gameInit();
	printf("%d %d %d %d", player.x, player.y, player.r, player.flag);
	system("cls");  //����  ��Կ���̨��
	//��������.˫����
	BeginBatchDraw();
	while (1) {
		gameDraw();
		movePlayer(5);
		PlayEatFood();

		FlushBatchDraw();  //ˢ�£����ڴ�����������ȴ���
		//Sleep(50);
	}
	closegraph();
	return 0;
}