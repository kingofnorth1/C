#include <stdio.h>
#include <graphics.h>
#include <math.h>
#define INTERVAL 22 //间隔距离
#define CHESS_SIZE_X 75.5 //格子宽度
#define CHESS_SIZE_Y 73
#define ROW 10 //行
#define COL 9 //列

//int num;定义整形
struct Chess {
	int x;
	int y;
	int id;//棋子名称
	int type;//红棋,还是黑棋
	bool river;//是否过了河 
};

enum Pieces {	//棋子
	SPACE = -1,
	車,馬,象,士,将,砲,卒,
	俥,马,相,仕,帥,炮,兵,
	BEGIN,END,//下棋标志
};
//给id赋值
enum Pieces redChess[] = { 車,馬,象,士,将,砲,卒 };
enum Pieces blackChess[] = { 俥,马,相,仕,帥,炮,兵 };
//绘制时转化成字符串
const char* ChessName[] = { "車","馬","象","士","将","砲","卒","俥","马","相","仕","帥","炮","兵" };

IMAGE img;//顶以图片数组
struct Chess map[ROW][COL];//二维数组表示地图
POINT begin = { -1,-1 }, end = { -1,-1 };//下棋坐标记录
enum Pieces state = BEGIN;
void GameInit() {
	//加载棋盘图片
	loadimage(&img, "./res/Chess.jpg");//改为多字节字符集
	//创建图形窗口
	initgraph(img.getwidth(), img.getheight(), 1);
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			enum Pieces chessID = SPACE;
			DWORD chessType = 0;
			if (i <= 4) {//黑棋
				chessType = BLACK;
				//设置第一行棋子
				if (i == 0) {
					if (k <= 4) {
						chessID = blackChess[k];//k 0 1 2 3 4
					}
					else {
						chessID = blackChess[8 - k];// 3 2 1 0  k 5 6 7 8
					}
				}
				//设置炮
				if (i == 2 && (k == 1 || k == 7)) {
					chessID = blackChess[5];
				}
				//设置卒
				if (i == 3 && k % 2 == 0) {
					chessID = blackChess[6];
				}
			}
			else {//红棋
				chessType = RED;
				//设置第一行棋子
				if (i == 9) {
					if (k <= 4) {
						chessID = redChess[k];//k 0 1 2 3 4
					}
					else {
						chessID = redChess[8 - k];// 3 2 1 0  k 5 6 7 8
					}
				}
				//设置炮
				if (i == 7 && (k == 1 || k == 7)) {
					chessID = redChess[5];
				}
				//设置卒
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
	//输出棋盘
	putimage(0, 0, &img);

	settextstyle(30, 0, "黑体");
	setbkmode(0);//设置文字背景透明
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			if (map[i][k].id != SPACE) {
				//设置填充颜色
				setfillcolor(RGB(249, 236, 192));
				setlinecolor(map[i][k].type); 
				setlinestyle(PS_SOLID, 2);
				settextcolor(map[i][k].type);
				//画棋子
				fillcircle(map[i][k].x, map[i][k].y, 30);
				fillcircle(map[i][k].x, map[i][k].y, 25);
				//绘制棋子文字
				outtextxy(map[i][k].x-13, map[i][k].y-13, ChessName[map[i][k].id]);
			}
		}
	}
}
void MouseControl() {
	//检测有没有鼠标消息
	if (MouseHit()) {
		MOUSEMSG msg = GetMouseMsg();
		//判断是否是鼠标左键消息
		if (msg.uMsg == WM_LBUTTONDOWN) {
			//把鼠标坐标转换成数组下标
			int row = (msg.y - INTERVAL) / CHESS_SIZE_Y;
			int col = (msg.x - INTERVAL) / CHESS_SIZE_X;
			if ((msg.x > map[row][col].x + 38) && (msg.y < map[row][col].y + 36)) {
				col++;	//左下角
			}
			if (msg.x < map[row][col].x + 38 && msg.y > map[row][col].y + 36) {
				row++;	//右上角
			}
			if (msg.x > map[row][col].x + 38 && msg.y > map[row][col].y + 36) {
				row++;	//左上角
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

//棋子移动判断
void ChessMove() {
	//红方和黑方将领,九宫格左上角下表
	if (!(begin.x == end.x && begin.y == end.y) && begin.x!=-1 && end.x!=-1 && 
			map[begin.x][begin.y].id != SPACE && map[end.x][end.y].id == SPACE) {
		POINT general[2] = { {0,3},{7,3} };
		switch (map[begin.x][begin.y].id) {
		case Pieces::将:
		case Pieces::帥:
			for (int t = 0; t < 2; t++) {
				for (int i = general[t].x; i <= general[t].x + 2; i++) {
					for (int k = general[t].y; k <= general[t].y + 2; k++) {
						//九宫格所有的下标 end 
						if (end.x == i && end.y == k && //不能出九宫格
							((begin.x == end.x) || (begin.y == end.y)) && // 只能走直线
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
		case Pieces::仕:
		case Pieces::士:
			for (int t = 0; t < 2; t++) {
				for (int i = general[t].x; i <= general[t].x + 2; i++) {
					for (int k = general[t].y; k <= general[t].y + 2; k++) {
						if (end.x == i && end.y == k && //不能出九宫格
							(begin.x != end.x) && (begin.y != end.y) && // 只能走直线
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
	//双缓冲绘图
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