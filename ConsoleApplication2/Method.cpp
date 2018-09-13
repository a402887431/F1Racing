#include "stdafx.h"
#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 800

#define DELTA_TIME 1

typedef struct wall {
	int wall_x;
	int wall_y;
}WALL;
WALL A[6];
IMAGE background, ground;

IMAGE car, car_mask;
IMAGE xuhuan, xuhuan_mask, fire, fire_mask, pikaqiu, pikaqiu_mask;
IMAGE Fire, Fire_mask, lightning, lightning_mask;
IMAGE wall, wall_mask;
IMAGE Background;
IMAGE GetScoreb;
int property = 0, skill = 0, skilltime = 0, GetScore;

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

int step;

int wall_speed;

int i;


int WallCrash() {
	for (i = 0; i < 6; i++) {

		if (A[i].wall_y > car_y && A[i].wall_x == car_x && A[i].wall_y < 70)
		{
			EndBatchDraw();
			End(GetScore);
			Go();
			Startup();
			break;
		}
	}
	return 0;
}
void Loadimage() {
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
	loadimage(&Background, _T("GoBackground.png"));
	loadimage(&GetScoreb, _T("GetScore.png"));
}
void Startup() {
	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);//画布 
	// 设置窗口标题文字
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "绝地赛车 v1.0");
	car_x = 40;
	temp = car_x + 260;
	car_y = 0;
	Carspeed = 18;
	Xuhuan_x = 80;
	Xuhuan_y = 6000;
	fire_x = 340;
	fire_y = 4600;
	pikaqiu_x = 340;
	pikaqiu_y = 3500;
	GetScore = 0;
	
	for (i = 0; i < 6; i++)
	{
		if (i % 2 == 0) {
			A[i].wall_x = 40;
		}
		else
		{
			A[i].wall_x = 300;
		}
		A[i].wall_y = 900 + i * 200;
	}
	
	if (property != 0) {
		loadimage(&car, _T("WhiteCar.png"), 150, 150);
		loadimage(&car_mask, _T("WhiteCar_mask.png"), 150, 150);
		property = 0;
		skill = 0;
	}
	wall_speed = 5;
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
	for (i = 0; i < 6; i++) {
		putimage(A[i].wall_x, A[i].wall_y, &wall_mask, NOTSRCERASE);
		putimage(A[i].wall_x, A[i].wall_y, &wall, SRCERASE);
	}
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
	if (A[0].wall_y < -150) {

		A[0].wall_y = rand() % 2000 + 1500;
	}
	if (groundScroll == 0) {
		GetScore++;
		if (GetScore % 2 == 0 && Carspeed > 5) {
			Carspeed--;
		}
		if (Carspeed == 6 && wall_speed < 10) {
			wall_speed++;

		}
	}

	for (i = 0; i < 6; i++)
	{
		A[i].wall_y = A[i].wall_y - wall_speed;
	}
	for (i = 1; i < 6; i++)
	{

		if (A[i].wall_y < -150) {
			A[i].wall_y = A[i - 1].wall_y - 200;
			A[i].wall_x = rand() % 10 + 1;
			if (A[i].wall_x % 2 != 0) {
				A[i].wall_x = 300;
			}
			else {
				A[i].wall_x = 40;
			}
		}
	}

	if (Xuhuan_y < -20) {
		Xuhuan_y = rand() % 7000 + 4000;
		Xuhuan_x = rand() % 10 + 1;
		if (Xuhuan_x % 2 == 0) {
			Xuhuan_x = 340;
		}
		else {
			Xuhuan_x = 80;
		}
	}
	if (fire_y < -20) {

		fire_y = rand() % 9000 + 7000;
		fire_x = rand() % 10 + 1;
		if (fire_x % 2 == 0) {
			fire_x = 340;
		}
		else {
			fire_x = 80;
		}
	}
	if (pikaqiu_y < -20) {
		pikaqiu_y = rand() % 11900 + 5000;
		pikaqiu_x = rand() % 10 + 1;
		if (pikaqiu_x % 2 == 0) {
			pikaqiu_x = 340;
		}
		else {
			pikaqiu_x = 80;
		}
	}
	if (Xuhuan_y > car_y && Xuhuan_x - 40 == car_x && Xuhuan_y < 70)
	{
		if (property == 0) {
			loadimage(&car_mask, _T("Change.png"), 150, 150);
			property = 1;//1为虚幻状态
			skill = 1;//1为无敌
			skilltime = 20;
			Xuhuan_x = -1000;
			Xuhuan_y = 1000;

		}
	}
	if (pikaqiu_y > car_y && pikaqiu_x - 40 == car_x && pikaqiu_y < 70)
	{
		if (property == 0) {


			loadimage(&car, _T("pika.png"), 150, 150);
			loadimage(&car_mask, _T("pikahei.png"), 150, 150);
			property = 2;//2为皮卡丘状态
			skill = 2;//2为雷电
			skilltime = 10;
			pikaqiu_x = -1000;
			pikaqiu_y = 1000;
		}
	}
	if (fire_y > car_y && fire_x - 40 == car_x && fire_y < 70)
	{
		if (property == 0) {
			loadimage(&car, _T("penhuolong.png"), 150, 150);
			loadimage(&car_mask, _T("penhuolong1.png"), 150, 150);
			property = 3;//3为喷火龙状态
			skill = 3;//3为喷火 
			skilltime = 10;
			fire_x = -1000;
			fire_y = 1000;
		}
	}
	if (property != 1) {
         WallCrash();
	}
	
	if (car_x > temp) {
		car_x = temp;
		skill_x = car_x;
	}
	if (car_x < 0) {

		car_x = 40;
		skill_x = car_x;
	}
	if (property != 0) {
		if (groundScroll == 0)
		{
			skilltime--;
		}

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
				for (i = 0; i < 6; i++) {
					if (A[i].wall_y < skill_y+150 && A[i].wall_x == skill_x && A[i].wall_y < 250)
					{
						A[i].wall_y = 1000;
						A[i].wall_x = 1000;
					}
				}
				break;
			case 3:
				putimage(skill_x, skill_y, &Fire_mask, NOTSRCERASE);
				putimage(skill_x, skill_y, &Fire, SRCERASE);
				for (i = 0; i < 6; i++) {
					if (A[i].wall_y < skill_y+150 && A[i].wall_x == skill_x && A[i].wall_y < 250)
					{
						A[i].wall_y = 1000;
						A[i].wall_x = 1000;
					}
				}
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

void Go() {
	EndBatchDraw();
	MOUSEMSG m;
	initgraph(1200, 800);//画布 
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "绝地赛车 v1.0");
	putimage(0, 0, &Background);
	FlushBatchDraw();
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	settextstyle(40, 0, _T("楷体"));
	outtextxy(520, 450, "开始游戏");
	outtextxy(520, 500, "退出游戏");
	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN)//如果按下鼠标左键，则画一个点。
		{
			if (m.x > 520 && m.x < 675 && m.y < 480 && m.y > 420) {
				mciSendString("open .\\55.mp3 alias bkmusic", NULL, 0, NULL);//打开背景音乐
				mciSendString("play bkmusic repeat", NULL, 0, NULL);  // 循环播放
				break;
			}
			if (m.x > 520 && m.x < 675 && m.y < 530 && m.y > 470) {
				exit(0);

			}
		}
	}
	closegraph();
	Startup();
	

}
void End(int x) {
	mciSendString("stop bkmusic", NULL, 0, NULL);   // 先把前面一次的音乐停止
	mciSendString("close bkmusic", NULL, 0, NULL); // 先把前面一次的音乐关闭
	MOUSEMSG m;
	initgraph(1024, 680);//画布 
	HWND hwnd = GetHWnd();
	SetWindowText(hwnd, "绝地赛车 v1.0");
	putimage(0, 0, &GetScoreb);
	FlushBatchDraw();
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	char s[5];
	sprintf_s(s, "%d", x);
	settextstyle(40, 0, _T("楷体"));
	outtextxy(520, 450, "返回菜单");
	outtextxy(520, 500, "退出游戏");
	outtextxy(340, 0, "您的得分为：");
	outtextxy(570, 5, s);
	while (true)
	{
		m = GetMouseMsg();//获取一条鼠标消息
		if (m.uMsg == WM_LBUTTONDOWN)//如果按下鼠标左键，则画一个点。
		{
			if (m.x > 520 && m.x < 675 && m.y < 480 && m.y > 420) {


				break;
			}
			if (m.x > 520 && m.x < 675 && m.y < 530 && m.y > 470) {
				exit(0);

			}
		}
	}
	closegraph();


}