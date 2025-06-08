#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define SIZE 10
#define START_X 15
#define START_Y 5
#define NORMAL_TIMELIMIT 60000
#define NORMAL_WORDLIMIT 20
#define STORY_WORDLIMIT 30
#define TIMER_END -1
#define STORY_WORD_CYCLE 4 // generate new word every CYCLE times of drops

#define COLOR_PRINTF(color,str) printf("\033[0;"#color"m" str)
// Black(30) : \033[0;30m
// red 31
// yellow 33
// bright red 91
// bright blue 94
// reset 0

typedef struct Word {
	char text[SIZE];
	int x;
	int y;
} Word;

typedef struct Node {
	Word word;
	struct Node* next;
} Node;

typedef struct GameSettings {
	int story_startstage;
	int view_story;
	int is_normal_cleared;
} GameSettings;


// main.c
void gotoxy(int x, int y);
int gametimer(int time);
int wordtimer(int time);
char* generate_word(int _difficulty);

void settings();
void lobby(int* gametype);
void normalmode(int difficulty);
void storymode();

// story.c
void printstory(int i);
void print_str(char* str);

// linkedlist.c
void append_node(Node** head, Word word);
int delete_bottom(Node** head, int* heart);
int delete_node(Node** head, char* str);
void free_list(Node** head);
void move_down(Node* head);
void print_list(Node* head);
void print_word_text(Node* head);
void unprint_word_text(Node* head);