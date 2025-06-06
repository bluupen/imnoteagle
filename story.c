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
		Sleep(30); // �� ���� ��� ���̿� 50ms ������
	}
}

// �� �پ� ����ϴ� �Լ�
void print_story_lines(char* lines[], int line_count) {
    system("cls");
    for (int i = 0; i < line_count; i++) {
        gotoxy(START_X, START_Y + i);
		print_str(lines[i]);
        Sleep(1000); // 1�� ��
    }
    Sleep(1000);
}

// Enter �Է� ��� �Լ�
void wait_for_enter() {
    gotoxy(START_X, START_Y + 10);
    printf("[Enter Ű�� ���� ����ϼ���...]");
    while (_getch() != 13); // ���� Ű ASCII 13
}

void printstory(int i) {
    static const char* level1_story[] = {
        "2084��, �η��� �ϳ��� ������ ��Ʈ��ũ '�ھ��'���� ����Ǿ���...",
        "�׳�, ��� �ý����� ���ÿ� �����.",
        "�̻��� ���ڿ��� ȭ���� �ڵ�����...",
        "�����Ͱ� ������ ������ �����ߴ�.\n",
        "���� ��� ȣ�� ��...",
        "Ÿ���� ��� ������.",
        "�ý��� ���� ���������� �����մϴ�...",
        "-- ���� 1 ���� --"
        // 5�ڸ� 1��
    };
    static const char* level2_story[] = {
        "�ھ�� ���η� �� ����� �����߽��ϴ�.",
        "���� ������ �ڵ� �������� �귯�ٴϴ� ���� ����...",
        "�����͵��� ���̷����� �ڼ��� �����ǰ� �־��.",
        "�� ������ ��Ȯ�ϰ� �Է��ϼ���.",
        "-- ���� 2 ���� --"
        // 5�ڸ� 0.8��
    };
    static const char* level3_story[] = {
        "���̷����� ��ȭ���� ħ���ϰ� �ֽ��ϴ�!",
        "������ ���� �庮�� �������� �־��.",
        "�ı��� ȸ�θ� �籸���Ϸ��� ��� ��ɾ �����ؾ� �մϴ�.",
        "�� �ܾ�, ���� ������ �ʿ��մϴ�.",
        "-- ���� 3 ���� --"
        // 7�ڸ� 0.8��
    };
    static const char* level4_story[] = {
        "����� �Է��� �����Ͱ� �ݺ��˴ϴ�...",
        "��� ȸ�ΰ� �������. �ý����� �ڰ������� �����߾��.",
        "�Ϻ� �ܾ�� �Ųٷ� ��µǰų�, ������ �����մϴ�.",
        "�򰥸��� �ܾ�, ����... ������ �ȹٷ� ��������.",
        "-- ���� 4 ���� --"
        // 7�ڸ� �Ϻ� �Ųٷ� 0.8��
    };
    static const char* boss_story[] = {
        "�̰� �ܼ��� ���̷����� �ƴϾ�...",
        "�ھ���� �ɺο��� �ΰ��� ������ �����ƽ��ϴ�.",
        "'����'�� �Ҹ��� �ڰ�, �ý����� �߽��� ��� ���Դϴ�.",
        "�״� ���մϴ�. '�ΰ��� �ճ��� ������ �����Ѵ�... ������ ����.'",
        "�����Ρ��� �ܾ� ��ǳ�� �����մϴ�.",
        "������ ��Ȯ�� �Է¸��� ������ �����մϴ�.",
        "-- ���� ���� ���� --"
		// 9�ڸ� / 7�ڸ��Ųٷ� 0.7��
    };
    static const char* ending_story[] = {
        "...�����ߴ� ȸ�ΰ� �ٽ� ���ư��� �����մϴ�.",
        "�ҿ����ߴ� �����͵��� ���ڸ��� ã�ư��ϴ�.",
        "�ھ���� �����Ǿ����ϴ�.",
        "����� �ճ��� ������ ���׽��ϴ�.",
        "�������� ���� ���Դϴ�. �� ������ �¸���.",
        "-- ���� Ŭ����! �����մϴ�! --"
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



// ===== ���丮��� ���� �Լ� =====
void start_story_mode() {
    for (int i = 1; i <= 6; i++) {
        printstory(i);
        wait_for_enter();
    }
}

