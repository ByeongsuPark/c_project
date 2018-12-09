#include <stdio.h>
#include <stdlib.h>

#define SEARCH 1
#define MY_BORROW 2
#define MODIFY_CLIENT 3
#define SECESSION 4
#define LOGOUT 5
#define SHUT 6

void user_search(BookNode *);
void printResult(BookNode *);
int *checkAvailable(BookNode *, BookNode *);
void printMyBorrow(BorrowNode *,BookNode *, Client );
char *getBookNameById(BookNode *, int );
void modifyClientInfo(ClientNode *, Client);
void modifyClientTel(ClientNode *, Client, char *);
void modifyClientAddr(ClientNode *, Client, char *);
void modifyClientPw(ClientNode *, Client, char *);


void user_service(Client myClient, BookNode *bookHead, BorrowNode *borrowHead, ClientNode *clientHead){


	while(1){
		int choice;

		printf(">>회원 메뉴<<\n");
		printf("1.도서검색 2.내 대여 목록\n");
		printf("3.개인정보 수정 4.회원 탈퇴\n");
		printf("5.로그아웃 6.프로그램 종료\n");



		scanf("%d", &choice);

		switch(choice){

		case SEARCH:
			user_search(bookHead);
			break;
	
		case MY_BORROW:
			printMyBorrow(borrowHead,bookHead, myClient);
	
			break;
		case MODIFY_CLIENT:{
			modifyClientInfo(clientHead, myClient);

			break;
			}
		case SECESSION:
			if(!removeClient(clientHead, borrowHead, myClient.clientStuId))
				printf("탈퇴 불가능. 대여중인 도서가 존재합니다.\n");
			else
				return ;

			break;
		case LOGOUT:
			return ;

			break;
		case SHUT:
			exit(1);
			break;

		}
	}

}

void modifyClientInfo(ClientNode *clientHead, Client myClient){ 

	int changeInfoNum;

	printf("\n어떤 정보를 수정하시겠습니까?\n");
	printf("1.비밀번호 2.주소 3.전화번호\n");
	scanf("%d", &changeInfoNum);

	switch(changeInfoNum){

		case 1:{
			char pwTochange[50];
			printf("바꿀 비밀번호를 입력해주세요: ");
			scanf("%s", pwTochange);

			modifyClientPw(clientHead, myClient, pwTochange);

		break;
		}
		case 2:{
			char addrTochange[100];
			printf("바꿀 주소를 입력해주세요: ");
			scanf("%s", addrTochange);

			modifyClientAddr(clientHead, myClient, addrTochange);

		break;
		}
		case 3:{
			char telTochange[20];
			printf("바굴 전화번호를 입력해주세요: ");
			scanf("%s", telTochange);

			modifyClientTel(clientHead, myClient, telTochange);

		break;
		}

	}
}

void modifyClientTel(ClientNode *clientHead, Client myClient, char *telTochange){

	ClientNode *clientCurr = clientHead->nextNode;

	while(clientCurr != NULL){
		
		if(clientCurr->client.clientStuId == myClient.clientStuId){
			strcpy(clientCurr->client.clientTel, telTochange);
			save(CLIENT, clientHead);
		}

		clientCurr = clientCurr->nextNode;
	}
}

void modifyClientAddr(ClientNode *clientHead, Client myClient, char *addrTochange){

	ClientNode *clientCurr = clientHead->nextNode;

	while(clientCurr != NULL){
		
		if(clientCurr->client.clientStuId == myClient.clientStuId){
			strcpy(clientCurr->client.clientAddr, addrTochange);
			save(CLIENT, clientHead);
		}

		clientCurr = clientCurr->nextNode;
	}


}

void modifyClientPw(ClientNode *clientHead, Client myClient, char *pwTochange){

	ClientNode *clientCurr = clientHead->nextNode;

	while(clientCurr != NULL){
		
		if(clientCurr->client.clientStuId == myClient.clientStuId){
			strcpy(clientCurr->client.clientPw, pwTochange);
			save(CLIENT, clientHead);
		}

		clientCurr = clientCurr->nextNode;
	}



}


void printMyBorrow(BorrowNode *borrowHead, BookNode *bookHead, Client myClient){
	
	char *wday[7] = { "일", "월", "화", "수", "목", "금", "토"};
	BorrowNode *curr = borrowHead->nextNode;

	printf("\n>>내 대여 목록<<\n");
	while( curr != NULL){

		if( curr->borrow.clientStuId == myClient.clientStuId){

			time_t borrowTime = time(&curr->borrow.checkoutDay);
			time_t returnTime = time(&curr->borrow.returnDay);

			struct tm borrow_t;
			localtime_r(&borrowTime, &borrow_t);
			struct tm return_t;
			localtime_r(&returnTime, &return_t);


			printf("도서번호 : %d\n", curr->borrow.bookId);
			printf("도서명 : %s\n", getBookNameById(bookHead, curr->borrow.bookId));
			printf("대여일자: %d년 %d월 %d일 %s요일\n",
				borrow_t.tm_year + 1900,
				borrow_t.tm_mon + 1,
				borrow_t.tm_mday,
				wday[borrow_t.tm_wday]);

			printf("반납일자: %d년 %d월 %d일 %s요일\n",
				return_t.tm_year + 1900,
				return_t.tm_mon + 1,
				return_t.tm_mday,
				wday[return_t.tm_wday]);

		}


		curr = curr->nextNode;

	}

	curr = borrowHead->nextNode;

	while( curr != NULL){
		printf("%d %d\n", (int)curr->borrow.checkoutDay,
				(int)curr->borrow.returnDay);

		curr = curr->nextNode;
	}


}

char *getBookNameById(BookNode *bookHead, int targetBookId){

	BookNode *curr = bookHead->nextNode;

	while( curr != NULL ){

		if( curr->book.bookId == targetBookId)
			return curr->book.bookName;

		curr = curr->nextNode;

	}

}

void user_search(BookNode *head){

	printf(">> 도서 검색<<\n");
	printf("1.도서명 검색 2.출판사 검색\n");
	printf("3.ISBN 검색   4.저자명 검색\n");
	printf("5.전체 검색   6.이전 메뉴\n");
	printf("번호를 선택하세요: ");

	int choice;
	char temp[50];
	Book value;

	scanf("%d", &choice);

	switch(choice){

		case BOOK_NAME:
		{
			printf("도서명을 입력하세요: ");
			
			char temp[50];
			scanf("%s", temp);

			Book value = { .bookName = temp };

			printf("\n");
			printResult(searchBy(head, BOOK_NAME, value));
			
			break;
		}
		case PUBLISHER:
		{
			printf("출판사를 입력하세요: ");

			char temp[50];
			scanf("%s", temp);

			Book value = { .bookPublisher = temp };

			printf("\n");
			printResult(searchBy(head, PUBLISHER, value));

			break;
		}

		case ISBN:
		{
			printf("ISBN을 입력하세요: ");
			long long isbn;

			scanf("%lld", &isbn);

			Book value = { .bookISBN = isbn };

			printf("\n");
			printResult(searchBy(head, ISBN, value));

			break;
		}
		case AUTHOR:
		{
			printf("작가를 입력하세요: ");

			scanf("%s", temp);

			Book value = { .bookAuthor = temp};

			printf("\n");
			printResult(searchBy(head, AUTHOR, value));

		break; 
		}
		case ALL:
		{// 전체 출력
			BookNode *curr = head->nextNode;
		
			while( curr != NULL){
				printf("도서명: %s\n", curr->book.bookName);
				printf("출판사: %s\n", curr->book.bookPublisher);
				printf("저자명: %s\n", curr->book.bookAuthor);
				printf("ISBN  : %lld\n", curr->book.bookISBN);
				printf("소장처: %s\n", curr->book.bookLocation);
			
				int *checkoutResult = checkAvailable(head , curr);
				printf("대여가능 여부: %c(%d/%d) \n", 
					checkoutResult[0] == checkoutResult[1] ? 'N' : 'Y', checkoutResult[1], checkoutResult[0]);
				printf("\n");

				curr = curr->nextNode;
			}
			break;
		}
		case 6:
			return ;
			break;
	}

	}



void printResult(BookNode *result){
	if(result->nextNode == NULL){
		printf("입력하신 도서명에 맞는 결과가 없습니다.\n");
		return ;
	}
	else{
		BookNode *curr = result->nextNode;

		while( curr != NULL){
			printf("도서명: %s\n", curr->book.bookName);
			printf("출판사: %s\n", curr->book.bookPublisher);
			printf("저자명: %s\n", curr->book.bookAuthor);
			printf("ISBN  : %lld\n", curr->book.bookISBN);
			printf("소장처: %s\n", curr->book.bookLocation);
			int *checkoutResult = checkAvailable(result, curr);
			printf("대여가능 여부: %c(%d/%d) \n", 
					checkoutResult[0] == checkoutResult[1] ? 'N' : 'Y', checkoutResult[1], checkoutResult[0]);
			printf("\n");

			curr = curr->nextNode;
		}

	}

}

/**
 *
 *
/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief 검색결과인 result노드에서 파라미터로 넘어온 책이 
 *        여러 권 있는지 확인한다.
 *        여러 권 있는 경우 대출된 책의 갯수를 센다.
 *        맨 처음 노드를 제외한 뒤에 중복되는 노드들은 삭제한다.
 * 	  
 * @param BookNode *result : 검색결과 연결리스트 최상위 노드
 *        BookNode *value  : 해당 책
 * 
 * @return int *checkAvailable : 해당 책의 총 장서 수(0)와 
 * 				 대출된 책의 수(1)가 담긴 배열을 리턴함
 */
int *checkAvailable(BookNode *result, BookNode *value){

	BookNode *curr = result->nextNode;
	int numOfBook = 0;
	int numOfCheckoutBook = 0;

	// 맨 처음 받아온 책이 대출 불가능한 경우 예외처리
	if( value->book.isBookAvailable == 'N')
		numOfCheckoutBook++;

	while( curr != NULL){
		// 같은 책일 경우 보유 총 장서수 증가
		if( value->book.bookISBN == curr->book.bookISBN){
			numOfBook++;
			// 맨 처음 노드가 아닐 경우 
			// 대출 여부 확인 후 해당 노드 제거
			if( value->book.bookId != curr->book.bookId){
				if(curr->book.isBookAvailable == 'N')
					numOfCheckoutBook++;
				removeBook(result, NULL, curr->book.bookId);
			}

		}

		curr = curr->nextNode;
	}

	int *processedResult = malloc(sizeof(int) * 2);

	processedResult[0] = numOfBook;
	processedResult[1] = numOfCheckoutBook;


	return processedResult;

}




