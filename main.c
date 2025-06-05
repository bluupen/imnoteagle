#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define SIZE 6
#define START_X 20
#define START_Y 5
#define GAME_TIMELIMIT 60000
#define TIMER_END -1

void gotoxy(int x, int y);
int gametimer(int time);
int wordtimer(int time);
char* generate_word(int difficulty);

void lobby(int* gametype);
void normalmode();
void storymode();

int gameover = 1;
static int wordtimelimit[] = { 6000,5000,3000 };

void test() {
	while (1) {
		char ch = _getch();
		printf("ascii is %d\n", ch);
	}
}
 
int main() {
	// off cursor blinking
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0; // 커서를 보일지 말지 결정(0이면 안보임, 0제외 숫자 값이면 보임)
	cursorInfo.dwSize = 1; // 커서의 크기를 결정 (1~100 사이만 가능)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	// console size setting
	system("mode con: cols=100 lines=30");

	srand(time(0));


	int gametype = 1; // 1: normal,2: story mode

	while (gameover) {
		//lobby(&gametype); // 게임 선택화면
		if (gametype == 1) {
			normalmode();
		}
		else {
			storymode();
		}
	}
	
	return 0;
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int gametimer(int time) {
	static int starttime = 0;
	if (time == TIMER_END) {
		starttime = timeGetTime() - 1000000; // in next call, will return 1
		return TIMER_END;
	}
	if (timeGetTime() - starttime >= time) {
		starttime = timeGetTime();
		return 1;
	}
	else
		return 0;
}

int wordtimer(int time) {
	static int starttime = 0;
	if (time == TIMER_END) {
		starttime = timeGetTime() - 1000000; // in next call, will return 1
		return TIMER_END;
	}
	if (timeGetTime() - starttime >= time) {
		starttime = timeGetTime();
		return 1;
	}
	else
		return 0;
}

char* generate_word(int difficulty) {
	// Generate a random word based on difficulty
	// features to make later: list of words and difficulty levels
	static char word[SIZE];
	for (int i = 0; i < SIZE; i++) {
		word[i] = 'a' + rand() % 26;
	}
	word[SIZE-1] = '\0';
	return word;
}

void lobby(int* gametype) {
	// 게임 선택화면
	// 게임 선택(기본모드 / 스토리모드), 설정, 툴팁
	while (1) {
		gotoxy(10, 3 + *gametype);
		printf(">");
		gotoxy(23, 3 + *gametype);
		printf("<");
		char ch;
		if (_kbhit()) {
			ch = _getch();
			if (ch == 27) {
				gameover = 0;
				gotoxy(0, 8);
			}
			else if (ch == -32) {
				gotoxy(10, 3 + *gametype);
				printf(" ");
				gotoxy(23, 3 + *gametype);
				printf(" ");
				ch = _getch(); // Handle arrow keys
				switch (ch) {
				case 72: // Up arrow
					(*gametype)--;
					if (*gametype < 1) *gametype = 3;
					break;
				case 80: // Down arrow
					(*gametype)++;
					if (*gametype > 3) *gametype = 1;
					break;
				default:
					break;
				}
			}
		}
	}

	
	
	return;
}

void normalmode() {
	char answer[SIZE] = "hello";
	char word[SIZE];
	int difficulty = 0, idx = 0, score = 0;
	char ch;
	
	difficulty++; // 1: easy, 2: medium, 3: hard
	int t = wordtimelimit[difficulty - 1]; // Get time limit based on difficulty
	
	gotoxy(START_X, START_Y);
	printf("===== Normal Mode =====");
	gotoxy(START_X, START_Y + 1);
	printf("Difficulty: %d | Score: %d           ", difficulty, score);

	gametimer(0);
	wordtimer(0);
	int gamestart = timeGetTime();
	
	// 시작할때 첫 단어 생성
	strcpy(answer, generate_word(difficulty));
	idx = 0;
	gotoxy(START_X, START_Y + 2);
	printf("%s", answer);

	while (!gametimer(GAME_TIMELIMIT)) {
		gotoxy(START_X, START_Y + 1);
		printf("Time Left: %d | Difficulty: %d | Score: %d           ", GAME_TIMELIMIT/1000 - (timeGetTime()-gamestart)/1000, difficulty, score);
		if (wordtimer(t)) {
			gotoxy(START_X, START_Y + 2);
			printf("                      ");
			gotoxy(START_X, START_Y + 3);
			printf("                      ");
			gotoxy(START_X, START_Y + 4);
			printf("                                        ");
			strcpy(answer, generate_word(difficulty));
			idx = 0;
			gotoxy(START_X, START_Y + 2);
			printf("%s", answer);
		}
		if (_kbhit()) {
			ch = _getch();
			if (ch == 27) { // ESC
				gameover = 0;
				gotoxy(0, 10);
				break;
			}
			else if (ch == 8) { // Backspace
				if (idx > 0) {
					gotoxy(START_X + idx, START_Y + 3);
					printf("\b  \b"); // Clear last character
					idx--;
				}
			}
			else if ('a' <= ch && ch <= 'z') {
				gotoxy(START_X + idx, START_Y + 3);
				word[idx++] = ch;
				printf("%c", ch);
				if (idx >= SIZE) {
					printf("\b \b"); // Overwrite last character
					idx--;
				}
			}
			else if (ch == 13) { // Enter
				word[idx] = '\0';
				if (strcmp(word, answer) == 0) {
					gotoxy(START_X, START_Y + 4);
					printf("Correct!"); // will change to playsound
					score++;
				}
				else {
					gotoxy(START_X, START_Y + 4);
					printf("Wrong"); // will change to playsound
				}
				wordtimer(TIMER_END); // Reset word timer
			}
		}
	}

	gotoxy(0, 0);
	printf("Again? (esc to escape)");
	if (_getch() == 27) gameover = 0;
	gotoxy(0, 0);
	printf("                      "); // Clear line

	return;

}

void storymode() {
	gotoxy(10, 3);
	printf("Story mode is not implemented yet.");
	gotoxy(10, 4);
	printf("Press any key to return to the lobby.");
	_getch();
	return;
}