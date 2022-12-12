#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

void file_finder(void);
void last_play(void);
void best_play(void);
void random_number(int* a);
int number_baseball(int* a);
int judge(int* a, int b);
void write_score(int a);

char name[100];
int s;

int main()
{
	file_finder();
	printf("숫자야구를 하시겠습니까?(Y/N)\n");
	if (getch() == 'n')
	{
		printf("프로그렘을 종료합니다.\n");
		return 0;
	}
	int num[3];
	int score;
	char ans;
	do
	{
		printf("1.게임시작\n2.최근 플레이 기록\n3.최고 기록\n4.나가기\n\n");
		ans = getch();
		if (ans == '1')
		{
			do
			{
				random_number(num);
				score = 100 - 10 * number_baseball(num);
				printf("점수 : %d점\n", score);
				write_score(score);
				printf("계속 하시겠습니까? (Y/N)\n");
				ans = getch();
			} while (ans != 'n');
		}
		else if (ans == '2')
		{
			last_play();
			ans = '0';
		}
		else if (ans == '3')
		{
			best_play();
			ans = '0';
		}
	} while (ans != '4');
	return 0;
}

void file_finder(void)
{
	FILE* lfp = fopen("Result.txt", "r");
	if (lfp == NULL)
	{
		printf("최근 플레이 파일이 없습니다.\n파일을 생성합니다.\n");
		lfp = fopen("Result.txt", "w");
		fprintf(lfp, "NoName -1");
		fclose(lfp);
	}
	FILE* bfp = fopen("BestPlay.txt", "r");
	if (bfp == NULL)
	{
		printf("최고 기록 파일이 없습니다.\n파일을 생성합니다.\n");
		bfp = fopen("BestPlay.txt", "w");
		fprintf(bfp, "NoName -1");
		fclose(bfp);
	}
}

void last_play(void)
{
	FILE* lfp = fopen("Result.txt", "r");
	fscanf(lfp, "%s %d", name, &s);
	printf("가장 최근 플레이 기록 : %s님 %d점\n\n", name, s);
	fclose(lfp);
}

void best_play(void)
{
	FILE* bfp = fopen("BestPlay.txt", "r");
	fscanf(bfp, "%s %d", name, &s);
	printf("최고 점수 : %s님 %d점\n\n", name, s);
	fclose(bfp);
}

void random_number(int* a)
{
	srand(time(NULL));
	int overlap = 0;
	do
	{
		a[0] = rand() % 8 + 1;
		a[1] = rand() % 9;
		a[2] = rand() % 9;
		if (a[0] == a[1] || a[0] == a[2])
		{
			overlap++;
		}
		if (a[1] == a[0] || a[1] == a[2])
		{
			overlap++;
		}
		if (a[2] == a[1] || a[2] == a[0])
		{
			overlap++;
		}
	} while (overlap != 0);
}

int number_baseball(int* a)
{
	int ans;
	int i;
	for (i = 1; i < 11; i++)
	{
		printf("세자리 수를 입력하세요.\n");
		do
		{
			scanf("%d", &ans);
			if (ans <= 99 || ans > 1000)
			{
				printf("숫자가99 이하이거나 1000 이상입니다.\n");
				printf("다시 세자리 수를 입력하세요.\n");
			}
		} while (ans <= 99 || ans > 1000);
		printf("%d회차 : ", i);
		if (judge(a,ans) == 0)
		{
			return i-1;
		}
	}
	printf("정답 : ");
	for (int j = 0; j < 3; j++)
	{
		printf("%d",a[j]);
	}
	printf("\n");
	return i-1;
}

int judge(int* a, int b)
{
	int play[3];
	int strike = 0, ball = 0, out = 0;
	int i;
	for (i = 0; i < 3; i++)
	{
		play[2 - i] = b % 10;
		b = b / 10;
		if (play[2-i] == a[2-i])
		{
			strike += 1;
		}
		else if (play[2 - i] == a[0] || play[2 - i] == a[1] || play[2 - i] == a[2])
		{
			ball += 1;
		}
		else
		{
			out += 1;
		}
	}
	printf("%dStrike! %dBall %dOut\n", strike, ball, out);
	if (strike == 3)
	{
		return 0;
	}
	else
	{
		return 1;
	}
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
	if (a > s)
	{
		FILE* bfp = fopen("BestPlay.txt", "w");
		printf("최고 기록 경신! 축하드립니다!\n");
		printf("최고 기록은 자동으로 BestPlay.txt 파일에 자동으로 저장됩니다.\n");
		fprintf(bfp, "%s %d", name, a);
		fclose(bfp);
	}
}