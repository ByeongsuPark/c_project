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
	getchar();
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

	Client newclient = { tmpId, tmpPw, tmpName, tmpAddr, tmpTel };
	
	printf("%d\n", newclient.clientStuId);
	printf("%s\n", newclient.clientPw);
	printf("%s\n", newclient.clientName);
	printf("%s\n", newclient.clientAddr);
	printf("%s\n", newclient.clientTel);

	addClient(clienthead, newclient);

	return newclient;
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
int checkUser(ClientNode *head, NowUser nowUser, Client *myClient)
{
	ClientNode *curr = head->nextNode;

	int tmp_userId;

	while (curr != NULL)
	{
		if (strcmp(nowUser.userId, "admin") == 0)
			return 2;

		tmp_userId = atoi(nowUser.userId);

		if (curr->client.clientStuId == tmp_userId)
			if(strcmp(curr->client.clientPw, nowUser.userPw) == 0)
			{	
				*myClient = curr->client;
				return 1;
			}

		curr = curr->nextNode;
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
		scanf("%s", nowUser.userId);
		printf("비밀번호: ");
		scanf("%s", nowUser.userPw);

		num2 = checkUser(clientHead, nowUser, &myClient);

		// 사용자 판단 
		switch (num2)
		{
		// 회원 메뉴 선택 화면 
			case 0:
				printf("로그인 불가. 학번이나 비밀번호를 확인해주세요\n");
				break;
			case 1:
				user_service(myClient, bookHead, borrowHead, clientHead);
				break;

		// 관리자 메뉴 선택 화면
			case 2:
				admin_service();

				break;
			case 3:
				system("exit");
			break;


		}
	}

	}
	return 0;
}
