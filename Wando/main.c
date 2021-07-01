#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

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

//blackjack 함수
void setting(int* Card);
void CardSetting(int* Dealer, int* Player, int* Card);
int printCard(int* setCard, int* i, int* or );
void GameFinish(int gameSet, long long* bet);


//main에 있는 함수
void gotoxy(int x, int y);
void showStart();
void setdisplay();
void printFace(int face);
void showMoney(long long abalone, long long money, long long Aclick, long long big, long long smal, long long numHome, long long nursery, long long quote, long long price);
void openStore(long long* abalone, long long* money, long long* Aclick, long long* big, long long* smal, long long numHome, long long* nursery, long long quote, char news[], int face);
void harvest(long long* Aclick, long long* abalone, long long* big, long long* smal);
void printAbalone(long long abalone, long long Aclick, int set);
void levelUp(long long* level, long long* Aclick, long long* money, long long* price);
void Gacha(long long* money);
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
				if (quote > temp) {
					face = 1;
					printFace(face);
					strcpy_s(news, 100, newStoryUp[rand() % 10]);
				}
				else {
					face = 0;
					printFace(face);
					strcpy_s(news, 100, newStorydown[rand() % 10]);
					showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
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
					system("cls");
					showStart();
					setdisplay();
					printFace(face);
					showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
					printAbalone(abalone, Aclick, 0);
				}

				//레벨업
				if (key == l || key == L) levelUp(&level, &Aclick, &money, &price);

				// 상점 열기
				if (key == f || key == F) {
					openStore(&abalone, &money, &Aclick, &big, &smal, numHome, &nursery, quote, news, face);
					printAbalone(abalone, Aclick, 0);
				}

				// 전복 채취
				if (key == SPACEBAR) {
					harvest(&Aclick, &abalone, &big, &smal);
					printAbalone(abalone, Aclick, 1);
				}

				// black jack
				if (key == 103 || key == 71) {
					system("cls");
					Gacha(&money);
					setdisplay();
					printFace(face);
					showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
					printAbalone(abalone, Aclick, 0);
				}
			}


			// 메뉴창 업데이트
			showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
		}
	}

	return 0;
}

// blackjack---------------------------------------------------------------------------------------------------
void setting(int* Card) {
	// 카드 랜덤 셋팅
	int w = 0, c = 0;
	int cardPosition[52];

	for (int i = 0; i < 52; i++) {
		cardPosition[i] = 0;
	}
	while (w < 52) {
		c = rand() % 52;
		if (cardPosition[c] == 0) {
			cardPosition[c] = 1;
			Card[w] = c + 1;
			w++;
		}
	}
}

void CardSetting(int* Dealer, int* Player, int* Card) {
	for (int i = 0; i < 10; i++) Dealer[i] = Card[i];
	for (int i = 0; i < 10; i++) Player[i] = Card[i + 10];
}

int printCard(int* setCard, int* i, int* or ) {
	int card = setCard[*i], sum = 0;

	if (card >= 1 && card <= 13) {
		switch (card)
		{
		case 1:
			printf("♠ A");
			sum = 11;
			*or = 1;
			break;
		case 11:
			printf("♠ J");
			sum = 10;
			break;
		case 12:
			printf("♠ Q");
			sum = 10;
			break;
		case 13:
			printf("♠ K");
			sum = 10;
			break;
		default:
			printf("♠ %d", card);
			sum = card;
			break;
		}
	}
	if (card >= 14 && card <= 26) {
		switch (card - 13)
		{
		case 1:
			printf("◆ A");
			sum = 11;
			*or = 1;
			break;
		case 11:
			printf("◆ J");
			sum = 10;
			break;
		case 12:
			printf("◆ Q");
			sum = 10;
			break;
		case 13:
			printf("◆ K");
			sum = 10;
			break;
		default:
			printf("◆ %d", card - 13);
			sum = card - 13;
			break;
		}
	}
	if (card >= 27 && card <= 39) {
		switch (card - 26)
		{
		case 1:
			printf("♥ A");
			*or = 1;
			sum = 11;
			break;
		case 11:
			printf("♥ J");
			sum = 10;
			break;
		case 12:
			printf("♥ Q");
			sum = 10;
			break;
		case 13:
			printf("♥ K");
			sum = 10;
			break;
		default:
			printf("♥ %d", card - 26);
			sum = card - 26;
			break;
		}
	}
	if (card >= 40 && card <= 52) {
		switch (card - 39)
		{
		case 1:
			printf("♣ A");
			sum = 11;
			*or = 1;
			break;
		case 11:
			printf("♣ J");
			sum = 10;
			break;
		case 12:
			printf("♣ Q");
			sum = 10;
			break;
		case 13:
			printf("♣ K");
			sum = 10;
			break;
		default:
			printf("♣ %d", card - 39);
			sum = card - 39;
			break;
		}
	}
	printf("\n");
	*i = *i + 1;
	return sum;
}

int gameStart(int* Dealer, int* Player) {
	int pi = 0, di = 0, or , ord, Psum = 0, HorS, Dsum = 0, gameSet = -1;
	printf("your card\n");

	// 플레이어 시작 카드 2장
	Psum = Psum + printCard(Player, &pi, &or );
	Psum = Psum + printCard(Player, &pi, &or );

	while (1)
	{
		printf("Hit(1) or Stay(2) : ");
		HorS = _getch();
		printf("\n");

		// Hit
		if (HorS == 49) {
			Psum = Psum + printCard(Player, &pi, &or );

			// 수가 21을 넘고 A가 있을 때
			if (or == 1 && Psum > 21) {
				Psum = Psum - 10; // A가 있고 21이 넘으면 -10;
				or = 0;
			}

			// 21일 때
			if (Psum == 21) {
				printf("\n※You Black Jack※\n");
				gameSet = 1;
				break;
			}

			// 21 보다 적을 때
			if (Psum > 21) {
				gameSet = -1;
				break;
			}
		}

		// Stay
		else if (HorS == 50) {
			break;
		}
	}

	printf("\n\n\nDealer Card Open !!\n");
	Dsum = Dsum + printCard(Dealer, &di, &ord);
	Dsum = Dsum + printCard(Dealer, &di, &ord);

	if (Dsum < Psum && Psum <= 21) {
		Dsum = Dsum + printCard(Dealer, &di, &ord);
		if (Dsum > 21) gameSet = 1;
	}

	if (di == 1 && Dsum > 21) {
		Dsum = Dsum - 10; // A가 있고 21이 넘으면 -10;
		di = 0;
	}

	if (Dsum == 21) {
		printf("\n※Dealer Black Jack※\n");
		gameSet = -1;
	}


	if (Psum == Dsum) gameSet = 0;
	if (Psum > Dsum && Psum <= 21) gameSet = 1;

	return gameSet;
}

void GameFinish(int gameSet, long long* bet) {
	if (gameSet == 1) {
		*bet *= 2;
		printf("You Win!!!");
	}
	else if (gameSet == -1) {
		*bet = 0;
		printf("You Lose");
	}
	else {
		printf("You Drow");
	}
}

// wando-------------------------------------------------------------------------------------------------------

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

	gotoxy(29, 1);
	printf("!!한글이면 키가 입력이 안될 수 있습니다.!!");

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
		printf("                              큰 전복 : 4개                       작은 전복 : 8개");
		gotoxy(15, 1);
		printf("                              Space : 전복 따기                   q/Q   : 나가기\n\n");
		printf("                              f/F   : 상점                        ㅣ/ㅣ : 레벨업\n");
		printf("\n");
		printf("                              g     : black jack");
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
	printf("                                                                                               나가기(q) 상점(f) \n");
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
		printf(" ZWjyyyyyyyyyyyyyyyyyyyyy yyyWyZ8\n");
		printf(" ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\n");
		printf(" yZZZ                        ZZZy \n");
		printf(" Z  Z    ⌒             ⌒   Z  y  \n");
		printf(" ZZ Z    ○             ○   ZZ Z  \n");
		printf("  E9Z                       yZ8B  \n");
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
		printf(" ZWjyyyyyyyyyyyyyyyyyyyyyyyyyWyZ8\n");
		printf(" ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\n");
		printf(" yZZZ                        ZZZy \n");
		printf(" Z  Z    ＼             ／   Z  y  \n");
		printf(" ZZ Z    ○             ○   ZZ Z  \n");
		printf("  E9Z                       yZ8B  \n");
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
		printf(" ZWjyyyyyyyyyyyyyyyyyyyyyyyyyWyZ8\n");
		printf(" ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ\n");
		printf(" yZZZ                        ZZZy \n");
		printf(" Z  Z     -             -    Z  y  \n");
		printf(" ZZ Z    ○             ○   ZZ Z  \n");
		printf("  E9Z                       yZ8B  \n");
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
void openStore(long long* abalone, long long* money, long long* Aclick, long long* big, long long* smal, long long numHome, long long* nursery, long long quote, char news[], int face) {
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
		if (*nursery > 200) {
			gotoxy(16, 50);
			printf("양식장 가격 : %d", nurseryPrice);
		}
		else {
			gotoxy(16, 50);
			printf("                  ");
		}
		gotoxy(16, 80);
		printf("집 가격 : 1,000,000,000,000");
		gotoxy(29, 1);
		int key = _getch();
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
			if (*nursery < 200) {
				gotoxy(16, 10);
				printf("양식장이 너무 많습니다.                                         ");
			}
			else if (nurseryPrice <= *money) {
				*money -= nurseryPrice;
				nurseryPrice *= 1.2;
				*nursery += 1;
				*Aclick += 10;
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
}

void printAbalone(long long abalone, long long Aclick, int set) {
	if (set) {
		if (Aclick >= 1000) Aclick = 1000;
		for (int i = 0; i < Aclick; i++) {
			gotoxy(rand() % 19 + 5, rand() % 79 + 37);
			printf("()");
		}
	}
	else {
		if (abalone >= 1000) abalone = 1000;
		for (int i = 0; i < abalone; i++) {
			gotoxy(rand() % 19 + 5, rand() % 79 + 37);
			printf("()");
		}
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

//블랙잭
void Gacha(long long* money) {
reBet:
	system("cls");
	long long bet;
	printf("※black Jack※\n");
	if (*money <= 0 || *money < 10000) {
		printf("돈이 너무 부족합니다");
		printf("\n\n계속하려면 아무 키나 누르십시오...");
		trash = _getch();
		system("cls");
		return;
	}
	printf("돈 : %lld\n", *money);
	while (1) {
		printf("배팅 할 금액을 적어주세요 : ");
		scanf_s("%lld", &bet);

		if (bet > *money) printf("금액이 너무 높습니다.\n");
		else if (bet < 0 || bet < 10000) printf("배팅 금액은 만원 이상입니다\n");
		else if (*money >= bet) break;
		else printf("다시 입력해주세요\n");
	}

	*money -= bet;

	system("cls");

	// 블랙잭 시작
	int Card[52], Dealer[10], Player[10], gameSet, get;

	while (1) {
		setting(Card);
		CardSetting(Dealer, Player, Card);
		gameSet = gameStart(Dealer, Player);
		GameFinish(gameSet, &bet);

		if (bet == 0) {
			printf("\n돈을 전부 잃었습니다\n");
			while (1) {
				printf("다시 배팅하시겠습니까? (1)/(2) : ");
				get = _getch();
				printf("\n");
				if (get == 49) goto reBet;
				else if (get == 50) {
					printf("안녕히가십시오\n");
					printf("\n\n계속하려면 아무 키나 누르십시오...");
					trash = _getch();
					system("cls");
					return;
				}
			}
		}

	Retry:
		printf("\n\n획득 할 금액 : %lld원\n\n", bet);
		printf("만약 다음판을 이긴다면... : %lld원\n", bet * 2);
		printf("\n\n계속(1) / 그만하기(2) : ");
		get = _getch();

		printf("\n");

		if (get == 50)
		{
			printf("Thanks.\n"); // 종료
			break;
		}
		else if (get != 49) {
			printf("reTry.\n");
			goto Retry;
		}

		system("cls");
	}

	*money += bet;

	printf("\n\n계속하려면 아무 키나 누르십시오...");
	trash = _getch();

	system("cls");
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