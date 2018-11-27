#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

void SignUp(int num)
{
	// 새로운 회원 정보를 입력 받을 구조체
	/*
	struct new_user {
		int student_number;
		char password[20];
		char name[10];
		char address[50];
		char phone_number[15];
	};

	struct new_user new_user;
	*/

	typedef struct {
		int newClientId;
		char *newClientPw;
		char *newClientName;
		char *newClientAddr;
		char *newClientTel;
	} NewClient;

	NewClient newClient;

	printf(">> 회원 가입 <<\n");
	printf("학번, 비밀번호, 이름 , 주소, 전화번호를 입력하세요.\n");

	printf("학번: ");
	scanf("%d", &newClient.newClientId);
	getchar();
	printf("비밀번호: ");
	scanf("%s", newClient.newClientPw);
	getchar();
	printf("이름: ");
	scanf("%s", newClient.newClientName);
	getchar();
	printf("주소: ");
	scanf("%[^\n]", newClient.newClientAddr);
	getchar();
	printf("전화번호: ");
	scanf("%[^\n]", newClient.newClientTel);
	getchar();

	/*
	printf("%d\n", newClient.newClinetId);
	printf("%s\n", newClient.newClientPw);
	printf("%s\n", newClient.newClientName);
	printf("%s\n", newClient.newClientAddr);
	printf("%s\n", newClient.newClientTel);
	*/

	bool addClient(ClientNode *head, NewClient newClient);
}

// 로그인 사용자 Id/Pw 
typedef struct {
	int userId;
	char *userPw;
} NowUser;

typedef struct _NowUserNode {
	NowUser nowUser;
	struct _NowUserNode *nextNode;
} NowUserNode;

// 로그인 사용자 계정 존재 여부 판단 -> 어느 권한으로 접속할지 판단 
int checkUser(ClientNode *head, NowUser nowUser)
{
	ClientNode *curr = head->nextNode;

	while (curr != NULL)
	{
		// 회원 계정 존재 여부 확인 
		if (curr->client.clientStuId == nowUser.userId)
			return 1;
		else if (nowUser.userId == "admin")
			return 2;
		else
		{
			printf("존재하지 않습니다.");
			return 3;
		}
	}
	return 0;
}

int main(void)
{
	FILE *getBorrow();
	FILE *getClient();
	FILE *getBook();

	BookNode *bookMemAlloc();
	BookNode *clientMemAlloc();
	BookNode *borrowMemAlloc();

	printf(">> 도서관 서비스 <<\n");
	printf("1. 회원 가입\t2. 로그인\t3. 프로그램 종료\n");

	int num;
	printf("번호를 선택하세요: ");
	scanf("%d", &num);
	system("clear");

	switch (num)
	{
		int num2;

	case 1:
		SignUp(num);
		break; 

	case 2:
		printf("학번: ");
		scanf("%d", &nowUser.userId);
		printf("비밀번호: ");
		scanf("%s", nowUser.userPw);

		num2 = checkUser(head, nowUser);

		break;

	case 3:
		break;

	default:
		break;
	}

	return 0;
}
