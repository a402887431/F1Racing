#include "stdafx.h"
#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 800

#define DELTA_TIME 1
IMAGE background, ground;

IMAGE car, car_mask;
IMAGE xuhuan, xuhuan_mask, fire, fire_mask, pikaqiu, pikaqiu_mask;
IMAGE Fire, Fire_mask, lightning, lightning_mask;
IMAGE wall, wall_mask;
int property = 0, skill = 0, skilltime=0;

int temp;
int BACKGROUND_SCROLL_SPEED = 8; 
int GROUND_SCROLL_SPEED = 10;
int BACKGROUND_LOOPING_POINT = 1030;//413

int backgroundScroll;
int groundScroll;
int Carspeed;
int car_x;
int car_y;

int Xuhuan_x, fire_x, pikaqiu_x;
int Xuhuan_y, fire_y, pikaqiu_y;

int skill_x;
int skill_y;

int wall_x;
int wall_y;

 
void Startup() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//画布 
	loadimage(&background, _T("timg3.jpg"), 512, 2048);
	loadimage(&car, _T("WhiteCar.png"), 150, 150);
	loadimage(&car_mask, _T("WhiteCar_mask.png"), 150, 150);
	loadimage(&xuhuan, _T("Xuhuanguoshi.png"), 50, 50);
	loadimage(&xuhuan_mask, _T("Xuhuanguosh.png"), 50, 50);
	loadimage(&fire, _T("Fight.png"), 60, 60);
	loadimage(&fire_mask, _T("Fight1.png"), 60, 60);
	loadimage(&pikaqiu, _T("pikaqiu.png"), 80, 80);
	loadimage(&pikaqiu_mask, _T("pikaqiu1.png"), 80, 80);
	loadimage(&Fire, _T("Fire.png"), 150, 150);
	loadimage(&Fire_mask, _T("Fire1.png"), 150, 150);
	loadimage(&lightning, _T("电.png"), 150, 150);
	loadimage(&lightning_mask, _T("电1.png"), 150, 150);
	loadimage(&wall, _T("wang.png"), 150, 150);
	loadimage(&wall_mask, _T("Wang1.png"), 150, 150);
	

	car_x = 40;
	temp = car_x + 260;
	car_y = 0;
	Carspeed = 30;
	Xuhuan_x = 80;
	Xuhuan_y = 600;
	fire_x = 340;
	fire_y = 600;
	pikaqiu_x = 340;
	pikaqiu_y = 500;
	wall_x = 200;
	wall_y = 400;

	skill_x = car_x;
	skill_y = car_y + 150;
	BeginBatchDraw();


}
void Showword() {
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	settextstyle(20, 0, _T("黑体"));
	char s[5];
	sprintf_s(s, "%d", skilltime);
	outtextxy(340, 0, "进化时间还剩：");
	outtextxy(480, 0, s);
}
void Show() {
	
	putimage(0, -backgroundScroll, &background);
	putimage(car_x, car_y, &car_mask, NOTSRCERASE);
	putimage(car_x, car_y, &car, SRCERASE);
	putimage(Xuhuan_x, Xuhuan_y, &xuhuan_mask, NOTSRCERASE);
	putimage(Xuhuan_x, Xuhuan_y, &xuhuan, SRCERASE);
	putimage(fire_x, fire_y, &fire_mask, NOTSRCERASE);
	putimage(fire_x, fire_y, &fire, SRCERASE);
	putimage(pikaqiu_x, pikaqiu_y, &pikaqiu_mask, NOTSRCERASE);
	putimage(pikaqiu_x, pikaqiu_y, &pikaqiu, SRCERASE);
	putimage(wall_x, wall_y, &wall_mask, NOTSRCERASE);
	putimage(wall_x, wall_y, &wall, SRCERASE);
	if (property != 0) {
		Showword();
	}
	FlushBatchDraw();


}

void UpdateWithoutInput(int dt)
{
	srand(time(NULL));
	backgroundScroll = (backgroundScroll + BACKGROUND_SCROLL_SPEED * dt) % BACKGROUND_LOOPING_POINT;
	groundScroll = (groundScroll + GROUND_SCROLL_SPEED * dt) % WINDOW_HEIGHT;
	Sleep(Carspeed);
	Xuhuan_y = Xuhuan_y - 5;
	pikaqiu_y = pikaqiu_y - 5;
	fire_y = fire_y - 5;
	if (Xuhuan_y<-20) {
		Xuhuan_y = 900;
	}
	if (fire_y < -20) {
		
		fire_y = rand() % 900 + 700;
	}
	if (pikaqiu_y <-20) {
		pikaqiu_y = 900;
	}
	if (Xuhuan_y > car_y && Xuhuan_x - 40 == car_x && Xuhuan_y < 70)
	{
		if (property == 0) {
			 

			
			loadimage(&car_mask, _T("Change.png"), 150, 150);
			property = 1;//1为虚幻状态
			skill = 1;//1为无敌
			skilltime = 100;
		}
	}
	if (pikaqiu_y > car_y && pikaqiu_x - 40 == car_x && pikaqiu_y < 70)
	{
		if (property == 0) {

			
			loadimage(&car, _T("pika.png"), 150, 150);
			loadimage(&car_mask, _T("pikahei.png"), 150, 150);
			property = 2;//2为皮卡丘状态
			skill = 2;//2为雷电
			skilltime = 200;
		}
	}
	if (fire_y > car_y && fire_x - 40 == car_x && fire_y < 70)
	{
		if (property == 0) {

			
			loadimage(&car, _T("penhuolong.png"), 150, 150);
			loadimage(&car_mask, _T("penhuolong1.png"), 150, 150);
			property = 3;//3为喷火龙状态
			skill = 3;//3为喷火 
			skilltime = 200;
		}
	}
	if (car_x > temp) {
		car_x = temp;
	}
	if (car_x < 0) {

		car_x = 40;
	}
	if (property != 0) {
		skilltime--;
		if (skilltime <= 0) {
			loadimage(&car, _T("WhiteCar.png"), 150, 150);
			loadimage(&car_mask, _T("WhiteCar_mask.png"), 150, 150);
			property = 0;
			skill = 0;
		}
	}
	


}
void UpdateWithInput() {
	if (_kbhit()) {
		char c = _getch();
		switch (c)
		{
		case 'd':
			car_x = car_x + 260;
			skill_x = car_x;
			break;
		case 'a':
			car_x = car_x - 260;
			skill_x = car_x;

			break;
		case ' ':
			switch (skill)
			{
			case 2:
				putimage(skill_x, skill_y, &lightning_mask, NOTSRCERASE);
				putimage(skill_x, skill_y, &lightning, SRCERASE);
				break;
			case 3:
				putimage(skill_x, skill_y, &Fire_mask, NOTSRCERASE);
				putimage(skill_x, skill_y, &Fire, SRCERASE);
				break;
			default:
				break;
			}
			FlushBatchDraw();
			Sleep(50);
			break;
		default:
			break;
		}

	}

}
