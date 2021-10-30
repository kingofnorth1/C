#include <stdio.h>
#include <graphics.h>
#include <math.h>
#define INTERVAL 22 //�������
#define CHESS_SIZE_X 75.5 //���ӿ��
#define CHESS_SIZE_Y 73
#define ROW 10 //��
#define COL 9 //��

//int num;��������
struct Chess {
	int x;
	int y;
	int id;//��������
	int type;//����,���Ǻ���
	bool river;//�Ƿ���˺� 
};

enum Pieces {	//����
	SPACE = -1,
	܇,�R,��,ʿ,��,�h,��,
	�e,��,��,��,��,��,��,
	BEGIN,END,//�����־
};
//��id��ֵ
enum Pieces redChess[] = { ܇,�R,��,ʿ,��,�h,�� };
enum Pieces blackChess[] = { �e,��,��,��,��,��,�� };
//����ʱת�����ַ���
const char* ChessName[] = { "܇","�R","��","ʿ","��","�h","��","�e","��","��","��","��","��","��" };

IMAGE img;//����ͼƬ����
struct Chess map[ROW][COL];//��ά�����ʾ��ͼ
POINT begin = { -1,-1 }, end = { -1,-1 };//���������¼
enum Pieces state = BEGIN;
void GameInit() {
	//��������ͼƬ
	loadimage(&img, "./res/Chess.jpg");//��Ϊ���ֽ��ַ���
	//����ͼ�δ���
	initgraph(img.getwidth(), img.getheight(), 1);
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			enum Pieces chessID = SPACE;
			DWORD chessType = 0;
			if (i <= 4) {//����
				chessType = BLACK;
				//���õ�һ������
				if (i == 0) {
					if (k <= 4) {
						chessID = blackChess[k];//k 0 1 2 3 4
					}
					else {
						chessID = blackChess[8 - k];// 3 2 1 0  k 5 6 7 8
					}
				}
				//������
				if (i == 2 && (k == 1 || k == 7)) {
					chessID = blackChess[5];
				}
				//������
				if (i == 3 && k % 2 == 0) {
					chessID = blackChess[6];
				}
			}
			else {//����
				chessType = RED;
				//���õ�һ������
				if (i == 9) {
					if (k <= 4) {
						chessID = redChess[k];//k 0 1 2 3 4
					}
					else {
						chessID = redChess[8 - k];// 3 2 1 0  k 5 6 7 8
					}
				}
				//������
				if (i == 7 && (k == 1 || k == 7)) {
					chessID = redChess[5];
				}
				//������
				if (i == 6 && k % 2 == 0) {
					chessID = redChess[6];
				}
			}

			map[i][k].id=chessID;
			map[i][k].type=chessType;
			map[i][k].river = false;
			map[i][k].x = k*CHESS_SIZE_X+INTERVAL;
			map[i][k].y = i*CHESS_SIZE_Y+INTERVAL;
		}
	}
}
void GameDarw(){
	//�������
	putimage(0, 0, &img);

	settextstyle(30, 0, "����");
	setbkmode(0);//�������ֱ���͸��
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			if (map[i][k].id != SPACE) {
				//���������ɫ
				setfillcolor(RGB(249, 236, 192));
				setlinecolor(map[i][k].type); 
				setlinestyle(PS_SOLID, 2);
				settextcolor(map[i][k].type);
				//������
				fillcircle(map[i][k].x, map[i][k].y, 30);
				fillcircle(map[i][k].x, map[i][k].y, 25);
				//������������
				outtextxy(map[i][k].x-13, map[i][k].y-13, ChessName[map[i][k].id]);
			}
		}
	}
}
void MouseControl() {
	//�����û�������Ϣ
	if (MouseHit()) {
		MOUSEMSG msg = GetMouseMsg();
		//�ж��Ƿ�����������Ϣ
		if (msg.uMsg == WM_LBUTTONDOWN) {
			//���������ת���������±�
			int row = (msg.y - INTERVAL) / CHESS_SIZE_Y;
			int col = (msg.x - INTERVAL) / CHESS_SIZE_X;
			if ((msg.x > map[row][col].x + 38) && (msg.y < map[row][col].y + 36)) {
				col++;	//���½�
			}
			if (msg.x < map[row][col].x + 38 && msg.y > map[row][col].y + 36) {
				row++;	//���Ͻ�
			}
			if (msg.x > map[row][col].x + 38 && msg.y > map[row][col].y + 36) {
				row++;	//���Ͻ�
				col++;
			}
			printf("rowcol(%d,%d)\n", row, col);
			if (state == BEGIN) {
				begin.x = row;
				begin.y = col;
				state = END;
			}
			else if (state == END) {
				end.x = row;
				end.y = col;
				state = BEGIN;
			}
		}
	}
}

//�����ƶ��ж�
void ChessMove() {
	//�췽�ͺڷ�����,�Ź������Ͻ��±�
	if (!(begin.x == end.x && begin.y == end.y) && begin.x!=-1 && end.x!=-1 && 
			map[begin.x][begin.y].id != SPACE && map[end.x][end.y].id == SPACE) {
		POINT general[2] = { {0,3},{7,3} };
		switch (map[begin.x][begin.y].id) {
		case Pieces::��:
		case Pieces::��:
			for (int t = 0; t < 2; t++) {
				for (int i = general[t].x; i <= general[t].x + 2; i++) {
					for (int k = general[t].y; k <= general[t].y + 2; k++) {
						//�Ź������е��±� end 
						if (end.x == i && end.y == k && //���ܳ��Ź���
							((begin.x == end.x) || (begin.y == end.y)) && // ֻ����ֱ��
							(abs(end.x - begin.x) == 1 || abs(end.y - begin.y) == 1)) {
							map[end.x][end.y].id = map[begin.x][begin.y].id;
							map[end.x][end.y].river = map[begin.x][begin.y].river;
							map[end.x][end.y].type = map[begin.x][begin.y].type;
							map[begin.x][begin.y].id = SPACE;
							//printf("%d ", map[end.x][end.y].id);
						}
					}
				}
			}
			break;
		case Pieces::��:
		case Pieces::ʿ:
			for (int t = 0; t < 2; t++) {
				for (int i = general[t].x; i <= general[t].x + 2; i++) {
					for (int k = general[t].y; k <= general[t].y + 2; k++) {
						if (end.x == i && end.y == k && //���ܳ��Ź���
							(begin.x != end.x) && (begin.y != end.y) && // ֻ����ֱ��
							abs(end.x - begin.x) == 1 && abs(end.y - begin.y) == 1) {
							map[end.x][end.y].id = map[begin.x][begin.y].id;
							map[end.x][end.y].river = map[begin.x][begin.y].river;
							map[end.x][end.y].type = map[begin.x][begin.y].type;
							map[begin.x][begin.y].id = SPACE;
						}
					}
				}
			}
			break;
		default:
			break;
		}
	}
}
int main() {
	GameInit();
	//˫�����ͼ
	BeginBatchDraw();
	while (1) {
		GameDarw();
		FlushBatchDraw();
		MouseControl();
		ChessMove();
	}

	getchar();
	return 0;
}