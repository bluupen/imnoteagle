#include "game.h"

void test() {
	while (1) {
		COLOR_PRINTF(31, "hello\n");
		COLOR_PRINTF(33, "hello\n");
		COLOR_PRINTF(34, "hello\n");
		COLOR_PRINTF(35, "hello\n");
		COLOR_PRINTF(36, "hello\n");
		COLOR_PRINTF(37, "hello\n");
		COLOR_PRINTF(32, "hello\n");
		while (_getch()  != 27);
	}
}
 
GameSettings g_settings = { 
	1, // storymode starting stage
	1, // if show story
	0 // if ever clear normal mode
};

int main() {
	// no more cursor blinking
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	// console size setting
	system("mode con: cols=90 lines=34");

	srand(time(0));

	//test();

	int gametype = 1; // 1: easy, 2: normal, 3: hard, 4: story mode

	while (1) {
		lobby(&gametype);
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
	static DWORD starttime = 0;
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
	static DWORD starttime = 0;
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
	"morning", "notions", "offbeat", "passage", "quickly", "respect", "sandbox", "talking", "unclear", "violent",
	"aardvarks", "abilities", "absolutes", "admirable", "backpacks", "ballerina", "bankrupts", "baseboard", "campfires", "capsizing",
	"caretaker", "cellulose", "daffodils", "dashboard", "dedicated", "deviating", "education", "elevators", "elsewhere", "enlarging",
	"factories", "faltering", "favorable", "fireplace", "gardening", "gasolines", "gearshift", "goldsmith", "hairdryer", "hallucins",
	"hardcover", "harpooner", "idealists", "ignitions", "isolation", "immensity", "javelinas", "jealously", "jellyfish", "judgement",
	"kangaroos", "keepsakes", "keyboards", "kickstand", "landscape", "latchhook", "librarian", "lightbulb", "machinery", "mainframe",
	"marigolds", "musicians", "narrative", "navigator", "negligent", "notorious", "oakmosses", "oblivious", "offending", "omnivores",
	"packaging", "pamphlets", "parallels", "pervasive", "quadrants", "qualified", "quickstep", "quotables", "radiation", "rainstorm",
	"receptors", "relevance", "sailboats", "signature", "tailwinds", "telephone", "tenderize", "traveling", "ulcerated", "ululation",
	"urbanized", "vacations", "valentine", "vaporized", "vegetable", "wanderers", "waterfall", "welcoming", "windswept", "xenoliths",
	"xenograft", "xerophobe", "yearbooks", "yellowing", "youngster", "yieldings", "zealously", "zeppelins", "zookeeper", "zucchinis"
	};
	static char word[SIZE];

	if (difficulty > 10) {
		switch (difficulty) {
		case 11:
			strcpy(word, words[rand() % 100]);
			break;
		case 12:
			strcpy(word, words[rand() % 100]);
			break;
		case 13:
			strcpy(word, words[100 + rand() % 100]);
			break;
		case 14:
			if (rand() % 100 < 25) {
				char tmp[SIZE];
				strcpy(tmp, words[100 + rand() % 100]);
				for (int i = 0; i < 7; i++) 
					word[6 - i] = tmp[i];
				word[7] = '\0';
			}
			else
				strcpy(word, words[100 + rand() % 100]);
			break;
		case 15:
			if (rand() % 100 < 25) {
				char tmp[SIZE];
				strcpy(tmp, words[100 + rand() % 100]);
				for (int i = 0; i < 7; i++)
					word[6 - i] = tmp[i];
				word[7] = '\0';
			}
			else
				strcpy(word, words[200 + rand() % 100]);
			break;
		}
		return word;
	}
	else if (1 <= difficulty && difficulty <= 3) {
		if (rand() % 4) {
			strcpy(word, words[rand() % 100 + (difficulty - 1) * 100]);
		}
		else {
			for (int i = 0; i < 3 + difficulty * 2; i++) {
				word[i] = (rand() % 2 ? 'A' : 'a') + rand() % 26;
			}
			word[3 + difficulty * 2] = '\0';
		}
		return word;
	}
	return 0; // error
}

void settings() {
	int option = 1;
	char ch;
	gotoxy(START_X, START_Y + 1);
	printf("    storymode start : ");
	COLOR_PRINTF(33, "");
	printf("Stage %d         ", g_settings.story_startstage);
	COLOR_PRINTF(0, "");
	if (g_settings.story_startstage == 5) { // boss
		gotoxy(START_X + 22, START_Y + 1);
		COLOR_PRINTF(31, "Stage BOSS");
		COLOR_PRINTF(0, "");
	}
	gotoxy(START_X, START_Y + 2);
	printf("         show story : ");
	if (g_settings.view_story) COLOR_PRINTF(94, "true  ");
	else COLOR_PRINTF(91, "false ");
	COLOR_PRINTF(0, "");
	gotoxy(START_X, START_Y + 3);
	printf("         return to lobby           ");
	gotoxy(START_X, START_Y + 4);
	printf("                        ");
	while (1) {
		gotoxy(START_X, START_Y + option);
		printf(">>");
		if (_kbhit()) {
			Beep(392, 50); // G4
			ch = _getch();
			if (ch == -32) {
				gotoxy(START_X, START_Y + option);
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
			else if (ch == 13) { // Enter key
				switch (option) {
				case 1:
					g_settings.story_startstage++;
					if (g_settings.story_startstage > 5) g_settings.story_startstage = 1;
					if (g_settings.story_startstage == 5) { // boss
						gotoxy(START_X + 22, START_Y + 1);
						COLOR_PRINTF(31, "Stage BOSS      ");
						COLOR_PRINTF(0, "");
					}
					else {
						gotoxy(START_X + 22, START_Y + 1);
						COLOR_PRINTF(33, "");
						printf("Stage %d       ", g_settings.story_startstage);
						COLOR_PRINTF(0, "");
					}
					break;
				case 2:
					g_settings.view_story++;
					if (g_settings.view_story > 1) g_settings.view_story = 0;
					gotoxy(START_X + 22, START_Y + 2);
					if (g_settings.view_story) COLOR_PRINTF(94, "true  ");
					else COLOR_PRINTF(91, "false ");
					COLOR_PRINTF(0, "");
					break;
				case 3:
					return;
				default: break;
				}
			}
		}
	}
}

void lobby(int* gametype) {
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
	printf("        3. Settings");
	gotoxy(START_X, START_Y + 4);
	printf("        4. Exit");
	while (1) {
		gotoxy(START_X + 4, START_Y + option);
		printf(">>");
		if (_kbhit()) {
			Beep(392, 50); // G4
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
							Beep(392, 50); // G4
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
					settings();
					gotoxy(START_X, START_Y + 1);
					printf("        1. Normal Mode           ");
					gotoxy(START_X, START_Y + 2);
					printf("        2. Story Mode            ");
					gotoxy(START_X, START_Y + 3);
					printf("        3. Settings              ");
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
}

void normalmode(int _difficulty) {
	static int wordtimelimit[] = { 6000, 5000, 5000 };
	char answer[SIZE];
	char word[SIZE];
	int difficulty = _difficulty - 1, idx = 0, score = 0;
	DWORD t = 0;
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
		DWORD gamestart = timeGetTime();
		DWORD wordstart = timeGetTime();

		// 시작할때 첫 단어 생성
		strcpy(answer, generate_word(difficulty));
		idx = 0;
		gotoxy(START_X + 6, START_Y + 3);
		printf(">> ");
		gotoxy(START_X + 18, START_Y + 3);
		printf(" <<");
		gotoxy(START_X + 12 - difficulty, START_Y + 3);
		printf("%s", answer);

		while (!gametimer(NORMAL_TIMELIMIT)) {
			gotoxy(START_X, START_Y + 1);
			printf("Game Left:%2d | Word Left:%2d | Score:%2d    ", NORMAL_TIMELIMIT / 1000 - (timeGetTime() - gamestart) / 1000, t / 1000 - (timeGetTime() - wordstart) / 1000, score);
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
				printf(">>           <<");
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
						Beep(1108, 70);  // C6#
						Beep(1318, 70);  // E6
						score++;
						if (score >= NORMAL_WORDLIMIT) {
							gotoxy(START_X + 36, START_Y + 1);
							printf("%2d", score);
							break;
						}
					}
					else {
						Beep(196, 70);  // G3
						Beep(196, 70);
					}
					wordtimer(TIMER_END); // Reset word timer
				}
			}
		}
		if (score >= NORMAL_WORDLIMIT) {
			if (difficulty >= 3) {
				g_settings.is_normal_cleared = 1;
				gotoxy(START_X, START_Y + 6);
				printf("Congratulations! You completed all difficulties.");
				Beep(587, 90);  // D5
				Beep(739, 90);  // F5#
				Beep(880, 90);  // A5
				Beep(1108, 90);  // C6#
				Beep(1174, 200); // D6
				gotoxy(START_X, START_Y + 7);
				printf("Press Enter to return to the lobby.");
				while (_getch() != 13);
				break;
			}
			gotoxy(START_X, START_Y + 6);
			printf("You win!");
			Beep(587, 90);  // D5
			Beep(739, 90);  // F5#
			Beep(880, 90);  // A5
			Beep(1108, 90);  // C6#
			Beep(1174, 200); // D6
			gotoxy(START_X, START_Y + 7);
			printf("Press Enter to next difficulty.");
			while (_getch() != 13);
			continue;
		}
		else {
			gotoxy(START_X, START_Y + 6);
			printf("Lost the game. TOO SLOW!");
			gotoxy(START_X, START_Y + 7);
			Beep(698, 90);  // F5
			Beep(622, 90);  // D#5
			Beep(587, 90);  // D5
			Beep(523, 90);  // C5
			Beep(196, 90);  // G3
			Beep(196, 200);  // G3
			printf("Press Enter to return to the lobby.");
			while (_getch() != 13);
			break;
		}
	}
}

void storymode() {
	if (g_settings.is_normal_cleared == 0) {
		if (g_settings.story_startstage == 5 && g_settings.view_story == 0) g_settings.is_normal_cleared = 1;
		else {
			system("cls");
			gotoxy(START_X, START_Y);
			COLOR_PRINTF(31, "");
			printf("(Error) CoreNet: You are NOT Authorized to Access.");
			COLOR_PRINTF(0, "");
			gotoxy(START_X, START_Y + 2);
			printf("you have to clear Normal Mode to access.");
			gotoxy(START_X, START_Y + 3);
			printf("returning to the lobby...");
			Beep(130, 70);  // C3
			Beep(130, 70);
			Beep(130, 70);
			Sleep(5000);
			return;
		}
	}

	static int stagetimelimit[] = { 1000, 800, 800, 800, 700 };
	char word[SIZE];
	int stage = g_settings.story_startstage - 1, idx, score, heart;
	DWORD t = 0;
	char ch;

	while (stage < 5) {
		stage++;
		Node* wordlisthead = NULL;
		score = 0;
		idx = 0;
		heart = 4;
		
		// show stories
		if (g_settings.view_story) {
			system("cls");
			printstory(stage);
			gotoxy(START_X, START_Y + 22);
			printf("[Enter 키를 눌러 계속하세요...]");
			while (_getch() != 13);
			system("cls");
		}

		gotoxy(START_X, START_Y - 1);
		switch (stage) {
		case 1:	case 2:	case 3:	case 4:
			printf("===================  [  ");
			COLOR_PRINTF(33, "");
			printf("Stage %d", stage);
			COLOR_PRINTF(0, "");
			printf("  ]  ==================");
			break;
		case 5: 
			printf("===================  [   ");
			COLOR_PRINTF(31, "");
			printf("BOSS");
			COLOR_PRINTF(0, "");
			printf("  ]  ==================");
			break;
		default: break;
		}
		gotoxy(START_X + 19, START_Y + 22);
		printf(">>           <<");
		gotoxy(START_X, START_Y + 20);
		printf("------------------------------------------------------");

		wordtimer(0);
		DWORD gamestart = timeGetTime();
		DWORD wordstart = timeGetTime();
		t = stagetimelimit[stage - 1];
		wordtimer(TIMER_END);

		int wordcnt = 5;
		while (heart) {
			gotoxy(START_X, START_Y - 3);
			printf("score: %2d                                   ", score);
			COLOR_PRINTF(31, "");
			for (int i = 0; i < 4; i++) {
				if (4 - heart > i) printf("♡");
				else printf("♥");
			}
			COLOR_PRINTF(0, "");

			if (wordtimer(t)) {
				wordcnt++;
				unprint_word_text(wordlisthead);
				move_down(wordlisthead);
				if (delete_bottom(&wordlisthead, &heart)) {
					Beep(130, 70); // C3
					Beep(130, 70);
					gotoxy(START_X, START_Y - 3);
					printf("score: %2d                                   ", score);
					COLOR_PRINTF(31, "");
					for (int i = 0; i < 4; i++) {
						if (4 - heart > i) printf("♡");
						else printf("♥");
					}
					COLOR_PRINTF(0, "");
				}
				if (wordcnt >= STORY_WORD_CYCLE) {
					wordcnt = 0;
					Word tmpword;
					tmpword.x = START_X + 15 * (rand() % 4);
					tmpword.y = START_Y + 1;
					strcpy(tmpword.text, generate_word(10 + stage));
					append_node(&wordlisthead, tmpword);
				}
				print_word_text(wordlisthead);
			}

			if (_kbhit()) {
				ch = _getch();
				if (ch == 27) { // ESC, quit game
					gotoxy(START_X, START_Y + 24);
					printf("You quit the game.");
					gotoxy(START_X, START_Y + 25);
					printf("Press Enter to return to the lobby.");
					while (_getch() != 13);
					return;
				}
				else if (ch == 8) { // Backspace
					if (idx > 0) {
						gotoxy(START_X + 22 + idx, START_Y + 22);
						printf("\b "); // Clear last character
						idx--;
					}
				}
				else if ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z') {
					gotoxy(START_X + 22 + idx, START_Y + 22);
					word[idx++] = ch;
					printf("%c", ch);
					if (idx >= SIZE) {
						printf("\b \b");
						idx--;
					}
				}
				else if (ch == 13) { // Enter
					word[idx] = '\0';
					unprint_word_text(wordlisthead);
					if (delete_node(&wordlisthead, word)) {
						print_word_text(wordlisthead);
						Beep(1108, 70);  // C6#
						Beep(1318, 70);  // E6
						score++;
						if (score >= STORY_WORDLIMIT) {
							gotoxy(START_X, START_Y - 3);
							printf("score: %2d                                   ", score);
							COLOR_PRINTF(31, "");
							for (int i = 0; i < 4; i++) {
								if (4 - heart > i) printf("♡");
								else printf("♥");
							}
							COLOR_PRINTF(0, "");
							break;
						}
					}
					else {
						print_word_text(wordlisthead);
						Beep(196, 70);  // G3
						Beep(196, 70);
					}
					gotoxy(START_X + 22, START_Y + 22);
					printf("         ");
					strcpy(word, "\0");
					idx = 0; // Reset index after entering word
				}
			}
		}
		if (score >= STORY_WORDLIMIT) {
			if (stage >= 5) {
				stage++;
				if (g_settings.view_story) {
					printstory(stage);
					gotoxy(START_X, START_Y + 22);
					printf("로비로 돌아가기 (Enter)");
					while (_getch() != 13);
				}
				break;
			}
			gotoxy(START_X, START_Y + 24);
			printf("복원에 성공했습니다!!");
			Beep(587, 90);  // D5
			Beep(739, 90);  // F5#
			Beep(880, 90);  // A5
			Beep(1108, 90);  // C6#
			Beep(1174, 200); // D6
			gotoxy(START_X, START_Y + 25);
			printf("다음 스테이지 (Enter)");
			while (_getch() != 13);
			continue;
		}
		else {
			gotoxy(START_X, START_Y + 24);
			printf("복원에 실패했습니다. 너무 느려요!!");
			gotoxy(START_X, START_Y + 25);
			Beep(698, 90);  // F5
			Beep(622, 90);  // D#5
			Beep(587, 90);  // D5
			Beep(523, 90);  // C5
			Beep(196, 90);  // G3
			Beep(196, 200);  // G3
			printf("로비로 돌아가기 (Enter)");
			while (_getch() != 13);
			break;
		}
	}
}
