#ifndef _HOTEL_H_INCLUDED
#define _HOTEL_H_INCLUDED

#define QUIT 5
#define HOTEL1 180.00
#define HOTEL2 225.00
#define HOTEL3 255.00
#define HOTEL4 355.00
#define DISCOUNT 0.95
#define STARS "*************************"

//显示选择列表
int menu(void);

//根据预定的天数
int gennights(void);

//根据费率、入驻天数计算费用
//并显示结果
void showprice(double rate, int nights);

#endif