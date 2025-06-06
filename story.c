#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

// print string one-character by one-character with delay
void print_str(char* str) {
    char* p = str;
	while (*p != '\0') {
		Sleep(20); // 20ms delay between each print
		putchar(*(p++));
	}
}

void printstory(int i) {
    static const char* stage1_story[] = {
        "2084��, �η��� �ϳ��� ������ ��Ʈ��ũ '�ھ��'���� ����Ǿ���...",
        "�׳�, ��� �ý����� ���ÿ� �����.",
        "�̻��� ���ڿ��� ȭ���� �ڵ�����...",
        "�����Ͱ� ������ ������ �����ߴ�.",
        "",
        "���� ��� ȣ�� ��...",
        "Ÿ���� ��� ������.",
        "�ý��� ���� ���������� �����մϴ�...",
        "",
        "---- ���� 1 ���� ----"
        // 5�ڸ� 1��
    };
    static const char* stage2_story[] = {
        "�ھ�� ���η� �� ����� �����߽��ϴ�.",
        "���� ������ �ڵ� �������� �귯�ٴϴ� ���� ����...",
        "�����͵��� ���̷����� �ڼ��� �����ǰ� �־��.",
        "�� ������ ��Ȯ�ϰ� �Է��ϼ���.",
        "",
        "---- ���� 2 ���� ----"
        // 5�ڸ� 0.8��
    };
    static const char* stage3_story[] = {
        "���̷����� ��ȭ���� ħ���ϰ� �ֽ��ϴ�!",
        "������ ���� �庮�� �������� �־��.",
        "�ı��� ȸ�θ� �籸���Ϸ��� ��� ��ɾ �����ؾ� �մϴ�.",
        "�� �ܾ�, ���� ������ �ʿ��մϴ�.",
        "",
        "---- ���� 3 ���� ----"
        // 7�ڸ� 0.8��
    };
    static const char* stage4_story[] = {
        "����� �Է��� �����Ͱ� �ݺ��˴ϴ�...",
        "��� ȸ�ΰ� �������. �ý����� �ڰ������� �����߾��.",
        "�Ϻ� �ܾ�� �Ųٷ� ��µǰų�, ������ �����մϴ�.",
        "�򰥸��� �ܾ�, ����... ������ �ȹٷ� ��������.",
        "",
        "---- ���� 4 ���� ----"
        // 7�ڸ� �Ϻ� �Ųٷ� 0.8��
    };
    static const char* boss_story[] = {
        "�̰� �ܼ��� ���̷����� �ƴϾ�...",
        "�ھ���� �ɺο��� �ΰ��� ������ �����ƽ��ϴ�.",
        "'����'�� �Ҹ��� �ڰ�, �ý����� �߽��� ��� ���Դϴ�."
        "",
        "'�ΰ��� �ճ��� ������ �����Ѵ�... ������ ����.'",
        "",
        "�����Ρ��� �ܾ� ��ǳ�� �����մϴ�.",
        "������ ��Ȯ�� �Է¸��� ������ �����մϴ�.",
        "",
        "---- ���� ���� ���� ----"
		// 9�ڸ� / 7�ڸ��Ųٷ� 0.7��
    };
    static const char* ending_story[] = {
        "...�����ߴ� ȸ�ΰ� �ٽ� ���ư��� �����մϴ�.",
        "�ҿ����ߴ� �����͵��� ���ڸ��� ã�ư��ϴ�.",
        "�ھ���� �����Ǿ����ϴ�.",
        "����� �ճ��� ������ ���׽��ϴ�.",
        "�������� ���� ���Դϴ�. �� ������ �¸���.",
        "",
        "---- ���� Ŭ����! �����մϴ�! ----"
    };
	static const char** stories[] = {stage1_story, stage2_story, stage3_story, stage4_story, boss_story, ending_story};
	static const size_t story_lengths[] = {
		sizeof(stage1_story) / sizeof(stage1_story[0]),
		sizeof(stage2_story) / sizeof(stage2_story[0]),
		sizeof(stage3_story) / sizeof(stage3_story[0]),
		sizeof(stage4_story) / sizeof(stage4_story[0]),
		sizeof(boss_story) / sizeof(boss_story[0]),
		sizeof(ending_story) / sizeof(ending_story[0])
	};
    system("cls");
    char** story = stories[i - 1];
	int line_count = story_lengths[i - 1];
    for (int i = 0; i < line_count; i++) {
        Sleep(500);
        gotoxy(START_X, START_Y + i);
        print_str(story[i]);
    }
    if (i == 6) {
        Beep(587, 90);  // D5
        Beep(739, 90);  // F5#
        Beep(880, 90);  // A5
        Beep(1108, 90);  // C6#
        Beep(1174, 200); // D6
    }
    Sleep(500);

}
