#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"

void SignUp()
{
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
	NowUser NowUser;
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

	NowUser nowUser;

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
		SignUp();
		break; 

	// 로그인
	case 2:
		printf(">> 로그인 <<");
		printf("학번: ");
		scanf("%d", &nowUser.userId);
		printf("비밀번호: ");
		scanf("%s", nowUser.userPw);

		ClientNode *head;

		num2 = checkUser(head, nowUser);

		// 사용자 판단 
		switch (num2)
		{
		// 회원 메뉴 선택 화면 
		case 1:
			printf(">> 회원 메뉴 <<");
			printf("1. 도서 검색\t2. 내 대여 목록\n3. 개인 정보 수정\t4. 회원 탈퇴\n5. 로그아웃\t6. 프로그램 종료\n");

			int num3;

			printf("번호를 선택하세요: ");
			scanf("%d", num3);

			
			switch (num3)
			{
			// 도서 검색
			case 1:
				printf(">> 도서 검색 <<");
				break;

			// 내 대여 목록
			case 2: 
				break;

			// 개인 정보 수정
			case 3:
				break;

			// 회원 탈퇴 
			case 4: 
				break;

			// 로그아웃 
			case 5: 
				break;

			// 프로그램 종료
			case 6:
				system("exit");
				break;

			default:
				break;
			}

			break;

		// 관리자 메뉴 선택 화면
		case 2:
			printf(">> 관리자 메뉴 <<");
			printf("1. 도서 등록\t2. 도서 삭제\n3.도서 대여\t4. 도서 반남\n5. 도서 검색\t6. 회원 목록\n7. 로그아웃\t8. 프로그램 종료\n");

			int num4;

			printf("번호를 선택하세요: ");
			scanf("%d", &num4);

			// 
			switch (num4)
			{
			// 도서 등록
			case 1:
				break;

			// 도서 삭제 
			case 2:
				break;

			// 도서 대여 
			case 3:
				break;

			// 도서 반납 
			case 4:
				break;

			// 도서 검색 
			case 5: 
				break;;

			// 회원 목록 
			case 6:
				break;

			// 로그아웃 
			case 7:
				break;

			// 프로그램 종료
			case 8:
				system("exit");
				break;

			default:
				break;
			}
			break;

		default:
			break;
		}
		break;

	case 3:
		system("exit");
		break;

	default:
		break;
	}

	return 0;
}
