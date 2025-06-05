//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <windows.h>
//#include <conio.h>
//
//// �ܼ� Ŀ�� �̵� �Լ�
//void gotoxy(int x, int y) {
//    COORD pos = { x, y };
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}
//
//// �� �پ� ����ϴ� �Լ�
//void print_story_lines(const char* lines[], int line_count) {
//    system("cls");
//    for (int i = 0; i < line_count; i++) {
//        gotoxy(5, 5 + i);
//        printf("%s", lines[i]);
//        Sleep(1000); // 1�� ��
//    }
//    Sleep(1000);
//}
//
//// Enter �Է� ��� �Լ�
//void wait_for_enter() {
//    gotoxy(5, 13);
//    printf("[Enter Ű�� ���� ����ϼ���...]");
//    while (_getch() != 13); // ���� Ű ASCII 13
//    system("cls");
//}
//
//// ===== ������ ���丮 �ؽ�Ʈ =====
//
//const char* level1_story[] = {
//    "2084��, �η��� �ϳ��� ������ ��Ʈ��ũ '�ھ��'���� ����Ǿ���...",
//    "�׳�, ��� �ý����� ���ÿ� �����.",
//    "�̻��� ���ڿ��� ȭ���� �ڵ�����...",
//    "�����Ͱ� ������ ������ �����ߴ�.",
//    "���� ��� ȣ�� ��...",
//    "Ÿ���� ��� ������.",
//    "�ý��� ���� ���������� �����մϴ�...",
//    "-- ���� 1 ���� --"
//};
//
//const char* level2_story[] = {
//    "�ھ�� ���η� �� ����� �����߽��ϴ�.",
//    "���� ������ �ڵ� �������� �귯�ٴϴ� ���� ����...",
//    "�����͵��� ���̷����� �ڼ��� �����ǰ� �־��.",
//    "�� ������ ��Ȯ�ϰ� �Է��ϼ���.",
//    "-- ���� 2 ���� --"
//}; //���ѽð� ���̱�
//
//const char* level3_story[] = {
//    "���̷����� ��ȭ���� ħ���ϰ� �ֽ��ϴ�!",
//    "������ ���� �庮�� �������� �־��.",
//    "�ı��� ȸ�θ� �籸���Ϸ��� ��� ��ɾ �����ؾ� �մϴ�.",
//    "�� �ܾ�, ���� ������ �ʿ��մϴ�.",
//    "-- ���� 3 ���� --"
//}; //�ܾ� ��� �ϱ�
//
//const char* level4_story[] = {
//    "����� �Է��� �����Ͱ� �ݺ��˴ϴ�...",
//    "��� ȸ�ΰ� �������. �ý����� �ڰ������� �����߾��.",
//    "�Ϻ� �ܾ�� �Ųٷ� ��µǰų�, ������ �����մϴ�.",
//    "�򰥸��� �ܾ�, ����... ������ �ȹٷ� ��������.",
//    "-- ���� 4 ���� --"
//};//�ܾ� �Ųٷ� ���
//
//const char* boss_story[] = {
//    "�̰� �ܼ��� ���̷����� �ƴϾ�...",
//    "�ھ���� �ɺο��� �ΰ��� ������ �����ƽ��ϴ�.",
//    "'����'�� �Ҹ��� �ڰ�, �ý����� �߽��� ��� ���Դϴ�.",
//    "�״� ���մϴ�. '�ΰ��� �ճ��� ������ �����Ѵ�... ������ ����.'",
//    "�����Ρ��� �ܾ� ��ǳ�� �����մϴ�.",
//    "������ ��Ȯ�� �Է¸��� ������ �����մϴ�.",
//    "-- ���� ���� ���� --"
//}; //���ռ�����Ʈ /������, ���, ���� ����
//
//const char* ending_story[] = {
//    "...�����ߴ� ȸ�ΰ� �ٽ� ���ư��� �����մϴ�.",
//    "�ҿ����ߴ� �����͵��� ���ڸ��� ã�ư��ϴ�.",
//    "�ھ���� �����Ǿ����ϴ�.",
//    "����� �ճ��� ������ ���׽��ϴ�.",
//    "�������� ���� ���Դϴ�. �� ������ �¸���.",
//    "-- ���� Ŭ����! �����մϴ�! --"
//};
//
//// ===== ���丮��� ���� �Լ� =====
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
//// ===== ���� �Լ� =====
//
//int main() {
//    start_story_mode();
//    return 0;
//}
