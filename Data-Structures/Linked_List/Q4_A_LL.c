//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 4 목적: 문제 4번에서 요구되는 함수들을 구현하는 것 */

/* 짝수를 리스트 뒤로 보내라 
void moveEvenItemsToBack(LinkedList *ll) <- 프로토타입 함수
예시: 1, 3, 5 -> 1, 3, 5
2, 4, 6 -> 2, 4, 6
2, 3, 4, 7, 15, 18 -> 3, 7, 15, 2, 4, 18
*/

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h> //standard library

//////////////////////////////////////////////////////////////////////////////////

//typedef 별칭, struct 구조체 타입
typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


//////////////////////// function prototypes /////////////////////////////////////

// You should not change the prototype of this function
void moveEvenItemsToBack(LinkedList *ll);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);

//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;
	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;


	printf("1: Insert an integer to the linked list:\n");
	printf("2: Move all even integers to the back of the linked list:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			moveEvenItemsToBack(&ll); // You need to code this function
			printf("The resulting linked list after moving even integers to the back of the linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void moveEvenItemsToBack(LinkedList *ll) //짝수 노드를 뒤로 옮기는 함수
{
    if (ll == NULL || ll->head == NULL) return; //NULL 이면 그 뒤 작업들에서 에러 나기 때문에 끝

    ListNode *cur = ll->head; 

	// 새 리스트 구조체 할당 및 반드시 초기화 필요!
    // 초기화 안 하면 구조체 내 멤버에 쓰레기 값이 들어가서 이상 동작 발생 가능
    LinkedList *oddList = malloc(sizeof(LinkedList)); 
    oddList->head = NULL;
    oddList->size = 0;

    LinkedList *evenList = malloc(sizeof(LinkedList));
    evenList->head = NULL;
    evenList->size = 0;
 
    while (cur != NULL)
    {
        if(cur->item % 2 == 0){
            insertNode(evenList, evenList->size, cur->item); //짝수 리스트 생성
        }
        else{
            insertNode(oddList, oddList->size, cur->item); //홀수 리스트 생성
        }
        cur = cur->next; //다음 노드 보기
    }

	//홀수 + 짝수 붙이기
    if (oddList->head == NULL){ //홀수가 없을 때
        ll->head = evenList->head; // 홀수 리스트가 비어있으면 짝수 리스트를 머리로 세팅
        ll->size = evenList->size;
    } else {
        ListNode *tail = oddList->head; 
        while (tail->next != NULL)
        {
            tail = tail->next; // 홀수 리스트 끝 값을 taill에 넣기
        }
        tail->next = evenList->head; //홀수 리스트 끝 노드 다음에 짝수 머리 연결
        ll->head = oddList->head; //ll 헤드는 홀수
        ll->size = oddList->size + evenList->size; //둘을 합친 사이즈
    }

    free(oddList); //안 하면 메모리 누수됨!
    free(evenList);
}


///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
