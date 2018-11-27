#include <stdio.h>
#include "fileIO.h"

#define SEARCH 1
#define MY_BORROW 2
#define MODIFY_CLIENT 3
#define LOGOUT 4
#define SHUT 5

void user_search(BookNode *);
void printResult(BookNode *);
int *checkAvailable(BookNode *, BookNode *);

int main(void){

	BookNode *head = bookMemAlloc();

	while(1){
		int choice;

		printf(">>회원 메뉴<<\n");
		printf("1.도서검색 2.내 대여 목록\n");
		printf("3.개인정보 수정 4.회원 탈퇴\n");
		printf("5.로그아웃 6.프로그램 종료\n");



		scanf("%d", &choice);

		switch(choice){

		case SEARCH:
			user_search(head);
			break;
	
		case MY_BORROW:
	
			break;
		case MODIFY_CLIENT:

			break;
		case LOGOUT:

			break;
		case SHUT:

			break;

		}
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

	getchar();
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




