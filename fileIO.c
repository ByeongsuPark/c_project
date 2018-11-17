#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

typedef struct {
	int clientStuId; 			// 학번
	char *clientPw; 			// 비밀번호
	char *clientName; 			// 이름
	char *clientAddr;			// 주소
	char *clientTel;			// 전화번호
} Client;

typedef struct _clientNode {			// 고객 연결 리스트 구조체 정의
	Client client;				// 고객 정보
	struct _clientNode *nextClient;		// 다음 노드의 주소를 저장할 포인터
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
	struct _borrowNode *nextBorrow;		// 다음 노드의주소를 저장할 포인터
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
 * @brief book.txt파일로부터 책 데이터를 읽어서
 * 	  연결리스트 구조에 맞게 동적할당한다.
 * 
 * @param None
 * 
 * @return BookNode *, 연결리스트의 head주소를 리턴한다.
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

int main(void){

	BookNode *head = bookMemAlloc();
	BookNode *curr = head->nextNode;

	while( curr != NULL){
		printf("텍스트 내용:%d|%s|%s|%s|%s|%s|%c\n", 
			curr->book.bookId, curr->book.bookName, curr->book.bookPublisher, curr->book.bookAuthor, 
			curr->book.bookISBN, curr->book.bookLocation, curr->book.isBookAvailable);

			curr = curr->nextNode;
		}


	return 0;
}

