#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define SIZE 6

void gotoxy(int x, int y);
void printui();
void runinput();
void game();

int gameover = 1;

void test() {
	while (1) {
		char ch = _getch();
		printf("ascii is %d\n", ch);
	}
}

int main() {
	// off cursor
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0; // 커서를 보일지 말지 결정(0이면 안보임, 0제외 숫자 값이면 보임)
	cursorInfo.dwSize = 1; // 커서의 크기를 결정 (1~100 사이만 가능)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	srand(time(0));

	//test();

	printui();

	while (gameover) {
		//runinput();
		game();
	}
	

	return 0;
}

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printui() {
	system("cls");
	gotoxy(10, 3);
	printf("Im not Eagle!");
	gotoxy(10, 4);
	printf("  1. easy");
	gotoxy(10, 5);
	printf("  2. medium");
	gotoxy(10, 6);
	printf("  3. hard");
	return;
}

void runinput() {
	static int arr = 1;
	gotoxy(10, 3 + arr);
	printf(">");
	gotoxy(23, 3 + arr);
	printf("<");
	char ch;
	if (_kbhit()) {
		ch = _getch();
		if (ch == 27) {
			gameover = 0;
			gotoxy(0, 8);
		}
		else if (ch == -32){
			gotoxy(10, 3 + arr);
			printf(" ");
			gotoxy(23, 3 + arr);
			printf(" ");
			ch = _getch(); // Handle arrow keys
			switch (ch) {
			case 72: // Up arrow
				arr--;
				if (arr < 1) arr = 3;
				break;
			case 80: // Down arrow
				arr++;
				if (arr > 3) arr = 1;
				break;
			}
		}
	}
	return;
}

void game() {
	int nowtime = time(0) - 5;
	char word[SIZE] = "hello";
	char userword[SIZE] = { 0, };
	int idx = 0;
	char ch;

	while (1) {
		if (time(0) - nowtime > 5) {
			gotoxy(10, 8);
			printf("                                ");
			gotoxy(10, 10);
			printf("                                ");
			nowtime = time(0);
			for (int i = 0; i < SIZE; i++) {
				word[i] = 'a' + rand() % 26; // Generate random letters
			}
			word[SIZE - 1] = '\0'; // Null-terminate the string
			idx = 0;
			gotoxy(10, 0);
			printf("%s", word);
		}
		if (_kbhit()) {
			ch = _getch();
			if (ch == 27) { // ESC key
				gameover = 0;
				gotoxy(0, 10);
				break;
			}
			else if ('a' <= ch && ch <= 'z') {
				gotoxy(10 + idx, 8);
				userword[idx++] = ch;
				printf("%c", ch);
				if (idx >= SIZE) {
					userword[SIZE - 1] = '\0'; // Null-terminate the string
					if (strcmp(userword, word) == 0) {
						gotoxy(10, 0);
						printf("You win! The word was: %s\n", word);
					}
					else {
						gotoxy(10, 10);
						printf("You lose! The word was: %s\n", word);
					}
				}
			}
			else if (ch == 13) {
				userword[idx] = '\0'; // Null-terminate the string
				if (strcmp(userword, word) == 0) {
					gotoxy(10, 10);
					printf("You win! The word was: %s   ", word);
				}
				else {
					gotoxy(10, 10);
					printf("You lose! The word was: %s  ", word);
				}
				nowtime = time(0) - 3;
			}
		}
	}

	gotoxy(0, 0);
	printf("Again?");
	if (_getch() == 27) gameover = 0;

	return;
}