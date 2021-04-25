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

#define _CRT_SECURE_NO_WARNINGS

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
	headNode* headnode = NULL;

	printf("\n\n ----- [손영재] [2018038080] -----\n\n");

	do {
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

		switch (command) {
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

	} while (command != 'q' && command != 'Q'); // 프로그램을 종료할 때까지 반복 실행

	return 1;
}


int initialize(headNode** h) {

	if (*h != NULL) // headNode가 NULL이 아닌 경우 초기화를 먼저 진행해야 하므로
		freeList(*h); // freeList 함수 호출, 인자로 헤드 포인터 *h 넘겨 할당 메모리 해제

	*h = (headNode*)malloc(sizeof(headNode)); // 헤드 포인터 h에 메모리 할당
	(*h)->first = NULL; // 초기화된 상태로 리스트에 노드가 없으므로 (*h)->first에 NULL을 대입
	return 1;
}

int freeList(headNode* h) {

	listNode* p = h->first; // 노드 포인터 p를 선언해 h->first 대입
	listNode* temp; // free()함수를 실행하기 위한 임시 포인터 선언
	while (p != NULL) { // 모든 노드에 대한 공간 할당 해제를 완료할 때까지
		temp = p; // temp를 p로 설정
		p = p->rlink; // p를 p->rlink로 설정
		free(temp); // prev가 가리키는 노드 공간에 대한 할당 해제
	}
	free(h); // headNode 뒷부분의 노드 할당 해제 완료 후 headNode도 할당 해제

	return 0;
}


void printList(headNode* h) {
	int i = 0; // 리스트의 index 값을 나타내는 변수 선언
	listNode* p; // 리스트 탐색을 위한 노드 포인터 p 선언

	printf("\n---PRINT\n");

	if (h == NULL) { // 노드가 없는 빈 리스트일 경우
		printf("Nothing to print....\n"); // 메시지 출력 및 복귀
		return;
	}

	p = h->first; // 노드 포인터에 리스트의 헤드 포인터 값 대입

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key); // 각 노드의 index와 key 값을 출력
		p = p->rlink; // 노드 포인터가 기존 노드 우측 노드를 가리키게 함
		i++; // index 값 증가
	}

	printf("  items = %d\n", i); // 총 노드의 개수, 즉 index 값을 출력
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드의 정보를 저장할 node 선언 및 공간 할당
	node->key = key; // node의 key를 사용자가 입력한 key 값으로 설정

	if (h->first == NULL) // h->first == NULL, 즉 리스트에 노드가 없는 경우
	{
		node->rlink = NULL; // 첫 번째이자 유일한 노드로 추가하므로 node->link를 NULL로 설정
		h->first = node; // 헤드 포인터가 새로 추가한 node를 가리키게 함
		node->llink = h; // 새롭게 첫 번째로 된 노드의 llink를 헤드 포인터를 가리키게 함
		return 0;
	}
	// 기존 리스트에 노드가 있는 경우
	listNode* listPoint; // 마지막 노드를 가리키는 포인터인 listPoint 선언
	for (listPoint = h->first; (listPoint->rlink) != NULL; )
		listPoint = listPoint->rlink; // for문을 통해 listPoint가 리스트의 마지막 노드를 가리킴


	listPoint->rlink = node; // listPoint가 가리키는 리스트의 마지막 노드의 rlink를 새로 추가하는 node로 설정
	node->llink = listPoint; // 새로 추가하는 마지막 node의 llink를 좌측 노드 포인터인 listPoint로 설정
	node->rlink = NULL; // node가 리스트의 새로운 마지막 노드이므로 node->rlink를 NULL로 설정

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) // h->first = NULL, 즉 입력된 노드가 없는 경우
	{
		printf("입력된 노드가 없습니다.\n"); // 메시지 출력 및 복귀
		return 0;
	}
	else if (h->first != NULL && h->first->rlink == NULL) // 리스트에 노드가 1개 있는 경우
	{
		listNode* temp = h->first; // 노드 포인터 temp를 선언하여 헤드 포인터 값 대입
		h->first = NULL; // 모든 노드를 삭제하므로 h->first = NULL
		free(temp); // temp, 즉 첫 번째 노드에 대한 공간 할당을 해제하여 노드 삭제함
		return 0;
	}
	// 노드가 2개 이상 있는 경우

	listNode* temp; // 마지막 노드 탐색을 위한 노드 포인터 temp 선언
	for (temp = h->first; ; temp = temp->rlink)
	{
		if (temp->rlink == NULL) // for문 반복을 통해 temp가 리스트의 마지막 노드를 가리킬 경우
		{
			temp->llink->rlink = NULL; // temp의 좌측 노드가 새로운 마지막 노드가 되므로 좌측 노드의 rlink = NULL
			free(temp); // 마지막 노드 삭제를 위한 free() 함수 실행
			break;
		}
	}
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드에 대한 공간을 할당에 node에 저장
	node->key = key; // node의 key를 사용자가 입력한 값으로 설정


	if (h->first == NULL) // 리스트에 노드가 존재하지 않을 경우
	{
		h->first = node; // h->first를 node로 설정하고
		node->rlink = NULL; // node가 리스트의 마지막 노드이므로 node->link를 NULL로 설정
		node->llink = h; // node의 llink가 헤드 포인터를 가리키게 함
		return 0;
	}
	// 기존 리스트에 노드가 존재하는 경우
	h->first->llink = node; // 기존 첫 번째 노드의 llink를 새로 추가하는 node를 가리키게 하고
	node->rlink = h->first; // 새로 추가하는 node의 node->rlink가 기존 첫 번째 노드를 가리키게 하고
	h->first = node; // 헤드 포인터가 가리키는 위치를 추가한 node로 새로 지정
	node->llink = h; // node의 llink가 헤드 포인터를 가리키게 함

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) // h->first = NULL인 경우, 즉 리스트에 노드가 존재하지 않을 경우
	{
		printf("입력된 node가 없습니다.\n"); // 메시지 출력 및 복귀
		return 0;
	}

	listNode* temp = h->first; // 노드 포인터 temp를 선언후 헤드 포인터가 가리키는 첫 번째 노드 주소 대입
	h->first = h->first->rlink; // 헤드 포인터가 두 번째 노드(첫 번째 노드의 rlink를 통해)를 가리키게 하여 첫 번째 노드의 연결고리 끊음
	h->first->llink = h; // 새롭게 첫 번째로 된 노드의 llink를 헤드 포인터를 가리키게 함
	free(temp); // 기존 첫 번째 노드의 주소를 가지고 있는 temp에 대한 할당을 해제하여 첫 번째 노드를 삭제


	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* lead = h->first;  // 역순 재배치를 위한 노드 포인터 lead 선언, 첫 번째 노드 가리키게 함
	listNode* temp = NULL; // lead의 우측 노드를 가리키는 포인터 temp 선언
	lead->llink = NULL;

	while (lead != NULL) // lead가 가리키는 노드의 다음 노드가 있을 때까지 반복
	{
		temp = lead->rlink; // temp가 기존 lead 노드의 우측 노드를 가리키게 함
		lead->rlink = lead->llink; // lead의 rlink를 lead의 llink로 대입하여 순서 바꿈
		lead->llink = temp; // lead의 llink를 기존 우측 노드인 temp를 가리키게 하여 순서 바꿈
		if (temp == NULL) // 마지막 노드까지 탐색을 완료하였을 때
		{
			h->first = lead; // 순서를 모두 바꾼 후 헤드 포인터가 lead를 가리키게 하여 첫 번째 노드로 함
			lead -> llink = h; // lead 노드의 llink가 헤드 포인터를 가리키게 함
		}
		lead = temp; // lead에 기존 우측 노드 포인터인 temp 대입하여 다음 노드 탐색 실행

	}
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 추가할 노드에 대한 공간을 할당에 node에 저장
	node->key = key; // node의 key를 사용자가 입력한 값으로 설정


	listNode* temp = h->first; // 값을 비교하기 위한 노드 포인터 temp, prevtemp 선언
	listNode* prevtemp = NULL; // 각각 h->first, NULL로 초기화

	if (temp == NULL) // temp가 NULL일때, 즉 리스트에 노드가 존재하지 않는 경우
	{
		printf("연결리스트 상 첫 번째로 입력하는 key로 비교대상 node가 없습니다.\n");
		node->rlink = NULL; // 첫 번째이자 유일한 노드로 추가하므로 node->link를 NULL로 설정
		h->first = node; // 헤드 포인터가 새로 추가한 node를 가리키게 함
		node->llink = h; // 새롭게 첫 번째로 된 노드의 llink를 헤드 포인터를 가리키게 함

		return 0;
	}
	else if (temp != NULL) // temp가 NULL이 아닐 때, 즉 노드가 1개 이상 존재하는 경우
	{
		for (temp = h->first; ; ) // temp가 리스트의 모든 노드를 한 번씩 가리킬 때까지 반복
		{
			if (key < (temp->key)) // 사용자가 추가하고자 하는 노드 key값 보다 큰 key를 가진 기존 노드를 발견한 경우
			{
				if (prevtemp == NULL) // h->first->rlink가 NULL, 즉 기존 노드가 1개 있는 경우
				{
					h->first = node; // 새로 추가하는 node를 기존 노드보다 앞선 위치에 추가해야 하므로
					node->rlink = temp; // 헤드 포인터가 node를 가리키게 하고 node->rlink가 기존 노드를 가리키게 함
					node->llink = h; // 새로 추가한 노드의 llink가 헤드 포인터를 가리키게 함
					temp->llink = node; // 기존 노드의 llink가 새로 추가된 노드 가리키게 함
					return 0;
				}
				else
				{ // 기존 노드가 2개 이상 있는 경우

					node->rlink = temp;  // 새로 추가하는 node->rlink를 값이 큰 뒤쪽 노드를 가리키게 하고
					node->llink = temp->llink; // 새로 추가하는 node의 llink가 좌측 노드를 가리키게 하고
					temp->llink->rlink = node; // 새로 추가하는 node의 좌측 노드의 rlink가 node를 가리키게 하며
					temp->llink = node; // 새로 추가하는 node보다 값이 큰 우측 노드의 llink가 node를 가리키게 한다.

					return 0;
				}
			}

			if ((temp->rlink) == NULL)
			{
				break; // temp->rlink가 NULL일 때, 즉 모든 노드에 대한 값 탐색을 완료한 경우 for문 탈출
			}

			prevtemp = temp; // 하나의 노드에 대한 탐색을 완료한 경우
			temp = temp->rlink; // prevtemp, temp가 가리키는 노드 + 1

		}


		if ((temp->rlink) == NULL) // 모든 노드에 대한 탐색을 마쳤을 때 입력한 key보다 큰값 가지는 node 없는 경우
		{
			//			printf("입력한 key보다 큰값을 가지는 노드가 없어 마지막 노드로 추가합니다.\n");
			temp->rlink = node; // temp가 가리키는 리스트의 마지막 노드의 rlink를 새로 추가하는 node로 설정
			node->llink = temp; // 새로 추가하는 마지막 node의 llink를 좌측 노드인 temp로 설정
			node->rlink = NULL; // node가 리스트의 새로운 마지막 노드이므로 node->rlink를 NULL로 설정
		}
		return 0;
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) // h->first = NULL인 경우, 즉 리스트에 노드가 존재하지 않을 경우
	{
		printf("입력된 노드가 없습니다.\n"); // 메시지 출력 및 복귀
		return 0;
	}

	listNode* temp = h->first; // 값을 비교하기 위한 노드 포인터 temp, prevtemp 선언

	for (temp = h->first; ; temp = temp->rlink) // for문을 통해 리스트의 모든 노드를 탐색하여
	{
		if (h->first->rlink != NULL && temp->rlink == NULL) // 탐색 완료 후에도 값이 일치하는 노드가 없을 경우
		{
			printf("입력한 key와 같은 값을 가지는 노드가 없어 삭제하지 않습니다.\n"); // 메시지 출력 및 복귀
			break;
		}

		if (key == (temp->key)) // 입력한 key와 같은 값을 가지는 노드를 찾은 경우
		{
			if (h->first->rlink == NULL) // 리스트의 노드가 1개인 경우
			{
				h->first = NULL; // 리스트의 노드를 모두 없애므로 h->first = NULL
				free(temp); // 값이 같은 리스트의 노드에 대한 공간 할당 해제
				return 0;
			}
			// 리스트의 노드가 2개 이상일 경우
			temp->llink->rlink = temp->rlink; // temp 노드 좌측 노드의 rlink를 temp 노드 우측 노드를 가리키게 함
			temp->rlink->llink = temp->llink; // temp 노드 우측 노드의 llink를 temp 노드 좌측 노드를 가리키게 함
			free(temp); // 지울 노드(temp)에 대한 공간 할당 해제
			break; // for문 빠져나옴
		}
	}

	return 1;
}


