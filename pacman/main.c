#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define q 113
#define f 102
#define Q 813
#define F 702
#define l 108
#define L 768
#define SPACEBAR 32

void gotoxy(int x, int y);
void showStart();
void setDisplay();
void showMoney(int abalone, int money, int Aclick, int big, int smal, int numHome, int nursery, int quote, int price);
void openStore(int *abalone, int *money, int *Aclick, int *big, int *smal, int numHome, int *nursery, int quote);
void harvest(int* Aclick, int* abalone, int* big, int* smal);
void levelUp(int* level, int* Aclick, int* money, int* price);

int main() {
	showStart();

	INPUT_RECORD rc;
	DWORD        dw;
	COORD pos = { 0,0 };
	KEY_EVENT_RECORD keyEvent;

	srand(time(NULL));
	int unsigned abalone = 0, money = 0, Aclick = 1, nursery = 0, numHome = 0, smal = 0, big = 0, quote, cnt = 0, limit, level = 1, price = 10000;
	setDisplay();
	quote = (rand() % 150 + 20) * 100;
	limit = rand() % 500 + 100;
	showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
	while (1) {
		if (cnt >= limit) {
			quote = (rand() % 100 + 25) * 100;
			limit = rand() % 500 + 100;
			cnt = 0;
		}
		else cnt++;
		gotoxy(29, 1);
		int key = _getch();
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rc, 1, &dw); //핸들정보       
		keyEvent = rc.Event.KeyEvent;
		
		if (keyEvent.bKeyDown) {}
		else {
			//나가기
			if (key == Q || key == q) {
				system("cls");

				exit(1);
			}

			//레벨업
			else if (key == l || key == L) levelUp(&level, &Aclick, &money, &price);

			// 상점 열기
			else if (key == f || key == F) openStore(&abalone, &money, &Aclick, &big, &smal, numHome, &nursery, quote);

			// 전복 채취
			else if (key == SPACEBAR) harvest(&Aclick, &abalone, &big, &smal);
		}

		// 메뉴창 업데이트
		showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
	}
	
	return 0;
}


//----------------------------------------
void gotoxy(int x, int y) {
	COORD Pos = { y - 1,x - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
//----------------------------------------
void showStart() {
	int get = 0;
	A:
	gotoxy(2, 1);
	printf("                                000   0        00000000      000    0    000000   0\n");
	printf("                               0   0  0        0            0   0   0    0    0   0\n");
	printf("                                000   0000     0           0     0000    0    0   0\n");
	printf("                                 0    0        00000000     0   0   0    000000   0\n");
	printf("                              0000000 0            0         000    0      0\n");
	printf("                                0             00000000000           0      0\n");
	printf("                                000000                                     0000000\n\n");
	printf("                                      00000000  0       000     000000    0\n");
	printf("                                             0  0      0   0         0    0\n");
	printf("                                      0000000   0       000          0    0\n");
	printf("                                           0    0     0000000       0     0\n");
	printf("                                          0     0        0         0      0\n");
	printf("                                         0      0        0        0       0\n");

	// 로고 출력
	gotoxy(19, 50);
	printf("게임 시작(1)\n");
	gotoxy(21, 50);
	printf("게임 스토리(2)\n");
	gotoxy(23, 50);
	printf("게임 종료(3)\n");
	get = _getch();
	switch (get) {
	case 49:
		system("cls");
		return;
	case 50:
		//스토리 진행
		system("cls");

		char story[] = "비트코인을 하다 망한 완도어민 오XX";
		char story2[] = "결국 전복을 팔아 갱생을 노리는데..";

		gotoxy(3, 40);
		for (int i = 0; i < strlen(story); i++) {
			printf("%c", story[i]);
			Sleep(70);
		}
		printf("\n");
		Sleep(1000);

		gotoxy(4, 40);
		for (int i = 0; i < strlen(story2); i++) {
			printf("%c", story2[i]);
			Sleep(70);
		}
		printf("\n");
		Sleep(1000);
		printf("\n\n계속하려면 아무 키나 누르십시오...");
		_getch();

		goto A;
	case 51:
		system("cls");
		exit(1);
	default:
		system("cls");
		goto A;
	}
}

void setDisplay() {
	//header
	printf("         ┌---------------------------------------------------------------------------------------------------┐\n");
	printf("         │                                                                                                   │\n");
	printf("         └---------------------------------------------------------------------------------------------------┘\n");
	
	//bottom
	gotoxy(24, 1);
	printf("                                                                                                      상점(f) \n");
	printf("         ┌---------------------------------------------------------------------------------------------------┐\n");
	printf("         │                                                                                                   │\n");
	printf("         │                                                                                                   │\n");
	printf("         │                                                                                                   │\n");
	printf("         └---------------------------------------------------------------------------------------------------┘\n");
}

void showMoney(int abalone, int money, int Aclick, int big, int smal, int level, int nursery, int quote, int price) {
	// header
	gotoxy(2, 12);
	printf("%4d : 클릭당 전복 개수%68d원 : 돈", Aclick, money);
	gotoxy(4, 86);
	printf("1미 %6d원 : 전복 시세", quote);
	
	//bottom
	gotoxy(26, 12);
	printf("양식장 수 : %4d%70d : 전복 합계", nursery, abalone);
	
	
	if (price == 2147483647) {
		gotoxy(27, 12);
		printf("레벨 : max%74d : 작은 사이즈", smal);
		gotoxy(28, 12);
		printf("%86d : 큰 사이즈", big);

	}
	else {
		gotoxy(27, 12);
		printf("레벨 : %4d%73d : 작은 사이즈", level, smal);
		gotoxy(28, 12);
		printf("Level Up 비용 : %8d%62d : 큰 사이즈", price, big);
	}

}

void openStore(int *abalone, int *money, int *Aclick, int* big, int* smal, int numHome, int *nursery, int quote) {
	static int nurseryPrice = 1500000;
	system("cls");
	gotoxy(10, 1);
	printf("                                                                                                  상점 나가기(f)\n");
	printf("         ┌----상점-------------------------------------------------------------------------------------------┐\n");
	printf("         │                                                                                                   │\n");
	printf("         │         전복 판매(a)                    양식장 구매(b)                      집 구매(c)            │\n");
	printf("         │                                                                                                   │\n");
	printf("         └---------------------------------------------------------------------------------------------------┘\n");

	while (1) {
		gotoxy(14, 50);
		printf("양식장 가격 : %d", nurseryPrice);
		gotoxy(29, 1);
		int key = _getch();
		printf("%d", key);
		if (key == f || key == F) {
			system("cls");
			setDisplay();
			return;
		}

		//전복 판매
		else if (key == 97 || key == 65) {
			int unsigned Bprice = (*big / 4) * quote, Sprice = (*smal / 8) * quote;
			*abalone = *abalone - (((*big / 4) * 4) + ((*smal / 8) * 8));
			*big = *big - ((*big / 4) * 4);
			*smal = *smal - ((*smal / 8) * 8);
			*money = *money + Bprice + Sprice;
			gotoxy(16, 10);
			printf("판매 되었습니다. (+%d)                                        ", Bprice + Sprice);
		}

		//양식장 구매
		else if (key == 98 || key == 66) {
			if (nurseryPrice <= *money) {
				*money -= nurseryPrice;
				nurseryPrice *= 1.5;
				*nursery += 1;
				*Aclick += 5;
				gotoxy(16, 10);
				printf("양식장이 구매되었습니다. (+1)                              ");
			}
			else {
				gotoxy(16, 10);
				printf("구매가 불가합니다.                                         ");
			}
		}

		//집 구매
		else if (key == 99 || key == 67) {

		}
	}
}

void harvest(int* Aclick, int* abalone, int* big, int* smal) {
	for (int i = 0; i < *Aclick; i++) {
		int persent = rand() % 100;

		if (persent >= 80) { // 큰 전복
			*big = *big + 1;
		}
		else { // 작은 전복
			*smal = *smal + 1;
		}
		*abalone = *abalone + 1;
	}
}

void levelUp(int* level, int* Aclick, int* money, int* price) {
	if (*level >= 999) {
		*price = 2147483647;
	}

	if (*money >= *price) {
		*money -= *price;
		*price += 5000;
		*level += 1;
		if (*level % 10 == 0) *Aclick += 1;
		// 레벨업 띄우기
		gotoxy(24, 1);
		printf("           LEVEL UP!                 ");
	}
	else {
		// 구매 불가 띄우기
		gotoxy(24, 1);
		printf("           구매 불가                      ");
	}
}