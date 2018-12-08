#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define CLIENT 0
#define BORROW 1
#define BOOK 2

#define BOOK_NAME 1 
#define PUBLISHER 2
#define ISBN      3
#define AUTHOR    4
#define ALL       5
typedef struct {
	int clientStuId; 			// 학번
	char *clientPw; 			// 비밀번호
	char *clientName; 			// 이름
	char *clientAddr;			// 주소
	char *clientTel;			// 전화번호
} Client;

typedef struct _clientNode {			// 고객 연결 리스트 구조체 정의
	Client client;				// 고객 정보
	struct _clientNode *nextNode;		// 다음 노드의 주소를 저장할 포인터
}ClientNode;
	

typedef struct {
	int bookId;				// 도서번호
	char *bookName;				// 도서명
	char *bookPublisher;			// 출판사
	char *bookAuthor;			// 저자명
	long long  bookISBN;			// ISBN
	char *bookLocation;			// 소장처
	char isBookAvailable;			// 대여가능여부
} Book;

typedef struct _bookNode{			// 도서 연결 리스트 구조체 정의
	Book book;				// 도서 정보
	struct _bookNode *nextNode;		// 다음 노드의 주소를 저장할 포인터
}BookNode;

typedef struct {
	int clientStuId;			// 학번
	int bookId;				// 도서번호
	time_t checkoutDay;			// 대여일자
	time_t returnDay;			// 반납일자
} Borrow;

typedef struct _borrowNode {			// 대여 연결 리스트 구조체 정의
	Borrow borrow;				// 대여 정보
	struct _borrowNode *nextNode;		// 다음 노드의주소를 저장할 포인터
} BorrowNode;

FILE *getBorrow(){
	FILE *borrowFile = fopen("borrow.txt", "r");

	return borrowFile; 
}

FILE *getClient(){
	FILE *clientFile = fopen("client.txt", "r");

	return clientFile;
}

FILE *getBook(){
	FILE *bookFile = fopen("book.txt", "r");

	return bookFile;
}

/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief client.txt파일로부터 회원 데이터를 읽어서
 * 	  연결리스트 구조에 맞게 동적할당한다.
 * 
 * @param None
 * 
 * @return ClientNode *, 연결리스트의 head주소를 리턴한다.
 */
ClientNode *clientMemAlloc(){

	FILE *ifp = getClient(); 
	Client temp;
	ClientNode *head, *curr; 
	int check = 1;
	char *format = "%d|%[^|]|%[^|]|%[^|]|%s\n";
	
	// 임시로 문자열들 담을 변수
	char tempPw[100];
	char tempName[100];
	char tempAddr[100];
	char tempTel[100];

	head = malloc(sizeof(ClientNode));
	curr = head;
	while(check){

		check = fscanf(ifp,format, &temp.clientStuId, tempPw, tempName, tempAddr, tempTel);

		if( check == 0 || check == EOF)
			break;
		
		// 노드 메모리 할당
		curr->nextNode = malloc(sizeof(ClientNode));
		curr = curr->nextNode;

		// 파일로 부터 읽어들인 데이터 할당(포인터 변수들만 해당)
		temp.clientPw = malloc(sizeof(char)*(strlen(tempPw)+1));
		temp.clientName = malloc(sizeof(char)*(strlen(tempName)+1));
		temp.clientAddr = malloc(sizeof(char)*(strlen(tempAddr)+1));
		temp.clientTel = malloc(sizeof(char)*(strlen(tempTel)+1));

		strcpy(temp.clientPw, tempPw);
		strcpy(temp.clientName, tempName);
		strcpy(temp.clientAddr, tempAddr);
		strcpy(temp.clientTel, tempTel);

		curr->client = temp; // 데이터 노드에 복사
		}

		fclose(ifp); 


		curr->nextNode = NULL;

		curr = head->nextNode;

	return head;
}


/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief book.txt파일로부터 책 데이터를 읽어서
 * 	  연결리스트 구조에 맞게 동적할당한다.
 * 
 * @param None
 * 
 * @return BookNode*, 연결리스트의 head주소를 리턴한다.
 */
BookNode *bookMemAlloc(){

	FILE *ifp = fopen("book.txt", "r");
	Book temp;
	BookNode *head, *curr; 
	int check = 1;
	char *format = "%d|%[^|]|%[^|]|%[^|]|%lld|%[^|]|%c\n";
	
	// 임시로 문자열들 담을 변수
	char tempName[100];
	char tempPublisher[100];
	char tempAuthor[100];
	char tempLocation[100];	

	head = malloc(sizeof(BookNode));
	curr = head;
	while(check){

		check = fscanf(ifp,format, &temp.bookId, tempName, tempPublisher, tempAuthor, &temp.bookISBN, tempLocation, &temp.isBookAvailable );

		if( check == 0 || check == EOF)
			break;
		
		// 노드 메모리 할당
		curr->nextNode = malloc(sizeof(BookNode));
		curr = curr->nextNode;

		// 파일로 부터 읽어들인 데이터 할당(포인터 변수들만 해당)
		temp.bookName = malloc(sizeof(char)*(strlen(tempName)+1));
		temp.bookPublisher = malloc(sizeof(char)*(strlen(tempPublisher)+1));
		temp.bookAuthor = malloc(sizeof(char)*(strlen(tempAuthor)+1));
		temp.bookLocation = malloc(sizeof(char)*(strlen(tempLocation)+1));

		strcpy(temp.bookName, tempName);
		strcpy(temp.bookPublisher, tempPublisher);
		strcpy(temp.bookAuthor, tempAuthor);
		strcpy(temp.bookLocation, tempLocation);

		curr->book = temp; // 데이터 노드에 복사
		}

		fclose(ifp); 


		curr->nextNode = NULL;

		curr = head->nextNode;

	return head;
}

/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief borrow.txt파일로부터 대출 데이터를 읽어서
 * 	  연결리스트 구조에 맞게 동적할당한다.
 * 
 * @param None
 * 
 * @return BorrowNode *, 연결리스트의 head주소를 리턴한다.
 */
BorrowNode *borrowMemAlloc(){

	FILE *ifp = getBorrow();
	Borrow temp;
	BorrowNode *head, *curr; 
	int check = 1;
	char *format = "%d|%d|%d|%d\n";
	
	head = malloc(sizeof(BookNode));
	curr = head;
	while(check){

		check = fscanf(ifp,format, &temp.clientStuId, &temp.bookId, &temp.checkoutDay, &temp.returnDay); 

		if( check == 0 || check == EOF)
			break;
		
		// 노드 메모리 할당
		curr->nextNode = malloc(sizeof(BorrowNode));
		curr = curr->nextNode;

		// 파일로 부터 읽어들인 데이터 할당(포인터 변수들만 해당)


		curr->borrow = temp; // 데이터 노드에 복사
		}

		fclose(ifp); 


		curr->nextNode = NULL;

		curr = head->nextNode;

	return head;
}

/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief borrow.txt파일로부터 대출 데이터를 읽어서
 * 	  연결리스트 구조에 맞게 동적할당한다.
 * 
 * @param int type   : define된 쓸 파일 종류 ( CLIENT, BOOK, BORROW)
 * 	  void *head : 파일에 쓸 연결리스트의 최상위 노드 
 * 
 * @return bool true  : 성공적으로 파일에 기록한 경우 
 * 	 	false : 파일 기록 실패
 */
bool save(int type, void *head){

	char *format;

	switch(type){

		case CLIENT:
		{
			FILE *ofp = fopen("client.txt", "w");
			char *format = "%d|%s|%s|%s|%s\n";
			ClientNode *curr = ((ClientNode *)head)->nextNode;

			while( curr != NULL ){
				fprintf(ofp, format, curr->client.clientStuId,
					curr->client.clientPw,
					curr->client.clientName,
					curr->client.clientAddr,
					curr->client.clientTel);

				curr = curr->nextNode;
			}

			fclose(ofp);
		}
			break;

		case BORROW:
		{
			FILE *ofp = fopen("borrow.txt", "w");
			char *format = "%d|%d|%d|%d\n";
			BorrowNode *curr = ((BorrowNode *)head)->nextNode;

			while( curr != NULL ){
				fprintf(ofp, format, curr->borrow.clientStuId,
					curr->borrow.bookId,
					(int)curr->borrow.checkoutDay,
					(int)curr->borrow.returnDay);

				curr = curr->nextNode;
			}

			fclose(ofp);
		}
			break;
		case BOOK:
		{
			FILE *ofp = fopen("book.txt", "w");
			char *format = "%d|%s|%s|%s|%lld|%s|%c\n";
			BookNode *curr = ((BookNode *)head)->nextNode;

			while( curr != NULL ){
				fprintf(ofp, format, curr->book.bookId,
					curr->book.bookName,
					curr->book.bookPublisher,
					curr->book.bookAuthor,
					curr->book.bookISBN,
					curr->book.bookLocation,
					curr->book.isBookAvailable);

				curr = curr->nextNode;
			}

			fclose(ofp);
		}
			break;


		}

	return true;
	
}

/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief 연결리스트에 추가할 고객을 받아 
 * 	  동일 학번 존재 여부를 확인하고
 * 	  없는 경우 기존 연결리스트에 추가,
 * 	  추가한 후에는 파일 반영 함수 호출
 * 	  
 * 
 * @param ClientNode *head : 고객 데이터 연결리스트의 최상위 노드
 * 	  Client     newClient : 추가할 고객 구조체
 * 
 * @return bool true  : 성공적으로 메모리에 등록
 * 	 	false : 메모리에 등록 실패
 */
bool addClient(ClientNode *head, Client newClient){

	ClientNode *curr = head->nextNode;

	while( curr != NULL ){

		// 동일 학번이 존재할 경우 false 리턴
		if( curr->client.clientStuId == newClient.clientStuId){
			printf("동일 학번 존재\n");
			return false;
		}
		
		// 노드 연결 작업 시작
		if( newClient.clientStuId < curr->client.clientStuId) // 맨 첫번째 노드로 삽입되는 경우
		{
			ClientNode *newClientNode= malloc(sizeof(ClientNode));
			newClientNode->client = newClient;
			newClientNode->nextNode = curr->nextNode;

			head->nextNode = newClientNode;

			save(CLIENT, head);

			return true;

		}else if( curr->client.clientStuId< newClient.clientStuId && curr->nextNode == NULL){ // 마지막노드일 경우
		
				ClientNode *newClientNode = malloc(sizeof(ClientNode));

				newClientNode->client= newClient;
				newClientNode->nextNode = NULL;

				curr->nextNode = newClientNode;
;

				save(CLIENT, head);

				return true;

		}else if( curr->client.clientStuId < newClient.clientStuId){ // 중간에 추가되는 경우
			if(newClient.clientStuId < curr->nextNode->client.clientStuId){
				
				ClientNode *newClientNode= malloc(sizeof(ClientNode));

				newClientNode->client= newClient;
				newClientNode->nextNode = curr->nextNode;

				// 메모리 주소 변경
				curr->nextNode = newClientNode;
;

				// 추가가 성공적으로 진행됐다면 파일에 즉시 반영
				save(CLIENT, head);
				return true;		
			}
		}

		curr = curr->nextNode;
	
	}



}

/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief 연결리스트에 추가할 책을 받아 
 * 	  ISBN 값을 비교하여 기존 연결리스트에 추가,
 * 	  추가한 후에는 파일 반영 함수 호출
 * 	  
 * 
 * @param BookNode *head : 책 데이터 연결리스트의 최상위 노드
 * 	  Book   newBook : 추가할 책 구조체
 * 
 * @return bool true  : 성공적으로 메모리에 등록
 * 	 	false : 메모리에 등록 실패
 */
bool addBook(BookNode *head, Book newBook){

	BookNode *curr = head->nextNode;

	while( curr != NULL ){

		
		// 노드 연결 작업 시작
		if( newBook.bookISBN <= curr->book.bookISBN) // 맨 첫번째 노드로 삽입되는 경우
		{
			BookNode *newBookNode= malloc(sizeof(BookNode));
			newBookNode->book = newBook;
			newBookNode->nextNode = curr;

			head->nextNode = newBookNode;

			save(BOOK, head);

			return true;

		}else if( curr->book.bookISBN < newBook.bookISBN && curr->nextNode == NULL){ // 마지막노드일 경우
		
				BookNode *newBookNode = malloc(sizeof(BookNode));

				newBookNode->book= newBook;
				newBookNode->nextNode = NULL;

				curr->nextNode = newBookNode;

				save(BOOK, head);

				return true;

		}else if( curr->book.bookISBN <= newBook.bookISBN){ // 중간에 추가되는 경우
			if(newBook.bookISBN <= curr->nextNode->book.bookISBN){
				
				BookNode *newBookNode= malloc(sizeof(BookNode));

				newBookNode->book= newBook;
				newBookNode->nextNode = curr->nextNode;

				// 메모리 주소 변경
				curr->nextNode = newBookNode;

				// 추가가 성공적으로 진행됐다면 파일에 즉시 반영
				save(BOOK, head);
				return true;		
			}
		}

		curr = curr->nextNode;
	
	}



}

/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief 추가할 대여 구조체를 받아
 * 	  기존의 대여 연결리스트에 추가한다.
 * 	  기존의 책 연결리스트에서 대여되는 도서의 도서번호를 찾아
 * 	  대여 가능 여부를 N으로 바꾼다.
 * 	  최종적으로 둘의 변경사항을 파일에 반영 한다.
 * 	  
 * @param BookNode    *bookHead  : 책 연결리스트의 최상위 노드
 * 	  BorrowNode  *borrwHead : 대여 데이터 연결리스트의 최상위 노드
 * 	  Borrow       newBorrow : 추가할 대여 데이터 관련 구조체
 * 
 * @return bool true  : 정상적으로 파일 반영 
 * 		false : 파일 반영 실패  					
 */
bool addBorrow(BookNode *bookHead, BorrowNode *borrowHead, Borrow newBorrow){

	BorrowNode *borrowCurr = borrowHead;
	BookNode *bookCurr = bookHead->nextNode;

	// 마지막 노드 까지 돌리고 돌리고~
	while( borrowCurr->nextNode != NULL )
	{
		borrowCurr = borrowCurr->nextNode;
	}
	// 대여 연결리스트에 새로운 노드 삽입
	borrowCurr->nextNode = malloc(sizeof(BorrowNode));
	borrowCurr = borrowCurr->nextNode;
	borrowCurr->borrow = newBorrow;
	borrowCurr->nextNode = NULL;

	// 대여 가능 여부 변경
	while( bookCurr != NULL)
	{
		if( bookCurr->book.bookId == newBorrow.bookId )
			bookCurr->book.isBookAvailable = 'N';

		bookCurr = bookCurr->nextNode;
	}

	// 변경사항 파일 반영
	save(BORROW, borrowHead);
	save(BOOK, bookHead);

	return true;
}


/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief 검색할 책에 대한 구조체를 받아 
 * 	  원하는 기준(criteria)로 검색을 수행,
 * 	  수행한 후에는 결과가 저장된 BookNode의 연결리스트 리턴
 * 	  
 * @param BookNode *head : 책 연결리스트의 최상위 노드
 * 	  int criteria : 검색 기준( 도서명, 출판사, ISBN등등..)
 * 			 이미 define되어 있음.
 * 	  Book value   : 검색 값을 저장한 Book 구조체
 * 
 * @return BookNode *searchResultHead : 검색 결과.
 * 					검색 결과가 0 일경우
 * 					다음 노드의 값이 NULL
 */
BookNode *searchBy(BookNode *head, int criteria, Book value){

	BookNode *resultHead = malloc(sizeof(BookNode));
	BookNode *curr = head->nextNode;
	BookNode *resultCurr = resultHead;


	while( curr != NULL ){
		switch(criteria){

			case BOOK_NAME:
			
				if(strstr( curr->book.bookName , value.bookName) != NULL){ // 이름이 검색될경우
					resultCurr->nextNode = malloc(sizeof(BookNode));
					resultCurr = resultCurr->nextNode;
					resultCurr->book = curr->book; // 결과 연결리스트에 현재 노드 추가
				}
				break;

			case PUBLISHER:
				if(strstr( curr->book.bookPublisher , value.bookPublisher ) != NULL){
					resultCurr->nextNode = malloc(sizeof(BookNode));
					resultCurr = resultCurr->nextNode;
					resultCurr->book = curr->book;
				}
				break;

			case ISBN:
				if( curr->book.bookISBN == value.bookISBN ){
					resultCurr->nextNode = malloc(sizeof(BookNode));
					resultCurr = resultCurr->nextNode;
					resultCurr->book = curr->book;
				}

				break;

			case AUTHOR:
				if(strstr( curr->book.bookAuthor, value.bookAuthor ) != NULL){
					resultCurr->nextNode = malloc(sizeof(BookNode));
					resultCurr = resultCurr->nextNode;
					resultCurr->book = curr->book;
				}
				break;

			case ALL:
				return head; 
				break;
			}

			curr = curr->nextNode;
		}

			resultCurr->nextNode = NULL;
	



	return resultHead;

}

/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief 삭제할 회원의 학번을 입력받아서
 * 	  대여중인 도서 목록이 존재하는지 확인한다.
 * 	  대여중인 도서가 있을 경우 false를 리턴한다.
 * 	  
 * @param ClientNode *clientHead : 회원 연결리스트의 최상위 노드
 * 	  BorrowNode *borrowHead : 대여 목록 연결리스트의 최상위 노드 
 * 	  int  	     targetStuId : 삭제할 회원의 학번
 * 
 * @return bool true : 성공적으로 삭제
 * 		false : 삭제 실패 ( 대여중인 도서 목록 존재 ) 
 */
bool removeClient(ClientNode *clientHead,BorrowNode *borrowHead, int targetStuId){

	ClientNode *clientCurr = clientHead->nextNode;
	BorrowNode *borrowCurr = borrowHead->nextNode;

	// 대여 목록에 해당 학번이 하나라도 존재할 경우 삭제 불가
	while( borrowCurr != NULL ){
		if( borrowCurr->borrow.clientStuId == targetStuId)
			return false;

		borrowCurr = borrowCurr->nextNode;
	}

	ClientNode *previousNode = clientHead;

	// 없다면 삭제 작업
	while( clientCurr != NULL ){
	
		if( clientCurr->client.clientStuId == targetStuId){
			previousNode->nextNode = clientCurr->nextNode;
			free(clientCurr);

			save(CLIENT, clientHead);

			return true;
		}

		previousNode = clientCurr;
		clientCurr = clientCurr->nextNode;
		}

	}

/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief 삭제할 책의 도서 번호를 입력받아서
 * 	  해당 책이 대여 중인지 확인한다.
 * 	  대여중인 경우 false를 리턴한다.
 * 	  대여중이지 않은 경우 책 연결리스트에서 해당 책을 삭제 후
 * 	  해당 변경사항을 파일에 반영한다.
 * 	  
 * @param BookNode   *bookHead   : 책 연결리스트의 최상위 노드
 * 	  BorrowNode *borrowHead : 대여 목록 연결리스트의 최상위 노드 
 * 	  int  	    targetBookId : 삭제할 책의 도서번호
 * 
 * @return bool true : 성공적으로 삭제
 * 		false : 삭제 실패 ( 해당 도서번호의 책이  대여중 ) 
 */
bool removeBook(BookNode *bookHead,BorrowNode *borrowHead, int targetBookId){

	BorrowNode *borrowCurr = NULL;
	BookNode   *bookCurr = bookHead->nextNode;
	if( borrowHead != NULL) // 도서 검색에서 쓸수 있도록 범용성 고려 
		borrowCurr = borrowHead->nextNode;

	// 대여 목록에 해당 도서번호가 있을 경우 삭제 불가
	while( borrowCurr != NULL ){
		if( borrowCurr->borrow.bookId == targetBookId)
			return false;

		borrowCurr = borrowCurr->nextNode;
	}

	BookNode *previousNode = bookHead;

	// 없다면 삭제 작업
	while( bookCurr != NULL ){
	
		if( bookCurr->book.bookId== targetBookId){
			previousNode->nextNode = bookCurr->nextNode;

			free(bookCurr);

			if( borrowCurr != NULL)
				save(BOOK, bookHead);

			return true;
		}

		previousNode = bookCurr;
		bookCurr = bookCurr->nextNode;
		}

	}

/**
 * @author ByeongsuPark (byonsu@gmail.com)
 *
 * @brief 반납할 책의 도서 번호를 입력받아서
 * 	  해당 번호 도서를 대여 목록에서 삭제한다.
 * 	  또한 해당 책의 대여 가능 여부를 Y로 바꾼다.
 * 	  최종적으로 해당 변경사항을 파일에 반영한다.
 * 	  
 * @param BookNode   *bookHead   : 책 연결리스트의 최상위 노드
 * 	  BorrowNode *borrowHead : 대여 목록 연결리스트의 최상위 노드 
 * 	  int  	    targetBookId : 삭제할 책의 도서번호
 * 
 * @return bool true : 성공적으로 삭제
 * 		false : 삭제 실패 
 */
bool removeBorrow(BookNode *bookHead,BorrowNode *borrowHead, int targetBookId){

	BookNode   *bookCurr = bookHead->nextNode;
	BorrowNode *borrowCurr = borrowHead->nextNode;

	BorrowNode *previousNode = borrowHead;

	// 해당 대여 데이터를 메모리에서 삭제
	while( borrowCurr != NULL ){
		printf("데이터 메모리 삭제 함수 진입\n");
		if( borrowCurr->borrow.bookId == targetBookId){
			if(borrowCurr->nextNode != NULL) // 마지막 노드 같은 경우는 그냥 메모리 해제만 해주면 됨
				previousNode->nextNode = borrowCurr->nextNode;
			else
				previousNode->nextNode = NULL;

			free(borrowCurr);

			break;
		}
		previousNode = borrowCurr;
		borrowCurr = borrowCurr->nextNode;
	}

	while( bookCurr != NULL)
	{
		if( bookCurr->book.bookId == targetBookId )
			bookCurr->book.isBookAvailable = 'Y';

		bookCurr = bookCurr->nextNode;
	}

	// 변경사항 파일 반영
	save(BORROW, borrowHead);
	save(BOOK, bookHead);

	}

/**
int main(void){

	BookNode *bookHead= bookMemAlloc();
	BookNode *bookCurr = bookHead->nextNode;

	while( bookCurr != NULL){
		printf("텍스트 내용:%d|%s|%s|%s|%lld|%s|%c\n", 
			bookCurr->book.bookId, bookCurr->book.bookName, bookCurr->book.bookPublisher, bookCurr->book.bookAuthor,
			bookCurr->book.bookISBN,
			bookCurr->book.bookLocation,
			bookCurr->book.isBookAvailable);

			bookCurr = bookCurr->nextNode;
		}

	ClientNode *clientHead = clientMemAlloc();
	BorrowNode *borrowHead = borrowMemAlloc();

	Borrow test = { .clientStuId = 3, .bookId = 2 }; 

	removeBorrow(bookHead, borrowHead, 2);


	return 0;
}
**/
