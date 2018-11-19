#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define CLIENT 0
#define BORROW 1
#define BOOK 2
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
	char *bookISBN;				// ISBN
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
	char *format = "%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%c\n";
	
	// 임시로 문자열들 담을 변수
	char tempName[100];
	char tempPublisher[100];
	char tempAuthor[100];
	char tempISBN[100];
	char tempLocation[100];	

	head = malloc(sizeof(BookNode));
	curr = head;
	while(check){

		check = fscanf(ifp,format, &temp.bookId, tempName, tempPublisher, tempAuthor, tempISBN, tempLocation, &temp.isBookAvailable );

		if( check == 0 || check == EOF)
			break;
		
		// 노드 메모리 할당
		curr->nextNode = malloc(sizeof(BookNode));
		curr = curr->nextNode;

		// 파일로 부터 읽어들인 데이터 할당(포인터 변수들만 해당)
		temp.bookName = malloc(sizeof(char)*(strlen(tempName)+1));
		temp.bookPublisher = malloc(sizeof(char)*(strlen(tempPublisher)+1));
		temp.bookAuthor = malloc(sizeof(char)*(strlen(tempAuthor)+1));
		temp.bookISBN = malloc(sizeof(char)*(strlen(tempISBN)+1));
		temp.bookLocation = malloc(sizeof(char)*(strlen(tempLocation)+1));

		strcpy(temp.bookName, tempName);
		strcpy(temp.bookPublisher, tempPublisher);
		strcpy(temp.bookAuthor, tempAuthor);
		strcpy(temp.bookISBN, tempISBN);
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
			break;

		case BOOK:
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
		if( curr->client.clientStuId < newClient.clientStuId)
			if(newClient.clientStuId < curr->nextNode->client.clientStuId){
				
				ClientNode *newClientNode = malloc(sizeof(ClientNode));

				newClientNode->client = newClient;
				newClientNode->nextNode = curr->nextNode;

				// 메모리 주소 변경
				curr->nextNode = newClientNode;

				// 추가가 성공적으로 진행됐다면 파일에 즉시 반영
				save(CLIENT, head);
				return true;		
			}

		curr = curr->nextNode;
	
	}



}


int main(void){

	ClientNode *head = clientMemAlloc();
	ClientNode *clientCurr = head->nextNode;

	while( clientCurr != NULL){
		printf("텍스트 내용:%d|%s|%s|%s|%s\n", 
			clientCurr->client.clientStuId, clientCurr->client.clientPw, clientCurr->client.clientName, clientCurr->client.clientAddr, 
			clientCurr->client.clientTel);

			clientCurr = clientCurr->nextNode;
		}

	Client newClient = 
	{ 3, "123", "test", "seoul", "1234567890"};

	addClient(head, newClient);
	

	clientCurr = head->nextNode;
	while( clientCurr != NULL){
		printf("텍스트 내용:%d|%s|%s|%s|%s\n", 
			clientCurr->client.clientStuId, clientCurr->client.clientPw, clientCurr->client.clientName, clientCurr->client.clientAddr, 
			clientCurr->client.clientTel);

			clientCurr = clientCurr->nextNode;
		}


	return 0;
}

