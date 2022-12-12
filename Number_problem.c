#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void file_finder(void);
void score_print(void);
int test(void);
int sum(int* a);
void problem(int no, int* a);
int grading(int no, int* a);
void write_score(int a);

char name[100];
int s;

int main()
{
	file_finder();
	score_print();
	printf("수학 문제를 푸시겠습니까? (Y/N)\n");
	if (getch() == 'n')
	{
		printf("프로그렘을 종료합니다.");
		return 0;
	}
	int score = test();
	printf("100점 중에서 %d점입니다.\n",score);
	write_score(score);
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

void score_print(void)
{

	FILE* lfp = fopen("Result.txt", "r");
	FILE* bfp = fopen("BestPlay.txt", "r");
	fscanf(lfp, "%s %d", name, &s);
	printf("최근 플레이 기록 \n 이름 : %s 점수 : %d\n", name, s);
	fscanf(bfp, "%s %d", name, &s);
	printf("최고 기록 \n 이름 : %s 점수 : %d\n", name, s);
	fclose(lfp);
	fclose(bfp);
}

int test(void)
{
	int score = 0;
	int ans[4];
	srand(time(NULL));
	for (int i = 1; i < 11; i++)
	{
		ans[0] = rand() % 100;
		ans[1] = rand() % 9 + 1;
		ans[2] = rand() % 4;
		ans[3] = sum(ans);
		problem(i, ans);
		score += grading(i,ans);
	}
	return score;
}

int sum(int* a)
{
	switch (a[2])
	{
	case 0:
		return a[0] + a[1];
	case 1:
		return a[0] - a[1];
	case 2:
		return a[0] * a[1];
	case 3:
		return a[0] / a[1];
	}
}

void problem(int no, int* a)
{
	char op[] = { '+','-','*','/' };
	if (a[2] == 0)
	{
		printf("%d번 : %d + %d = ", no, a[0], a[1]);
	}
	else if (a[2] == 1)
	{
		printf("%d번 : %d - %d = ", no, a[0], a[1]);
	}
	else if (a[2] == 2)
	{
		printf("%d번 : %d * %d = ", no, a[0], a[1]);
	}
	else
	{
		printf("%d번 : %d / %d = ", no, a[0], a[1]);
	}
}

int grading(int no, int* a)
{
	int input, score = 10;
	char ans;
	for (int i = 10; i--; i > 0)
	{
		scanf("%d", &input);
		if (input != a[3]&&i != 0)
		{
			printf("\n틀렸습니다. 다시 시도 하시곘습니까? (Y/N) (기회 %d번)\n",i);
			ans = getch();
			if (ans == 'n')
			{
				printf("다음 문제로 넘어갑니다.\n");
				return 0;
			}
			problem(no, a);
		}
		else if(input == a[3])
		{
			printf("정답입니다!\n");
			return i+1;
		}
	}
	printf("기회를 다 소진 하여 다음 문제로 넘어갑니다.\n");
	return 0;
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