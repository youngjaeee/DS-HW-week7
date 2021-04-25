/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key; // 노드가 가지는 value 값
	struct Node* llink; // L노드를 가리키는 노드 포인터
	struct Node* rlink; // R노드를 가리키는 노드 포인터
} listNode;



typedef struct Head {
	struct Node* first; // 첫 번째 노드를 가리키는 헤드 포인터
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h); // 노드를 초기화하는 함수

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h); // 노드의 값을 지우고 할당한 메모리를 회수하는 함수

int insertNode(headNode* h, int key); // 리스트 탐색하여, 입력받은 key보다 큰값 나오는 노드 앞에 삽입하는 함수
int insertLast(headNode* h, int key); // 리스트의 마지막 부분에 노드를 추가하는 함수
int insertFirst(headNode* h, int key); // 리스트의 처음 부분에 노드를 추가하는 함수
int deleteNode(headNode* h, int key); // 사용자가 입력한 값을 가지는 노드를 찾아 삭제하는 함수
int deleteLast(headNode* h); // 리스트의 마지막 노드를 삭제하는 함수
int deleteFirst(headNode* h); // 리스트의 첫 번째 노드를 삭제하는 함수
int invertList(headNode* h); // 리스트의 순서를 역방향으로 전환하는 함수

void printList(headNode* h); // 리스트를 출력하는 함수


int main()
{
	char command; // 사용자의 메뉴 선택값을 저장하는 변수 선언
	int key; // 특정 노드의 value 값을 임시로 저장할 변수 선언
	headNode* headnode=NULL;

	printf("\n\n ----- [손영재] [2018038080] -----\n\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': // 사용자가 리스트 초기화를 선택했을 경우
			initialize(&headnode); // headnode로 시작하는 리스트에 대한 초기화 함수 호출
			break;
		case 'p': case 'P': // 사용자가 리스트 출력을 선택했을 경우
			printList(headnode); // 리스트 출력 함수 호출, 인자로 headnode를 넘김
			break;
		case 'i': case 'I': // 입력받은 key보다 큰값 나오는 노드 앞에 삽입하고자 하는 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값을 입력받은 후
			insertNode(headnode, key); // 노드 삽입 함수 호출, 매개변수로 headnode와 탐색할 key값을 넘김
			break;
		case 'd': case 'D': // 입력받은 key값을 가지는 노드를 삭제하고자 하는 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값을 입력받은 후
			deleteNode(headnode, key); // 노드 삭제 함수 호출, 매개변수로 headnode와 탐색할 key값을 넘김
			break;
		case 'n': case 'N': // 리스트의 가장 마지막에 노드를 삽입하고자 하는 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값을 입력받은 후
			insertLast(headnode, key); // 리스트 마지막에 노드 삽입 함수 호출, 매개변수로 headnode와 key값
			break;
		case 'e': case 'E': // 리스트의 마지막 노드를 삭제하고자 하는 경우
			deleteLast(headnode);  // 리스트 마지막 노드 삭제 함수 호출, 매개변수로 headnode를 넘김
			break;
		case 'f': case 'F': // 리스트의 가장 처음 부분에 노드를 추가하고자 하는 경우
			printf("Your Key = ");
			scanf("%d", &key); // key 값을 입력받은 후
			insertFirst(headnode, key); // 리스트 처음 부분 삽입 함수 호출, 매개변수로 headnode와 key 값
			break;
		case 't': case 'T': // 리스트의 가장 처음 부분 node를 삭제하고자 하는 경우
			deleteFirst(headnode); // 리스트 처음 부분 삭제 함수 호출, 매개변수로 headnode 넘김
			break;
		case 'r': case 'R': // 리스트의 순서를 역으로 변환하고자 하는 경우
			invertList(headnode); // 리스트 순서 변환 함수 호출, 매개변수로 headnode 넘김
			break;
		case 'q': case 'Q': // 프로그램을 종료하고자 하는 경우
			freeList(headnode); // 리스트 값 제거 및 할당한 메모리 환수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // 프로그램을 종료할 때까지 반복 실행

	return 1;
}


int initialize(headNode** h) {

	return 1;
}

int freeList(headNode* h){
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {


	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	return 1;
}


