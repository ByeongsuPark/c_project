#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileIO.h"
#include "user.h"
#include "admin.h"


Client SignUp(ClientNode *clienthead)
{

	int tmpId;
	char tmpPw[100];
	char tmpName[100];
	char tmpAddr[100];
	char tmpTel[100];

	printf(">> 회원 가입 <<\n");
	printf("학번, 비밀번호, 이름 , 주소, 전화번호를 입력하세요.\n");

	printf("학번: ");
	scanf("%d", &tmpId);
	printf("비밀번호: ");
	scanf("%s", tmpPw);
	getchar();
	printf("이름: ");
	scanf("%s", tmpName);
	getchar();
	printf("주소: ");
	scanf("%[^\n]", tmpAddr);
	getchar();
	printf("전화번호: ");
	scanf("%[^\n]", tmpTel);
	getchar();

	Client newClient = { .clientStuId = tmpId};

	newClient.clientPw = malloc(sizeof(char)*strlen(tmpPw)+1);
	newClient.clientName = malloc(sizeof(char)*strlen(tmpName)+1);
	newClient.clientAddr = malloc(sizeof(char)*strlen(tmpAddr)+1);
	newClient.clientTel = malloc(sizeof(char)*strlen(tmpTel)+1);

	strcpy(newClient.clientPw, tmpPw);
	strcpy(newClient.clientName, tmpName);
	strcpy(newClient.clientAddr, tmpAddr);
	strcpy(newClient.clientTel, tmpTel);
	
	printf("%d\n", newClient.clientStuId);
	printf("%s\n", newClient.clientPw);
	printf("%s\n", newClient.clientName);
	printf("%s\n", newClient.clientAddr);
	printf("%s\n", newClient.clientTel);

	addClient(clienthead, newClient);

	return newClient;
}

// 로그인 사용자 Id/Pw 
typedef struct {
	char userId[10];
	char userPw[20];
} NowUser;

typedef struct _NowUserNode {
	NowUser NowUser;
	struct _NowUserNode *nextNode;
} NowUserNode;

// 로그인 사용자 계정 존재 여부 판단 -> 어느 권한으로 접속할지 판단 
int checkUser(ClientNode *head, NowUser nowUser)
{
	ClientNode *curr = head->nextNode;
	char admin_passwd[20] = "lib_admin";

	int tmp_userId = 0;

	while (curr != NULL)
	{
		if (strcmp(nowUser.userId, "admin") == 0)
		{
			if (strcmp(nowUser.userPw, admin_passwd) == 0)
				return 2;
			else
			{
				printf("비밀번호가 틀렸습니다.\n");
				return 3;
			}
		}

		else
		{
			tmp_userId = atoi(nowUser.userId);
			if (curr->client.clientStuId == tmp_userId)
				return 1;
			else
			{
				printf("존재하지 않습니다.\n");
				return 3;
			}
		}
	}
	return 0;
}

int main(void)
{

	BookNode *bookHead = bookMemAlloc();
	ClientNode *clientHead = clientMemAlloc();
	BorrowNode *borrowHead = borrowMemAlloc();

	NowUser nowUser;
	Client myClient;
	myClient.clientStuId = -1;

	while(1){

	printf(">> 도서관 서비스 <<\n");
	printf("1. 회원 가입\t2. 로그인\t3. 프로그램 종료\n");

	int num1;
	
	printf("번호를 선택하세요: ");
	scanf("%d", &num1);
	system("clear");

	// 도서관 서비스 선택 화면 
	switch (num1)
	{
		int num2;
	// 회원 가입
	case 1:
		myClient = SignUp(clientHead);
		break; 

	// 로그인
	case 2:
		printf(">> 로그인 <<\n");
		printf("학번: ");
		getchar();
		scanf("%s", nowUser.userId);
		printf("비밀번호: ");
		getchar();
		scanf("%s", nowUser.userPw);

		ClientNode *head;

		num2 = checkUser(head, nowUser);

		// 사용자 판단 
		switch (num2)
		{
		// 회원 메뉴 선택 화면 
			case 0:
				printf("로그인 불가. 학번이나 비밀번호를 확인해주세요\n");
				printf("가입한 계정 : %d\n", myClient.clientStuId);
				break;
			case 1:
				user_service(myClient, bookHead, borrowHead, clientHead);
				break;

		// 관리자 메뉴 선택 화면
			case 2:
				admin_service(bookHead, borrowHead, clientHead);

				break;
			case 3:
				system("exit");
			break;


		}

		break;
	}

	}
	return 0;
}
