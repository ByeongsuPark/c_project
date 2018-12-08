#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fileIO.h"
#include "user.h"


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

	BookNode *bookhead = bookMemAlloc();
	ClientNode *clienthead = clientMemAlloc();

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
		myClient = SignUp(clienthead);
		break; 

	// 로그인
	case 2:
		printf(">> 로그인 <<\n");
		printf("학번: ");
		scanf("%s", nowUser.userId);
		printf("비밀번호: ");
		scanf("%s", nowUser.userPw);

		num2 = checkUser(clienthead, nowUser, &myClient);

		// 사용자 판단 
		switch (num2)
		{
		// 회원 메뉴 선택 화면 
			case 1:
				if( myClient.clientStuId != -1) 
					user_service(myClient);
				else
					printf("회원 정보가 없습니다. 회원가입을 먼저해주세요.\n");

				break;

		// 관리자 메뉴 선택 화면
			case 2:
				printf(">> 관리자 메뉴 <<");
				printf("1. 도서 등록\t2. 도서 삭제\n3.도서 대여\t4. 도서 반남\n5. 도서 검색\t6. 회원 목록\n7. 로그아웃\t8. 프로그램 종료\n");

				break;
			case 3:
				system("exit");
			break;


		}
	}

	}
	return 0;
}
