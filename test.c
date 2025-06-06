#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")  // timeGetTime() 사용

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


int main() {
    const int x = 40;       // 글자 떨어질 X 좌표
    const int bottom = 20;  // 글자가 멈출 Y 좌표
    int y = 1;              // 시작 Y (1부터: 0은 시간 표시용)
    char life[10] = "0 0 0"; // 생명 표시용 문자열
    char word[6] = "apple";
    int i = 0; // 생명 감소용 인덱스
    char userInput[6];
    DWORD start_time = timeGetTime();  // 시작 시간


    gotoxy(0, 21);
    printf("---------------------------------------------------------------------------------");
    while (1) {
        // 1. 시간 표시
        DWORD elapsed = timeGetTime() - start_time;
        int seconds = elapsed / 1000;

        gotoxy(0, 0);  // 항상 위 줄(0행)에 출력
        printf("경과 시간: %d초", seconds);
        if (seconds == 10) {
            printf("clear");
            break;
        }
        gotoxy(100, 0);
        printf("%s", life);


        // 2. 이전 글자 지우기
        if (y > 1) {
            gotoxy(x, y - 1);
            printf("       ");
        }

        // 3. 현재 글자 출력
        gotoxy(x, y);
        printf("%s", word);

        Sleep(100);  // 속도 조절 (100ms)

        y++;

        gotoxy(0, 23);
        // 문자열을 저장할 배열
        printf("입력: ");

        // 4. 바닥에 닿으면 다시 위에서 시작
        if (y > bottom) {
            life[i] = 'x'; // 생명 감소
            i += 2; // 다음 생명 감소 인덱스
            gotoxy(40, 20);
            printf("       "); // 바닥에 닿았을 때 글자 지우기
            gotoxy(x, y - 1);
            printf(" ");  // 마지막 남은 글자 지우기
            y = 1;
        }
        if (life[4] == 'x') {
            printf("Game Over");
            break;
        }

    }

    return 0;
}