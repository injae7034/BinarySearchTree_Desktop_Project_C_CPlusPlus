#include "LinkedList.h"
#include<stddef.h>//size_t
#include<stdlib.h>//free, malloc, calloc
#include<memory.h>//memcpy
#pragma warning(disable:4996)


//Create
void Create(LinkedList* linkedList)
{
	//1. 연결리스트를 만든다.
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->length = 0;
	linkedList->current = NULL;
	//2. 끝내다.
}

//InsertBefore
Node* InsertBefore(LinkedList* linkedList, Node* index, void* object, size_t size)
{
	//1. 위치와 데이터를 입력받는다.
	//2. 새로운 노드를 만든다.
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->next = index;
	//3. 새로 만든 노드를 위치에 넣는다.
	if (linkedList->head != index)
	{
		linkedList->current->previous = index->previous;
		index->previous->next = linkedList->current;
	}
	else
	{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	index->previous = linkedList->current;
	linkedList->length++;
	//4. 현재위치를 출력한다.
	return linkedList->current;
	//5. 끝내다.
}

//InsertAfter
Node* InsertAfter(LinkedList* linkedList, Node* index, void* object, size_t size)
{
	//1. 위치와 데이터를 입력받는다.
	//2. 새로운 노드를 만든다.
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->previous = index;
	//3. 새로 만든 노드를 위치에 넣는다.
	if (linkedList->tail != index)
	{
		linkedList->current->next = index->next;
		index->next->previous = linkedList->current;
	}
	else
	{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	index->next = linkedList->current;
	linkedList->length++;
	//4. 현재위치를 출력한다.
	return linkedList->current;
	//5. 끝내다.
}

//AppendFromHead
Node* AppendFromHead(LinkedList* linkedList, void* object, size_t size)
{
	//1. 데이터를 입력받는다.
	//2. 새로운 노드를 만든다.
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->previous = linkedList->current;
	//3. 새로 만든 노드를 처음에 둔다.
	if (linkedList->head != NULL)
	{
		linkedList->current->next = linkedList->head;
		linkedList->head->previous = linkedList->current;
	}
	else
	{
		linkedList->current->next = linkedList->current;
		linkedList->tail = linkedList->current;
	}
	linkedList->head = linkedList->current;
	linkedList->length++;
	//4. 현재위치를 출력한다.
	return linkedList->current;
	//5. 끝내다.
}

//AppendFromTail
Node* AppendFromTail(LinkedList* linkedList, void* object, size_t size)
{
	//1. 데이터를 입력받는다.
	//2. 새로운 노드를 만든다.
	linkedList->current = (Node*)malloc(sizeof(Node) + size);
	memcpy(linkedList->current + 1, object, size);
	linkedList->current->next = linkedList->current;
	//3. 새로 만든 노드를 마지막에 둔다.
	if (linkedList->head != NULL)
	{
		linkedList->current->previous = linkedList->tail;
		linkedList->tail->next = linkedList->current;
	}
	else
	{
		linkedList->current->previous = linkedList->current;
		linkedList->head = linkedList->current;
	}
	linkedList->tail = linkedList->current;
	linkedList->length++;
	//4. 현재위치를 출력한다.
	return linkedList->current;
	//5. 끝내다.
}

//Delete
Node* Delete(LinkedList* linkedList, Node *index)
{
	//1. 위치를 입력받는다.
	//2. 입력받은 위치와 head와 tail이 같지 않으면
	if (linkedList->head != index && linkedList->tail != index)
	{
		index->previous->next = index->next;
		index->next->previous = index->previous;
		linkedList->current = index->next;
	}
	//3. 입력받은 위치와 head가 같고 tail과는 같지 않으면
	else if (linkedList->head == index && linkedList->tail != index)
	{
		linkedList->head = index->next;
		index->next->previous = linkedList->head;
		linkedList->current = index->next;
	}
	//4. 입력받은 위치와 head가 다르고 tail과는 같으면
	else if (linkedList->head != index && linkedList->tail == index)
	{
		linkedList->tail = index->previous;
		index->previous->next = linkedList->tail;
		linkedList->current = index->previous;
	}
	//5. 입력받은 위치와 head와 tail이 서로 같으면
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	//6. index를 지운다.
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	linkedList->length--;
	//7. 위치를 출력한다.
	return index;
	//8. 끝내다.
}

//DeleteFromHead
Node* DeleteFromHead(LinkedList* linkedList)
{
	Node* index;
	//1. 노드개수가 1개가 아니면
	index = linkedList->head;
	if (linkedList->head != linkedList->tail)
	{
		linkedList->head = linkedList->head->next;
		linkedList->head->previous = linkedList->head;
		linkedList->current = linkedList->head;
	}
	//2. 노드개수가 1개이면
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	//3.  index를 없앤다.
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	linkedList->length--;
	//4. index를 출력한다.
	return index;
	//5. 끝내다.
}

//DeleteFromTail
Node* DeleteFromTail(LinkedList* linkedList)
{
	Node* index;
	//1. 노드개수가 1개가 아니면
	index = linkedList->tail;
	if (linkedList->head != linkedList->tail)
	{
		linkedList->tail = linkedList->tail->previous;
		linkedList->tail->next = linkedList->tail;
		linkedList->current = linkedList->tail;
	}
	//2. 노드개수가 1개이면
	else
	{
		linkedList->head = NULL;
		linkedList->tail = NULL;
		linkedList->current = NULL;
	}
	//3.  index를 없앤다.
	if (index != NULL)
	{
		free(index);
		index = NULL;
	}
	linkedList->length--;
	//4. index를 출력한다.
	return index;
	//5. 끝내다.
}

//DeleteAllItems
void DeleteAllItems(LinkedList* linkedList)
{
	Node* previous = NULL;
	//1. 연결리스트에서 순서대로 지운다.
	linkedList->current = linkedList->head;
	while (linkedList->current != previous)
	{
		previous = linkedList->current;
		linkedList->head = linkedList->current->next;
		if (linkedList->current != NULL)
		{
			free(linkedList->current);
		}
		linkedList->length--;
		linkedList->current = linkedList->head;
	}
	linkedList->head = NULL;
	linkedList->tail = NULL;
	linkedList->current = NULL;
	//2. 끝내다.
}

//GetAt
void GetAt(LinkedList* linkedList, Node* index, void* object, size_t size)
{
	//1. 위치를 입력받는다.
	//2. object에 데이터를 저장한다.
	memcpy(object, index + 1, size);
	//3. object를 출력한다.
	//4. 끝내다.
}

//First
Node* First(LinkedList* linkedList)
{
	//1. 현재위를 처음으로 이동시킨다.
	linkedList->current = linkedList->head;
	//2. 현재위치를 출력한다.
	return linkedList->current;
	//3. 끝내다.
}

//Previous
Node* Previous(LinkedList* linkedList)
{
	//1. 현재위치를 이전으로 이동시킨다.
	linkedList->current = linkedList->current->previous;
	//2. 현재위치를 출력한다.
	return linkedList->current;
	//3. 끝내다.
}

//Next
Node* Next(LinkedList* linkedList)
{
	//1. 현재위치를 다음으로 이동시킨다.
	linkedList->current = linkedList->current->next;
	//2. 현재위치를 출력한다.
	return linkedList->current;
	//3. 끝내다.
}

//Last
Node* Last(LinkedList* linkedList)
{
	//1. 현재위치를 마지막으로 이동시킨다.
	linkedList->current = linkedList->tail;
	//2. 현재 위치를 출력한다.
	return linkedList->current;
	//3. 끝내다.
}

//Move
Node* Move(LinkedList* linkedList, Node* index)
{
	//1. 위치를 입력받는다.
	//2. 현재 위치를 입력받은 위치로 이동시킨다.
	linkedList->current = index;
	//3. 현재위치를 출력한다.
	return linkedList->current;
	//4. 끝내다.
}

//LinearSearchUnique
Node* LinearSearchUnique(LinkedList* linkedList, void* key, int(*compare)(void*, void*))
{
	Node* index = NULL;
	Node* it;
	Node* previous = NULL;

	//1. 데이터를 입력받는다.
	//2. 마지막노드까지 그리고 찾고자하는 데이터와 같지 않을 동안 반복한다.
	it = linkedList->head;
	while (it != previous && compare(it + 1, key) != 0)
	{
		previous = it;
		it = it->next;
	}
	//3. 마지막노드가 아니면
	if (it != previous)
	{
		//3.1 위치를 저장한다.
		index = it;
	}
	//4. 위치를 출력한다.
	return index;
	//5. 끝내다.
}

//LinearSearchDuplicate
void LinearSearchDuplicate(LinkedList* linkedList, void* key, Node** (*indexes), Long* count,
	int(*compare)(void*, void*))
{
	Node* it;
	Node* previous = NULL;
	Long i = 0;

	*count = 0;
	//1. 데이터를 입력받는다.
	//2. 위치들 배열을 만든다.
	*indexes = (Node * (*))calloc(linkedList->length, sizeof(Node*));
	//3. 노드의 마지막까지 반복한다.
	it = linkedList->head;
	while (it != previous)
	{
		//3.1 찾는 값과 노드데이터 값이 같으면
		if (compare(it + 1, key) == 0)
		{
			//3.1.1 위치를 저장한다.
			(*indexes)[i] = it;
			i++;
			//3.1.2 개수를 센다.
			(*count)++;
		}
		previous = it;
		it = it->next;
	}
	//4. 위치들 배열과 개수를 출력한다.
	//5. 끝내다.
}

//Destory
void Destroy(LinkedList* linkedList)
{
	Node* previous = NULL;

	//1. 연결리스트를 순서대로 지운다.
	linkedList->current = linkedList->head;
	while (linkedList->current != previous)
	{
		previous = linkedList->current;
		linkedList->head = linkedList->current->next;
		if (linkedList->current != NULL)
		{
			free(linkedList->current);
		}
		linkedList->current = linkedList->head;
	}
	//2. 끝내다.
}