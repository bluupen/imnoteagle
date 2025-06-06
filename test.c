#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")  // timeGetTime() ���

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int main() {
    const int x = 40;       // ���� ������ X ��ǥ
    const int bottom = 20;  // ���ڰ� ���� Y ��ǥ
    int y = 1;              // ���� Y (1����: 0�� �ð� ǥ�ÿ�)
    char life[10] = "0 0 0"; // ���� ǥ�ÿ� ���ڿ�
    char word[6] = "apple";
    int i = 0; // ���� ���ҿ� �ε���
    char userInput[6];
    DWORD start_time = timeGetTime();  // ���� �ð�


    gotoxy(0, 21);
    printf("---------------------------------------------------------------------------------");
    while (1) {
        // 1. �ð� ǥ��
        DWORD elapsed = timeGetTime() - start_time;
        int seconds = elapsed / 1000;

        gotoxy(0, 0);  // �׻� �� ��(0��)�� ���
        printf("��� �ð�: %d��", seconds);
        if (seconds == 10) {
            printf("clear");
            break;
        }
        gotoxy(100, 0);
        printf("%s", life);


        // 2. ���� ���� �����
        if (y > 1) {
            gotoxy(x, y - 1);
            printf("       ");
        }

        // 3. ���� ���� ���
        gotoxy(x, y);
        printf("%s", word);

        Sleep(100);  // �ӵ� ���� (100ms)

        y++;

        gotoxy(0, 23);
        // ���ڿ��� ������ �迭
        printf("�Է�: ");

        // 4. �ٴڿ� ������ �ٽ� ������ ����
        if (y > bottom) {
            life[i] = 'x'; // ���� ����
            i += 2; // ���� ���� ���� �ε���
            gotoxy(40, 20);
            printf("       "); // �ٴڿ� ����� �� ���� �����
            gotoxy(x, y - 1);
            printf(" ");  // ������ ���� ���� �����
            y = 1;
        }
        if (life[4] == 'x') {
            printf("Game Over");
            break;
        }

    }

    return 0;
}