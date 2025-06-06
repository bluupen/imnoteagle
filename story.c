#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void print_str(char* str);
void print_story_lines(char* lines[], int line_count);
void wait_for_enter();
void printstory(int i);
void start_story_mode();

// print string one-character by one-character with delay
void print_str(char* str) {
    char* p = str;
	while (*p != '\0') {
		putchar(*(p++));
		Sleep(30); // 각 글자 출력 사이에 50ms 딜레이
	}
}

// 한 줄씩 출력하는 함수
void print_story_lines(char* lines[], int line_count) {
    system("cls");
    for (int i = 0; i < line_count; i++) {
        gotoxy(START_X, START_Y + i);
		print_str(lines[i]);
        Sleep(1000); // 1초 텀
    }
    Sleep(1000);
}

// Enter 입력 대기 함수
void wait_for_enter() {
    gotoxy(START_X, START_Y + 10);
    printf("[Enter 키를 눌러 계속하세요...]");
    while (_getch() != 13); // 엔터 키 ASCII 13
}

void printstory(int i) {
    static const char* level1_story[] = {
        "2084년, 인류는 하나의 초지능 네트워크 '코어넷'으로 연결되었다...",
        "그날, 모든 시스템이 동시에 멈췄다.",
        "이상한 문자열이 화면을 뒤덮었고...",
        "데이터가 무너져 내리기 시작했다.\n",
        "복구 요원 호출 중...",
        "타이핑 요원 인증됨.",
        "시스템 복원 프로토콜을 시작합니다...",
        "-- 레벨 1 시작 --"
        // 5자리 1초
    };
    static const char* level2_story[] = {
        "코어넷 내부로 더 깊숙이 진입했습니다.",
        "여긴 감염된 코드 조각들이 흘러다니는 위험 구역...",
        "데이터들이 바이러스에 뒤섞여 변질되고 있어요.",
        "더 빠르고 정확하게 입력하세요.",
        "-- 레벨 2 시작 --"
        // 5자리 0.8초
    };
    static const char* level3_story[] = {
        "바이러스가 방화벽을 침식하고 있습니다!",
        "데이터 보안 장벽이 무너지고 있어요.",
        "파괴된 회로를 재구성하려면 고급 명령어를 복구해야 합니다.",
        "긴 단어, 빠른 반응이 필요합니다.",
        "-- 레벨 3 시작 --"
        // 7자리 0.8초
    };
    static const char* level4_story[] = {
        "당신이 입력한 데이터가 반복됩니다...",
        "기억 회로가 꼬였어요. 시스템이 자가복제를 시작했어요.",
        "일부 단어는 거꾸로 출력되거나, 착각을 유도합니다.",
        "헷갈리는 단어, 패턴... 정신을 똑바로 차리세요.",
        "-- 레벨 4 시작 --"
        // 7자리 일부 거꾸로 0.8초
    };
    static const char* boss_story[] = {
        "이건 단순한 바이러스가 아니야...",
        "코어넷의 심부에서 인간의 흔적이 감지됐습니다.",
        "'제로'라 불리는 자가, 시스템의 중심을 장악 중입니다.",
        "그는 말합니다. '인간의 손끝이 세상을 지배한다... 웃기지 마라.'",
        "‘제로’가 단어 폭풍을 생성합니다.",
        "빠르고 정확한 입력만이 생존을 보장합니다.",
        "-- 최종 전투 시작 --"
		// 9자리 / 7자리거꾸로 0.7초
    };
    static const char* ending_story[] = {
        "...정지했던 회로가 다시 돌아가기 시작합니다.",
        "불완전했던 데이터들이 제자리를 찾아갑니다.",
        "코어넷이 복구되었습니다.",
        "당신의 손끝이 세상을 지켰습니다.",
        "누군가는 봤을 것입니다. 그 조용한 승리를.",
        "-- 게임 클리어! 축하합니다! --"
    };
	static const char** stories[] = {level1_story, level2_story, level3_story, level4_story, boss_story, ending_story};
	static const size_t story_lengths[] = {
		sizeof(level1_story) / sizeof(level1_story[0]),
		sizeof(level2_story) / sizeof(level2_story[0]),
		sizeof(level3_story) / sizeof(level3_story[0]),
		sizeof(level4_story) / sizeof(level4_story[0]),
		sizeof(boss_story) / sizeof(boss_story[0]),
		sizeof(ending_story) / sizeof(ending_story[0])
	};
	print_story_lines(stories[i - 1], story_lengths[i - 1]);
}



// ===== 스토리모드 실행 함수 =====
void start_story_mode() {
    for (int i = 1; i <= 6; i++) {
        printstory(i);
        wait_for_enter();
    }
}

