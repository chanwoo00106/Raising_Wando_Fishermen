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
	{"(��)�۹̶� �����, �ϵ� ���� ���� �� ���� ... '���ݱ��� �� �� ������ ��'"},
	{"(��)������ ����� �ϵ����� ������ �ϵ��� ���� �����..."},
	{"���� ���� �ܹ��� ǳ�Ρ� ���縸�� '�ϵ� ����'"},
	{"�߼� ��������, '�ϵ� ����' ��� ����"},
	{"���� ��� Ʈ��, ���Ͽ��� �����Ǿ�..."},
	{"�鿪�� ���, �ϵ� ������ �����������'û�� ���'"},
	{"'���� ������ �鿪�� ���'���ϵ���"},
	{"�ϵ� ���� �۳� ������ ���� ����"},
	{"������ '�ϵ��� ���� ��ǰ�� �ִ�'"},
	{"�ٽø��� ������� ���� ����� �����..."}
};
char newStorydown[][100] = {
	{"��ǳ�� ���� �߸����� �� �� �� ����� ��� �߻�"},
	{"�����³�ȭ�� �ϵ� ���� ���, �̿� ���� ���ϾƵ��� �ؿ� ������ �� ���� ��..."},
	{"'�ϵ���', ����� �������� �������� �ʰ� ���� ���� ����, ��XX '�ϵ��� ����'"},
	{"�ϵ��� ���� �԰� ��Ż�̳�..."},
	{"�ϵ��� ���� �԰� ����� �׾�..."},
	{"�� �ϵ� ���� �񸮷� ���� ������ ������..."},
	{"�ϵ� �չٴٿ� ������ ħ��, �⸧ ����� ���� �ϵ� �չٴ� ������..."},
	{"�ϵ��� �����뿹 �߰ߵ�... �ϵ��� ���� �Ҹſ Ȱ��..."},
	{"�ϵ� ������ �̼� �ö�ƽ �߰ߵ�..."},
	{"�ϵ� �������� ���� ���̷��� �߰�"}
};

void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

//blackjack �Լ�
void setting(int* Card);
void CardSetting(int* Dealer, int* Player, int* Card);
int printCard(int* setCard, int* i, int* or );
void GameFinish(int gameSet, long long* bet);


//main�� �ִ� �Լ�
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

	system("title �ϵ� ��� Ű���");
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
	char news[100] = "�ϵ� ��� ��**, �ϵ��� ������ �Ǵ�";
	limit = rand() % 500 + 100;
	showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
	//clock_t start = clock();
	while (1) {
	loot:
		if (_kbhit()) {

			// ���� �ü� ���� & �� ����
			if (cnt >= limit) {
				quote = (rand() % 100 + 25) * 100;
				limit = rand() % 500 + 100;
				cnt = 0;
				// �ü��� �´� ����
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
				//������
				if (key == Q || key == q) {
					system("cls");
					showStart();
					setdisplay();
					printFace(face);
					showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
					printAbalone(abalone, Aclick, 0);
				}

				//������
				if (key == l || key == L) levelUp(&level, &Aclick, &money, &price);

				// ���� ����
				if (key == f || key == F) {
					openStore(&abalone, &money, &Aclick, &big, &smal, numHome, &nursery, quote, news, face);
					printAbalone(abalone, Aclick, 0);
				}

				// ���� ä��
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


			// �޴�â ������Ʈ
			showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
		}
	}

	return 0;
}

// blackjack---------------------------------------------------------------------------------------------------
void setting(int* Card) {
	// ī�� ���� ����
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
			printf("�� A");
			sum = 11;
			*or = 1;
			break;
		case 11:
			printf("�� J");
			sum = 10;
			break;
		case 12:
			printf("�� Q");
			sum = 10;
			break;
		case 13:
			printf("�� K");
			sum = 10;
			break;
		default:
			printf("�� %d", card);
			sum = card;
			break;
		}
	}
	if (card >= 14 && card <= 26) {
		switch (card - 13)
		{
		case 1:
			printf("�� A");
			sum = 11;
			*or = 1;
			break;
		case 11:
			printf("�� J");
			sum = 10;
			break;
		case 12:
			printf("�� Q");
			sum = 10;
			break;
		case 13:
			printf("�� K");
			sum = 10;
			break;
		default:
			printf("�� %d", card - 13);
			sum = card - 13;
			break;
		}
	}
	if (card >= 27 && card <= 39) {
		switch (card - 26)
		{
		case 1:
			printf("�� A");
			*or = 1;
			sum = 11;
			break;
		case 11:
			printf("�� J");
			sum = 10;
			break;
		case 12:
			printf("�� Q");
			sum = 10;
			break;
		case 13:
			printf("�� K");
			sum = 10;
			break;
		default:
			printf("�� %d", card - 26);
			sum = card - 26;
			break;
		}
	}
	if (card >= 40 && card <= 52) {
		switch (card - 39)
		{
		case 1:
			printf("�� A");
			sum = 11;
			*or = 1;
			break;
		case 11:
			printf("�� J");
			sum = 10;
			break;
		case 12:
			printf("�� Q");
			sum = 10;
			break;
		case 13:
			printf("�� K");
			sum = 10;
			break;
		default:
			printf("�� %d", card - 39);
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

	// �÷��̾� ���� ī�� 2��
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

			// ���� 21�� �Ѱ� A�� ���� ��
			if (or == 1 && Psum > 21) {
				Psum = Psum - 10; // A�� �ְ� 21�� ������ -10;
				or = 0;
			}

			// 21�� ��
			if (Psum == 21) {
				printf("\n��You Black Jack��\n");
				gameSet = 1;
				break;
			}

			// 21 ���� ���� ��
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
		Dsum = Dsum - 10; // A�� �ְ� 21�� ������ -10;
		di = 0;
	}

	if (Dsum == 21) {
		printf("\n��Dealer Black Jack��\n");
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

// ���� �޴�
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
	printf("!!�ѱ��̸� Ű�� �Է��� �ȵ� �� �ֽ��ϴ�.!!");

	// �ΰ� ���
	gotoxy(19, 50);
	printf("���� ����(1)\n");
	gotoxy(21, 50);
	printf("���� ���丮(2)\n");
	gotoxy(23, 50);
	printf("���� ���(3)");
	gotoxy(25, 50);
	printf("���� ����(4)\n");
	get = _getch();
	switch (get) {
	case 49:
		system("cls");
		return;
	case 50:
		//���丮 ����
		system("cls");

		char story[] = "��Ʈ������ �ϴ� ���� �ϵ���� ��XX";
		char story2[] = "�ᱹ ������ �Ⱦ� ������ �븮�µ�..";

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
		printf("\n\n����Ϸ��� �ƹ� Ű�� �����ʽÿ�...");
		trash = _getch();

		goto A;
	case 51:
		system("cls");
		gotoxy(10, 1);
		printf("                              1�̿�\n");
		printf("                              ū ���� : 4��                       ���� ���� : 8��");
		gotoxy(15, 1);
		printf("                              Space : ���� ����                   q/Q   : ������\n\n");
		printf("                              f/F   : ����                        ��/�� : ������\n");
		printf("\n");
		printf("                              g     : black jack");
		gotoxy(29, 1);
		printf("����Ϸ��� �ƹ� Ű�� �����ʽÿ�...");
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

// ���� �޴�
void setdisplay() {
	//header
	printf("         ��---------------------------------------------------------------------------------------------------��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��---------------------------------------------------------------------------------------------------��\n");

	//bottom
	gotoxy(24, 1);
	printf("                                                                                               ������(q) ����(f) \n");
	printf("         ��---------------------------------------------------------------------------------------------------��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��---------------------------------------------------------------------------------------------------��\n");
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
		printf(" Z  Z    ��             ��   Z  y  \n");
		printf(" ZZ Z    ��             ��   ZZ Z  \n");
		printf("  E9Z                       yZ8B  \n");
		printf("    Z8          ��          ZZ    \n");
		printf("     Z                    BZ    \n");
		printf("     Z          ��        BZ    \n");
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
		printf(" Z  Z    ��             ��   Z  y  \n");
		printf(" ZZ Z    ��             ��   ZZ Z  \n");
		printf("  E9Z                       yZ8B  \n");
		printf("    Z8          ��          ZZ    \n");
		printf("     Z                    BZ    \n");
		printf("     Z          ��        BZ  �� \n");
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
		printf(" ZZ Z    ��             ��   ZZ Z  \n");
		printf("  E9Z                       yZ8B  \n");
		printf("    Z8          ��          ZZ    \n");
		printf("     Z          ��         BZ    \n");
		printf("     Z          ��        BZ    \n");
		printf("       ZZZ            ,ZZZ   \n");
		printf("         ZZZZZZZZZZZZZZZ     \n");
	}
}

// �������� ���� �����ֱ�
void showMoney(long long abalone, long long money, long long Aclick, long long big, long long smal, long long level, long long nursery, long long quote, long long price) {
	// header
	gotoxy(2, 12);
	printf("%91lld�� : ��", money);
	gotoxy(2, 12);
	printf("Ŭ���� ���� ���� : %lld", Aclick);
	gotoxy(4, 86);
	printf("1�� %6lld�� : ���� �ü�", quote);

	//bottom
	gotoxy(26, 12);
	printf("����� �� : %4lld%70lld : ���� �հ�", nursery, abalone);


	if (price == 2147483647) {
		gotoxy(27, 12);
		printf("���� : max%74lld : ���� ������", smal);
		gotoxy(28, 12);
		printf("%86lld : ū ������", big);
		gotoxy(20, 50);

	}
	else {
		gotoxy(27, 12);
		printf("���� : %4lld%73lld : ���� ������", level, smal);
		gotoxy(28, 12);
		printf("Level Up ��� : %8lld%62lld : ū ������", price, big);
		gotoxy(20, 50);
	}

}

// ����
void openStore(long long* abalone, long long* money, long long* Aclick, long long* big, long long* smal, long long numHome, long long* nursery, long long quote, char news[], int face) {
	static int nurseryPrice = 1500000;
	system("cls");

	gotoxy(2, 10);
	printf("[�Ӻ�] %s", news);

	gotoxy(10, 1);
	printf("                                                                                                  ���� ������(f)\n");
	printf("         ��----����-------------------------------------------------------------------------------------------��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��         ���� �Ǹ�(a)                    ����� ����(b)                      �� ����(c)            ��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��---------------------------------------------------------------------------------------------------��\n");

	while (1) {
		if (*nursery > 200) {
			gotoxy(16, 50);
			printf("����� ���� : %d", nurseryPrice);
		}
		else {
			gotoxy(16, 50);
			printf("                  ");
		}
		gotoxy(16, 80);
		printf("�� ���� : 1,000,000,000,000");
		gotoxy(29, 1);
		int key = _getch();
		if (key == f || key == F) {
			system("cls");
			setdisplay();
			printFace(face);
			return;
		}

		//���� �Ǹ�
		else if (key == 97 || key == 65) {
			long long Bprice = (*big / 4) * quote, Sprice = (*smal / 8) * quote;
			*abalone = *abalone - (((*big / 4) * 4) + ((*smal / 8) * 8));
			*big = *big - ((*big / 4) * 4);
			*smal = *smal - ((*smal / 8) * 8);
			*money = *money + Bprice + Sprice;
			gotoxy(16, 10);
			printf("�Ǹ� �Ǿ����ϴ�. (+%lld)                                        ", Bprice + Sprice);
		}

		//����� ����
		else if (key == 98 || key == 66) {
			if (*nursery < 200) {
				gotoxy(16, 10);
				printf("������� �ʹ� �����ϴ�.                                         ");
			}
			else if (nurseryPrice <= *money) {
				*money -= nurseryPrice;
				nurseryPrice *= 1.2;
				*nursery += 1;
				*Aclick += 10;
				gotoxy(16, 10);
				printf("������� ���ŵǾ����ϴ�. (+1)                              ");
			}

			else {
				gotoxy(16, 10);
				printf("���Ű� �Ұ��մϴ�.                                         ");
			}
		}

		//�� ����
		else if (key == 99 || key == 67) finish(*money);
	}
}

// ���� ����
void harvest(long long* Aclick, long long* abalone, long long* big, long long* smal) {
	for (int i = 0; i < *Aclick; i++) {

		int persent = rand() % 100;

		if (persent >= 80) { // ū ����
			*big = *big + 1;
		}
		else { // ���� ����
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

// ������
void levelUp(long long* level, long long* Aclick, long long* money, long long* price) {
	if (*level >= 999) {
		*price = 2147483647;
	}

	if (*money >= *price) {
		*money -= *price;
		*price += 5000;
		*level += 1;
		if (*level % 5 == 0) *Aclick += 1;
		// ������ ����
		gotoxy(24, 1);
		printf("           LEVEL UP!                 ");
	}
	else {
		// ���� �Ұ� ����
		gotoxy(24, 1);
		printf("           ���� �Ұ�                      ");
	}
}

//����
void Gacha(long long* money) {
reBet:
	system("cls");
	long long bet;
	printf("��black Jack��\n");
	if (*money <= 0 || *money < 10000) {
		printf("���� �ʹ� �����մϴ�");
		printf("\n\n����Ϸ��� �ƹ� Ű�� �����ʽÿ�...");
		trash = _getch();
		system("cls");
		return;
	}
	printf("�� : %lld\n", *money);
	while (1) {
		printf("���� �� �ݾ��� �����ּ��� : ");
		scanf_s("%lld", &bet);

		if (bet > *money) printf("�ݾ��� �ʹ� �����ϴ�.\n");
		else if (bet < 0 || bet < 10000) printf("���� �ݾ��� ���� �̻��Դϴ�\n");
		else if (*money >= bet) break;
		else printf("�ٽ� �Է����ּ���\n");
	}

	*money -= bet;

	system("cls");

	// ���� ����
	int Card[52], Dealer[10], Player[10], gameSet, get;

	while (1) {
		setting(Card);
		CardSetting(Dealer, Player, Card);
		gameSet = gameStart(Dealer, Player);
		GameFinish(gameSet, &bet);

		if (bet == 0) {
			printf("\n���� ���� �Ҿ����ϴ�\n");
			while (1) {
				printf("�ٽ� �����Ͻðڽ��ϱ�? (1)/(2) : ");
				get = _getch();
				printf("\n");
				if (get == 49) goto reBet;
				else if (get == 50) {
					printf("�ȳ������ʽÿ�\n");
					printf("\n\n����Ϸ��� �ƹ� Ű�� �����ʽÿ�...");
					trash = _getch();
					system("cls");
					return;
				}
			}
		}

	Retry:
		printf("\n\nȹ�� �� �ݾ� : %lld��\n\n", bet);
		printf("���� �������� �̱�ٸ�... : %lld��\n", bet * 2);
		printf("\n\n���(1) / �׸��ϱ�(2) : ");
		get = _getch();

		printf("\n");

		if (get == 50)
		{
			printf("Thanks.\n"); // ����
			break;
		}
		else if (get != 49) {
			printf("reTry.\n");
			goto Retry;
		}

		system("cls");
	}

	*money += bet;

	printf("\n\n����Ϸ��� �ƹ� Ű�� �����ʽÿ�...");
	trash = _getch();

	system("cls");
}

// ��
void finish(long long money) {
	if (money >= 1000000000000) {
		system("cls");
		gotoxy(6, 1);
		printf("                                               ������������ ������������\n");
		printf("                                                         ��           ��\n");
		printf("                                                         ��           ��\n");
		printf("                                                         ��           ��\n");
		printf("                                               ��������������������������\n");
		printf("\n");
		printf("                                                 ����������������������\n");
		printf("                                                 ��\n");
		printf("                                                 ����������������������\n");
		printf("                                                 ��\n");
		printf("                                                 ����������������������\n");
		gotoxy(20, 1);
		printf("\n\n");
		Sleep(1000);
		printf("\n\n����Ϸ��� �ƹ� Ű�� �����ʽÿ�...");
		trash = _getch();
		system("cls");
		char story[] = "�� �����ÿ� ������ �ϵ� ��� ��XX";
		char story2[] = "�״� ���ڰ� �ż� �ٽ� ��Ʈ������ �����ϴµ�...";

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
		printf("\n\n�����Ͻ÷��� �ƹ�Ű�� �����ʽÿ�");
		trash = _getch();
		exit(1);
	}
	else {
		gotoxy(16, 10);
		printf("���Ű� �Ұ��մϴ�.                                         ");
	}
}