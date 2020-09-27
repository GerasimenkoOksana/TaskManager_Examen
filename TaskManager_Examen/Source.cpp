#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<Windows.h>
#include<string>
#include"TaskManager.h"
using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	TaskManager* tm = new TaskManager;
	tm->menu();	
	system("pause");
}