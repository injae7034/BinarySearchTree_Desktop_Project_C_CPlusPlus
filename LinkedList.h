#ifndef _LINKEDLIST_H
#define _LINKEDLSIT_H

typedef signed long int Long;
template <typename T>
class LinkedList
{
public:
	//Nested Class
	class Node
	{
		friend class LinkedList;//LinkedList에서 Node의 private멤버에 접근하기 위해 선언해줌.
	public:
		//매개변수 0개 생성자
		Node()
		{
			this->previous = this;
			this->next = this;
		}
		//매개변수 1개 생성자
		Node(T object)
		{
			this->previous = this;
			this->object = object;
			this->next = this;
		}
		//매개변수 2개 생성자
		Node(Node* previous, T object)
		{
			this->previous = previous;
			this->object = object;
			this->next = this;
		}
		Node(T object, Node* next)
		{
			this->previous = this;
			this->object = object;
			this->next = next;
		}
		//매개변수 3개 생성자
		Node(Node* previous, T object, Node* next)
		{
			this->previous = previous;
			this->object = object;
			this->next = next;
		}
		//복사생성자
		Node(const Node& source)
		{
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;
		}
		//치환연산자
		Node& operator=(const Node& source)
		{
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;

			return *this;
		}
		//GetAt
		T& GetObject() const
		{
			return const_cast<T&>(this->object);
		}
		//소멸자
		~Node()
		{

		}
	private:
		Node* previous;
		T object;
		Node* next;
	};
public:
	//기본생성자
	LinkedList();
	//복사생성자
	LinkedList(const LinkedList& source);
	//치환연산자
	LinkedList<T>& operator=(const LinkedList& source);
	//첨자연산자
	T& operator[](Long index);
	Node* InsertBefore(Node* index, T object);
	Node* InsertAfter(Node* index, T object);
	Node* AppendFromHead(T object);
	Node* AppendFromTail(T object);
	Node* Delete(Node* index);
	Node* DeleteFromHead();
	Node* DeleteFromTail();
	void DeleteAllItems();
	Node* LinearSearchUnique(void* key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void* key, Node** (*indexes), Long* count, int(*compare)(void*, void*));
	Node* First();
	Node* Previous();
	Node* Next();
	Node* Last();
	Node* Move(Node* index);
	//소멸자
	~LinkedList();
	//인라인함수
	Long GetLength() const;
	Node* GetCurrent() const;

private:
	Node* head;
	Node* tail;
	Long length;
	Node* current;
};

//인라인함수
template <typename T>
inline Long LinkedList<T>::GetLength() const
{
	return this->length;
}

template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetCurrent() const
{
	return const_cast<Node*>(this->current);
}


//기본생성자
template <typename T>
LinkedList<T>::LinkedList()
{
	//1. 연결리스트를 만든다.
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
	//2. 끝내다.
}

//복사생성자
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& source)
{
	//this->head, this->tail을 대입함.
	Node* previous = 0;
	Node* it = source.head;
	while (it != previous)
	{
		if (previous != 0)
		{
			this->current = new Node(this->tail, it->object);
			this->tail->next = this->current;
			this->tail = this->current;
		}
		else //처음 this의 Node를 생성하는 경우
		{
			this->current = new Node(it->object);
			this->head = this->current;
			this->tail = this->current;
		}
		previous = it;
		it = it->next;
	}
	//this->length대입
	this->length = source.length;
	//this->currnet복사
	this->current = this->head;
	it = source.head;
	while (it != source.current)
	{
		this->current = this->current->next;
		it = it->next;
	}
}

//치환연산자
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& source)
{
	//치환하기 전에(대입하기 전에) this에 있는 기존 데이터를 모드 할당해제한다.
	//DeleteAllItems와 logic이 동일함. 다만 같은 class의 연산을 연산내에서 사용할 수 없기때문에
	//DeleteAllItems를 호출하지 않고 그냥 적어줌.
	if (this->head != 0)
	{
		Node* previous = 0;
		this->current = this->head;
		while (this->current != previous)
		{
			previous = this->current;
			this->head = this->current->next;
			if (this->current != 0)
			{
				delete this->current;
			}
			this->length--;
			this->current = this->head;
		}
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	//this->head, this->tail을 대입함.
	Node* previous = 0;
	Node* it = source.head;
	while (it != previous)
	{
		if (previous != 0)
		{
			this->current = new Node(this->tail, it->object);
			this->tail->next = this->current;
			this->tail = this->current;
		}
		else //처음 this의 Node를 생성하는 경우
		{
			this->current = new Node(it->object);
			this->head = this->current;
			this->tail = this->current;
		}
		previous = it;
		it = it->next;
	}
	//this->length대입
	this->length = source.length;
	//this->currnet복사
	this->current = this->head;
	it = source.head;
	while (it != source.current)
	{
		this->current = this->current->next;
		it = it->next;
	}
	return *this;
}

//첨자연산자
template <typename T>
T& LinkedList<T>::operator[](Long index)
{
	Node* it = this->head;
	Long i = 0;
	while (i < index)
	{
		it = it->next;
		i++;
	}

	return it->GetObject();
}

//InsertBefore
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertBefore(Node* index, T object)
{
	if (this->head != index)
	{
		this->current = new Node(index->previous, object, index);
	}
	else
	{
		this->current = new Node(object, index);
	}
	if (this->head != index)
	{
		index->previous->next = this->current;
	}
	else
	{
		this->head = this->current;
	}
	index->previous = this->current;
	this->length++;

	return this->current;
}

//InsertAfter
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertAfter(Node* index, T object)
{
	if (this->tail != index)
	{
		this->current = new Node(index, object, index->next);
	}
	else
	{
		this->current = new Node(index, object);
	}
	if (this->tail != index)
	{
		index->next->previous = this->current;
	}
	else
	{
		this->tail = this->current;
	}
	index->next = this->current;
	this->length++;

	return this->current;
}

//AppendFromHead
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromHead(T object)
{
	if (this->head != 0)
	{
		this->current = new Node(object, this->head);
	}
	else
	{
		this->current = new Node(object);
	}
	if (this->head != 0)
	{
		this->head->previous = this->current;
	}
	else
	{
		this->tail = this->current;
	}
	this->head = this->current;
	this->length++;

	return this->current;
}

//AppendFromTail
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromTail(T object)
{
	if (this->head!= 0)
	{
		this->current = new Node(this->tail, object);
	}
	else
	{
		this->current = new Node(object);
	}
	if (this->head != 0)
	{
		this->tail->next = this->current;
	}
	else
	{
		this->head = this->current;
	}
	this->tail = this->current;
	this->length++;

	return this->current;
}

//Delete
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Delete(Node* index)
{
	if (this->head != index && this->tail != index)
	{
		index->previous->next = index->next;
		index->next->previous = index->previous;
		this->current = index->next;
	}
	else if (this->head == index && this->tail != index)
	{
		this->head = index->next;
		index->next->previous = this->head;
		this->current = index->next;
	}
	else if (this->head != index && this->tail == index)
	{
		this->tail = index->previous;
		index->previous->next = this->tail;
		this->current = index->previous;
	}
	else
	{
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	if (index != 0)
	{
		delete index;
		index = 0;//NULL로 초기화 댕글링 포인터 없앰.
	}
	this->length--;

	return index;
}

//DeleteFromHead
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromHead()
{
	Node* index = this->head;
	if (this->head != this->tail)
	{
		this->head = this->head->next;
		this->head->previous = this->head;
		this->current = this->head;
	}
	else
	{
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	if (index != 0)
	{
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

//DeleteFromTail
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromTail()
{
	Node* index = this->tail;
	if (this->head != this->tail)
	{
		this->tail = this->tail->previous;
		this->tail->next = this->tail;
		this->current = this->tail;
	}
	else
	{
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}

	if (index != 0)
	{
		delete index;
		index = 0;
	}
	this->length--;

	return index;
}

//DeleteAllItems
template <typename T>
void LinkedList<T>::DeleteAllItems()
{
	Node* previous = 0;
	this->current = this->head;
	while (this->current != previous)
	{
		previous = this->current;
		this->head = this->current->next;
		if (this->current != 0)
		{
			delete this->current;
		}
		this->length--;
		this->current = this->head;
	}
		this->head = 0;
		this->tail = 0;
		this->current = 0;
}

//LinearSearchUnique
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::LinearSearchUnique(void* key, int(*compare)(void*, void*))
{
	Node* index = 0;
	Node* it;
	Node* previous = 0;

	it = this->head;
	while (it != previous && compare(&it->object, key) != 0)
	{
		previous = it;
		it = it->next;
	}
	if (it != previous)
	{
		index = it;
	}

	return index;
}

//LinearSerchDuplicate
template <typename T>
void LinkedList<T>::LinearSearchDuplicate(void* key, Node** (*indexes), Long* count, int(*compare)(void*, void*))
{
	Node* it;
	Node* previous = 0;
	Long i = 0;
	//초기화
	*indexes = 0;
	*count = 0;
	//각 배열요소가 Node*인 포인터 배열을 힙에 할당함. 
	*indexes = new Node * [this->length];

	it = this->head;
	while (it != previous)
	{
		if (compare(&it->object, key) == 0)
		{
			(*indexes)[i] = it;
			i++;
			(*count)++;
		}
		previous = it;
		it = it->next;
	}
}

//First
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::First()
{
	this->current = this->head;

	return this->current;
}

//Previous
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Previous()
{
	this->current = this->current->previous;

	return this->current;
}

//Next
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Next()
{
	this->current = this->current->next;

	return this->current;
}

//Last
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Last()
{
	this->current = this->tail;

	return this->current;
}

//Move
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Move(Node* index)
{
	this->current = index;

	return this->current;
}


//소멸자
template <typename T>
LinkedList<T>::~LinkedList()
{
	//1. 연결리스트를 없앤다.
	Node* previous = 0;
	this->current = this->head;
	while (this->current != previous)
	{
		previous = this->current;
		this->head = this->current->next;
		if (this->current != 0)
		{
			delete this->current;
		}
		this->current = this->head;
	}
}


#endif // !_LINKEDLIST_H