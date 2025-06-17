//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section C - Stack and Queue Questions
Purpose: Implementing the required functions for Question 3 




*/

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//////////////////////////////////   linked list /////////////////////////////////

typedef struct _listnode{
	int item;
   struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
	int size;
   ListNode *head;
   ListNode *tail;
} LinkedList;

////////////////////////////////// stack //////////////////////////////////////////

typedef struct stack{
	LinkedList ll;
} Stack;

////////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int isStackPairwiseConsecutive(Stack *s);

void push(Stack *s, int item); //insertNode
int pop(Stack *s); //removeNode
int peek(Stack *s); //스택의 가장 위(top)에 있는 값을 꺼내지 않고 확인하는 함수
int isEmptyStack(Stack *s); //스택이 비어 있다 → 1 리턴 아니면 → 0 리턴

void printList(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);
void removeAllItems(LinkedList *ll);

//////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int c, value;

    Stack s;

    s.ll.head=NULL;
	s.ll.size =0;
	s.ll.tail =NULL;

    c =1;

    printf("1: Insert an integer into the stack:\n");
    printf("2: Check the stack is pairwise consecutive:\n");
    printf("0: Quit:\n");

    while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the stack: ");
			scanf("%d", &value);
			push(&s, value);
			printf("The stack is: ");
            printList(&(s.ll));
			break;
		case 2:
            if(isStackPairwiseConsecutive(&s))
            {
                printf("The stack is pairwise consecutive.\n");
            }
            else{
                printf("The stack is not pairwise consecutive.\n");
            }
            removeAllItems(&(s.ll));
            break;
		case 0:
			removeAllItems(&(s.ll));
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////

/**
 * 함수 이름: isStackPairwiseConsecutive
 * -------------------------------------
 * 스택 내의 숫자들이 쌍을 이루어 서로 연속적인지 확인한다.
 * 예: 16, 15, 11, 10, 5, 4 → (16,15), (11,10), (5,4) → 모두 연속 → 1 반환
 *
 * 조건:
 * - 스택의 크기가 홀수면 쌍이 맞지 않으므로 0 반환
 * - pop()과 push()만 사용해야 함
 * - 절댓값 차이(abs)를 이용해 연속성 판단 (순서 무관)
 * - 검사 후에는 스택이 원래대로 복원되어야 함
 *
 * 매개변수:
 *   Stack *s - 검사할 스택의 포인터
 *
 * 반환값:
 *   모든 쌍이 연속적이면 1, 아니면 0
 */

int isStackPairwiseConsecutive(Stack *s)
{
    // 예외 처리: 스택 자체가 NULL이거나 비어 있는 경우
    if (s == NULL || s->ll.head == NULL) {
        return 0;
    }

    // 스택의 원소 수가 홀수면 쌍이 맞지 않음
    if (s->ll.size % 2 != 0) {
        return 0;
    }

    // 임시로 데이터를 저장할 보조 스택 생성
    Stack tempStack;
    tempStack.ll.head = NULL;
    tempStack.ll.size = 0;
    tempStack.ll.tail = NULL;

    int isConsecutive = 1; // 결과: 기본값은 참(1)

    // 스택에서 두 개씩 꺼내서 쌍을 비교
    while (!isEmptyStack(s))
    {
        int first = pop(s);
        int second = pop(s);

        // 절댓값 차이가 1이 아니라면 연속 아님 → 즉시 0 설정
        if (abs(first - second) != 1) {
            isConsecutive = 0;
        }

        // 복원을 위해 보조 스택에 저장 (순서 유지 위해 역순으로 push)
        push(&tempStack, second);
        push(&tempStack, first);
    }

    // 보조 스택에 있던 원소들을 다시 원래 스택으로 복원
    while (!isEmptyStack(&tempStack))
    {
        push(s, pop(&tempStack));
    }

	
    return isConsecutive;
}


//////////////////////////////////////////////////////////////////////////////////

void push(Stack *s, int item){
   insertNode(&(s->ll), 0, item);
}

int pop(Stack *s){
   int item;
   if(!isEmptyStack(s)){
    item = ((s->ll).head)->item;
    removeNode(&(s->ll), 0);
    return item;
   }
    return INT_MIN;
}

int peek(Stack *s){
   return ((s->ll).head)->item;
}

int isEmptyStack(Stack *s){
   if ((s->ll).size == 0)
      return 1;
   return 0;
}

//////////////////////////////////////////////////////////////////////////////////

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

ListNode * findNode(LinkedList *ll, int index){

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
