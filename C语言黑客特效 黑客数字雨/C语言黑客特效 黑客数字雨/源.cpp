/*
	�γ�����:�ڿ͵۹���ѧ��
	֪ʶ��:ѭ���������жϡ��ṹ��
*/

#include <stdio.h>
#include <graphics.h>  //ͼ�ο�ͷ�ļ�
#include <Windows.h>

#define WIDTH 960
#define HEIGTH 640
#define STR_SIZE 20  //������������󴢴�
#define STR_NUM 128  //�����������
#define STR_WIDTH 15  //�ַ������
struct Rain {  //��Ľṹ
	int x;  //�������������
	int y;  //������������
	int speed;  //�½��ٶ�
	char str[STR_SIZE];  //����������
}rain[STR_NUM];

char CreateCh() {
	char temp = 0;
	int flag = rand() % 3;  //���� 0 1 2 ��������
	if (flag == 0) {
		temp = rand() % 26 + 'a';  //����0~25Ȼ�����a���ǲ���a~z
	}
	else if (flag == 1) {
		temp = rand() % 26 + 'A';
	}
	else {
		temp = rand() % 10 + '0';  //ΪʲôҪ����0�أ�
	}

	return temp;
}

void GameInit() {
	//��ʼ����������
	for (int i = 0; i < STR_NUM; i++) {
		rain[i].x = i * STR_WIDTH;
		rain[i].y = rand() % WIDTH;
		rain[i].speed = rand() % 5 + 5;  //����5~10������
	}
	//��ʼ���ַ���
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
		if (t2 - t1 > 20) {  //ʹ��Ϸ������ʱ
			Gamespeed();
			t1 = t2;
		}
		t2 = GetTickCount();
		EndBatchDraw();
		//Sleep(20); //ʹ����������ʱ
	}

	getchar();
	closegraph();
	return 0;
}