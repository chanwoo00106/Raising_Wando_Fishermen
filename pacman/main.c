
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define ll long long
#define q 113
#define f 102
#define Q 813
#define F 70
#define l 108
#define L 768
#define SPACEBAR 32

int trash;

char newStoryUp[][100] = {
	{"(앞)송미라 대통령, 완도 전복 맛본 뒤 극찬 ... '지금까지 볼 수 없었던 맛'"},
	{"(뒤)안은경 대통령 완도전복 먹은뒤 완도산 전복 사재기..."},
	{"지방 적고 단백질 풍부… 영양만점 '완도 전복'"},
	{"추석 명절선물, '완도 전복' 대박 났다"},
	{"전복 배송 트럭, 전북에서 전복되어..."},
	{"면역력 덩어리, 완도 전복… 산소포장으로'청정 배송'"},
	{"'전복 먹으면 면역력 향상'…완도군"},
	{"완도 전복 작년 설보다 매출 증가"},
	{"백종원 '완도산 전복 상품성 있다'"},
	{"다시마가 희귀해져 전복 양식이 힘들어..."}
};
char newStorydown[][100] = {
	{"태풍에 의해 중리마을 오 모 씨 양식장 사고 발생"},
	{"지구온난화로 완도 전복 폐사, 이에 전복 마니아들은 해외 전복을 더 많이 사..."},
	{"'완도군', 어민의 마음따윈 생각하지 않고 강제 전복 할인, 오XX '완도군 ㅆㅂ'"},
	{"완도산 전복 먹고 배탈이나..."},
	{"완도산 전복 먹고 사람이 죽어..."},
	{"현 완도 이장 비리로 인해 전복값 떨어져..."},
	{"완도 앞바다에 유람선 침몰, 기름 유출로 인해 완도 앞바다 오염돼..."},
	{"완도서 전복노예 발견돼... 완도산 전복 불매운동 활발..."},
	{"완도 전복에 미세 플라스틱 발견돼..."},
	{"완도 전복에서 신종 바이러스 발견"}
};

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void gotoxy(int x, int y);
void showStart();
void setdisplay();
void printFace(int face);
void showMoney(long long abalone, long long money, long long Aclick, long long big, long long smal, long long numHome, long long nursery, long long quote, long long price);
void openStore(long long *abalone, long long *money, long long *Aclick, long long *big, long long *smal, long long numHome, long long *nursery, long long quote, char news[], int face);
void harvest(long long* Aclick, long long* abalone, long long* big, long long* smal);
void levelUp(long long* level, long long* Aclick, long long* money, long long* price);
void finish(long long money);


int main() {
	CursorView();

	system("title 완도 어민 키우기");
	showStart();

	INPUT_RECORD rc;
	DWORD        dw;
	COORD pos = { 0,0 };
	KEY_EVENT_RECORD keyEvent;

	srand(time(NULL));
	long long abalone = 0, money = 0, Aclick = 1, nursery = 0, numHome = 0, smal = 0, big = 0, cnt = 0, level = 1, price = 10000, temp;
	int quote, limit, face = 2;

	setdisplay();
	printFace(face);
	quote = (rand() % 150 + 20) * 100;
	temp = quote;
	char news[100] = "완도 어민 오**, 완도의 이장이 되다";
	limit = rand() % 500 + 100;
	showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
	//clock_t start = clock();
	while (1) {
	loot:
		if (_kbhit()) {

			// 전복 시세 설정 & 얼굴 설정
			if (cnt >= limit) {
				quote = (rand() % 100 + 25) * 100;
				limit = rand() % 500 + 100;
				cnt = 0;
				// 시세에 맞는 뉴스
				if (quote > temp){
					face = 1;
					printFace(face);
					strcpy_s(news, 100, newStoryUp[rand() % 10]);
				}
				else {
					face = 0;
					printFace(face);
					strcpy_s(news, 100, newStorydown[rand() % 10]);
				}
				temp = quote;
			}
			else cnt++;

			int key = _getch();
			ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &rc, 1, &dw);
			keyEvent = rc.Event.KeyEvent;

			if (keyEvent.bKeyDown) {}
			else {
				//나가기
				if (key == Q || key == q) {
					re:
					system("cls");

					printf("정말 종료하시겠습니까? (y/n)\n");
					int ch;
					switch (ch = _getch()) {
					case 121:
					case 891:
						exit(1);
					case 110:
					case 780:
						system("cls");
						setdisplay();
						printFace(face);
						showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
						goto loot;
					default:
						goto re;
					}
				}

				//레벨업
				else if (key == l || key == L) levelUp(&level, &Aclick, &money, &price);
					
				// 상점 열기
				else if (key == f || key == F) openStore(&abalone, &money, &Aclick, &big, &smal, numHome, &nursery, quote, news, face);

				// 전복 채취
				else if (key == SPACEBAR) harvest(&Aclick, &abalone, &big, &smal);
			}
			

			// 메뉴창 업데이트
			showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
		}
	}
	
	return 0;
}



void gotoxy(int x, int y) {
	COORD Pos = { y - 1,x - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 시작 메뉴
void showStart() {
	int get = 0;
	A:
	gotoxy(2, 1);
	printf("                                000   0        00000000      000    0    000000   0\n");
	printf("                               0   0  0        0            0   0   0    0    0   0\n");
	printf("                                000   0000     0           0     0000    0    0   0\n");
	printf("                                 0    0        00000000     0   0   0    000000   0\n");
	printf("                              0000000 0            0         000    0      0\n");
	printf("                                0                  0                0      0\n");
	printf("                                000000        00000000000           0      0000000\n\n");
	printf("                                      00000000  0       000    00000000   0\n");
	printf("                                             0  0      0   0          0   0\n");
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
	printf("게임 방법(3)");
	gotoxy(25, 50);
	printf("게임 종료(4)\n");
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
		trash = _getch();

		goto A;
	case 51:
		system("cls");
		gotoxy(10, 1);
		printf("                              1미에\n");
		printf("                              큰 전복 : 4개                       작은 전복 : 6개");
		gotoxy(15, 1);
		printf("                              Space : 전복 따기                   q/Q   : 나가기\n\n");
		printf("                              f/F   : 상점                        ㅣ/ㅣ : 레벨업\n");
		gotoxy(29, 1);
		printf("계속하려면 아무 키나 누르십시오...");
		trash = _getch();
		system("cls");
		goto A;
	case 52:
		system("cls");
		exit(1);
	default:
		system("cls");
		goto A;
	}
}

// 게임 메뉴
void setdisplay() {
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

void printFace(int face) {
	if (face == 1) {
		gotoxy(5, 1);
		printf("        58ZZZZZZZZZZZZZ8y \n");
		printf("     ZZZzyzzzzzzzzzzzzzwDZZZ \n");
		printf("   9ZDzWzw8BzzzzzzzzzBBD5,,z9Zy \n");
		printf("  ZZZyWzzDB55555555555555D5W Z5\n");
		printf(" ZWjyyyyyyyyyyyyyyyyyyyyyyyyyWyZ88\n");
		printf(" ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\n");
		printf(" yZZZ                         ZZZy \n");
		printf(" Z  Z    ⌒             ⌒    Z  y  \n");
		printf(" ZZ Z    ○             ○    ZZ Z  \n");
		printf("  E9Z                       yZ8BB  \n");
		printf("    Z8          ㅁ          ZZ    \n");
		printf("     Z                    BZ    \n");
		printf("     Z          ∪        BZ    \n");
		printf("       ZZZ            ,ZZZ   \n");
		printf("         ZZZZZZZZZZZZZZZ     \n");
	}
	else if (face == 0) {
		gotoxy(5, 1);
		printf("        58ZZZZZZZZZZZZZ8y \n");
		printf("     ZZZzyzzzzzzzzzzzzzwDZZZ \n");
		printf("   9ZDzWzw8BzzzzzzzzzBBD5,,z9Zy \n");
		printf("  ZZZyWzzDB55555555555555D5W Z5\n");
		printf(" ZWjyyyyyyyyyyyyyyyyyyyyyyyyyWyZ88\n");
		printf(" ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\n");
		printf(" yZZZ                         ZZZy \n");
		printf(" Z  Z    ＼             ／    Z  y  \n");
		printf(" ZZ Z    ○             ○    ZZ Z  \n");
		printf("  E9Z                       yZ8BB  \n");
		printf("    Z8          ㅁ          ZZ    \n");
		printf("     Z                    BZ    \n");
		printf("     Z          ∩        BZ  凸 \n");
		printf("       ZZZ            ,ZZZ   \n");
		printf("         ZZZZZZZZZZZZZZZ     \n");
	}
	else {
		gotoxy(5, 1);
		printf("        58ZZZZZZZZZZZZZ8y \n");
		printf("     ZZZzyzzzzzzzzzzzzzwDZZZ \n");
		printf("   9ZDzWzw8BzzzzzzzzzBBD5,,z9Zy \n");
		printf("  ZZZyWzzDB55555555555555D5W Z5\n");
		printf(" ZWjyyyyyyyyyyyyyyyyyyyyyyyyyWyZ88\n");
		printf(" ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\n");
		printf(" yZZZ                         ZZZy \n");
		printf(" Z  Z     -             -     Z  y  \n");
		printf(" ZZ Z    ○             ○    ZZ Z  \n");
		printf("  E9Z                       yZ8BB  \n");
		printf("    Z8          ㅁ          ZZ    \n");
		printf("     Z          ㅜ         BZ    \n");
		printf("     Z          ◎        BZ    \n");
		printf("       ZZZ            ,ZZZ   \n");
		printf("         ZZZZZZZZZZZZZZZ     \n");
	}
}

// 여러가지 정보 보여주기
void showMoney(long long abalone, long long money, long long Aclick, long long big, long long smal, long long level, long long nursery, long long quote, long long price) {
	// header
	gotoxy(2, 12);
	printf("%91lld원 : 돈", money);
	gotoxy(2, 12);
	printf("클릭당 전복 개수 : %lld", Aclick);
	gotoxy(4, 86);
	printf("1미 %6lld원 : 전복 시세", quote);
	
	//bottom
	gotoxy(26, 12);
	printf("양식장 수 : %4lld%70lld : 전복 합계", nursery, abalone);
	
	
	if (price == 2147483647) {
		gotoxy(27, 12);
		printf("레벨 : max%74lld : 작은 사이즈", smal);
		gotoxy(28, 12);
		printf("%86lld : 큰 사이즈", big);
		gotoxy(20, 50);

	}
	else {
		gotoxy(27, 12);
		printf("레벨 : %4lld%73lld : 작은 사이즈", level, smal);
		gotoxy(28, 12);
		printf("Level Up 비용 : %8lld%62lld : 큰 사이즈", price, big);
		gotoxy(20, 50);
	}

}

// 시장
void openStore(long long *abalone, long long *money, long long *Aclick, long long* big, long long* smal, long long numHome, long long *nursery, long long quote, char news[], int face) {
	static int nurseryPrice = 1500000;
	system("cls");

	gotoxy(2, 10);
	printf("[속보] %s", news);

	gotoxy(10, 1);
	printf("                                                                                                  상점 나가기(f)\n");
	printf("         ┌----상점-------------------------------------------------------------------------------------------┐\n");
	printf("         │                                                                                                   │\n");
	printf("         │         전복 판매(a)                    양식장 구매(b)                      집 구매(c)            │\n");
	printf("         │                                                                                                   │\n");
	printf("         └---------------------------------------------------------------------------------------------------┘\n");

	while (1) {
		gotoxy(16, 50);
		printf("양식장 가격 : %d", nurseryPrice);
		gotoxy(16, 80);
		printf("집 가격 : 1000000000000");
		gotoxy(29, 1);
		int key = _getch();
		printf("%d", key);
		if (key == f || key == F) {
			system("cls");
			setdisplay();
			printFace(face);
			return;
		}

		//전복 판매
		else if (key == 97 || key == 65) {
			long long Bprice = (*big / 4) * quote, Sprice = (*smal / 8) * quote;
			*abalone = *abalone - (((*big / 4) * 4) + ((*smal / 8) * 8));
			*big = *big - ((*big / 4) * 4);
			*smal = *smal - ((*smal / 8) * 8);
			*money = *money + Bprice + Sprice;
			gotoxy(16, 10);
			printf("판매 되었습니다. (+%lld)                                        ", Bprice + Sprice);
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
		else if (key == 99 || key == 67) finish(*money);
	}
}

// 전복 따기
void harvest(long long* Aclick, long long* abalone, long long* big, long long* smal) {
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
	for (int i = 0; i < *Aclick; i++) {
		gotoxy(rand() % 19 + 5, rand() % 80 + 38);
		printf("()");
	}
}	

// 레벨업
void levelUp(long long* level, long long* Aclick, long long* money, long long* price) {
	if (*level >= 999) {
		*price = 2147483647;
	}

	if (*money >= *price) {
		*money -= *price;
		*price += 5000;
		*level += 1;
		if (*level % 5 == 0) *Aclick += 1;
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

// 끝
void finish(long long money) {
	if (money >= 1000000000000) {
		system("cls");
		gotoxy(6, 1);
		printf("                                               끝끝끝끝끝끝 끝끝끝끝끝끝\n");
		printf("                                                         끝           끝\n");
		printf("                                                         끝           끝\n");
		printf("                                                         끝           끝\n");
		printf("                                               끝끝끝끝끝끝끝끝끝끝끝끝끝\n");
		printf("\n");
		printf("                                                 끝끝끝끝끝끝끝끝끝끝끝\n");
		printf("                                                 끝\n");
		printf("                                                 끝끝끝끝끝끝끝끝끝끝끝\n");
		printf("                                                 끝\n");
		printf("                                                 끝끝끝끝끝끝끝끝끝끝끝\n");
		gotoxy(20, 1);
		printf("\n\n");
		Sleep(1000);
		printf("\n\n계속하려면 아무 키나 누르십시오...");
		trash = _getch();
		system("cls");
		char story[] = "내 집마련에 성공한 완도 어민 오XX";
		char story2[] = "그는 부자가 돼서 다시 비트코인을 시작하는데...";

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
		printf("\n\n종료하시려면 아무키나 누르십시오");
		trash = _getch();
		exit(1);
	}
	else {
		gotoxy(16, 10);
		printf("구매가 불가합니다.                                         ");
	}
}