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

void gotoxy(int x, int y);
int gametimer(int time);
int wordtimer(int time);
char* generate_word(int _difficulty);

void lobby(int* gametype);
void normalmode(int difficulty);
void storymode();

void test() {
	const char* level1_story[] = {
		"2084년, 인류는 하나의 초지능 네트워크 '코어넷'으로 연결되었다...",
		"그날, 모든 시스템이 동시에 멈췄다.",
		"이상한 문자열이 화면을 뒤덮었고...",
		"데이터가 무너져 내리기 시작했다.",
		"복구 요원 호출 중...",
		"타이핑 요원 인증됨.",
		"시스템 복원 프로토콜을 시작합니다...",
		"-- 레벨 1 시작 --"
	};
	int cnt = 0;
	while (1) {
		printf("\r%s\n", level1_story[cnt++]);
		if (cnt >= sizeof(level1_story) / sizeof(level1_story[0])) {
			break;
		}
	}
	while (_getch() != 27); // Wait for ESC to exit
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

	//test();

	int gametype = 1; // 1: easy, 2: normal, 3: hard, 4: story mode

	while (1) {
		lobby(&gametype); // 게임 선택화면
		if (1 <= gametype && gametype <= 3) {
			normalmode(gametype);
		}
		else if (gametype == 4) {
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
	static const char* words[300] = {
	"apple", "brave", "chair", "dream", "eagle", "flame", "grape", "heart", "ideal", "jelly",
	"knock", "lemon", "magic", "night", "ocean", "piano", "queen", "raven", "smile", "tiger",
	"urban", "vivid", "whale", "xenon", "young", "zebra", "angel", "beach", "candy", "delta",
	"earth", "frost", "giant", "honey", "ivory", "jolly", "kings", "lunar", "model", "nerdy",
	"optic", "penny", "quiet", "radio", "spice", "trace", "uncle", "vapor", "winds", "xerox",
	"yield", "zesty", "amber", "boost", "crisp", "daisy", "event", "fable", "glory", "hurry",
	"inner", "jazzy", "kneel", "latch", "motel", "noble", "orbit", "plant", "quake", "relax",
	"sweep", "trick", "unity", "vocal", "witty", "xylem", "yacht", "zonal", "actor", "beast",
	"cabin", "donut", "elite", "fungi", "gloom", "haste", "inbox", "joint", "koala", "loyal",
	"mirth", "ninja", "opera", "poise", "quest", "risen", "swirl", "tonic", "ultra", "vigor",
	"ability", "balance", "cabinet", "diamond", "eastern", "failure", "gallery", "harmony", "iceberg", "journey",
	"kingdom", "library", "machine", "natural", "observe", "package", "quality", "reality", "savings", "teacher",
	"unified", "village", "warrior", "xenonic", "younger", "zephyrs", "amazing", "between", "capital", "drawing",
	"empathy", "fiction", "grocery", "healthy", "impress", "justice", "kitchen", "lasting", "mention", "network",
	"opinion", "problem", "quarter", "reflect", "seventh", "tribune", "usually", "venture", "worship", "xanthic",
	"yielded", "zigzags", "absence", "breathe", "carried", "defence", "elastic", "feature", "glacier", "hostile",
	"install", "jealous", "keeping", "landing", "massive", "nations", "officer", "predict", "qualify", "rescuee",
	"striker", "turning", "urgency", "variety", "winning", "xeroxes", "youling", "zippers", "archive", "bargain",
	"contest", "deliver", "exclude", "fiction", "gestalt", "harvest", "invited", "jaggers", "kindled", "largely",
	"morning", "notions", "offbeat", "passage", "quickly", "respect", "sandbox", "talking", "unclear", "violent"
	"abandoning", "bachelorly", "caballero", "dandelion", "earthiest", "fabulists", "gallantly", "habitudes", "idealists", "jailbirds",
	"kaleidoses", "laborious", "macintosh", "narrating", "oblivious", "packaging", "quadrants", "radiators", "sabotaged", "tailoring",
	"umbilical", "vacillate", "wanderers", "xenoliths", "youngster", "zealotism", "absorbent", "benchmark", "calamitys", "delegator",
	"education", "fellowship", "grapevine", "hardcover", "ignitions", "jubilance", "kilobytes", "librarian", "mainlands", "navigated",
	"objective", "paintwork", "quarreled", "ranchland", "sailboats", "tailwinds", "undertook", "vandalism", "wanderlust", "xylophones",
	"youngling", "zeppelinz", "abduction", "blueprint", "comically", "discharge", "elsewhere", "figurines", "graceless", "hatchback",
	"idealistz", "judiciary", "kingships", "lifecycle", "mainframe", "newsletter", "offspring", "portables", "quickstep", "roadblock",
	"snowbound", "telepathy", "urbanites", "violation", "withdrawn", "xenocryst", "yellowing", "zookeeper", "aardvarks", "breeziest",
	"cataloged", "daydreams", "elevating", "flowerbed", "greenback", "housework", "intellect", "junctures", "keystones", "lifeboats",
	"marshland", "nobleness", "outsiders", "paperback", "questions", "rivalries", "screaming", "tradition", "unleashed", "volcanics"
	};


	static char word[SIZE];
	if (rand() % 2) {
		strcpy(word, words[rand() % 100 + (difficulty - 1) * 100]);
	}
	else {
		for (int i = 0; i < 3 + difficulty * 2; i++) {
			int is_upper = rand() % 2;
			word[i] = (is_upper ? 'A' : 'a') + rand() % 26;
		}
		word[SIZE - 1] = '\0';
	}
	return word;
}

void lobby(int* gametype) {
	// 게임 선택화면
	// 게임 선택(기본모드 / 스토리모드), 설정, 툴팁
	int option = 1; // 1: normal mode, 2: story mode, 3: tooltip, 4: exit
	char ch;
	system("cls");
	gotoxy(START_X, START_Y - 1);
	printf("     <  I'm not Eagle!!  >");
	gotoxy(START_X, START_Y);
	printf("-------------------------------");
	gotoxy(START_X, START_Y + 1);
	printf("        1. Normal Mode");
	gotoxy(START_X, START_Y + 2);
	printf("        2. Story Mode");
	gotoxy(START_X, START_Y + 3);
	printf("        3. Tooltip");
	gotoxy(START_X, START_Y + 4);
	printf("        4. Exit");
	while (1) {
		gotoxy(START_X + 4, START_Y + option);
		printf(">>");
		if (_kbhit()) {
			ch = _getch();
			if (ch == -32) {
				gotoxy(START_X + 4, START_Y + option);
				printf("  ");
				ch = _getch();
				switch (ch) {
				case 72: // Up arrow
					(option)--;
					if (option < 1) option = 4;
					break;
				case 80: // Down arrow
					(option)++;
					if (option > 4) option= 1;
					break;
				default: break;
				}
			}
			else if (ch == 13) { // Enter key
				switch (option) {
				case 1:
					gotoxy(START_X, START_Y + 1);
					printf("        1. EASY         ");
					gotoxy(START_X, START_Y + 2);
					printf("        2. NORMAL       ");
					gotoxy(START_X, START_Y + 3);
					printf("        3. HARD         ");
					gotoxy(START_X, START_Y + 4);
					printf("                        ");
					while (1) {
						gotoxy(START_X + 4, START_Y + option);
						printf(">>");
						if (_kbhit()) {
							ch = _getch();
							if (ch == -32) {
								gotoxy(START_X + 4, START_Y + option);
								printf("  ");
								ch = _getch();
								switch (ch) {
								case 72: // Up arrow
									(option)--;
									if (option < 1) option = 3;
									break;
								case 80: // Down arrow
									(option)++;
									if (option > 3) option = 1;
									break;
								default: break;
								}
							}
							else if (ch == 13) { // Enter
								*gametype = option;
								system("cls");
								return;
							}
						}
					}
					break;
				case 2:
					*gametype = 4;
					break;
				case 3:
					system("cls");
					gotoxy(START_X, START_Y + 6);
					printf("This is a typing game where you type words as fast as you can.");
					gotoxy(START_X, START_Y + 7);
					printf("Press ESC to return to the lobby");
					while (_getch() != 27);
					system("cls");
					gotoxy(START_X, START_Y - 1);
					printf("     <  I'm not Eagle!!  >");
					gotoxy(START_X, START_Y);
					printf("-------------------------------");
					gotoxy(START_X, START_Y + 1);
					printf("        1. Normal Mode");
					gotoxy(START_X, START_Y + 2);
					printf("        2. Story Mode");
					gotoxy(START_X, START_Y + 3);
					printf("        3. Tooltip");
					gotoxy(START_X, START_Y + 4);
					printf("        4. Exit");
					continue;
				case 4:
					gotoxy(0, 20);
					exit(0);
				default: break;
				}
				break;
			}
		}
	}

	system("cls");
	
	return;
}

void normalmode(int _difficulty) {
	static int wordtimelimit[] = { 6000, 5000, 5000 };
	char answer[SIZE];
	char word[SIZE];
	int difficulty = _difficulty - 1, idx = 0, score = 0, t;
	char ch;

	while (difficulty < 3) {
		difficulty++; // 1: easy, 2: normal, 3: hard
		score = 0;
		idx = 0;
		t = wordtimelimit[difficulty - 1]; // set time limit based on difficulty

		system("cls");
		gotoxy(START_X, START_Y - 1);
		switch (difficulty) {
		case 1: printf("======  [  Easy  ]  ======"); break;
		case 2: printf("======  [ Normal ]  ======"); break;
		case 3: printf("======  [  Hard  ]  ======"); break;
		default: break;
		}

		gametimer(0);
		wordtimer(0);
		int gamestart = timeGetTime();
		int wordstart = timeGetTime();

		// 시작할때 첫 단어 생성
		strcpy(answer, generate_word(difficulty));
		idx = 0;
		gotoxy(START_X + 6, START_Y + 3);
		printf(">> ");
		gotoxy(START_X + 18, START_Y + 3);
		printf(" <<");
		gotoxy(START_X + 12 - difficulty, START_Y + 3);
		printf("%s", answer);

		while (!gametimer(GAME_TIMELIMIT)) {
			gotoxy(START_X, START_Y + 1);
			printf("Game Left:%2d | Word Left:%2d | Score:%2d    ", GAME_TIMELIMIT / 1000 - (timeGetTime() - gamestart) / 1000, t / 1000 - (timeGetTime() - wordstart) / 1000, score);
			if (wordtimer(t)) {
				gotoxy(START_X + 6, START_Y + 3);
				printf("                    ");
				gotoxy(START_X + 6, START_Y + 4);
				printf("                    ");
				gotoxy(START_X, START_Y + 5);
				printf("                                        ");
				wordstart = timeGetTime(); // Reset word timer
				strcpy(answer, generate_word(difficulty));
				idx = 0;
				gotoxy(START_X + 6, START_Y + 3);
				printf(">> ");
				gotoxy(START_X + 18, START_Y + 3);
				printf(" <<");
				gotoxy(START_X + 12 - difficulty, START_Y + 3);
				printf("%s", answer);
			}
			if (_kbhit()) {
				ch = _getch();
				if (ch == 27) { // ESC, quit game
					gotoxy(START_X, START_Y + 6);
					printf("You quit the game.");
					gotoxy(START_X, START_Y + 7);
					printf("Press Enter to return to the lobby.");
					while (_getch() != 13);
					return;
				}
				else if (ch == 8) { // Backspace
					if (idx > 0) {
						gotoxy(START_X + 12 - difficulty + idx, START_Y + 4);
						printf("\b "); // Clear last character
						idx--;
					}
				}
				else if ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z') {
					gotoxy(START_X + 12 - difficulty + idx, START_Y + 4);
					word[idx++] = ch;
					printf("%c", ch);
					if (idx >= SIZE) {
						printf("\b \b");
						idx--;
					}
				}
				else if (ch == 13) { // Enter
					word[idx] = '\0';
					if (strcmp(word, answer) == 0) {
						gotoxy(START_X, START_Y + 5);
						printf("Correct!"); // will change to playsound
						score++;
						if (score >= GAME_WORDLIMIT) break;
					}
					else {
						gotoxy(START_X, START_Y + 5);
						printf("Wrong"); // will change to playsound
					}
					wordtimer(TIMER_END); // Reset word timer
				}
			}
		}
		if (score >= GAME_WORDLIMIT) {
			if (difficulty >= 3) {
				gotoxy(START_X, START_Y + 6);
				printf("Congratulations! You completed all difficulties.");
				gotoxy(START_X, START_Y + 7);
				printf("Press Enter to return to the lobby.");
				while (_getch() != 13);
				break;
			}
			gotoxy(START_X, START_Y + 6);
			printf("You win! Press Enter to continue...");
			while (_getch() != 13);
			continue;
		}
		else {
			gotoxy(START_X, START_Y + 6);
			printf("Lost the game. TOO SLOW!");
			gotoxy(START_X, START_Y + 7);
			printf("Press Enter to return to the lobby.");
			while (_getch() != 13);
			break;
		}
	}

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