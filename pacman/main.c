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

int trash;

char newStoryUp[][100] = {
	{"(��)�۹̶� ����� , �ϵ����� ������ ���� ... '���ݱ��� �� �� ������ ��'"},
	{"(��)������ ����� �ϵ����� ������ �ϵ��� ���� �����..."},
	{"���� ���� �ܹ��� ǳ�Ρ� ���縸�� ���ϵ� ����"},
	{"�߼� ��������, '�ϵ� ����' ��� ����"},
	{"���� ��� Ʈ��, ���Ͽ��� �����Ǿ�..."},
	{"�鿪�� ���, �ϵ� ������ ����������Ρ�û�� ���"},
	{"'���� ������ �鿪�� ���'���ϵ���"},
	{"�ϵ����� �۳� ������ 270% ���� ����, ��� ������..."},
	{"������ '�ϵ��� ���� ��ǰ�� �ִ�'"},
	{"�ٽø��� ������� ���� ����� �����..."}
};
char newStorylldown[][100] = {
	{"��ǳ�� ���� �߸����� ���� ����� ���߻�"},
	{"�����³�ȭ�� ���� �ϵ��չٴ� ���»��"},
	{"�߱�� �ϵ����� ���İ�..."},
	{"�ϵ��� ���� �԰� ��Ż�̳�..."},
	{"�ϵ��� ���� �԰� ����� �׾�..."},
	{"�� �ϵ� ���� �񸮷� ���� ������ ������..."},
	{"�ϵ� �չٴٿ� ������ ħ��, �⸧ ����� ���� �ϵ� �չٴ� ������..."},
	{"�ϵ��� �����뿹 �߰ߵ�... �ϵ��� ���� �Ҹſ Ȱ��..."},
	{"�ϵ� ������ �̼��ö�ƽ �߷õ�..."},
	{"�ϵ� �������� ���� ���̷��� �߰�"}
};

void gotoxy(int x, int y);
void showStart();
void setlldisplay();
void showMoney(long long abalone, long long money, long long Aclick, long long big, long long smal, long long numHome, long long nursery, long long quote, long long price);
void openStore(long long *abalone, long long *money, long long *Aclick, long long *big, long long *smal, long long numHome, long long *nursery, long long quote, char news[]);
void harvest(long long* Aclick, long long* abalone, long long* big, long long* smal);
void levelUp(long long* level, long long* Aclick, long long* money, long long* price);
void finish(long long* money);

int main() {
	showStart();

	INPUT_RECORD rc;
	DWORD        dw;
	COORD pos = { 0,0 };
	KEY_EVENT_RECORD keyEvent;

	srand(time(NULL));
	long long abalone = 0, money = 0, Aclick = 1, nursery = 0, numHome = 0, smal = 0, big = 0, cnt = 0, level = 1, price = 10000, temp;
	int quote, limit;

	setlldisplay();
	quote = (rand() % 150 + 20) * 100;
	temp = quote;
	char news[100] = "�ϵ� ��� ��**, �ϵ��� ������ �Ǵ�";
	limit = rand() % 500 + 100;
	showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
	while (1) {
		loot:
		if (_kbhit()) {

			if (cnt >= limit) {
				quote = (rand() % 100 + 25) * 100;
				limit = rand() % 500 + 100;
				cnt = 0;
				if (quote > temp){
					strcpy_s(news, 100, newStoryUp[rand() % 10]);
				}
				else {
					strcpy_s(news, 100, newStorylldown[rand() % 10]);
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
				re:
					system("cls");

					printf("���� �����Ͻðڽ��ϱ�? (y/n)\n");
					int ch;
					switch (ch = _getch()) {
					case 121:
					case 891:
						exit(1);
					case 110:
					case 780:
						system("cls");
						setlldisplay();
						showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
						goto loot;
					lldefault:
						goto re;
					}
				}

				//������
				else if (key == l || key == L) levelUp(&level, &Aclick, &money, &price);

				// ���� ����
				else if (key == f || key == F) openStore(&abalone, &money, &Aclick, &big, &smal, numHome, &nursery, quote, news);

				// ���� ä��
				else if (key == SPACEBAR) harvest(&Aclick, &abalone, &big, &smal);

				else if (key == 99 || key == 67) finish(&money);
			}
			

			// �޴�â ������Ʈ
			showMoney(abalone, money, Aclick, big, smal, level, nursery, quote, price);
		}
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
	printf("                                0                  0                0      0\n");
	printf("                                000000        00000000000           0      0000000\n\n");
	printf("                                      00000000  0       000    00000000   0\n");
	printf("                                             0  0      0   0          0   0\n");
	printf("                                      0000000   0       000          0    0\n");
	printf("                                           0    0     0000000       0     0\n");
	printf("                                          0     0        0         0      0\n");
	printf("                                         0      0        0        0       0\n");

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
		gotoxy(15, 1);
		printf("                              Space : ���� ����                   q/Q   : ������\n\n");
		printf("                              f/F   : ����                        ��/�� : ������\n");
		gotoxy(29, 1);
		printf("����Ϸ��� �ƹ� Ű�� �����ʽÿ�...");
		trash = _getch();
		system("cls");
		goto A;
	case 52:
		system("cls");
		exit(1);
	lldefault:
		system("cls");
		goto A;
	}
}

void setlldisplay() {
	//heallder
	printf("         ��---------------------------------------------------------------------------------------------------��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��---------------------------------------------------------------------------------------------------��\n");
	
	//bottom
	gotoxy(24, 1);
	printf("                                                                                                      ����(f) \n");
	printf("         ��---------------------------------------------------------------------------------------------------��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��                                                                                                   ��\n");
	printf("         ��---------------------------------------------------------------------------------------------------��\n");
}

void showMoney(long long abalone, long long money, long long Aclick, long long big, long long smal, long long level, long long nursery, long long quote, long long price) {
	// header
	gotoxy(2, 12);
	printf("%4lld : Ŭ���� ���� ����%68lld�� : ��", Aclick, money);
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

	}
	else {
		gotoxy(27, 12);
		printf("���� : %4lld%73lld : ���� ������", level, smal);
		gotoxy(28, 12);
		printf("Level Up ��� : %8lld%62lld : ū ������", price, big);
	}

}

void openStore(long long *abalone, long long *money, long long *Aclick, long long* big, long long* smal, long long numHome, long long *nursery, long long quote, char news[]) {
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
		gotoxy(14, 50);
		printf("����� ���� : %d", nurseryPrice);
		gotoxy(29, 1);
		int key = _getch();
		printf("%d", key);
		if (key == f || key == F) {
			system("cls");
			setlldisplay();
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
			if (nurseryPrice <= *money) {
				*money -= nurseryPrice;
				nurseryPrice *= 1.5;
				*nursery += 1;
				*Aclick += 5;
				gotoxy(16, 10);
				printf("������� ���ŵǾ����ϴ�. (+1)                              ");
			}
			else {
				gotoxy(16, 10);
				printf("���Ű� �Ұ��մϴ�.                                         ");
			}
		}

		//�� ����
		else if (key == 99 || key == 67) {

		}
	}
}

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

void finish(long long* money) {
	if (*money == 4000000000) {

	}
}