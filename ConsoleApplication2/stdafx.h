// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include<easyx.h>
#include<conio.h>
#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <graphics.h>
#include <iostream>
#include<easyx.h>
#include<time.h>
#include <stdlib.h>
#include <mmsystem.h>
#pragma comment(lib,"Winmm.lib")


void Startup();
void Show();
void UpdateWithoutInput(int dt);
void UpdateWithInput();
void Showword();
void Loadimage();
void Go();
void End(int x);

// TODO: 在此处引用程序需要的其他头文件
