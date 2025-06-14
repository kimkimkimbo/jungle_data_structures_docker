//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 
사용자에게 입력 받은 정수 하나를 오름차순 정렬 리스트에 삽입하는 것. 삽입이 안 되면 -1 삽입 시 인덱스 번호 반환
*/


//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
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

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
		//정수 입력 받고, 리스트에 삽입 후 달라지 리스트 프린트
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
		//값과 인덱스 위치 프린트
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
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

int insertSortedLL(LinkedList *ll, int item)
{
	/* j = insertSortedLL(&ll, i);
	   삽입 안 되면 -1, 삽입되면 인덱스 위치 반환 
	
	   1. 중복 값인지 확인
	   2. 중복 값이 아니라면 삽입 
	   3. 현재 노드(cur)와 다음 노드(cur->next)의 값을 비교해서
	      cur->item < item < cur->next->item이 되는 그 중간 자리를 찾아 삽입
	*/

	ListNode *cur = ll->head;

	// 중복 값 존재 여부 확인 (중복 시 바로 -1 반환)
	while (cur != NULL)
	{
		if (item == cur->item){
			return -1;  // 중복 발견, 삽입하지 않고 종료
		}
		cur = cur->next;
	}

	// 중복 검사 끝나면 cur는 NULL 상태임
	// 따라서 다시 리스트 처음으로 초기화 필요
	cur = ll->head;

	if (ll->head == NULL){
		// 빈 리스트면 그냥 첫 노드로 삽입해야 함 (안 그러면 아예 삽입 불가)
		insertNode(ll, 0, item);
		return 0; 
	}

	// 맨 앞에 삽입해야 할 경우 (맨 처음 값이 새 아이템보다 클 때)
	if (ll->head->item > item ){
		insertNode(ll, 0, item);
		return 0;  // 0번 인덱스에 삽입했으니 0 반환
	}

	int index = 0;
	while (cur->next != NULL)
	{
		// 중간에 넣어야 할 위치 탐색
		if (cur->item < item && item < cur->next->item){
			// 삽입 시 index 위치가 아니라 index+1 위치에 넣어야 함
			insertNode(ll, index + 1, item);
			return index + 1;  // 삽입 후 즉시 반환해서 중복 삽입 방지
		}
		cur = cur->next;
		++index;
	}

	// 마지막 노드까지 돌았는데도 삽입 위치를 못 찾았으면
	// 리스트의 가장 뒤에 삽입 (index는 마지막 노드 인덱스)
	insertNode(ll, ll->size, item);
	return ll->size - 1;  // 삽입 후 가장 마지막 인덱스 반환
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
