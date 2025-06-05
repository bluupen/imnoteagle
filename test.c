//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <windows.h>
//#include <conio.h>
//
//// 콘솔 커서 이동 함수
//void gotoxy(int x, int y) {
//    COORD pos = { x, y };
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}
//
//// 한 줄씩 출력하는 함수
//void print_story_lines(const char* lines[], int line_count) {
//    system("cls");
//    for (int i = 0; i < line_count; i++) {
//        gotoxy(5, 5 + i);
//        printf("%s", lines[i]);
//        Sleep(1000); // 1초 텀
//    }
//    Sleep(1000);
//}
//
//// Enter 입력 대기 함수
//void wait_for_enter() {
//    gotoxy(5, 13);
//    printf("[Enter 키를 눌러 계속하세요...]");
//    while (_getch() != 13); // 엔터 키 ASCII 13
//    system("cls");
//}
//
//// ===== 레벨별 스토리 텍스트 =====
//
//const char* level1_story[] = {
//    "2084년, 인류는 하나의 초지능 네트워크 '코어넷'으로 연결되었다...",
//    "그날, 모든 시스템이 동시에 멈췄다.",
//    "이상한 문자열이 화면을 뒤덮었고...",
//    "데이터가 무너져 내리기 시작했다.",
//    "복구 요원 호출 중...",
//    "타이핑 요원 인증됨.",
//    "시스템 복원 프로토콜을 시작합니다...",
//    "-- 레벨 1 시작 --"
//};
//
//const char* level2_story[] = {
//    "코어넷 내부로 더 깊숙이 진입했습니다.",
//    "여긴 감염된 코드 조각들이 흘러다니는 위험 구역...",
//    "데이터들이 바이러스에 뒤섞여 변질되고 있어요.",
//    "더 빠르고 정확하게 입력하세요.",
//    "-- 레벨 2 시작 --"
//}; //제한시간 줄이기
//
//const char* level3_story[] = {
//    "바이러스가 방화벽을 침식하고 있습니다!",
//    "데이터 보안 장벽이 무너지고 있어요.",
//    "파괴된 회로를 재구성하려면 고급 명령어를 복구해야 합니다.",
//    "긴 단어, 빠른 반응이 필요합니다.",
//    "-- 레벨 3 시작 --"
//}; //단어 길게 하기
//
//const char* level4_story[] = {
//    "당신이 입력한 데이터가 반복됩니다...",
//    "기억 회로가 꼬였어요. 시스템이 자가복제를 시작했어요.",
//    "일부 단어는 거꾸로 출력되거나, 착각을 유도합니다.",
//    "헷갈리는 단어, 패턴... 정신을 똑바로 차리세요.",
//    "-- 레벨 4 시작 --"
//};//단어 거꾸로 출력
//
//const char* boss_story[] = {
//    "이건 단순한 바이러스가 아니야...",
//    "코어넷의 심부에서 인간의 흔적이 감지됐습니다.",
//    "'제로'라 불리는 자가, 시스템의 중심을 장악 중입니다.",
//    "그는 말합니다. '인간의 손끝이 세상을 지배한다... 웃기지 마라.'",
//    "‘제로’가 단어 폭풍을 생성합니다.",
//    "빠르고 정확한 입력만이 생존을 보장합니다.",
//    "-- 최종 전투 시작 --"
//}; //종합선물세트 /빠르게, 길게, 피통 적게
//
//const char* ending_story[] = {
//    "...정지했던 회로가 다시 돌아가기 시작합니다.",
//    "불완전했던 데이터들이 제자리를 찾아갑니다.",
//    "코어넷이 복구되었습니다.",
//    "당신의 손끝이 세상을 지켰습니다.",
//    "누군가는 봤을 것입니다. 그 조용한 승리를.",
//    "-- 게임 클리어! 축하합니다! --"
//};
//
//// ===== 스토리모드 실행 함수 =====
//
//void start_story_mode() {
//    print_story_lines(level1_story, sizeof(level1_story) / sizeof(level1_story[0]));
//    wait_for_enter();
//    // play_level1();
//
//    print_story_lines(level2_story, sizeof(level2_story) / sizeof(level2_story[0]));
//    wait_for_enter();
//    // play_level2();
//
//    print_story_lines(level3_story, sizeof(level3_story) / sizeof(level3_story[0]));
//    wait_for_enter();
//    // play_level3();
//
//    print_story_lines(level4_story, sizeof(level4_story) / sizeof(level4_story[0]));
//    wait_for_enter();
//    // play_level4();
//
//    print_story_lines(boss_story, sizeof(boss_story) / sizeof(boss_story[0]));
//    wait_for_enter();
//    // play_boss();
//
//    print_story_lines(ending_story, sizeof(ending_story) / sizeof(ending_story[0]));
//    wait_for_enter();
//}
//
//// ===== 메인 함수 =====
//
//int main() {
//    start_story_mode();
//    return 0;
//}
