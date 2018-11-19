#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct date
{
	int year;
	int month;
	int day;
} date;

typedef struct identity
{
	char name[30];
	date birth;
	char gender[10];
	char phone[16];
} identity;

void printSet(identity ** set, int size);

void sort(identity ** set, int size, int mode);

int structtoi(date data);

int main()
{
	int subjectno;

	printf("입력할 명세서의 개수를 입력하시오: ");
	scanf("%d", &subjectno);
	identity ** group = (identity **)calloc(subjectno, sizeof(identity *));

	for (int personid = 0; personid < subjectno; personid++)
	{
		char name[30];
		int year, month, day;
		char gender[10];
		char phone[16];
		printf("개인명세 입력%d: ", personid + 1);
		scanf("%s %d/%d/%d %s %s", name, &year, &month, &day, gender, phone);
		while (getchar() != '\n');
		identity * individual = (identity *)malloc(sizeof(identity));
		strcpy(individual->name, name);
		individual->birth.year = year;
		individual->birth.month = month;
		individual->birth.day = day;
		strcpy(individual->gender, gender);
		if (strlen(phone) == 11)
		{
			char pushbuffer = phone[3];
			for (int cursor = 4; cursor < 16; cursor++)
			{
				char swapbuffer = pushbuffer;
				pushbuffer = phone[cursor];
				phone[cursor] = swapbuffer;
			}
			pushbuffer = phone[8];
			for (int cursor = 9; cursor < 16; cursor++)
			{
				char swapbuffer = pushbuffer;
				pushbuffer = phone[cursor];
				phone[cursor] = swapbuffer;
			}
			phone[3] = phone[8] = '-';
		}
		else
		{
			char pushbuffer = phone[2];
			for (int cursor = 3; cursor < 16; cursor++)
			{
				char swapbuffer = pushbuffer;
				pushbuffer = phone[cursor];
				phone[cursor] = swapbuffer;
			}
			pushbuffer = phone[7];
			for (int cursor = 8; cursor < 16; cursor++)
			{
				char swapbuffer = pushbuffer;
				pushbuffer = phone[cursor];
				phone[cursor] = swapbuffer;
			}
			phone[2] = phone[7] = '-';
		}
		strcpy(individual->phone, phone);
		group[personid] = individual;
	}
	printSet(group, subjectno);
	sort(group, subjectno, 1);
	printSet(group, subjectno);
	sort(group, subjectno, 2);
	printSet(group, subjectno);
	getchar();
	return 0;
}

void printSet(identity ** set, int size)
{
	printf("이름\t\t생년월일\t성별\t\t전화번호\n");
	for (int element = 0; element < size; element++)
	{
		printf("%s\t\t%d-%d-%d\t%s\t\t%s\n", (*(set + element))->name, (*(set + element))->birth.year, (*(set + element))->birth.month, (*(set + element))->birth.day, (*(set + element))->gender, (*(set + element))->phone);
	}
}

void sort(identity ** set, int size, int mode)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0; j--)
		{
			if (mode == 1 ? strcmp(set[j - 1]->name, set[j]->name) == 1 : structtoi(set[j - 1]->birth) > structtoi(set[j]->birth))
			{
				identity * swapbuffer = set[j - 1];
				set[j - 1] = set[j];
				set[j] = swapbuffer;
			}
		}
	}
}

int structtoi(date data)
{
	return (data.year * 100 + data.month) * 100 + data.day;
}
