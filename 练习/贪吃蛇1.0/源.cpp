#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>

#define up 'w'
#define down 's'
#define left 'a'
#define right 'd'

void welcome();               // ��ʼ����
void Finish();                // ��������
void creatgraph();            // Χǽ��ӡ
void gotoxy(int x, int y);    // �����ת����ΪX 0,1,2..
void gotoprint(int x, int y); // ��ת��ӡ
void gotodelete(int x, int y);// ��תɾ��
void creatfood();             // ʳ�����
int ClickControl();           // ��ȡ�����ź�
int Judge();                  // ��Ϸ�����ж�
void MovingBody();            // �ߵ��ƶ� 
void Eating();                // �߳Ե�������Ĳ������쳤��
void ChangeBody(int x, int y); // �ߵ�����任

/*ȫ�ֱ��� + Ԥ����*/
typedef struct Snakes
{
    int x;
    int y;
    struct Snakes* next;
}snake;

snake* head;    // ������ͷָ�� 

// ����������ʳ�� 
struct Food
{
    int x;
    int y;
}food;

char name[20];  // �����û��� ����Ȥ����������¼ϵͳ 
int score = 0;  // ���� 
char click = 1; // ��¼���µļ��̰��� 
int speed;      // �ٶ� ��ʵ���ӳٵĺ����� 

/************************************************************/

int main()
{
    system("color 0B"); // ���ÿ���̨������ɫ 
    welcome();          // ��ӭ���� 
    creatgraph();       // ������ͼ 
    creatfood();        // �½�ʳ�� 
    // ������갴�� ClickControl
    if (ClickControl() == 0) return 0;
    return 0;
}

/**********************************************************/
void welcome()
{
    gotoxy(15, 10);
    printf("/**********************************************/");
    gotoxy(15, 20);
    printf("/**********************************************/");
    gotoxy(20, 13);
    printf("WELCOME TO THE GAME OF RETRO SNAKE");
    gotoxy(14, 16);
    printf("����Ӣ�����뷨�в����������ƶ���ͬ�ڳԵ��Լ���wasd����p��ͣ");
    gotoxy(20, 18);
    printf("PLEASE ENTER YOUR NAME:");
    scanf_s("%s", &name, 20);
    system("cls");
}

/**********************************************************/
void creatgraph() {
    int i;
    /*
    ע�������������ÿ��+2 ��Ϊ����̨�ַ���߱�Ϊ1��2
    */
    for (i = 0; i < 58; i += 2)
    {
        gotoprint(i, 0);
        gotoprint(i, 26);
    }
    for (i = 1; i < 26; i++)
    {
        gotoprint(0, i);
        gotoprint(56, i);
    }
    gotoxy(63, 10);
    printf("hello %s,Welcome To Play", name);
    gotoxy(63, 15);
    printf("Your Score Is:%d    =���أ�= ", score);
    gotoxy(63, 20);
    printf("This Game Is Created By JOKER");
    head = (snake*)malloc(sizeof(snake));
    snake* p = (snake*)malloc(sizeof(snake));
    snake* q = (snake*)malloc(sizeof(snake));
    head->x = 16;
    head->y = 15;
    p->x = 16;
    p->y = 16;
    q->x = 16;
    q->y = 17;
    head->next = p;
    p->next = q;
    q->next = NULL;
}
/**********************************************************/
void gotoxy(int x, int y)
{
    // ���¹��λ�� 

      
    COORD pos;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOutput, pos);
    // ���ع�� 
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    SetConsoleCursorInfo(hOutput, &cursor);
}

/**********************************************************/
void gotoprint(int x, int y)
{
    gotoxy(x, y);
    printf("��");
}

/**********************************************************/
void gotodelete(int x, int y)
{
    gotoxy(x, y);
    printf("  ");
}

/**********************************************************/
void creatfood()
{
    // �������һ��ʳ�� 
    bool flag = false;
    while (!flag)
    {
        flag = true;
        srand((int)time(NULL));
        food.y = rand() % (25 - 1 + 1) + 1;
        food.x = rand() % (54 - 2 + 1) + 2;
        if (food.x % 2 != 0)
        {
            food.x = food.x + 1;
        }
        snake* judge = head;
        while (1)  //�����ų������ظ�
        {
            if (judge->next == NULL) break;
            if (food.x == judge->x && food.y == judge->y)
            {
                flag = false;
            }
            judge = judge->next;
        }
    }
    gotoxy(food.x, food.y);
    printf("��");
}

/**********************************************************/
// ������� ��Ϸ��ѭ�� 
int ClickControl()
{
    char c;
    while (1)
    {
        if (Judge() == 0) return 0;
        if (_kbhit())
        {
            click = _getch();
        }
        MovingBody();
        Eating();
    }
    return 1;
}

/**********************************************************/
void MovingBody() {
    int x = head->x, y = head->y;
    snake* p = head;
    // ͨ������պ��ӡʵ�ֶ���Ч��
    while (p->next != NULL) {
        p = p->next; 
    }
    gotodelete(p->x, p->y); // ����β�ڵ�
    switch (click)
    {
    case up:
        y -= 1;
        break;
    case down:
        y += 1;
        break;
    case left:
        x -= 2;
        break;
    case right:
        x += 2;
        break;
    default:
        break;
    }
    if (x != head->x || y != head->y) {
        // �ı�����ʱ���� ��ͣ��Ϸֹͣ������ 
        ChangeBody(x, y);
    }
    p = head;
    // ��ӡ��ͷ
    gotoprint(p->x, p->y);
    // ���ٶȿ��� 
    int count = score / 10;
    if (count <= 10) speed = 150;
    else if (count > 10 && count <= 20) speed = 100;
    else if (count > 20 && count <= 40) speed = 50;
    else speed = 10;
    Sleep(speed);
}

/**********************************************************/
// �Ե�ʳ�ﴦ�� ���һ��β�� 
void Eating()
{
    if (head->x == food.x && head->y == food.y)
    {
        creatfood();
        snake* _new = (snake*)malloc(sizeof(snake));
        snake* p;
        p = head;
        while (1)
        {
            if (p->next == NULL) break;
            p = p->next;
        }
        p->next = _new;
        _new->next = NULL;
        score += 10;
        gotoxy(77, 15);
        printf("%d", score);
    }
}

/**********************************************************/
// ������������ ֻ��Ҫ����β��� Ȼ�������������Ϊͷ��㼴�� 
void ChangeBody(int x, int y)
{
    snake* p = head;
    while (p->next->next != NULL) {
        p = p->next;
    }
    free(p->next);
    p->next = NULL;
    snake* new_head = (snake*)malloc(sizeof(snake));
    new_head->x = x;
    new_head->y = y;
    new_head->next = head;
    head = new_head;
}

/**********************************************************/
// �ж��Ƿ���Ϸ���� 
int Judge()
{
    if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)
    {
        Finish();
        return 0;
    }
    snake* p = head->next;
    while (1)
    {
        if (p == NULL) break;
        if (head->x == p->x && head->y == p->y)
        {
            Finish();
            return 0;
        }
        p = p->next;
    }
    return 1;
}

/**********************************************************/
void Finish()
{
    system("cls");
    gotoxy(15, 10);
    printf("/**********************************************/");
    gotoxy(15, 20);
    printf("/**********************************************/");
    gotoxy(18, 14);
    printf("GAME   OVER      o(*������*)o");
    gotoxy(20, 16);
    printf("Your Score is %d    hiahiahia", score);
    gotoxy(18, 18);
    printf("������Ŷ��     ����Ŭ��O(��_��)O");
    gotoxy(0, 27);
    // �ͷſռ� 
    snake* p = head, * q;
    while (p != NULL) {
        q = p->next;
        free(p);
        p = q;
    }
    system("pause");
}