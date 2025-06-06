#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define SIZE 10
#define START_X 20
#define START_Y 5
#define GAME_TIMELIMIT 10000
#define GAME_WORDLIMIT 2
#define TIMER_END -1

#define COLOR_PRINTF(color,str) printf("\033[0;"#color"m" str)
#define COLOR_BRIGHT_CYAN 96
#define COLOR_BLUE 34
#define COLOR_GRAY 90
#define COLOR_YELLOW 33
#define COLOR_BRIGHT_GREEN 92
#define COLOR_MAGENTA 35
#define COLOR_RED 31
#define COLOR_WHITE 37
//Black  : \033[0;30m

typedef struct Word {
	char text[SIZE];
	int x;
	int y;
} Word;

typedef struct Node {
	Word word;
	struct Node* next;
} Node;

void gotoxy(int x, int y);
int gametimer(int time);
int wordtimer(int time);
char* generate_word(int _difficulty);

void lobby(int* gametype);
void normalmode(int difficulty);
void storymode();