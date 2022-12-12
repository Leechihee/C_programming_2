#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int map[4][5] = { 0 };
int s;
char name[100];
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, coord);
}
void drow_card(char a[])
{
	int i, j;
	srand(time(NULL));
	int x, y;
	for (i = 0; i < 2; i++)
	{
		for (j = 0; j < 10; j++)
		{
			do
			{
				x = rand() % 4;
				y = rand() % 5;
			} while (map[x][y] != 0);
			map[x][y] = a[j];
		}
	}
}
void file_finder(void)
{
	FILE* lfp = fopen("Result.txt", "r");
	if (lfp == NULL)
	{
		printf("최근 플레이 파일이 없습니다.\n파일을 생성합니다.\n");
		lfp = fopen("Result.txt", "w");
		fprintf(lfp, "NoName 99999");
		fclose(lfp);
	}
	FILE* bfp = fopen("BestPlay.txt", "r");
	if (bfp == NULL)
	{
		printf("최고 기록 파일이 없습니다.\n파일을 생성합니다.\n");
		bfp = fopen("BestPlay.txt", "w");
		fprintf(bfp, "NoName 99999");
		fclose(bfp);
	}
}
void display()
{
	int i, j;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 5; j++)
		{
			printf("%5c", map[i][j]);
		}
		printf("\n");
	}
}
void delay(int n)
{
	int start = time(NULL),end;
	do
	{
		end = time(NULL);
	} while (end - start <n);
}
void write_score(int a)
{
	char bname[100];
	printf("플레이한 유저의 이름을 입력하세요.\n");
	scanf("%s", name);
	FILE* lfp = fopen("Result.txt", "w");
	fprintf(lfp, "%s %d", name, a);
	fclose(lfp);
	FILE* bfp = fopen("BestPlay.txt", "r");
	fscanf(bfp, "%s %d", bname, &s);
	fclose(bfp);
	if (a < s)
	{
		FILE* bfp = fopen("BestPlay.txt", "w");
		printf("최고 기록 경신! 축하드립니다!\n");
		printf("최고 기록은 자동으로 BestPlay.txt 파일에 자동으로 저장됩니다.\n");
		fprintf(bfp, "%s %d", name, a);
		fclose(bfp);
	}
}
int main()
{
	char card[11] = "~!@#$%^&*?";
	int visit[21] = { 0 };
	int start, end;
	int i, j,x,y,n,m,x1,y1,cnt = 0;
	file_finder();
	FILE* fp = fopen("BestPlay.txt", "r");
	fscanf(fp,"%s %d",name,&s);
	gotoxy(20, 20);
	printf("%s님이 %d초만에 하셨습니다.", name, s);
	fclose(fp);
	delay(5);
	system("cls");
	drow_card(card);
	display();
	delay(3);
	system("cls");
	for (i = 1; i < 21; i++)
	{
		printf("%5d", i);
		if (i%5==0)
		{
			printf("\n");
		}
	}
	start = time(NULL);
	printf("두개의 번호를 입력하세요 : ");
	while (1)
	{
		scanf("%2d %2d", &n, &m);
		x = (n - 1) / 5;
		y = (n - 1) % 5;
		x1 = (m - 1) / 5;
		y1 = (m - 1) % 5;
		if (visit[n] == 0 && visit[m]==0)
		{
			gotoxy(y * 5, x);
			printf("%5c", map[x][y]);
			gotoxy(y1 * 5, x1);
			printf("%5c", map[x1][y1]);
			delay(3);
			if (map[x][y] != map[x1][y1])
			{
				gotoxy(y * 5, x);
				printf("%5d", n);
				gotoxy(y1 * 5, x1);
				printf("%5d", m);
			}
			else
			{
				visit[n] = 1;
				visit[m] = 1;
				cnt++;
				if (cnt == 10)
				{
					break;
				}
			}
		}
		gotoxy(26, 4);
		printf("       ");
		gotoxy(26, 4);
	}
	end = time(NULL);
	gotoxy(0, 5);
	printf("%d초 걸리셨습니다.", end - start);
	write_score(end - start);
	return 0;
}

