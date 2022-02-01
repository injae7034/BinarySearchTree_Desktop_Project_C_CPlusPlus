#include "Array.h"
#include<stddef.h>//size_t
#include<stdlib.h>//malloc, calloc, free
#include<memory.h>//memcpy, memcmp

//Create
void Array_Create(Array* array, Long capacity, size_t size)
{
	//1. capacity를 입력받는다.
	//2. 배열을 만든다.
	array->front = calloc(capacity, size);
	//3. 할당량을 정한다.
	array->capacity = capacity;
	//4. 사용량을 정한다.
	array->length = 0;
	//5. 끝내다.
}

//Store
Long Array_Store(Array* array, Long index, void* object, size_t size)
{
	//1. 위치와 대상을 입력받는다.
	//2. object를 위치에 저장한다.
	memcpy(((char*)array->front) + (index * size), object, size);
	//3. 사용량을 증가시킨다.
	array->length++;
	//4. 위치를 출력한다.
	return index;
	//5. 끝내다.
}

//GetAt
void Array_GetAt(Array* array, Long index, void* object, size_t size)
{
	//1. 위치를 입력받는다.
	//2. object에 배열요소를 저장한다.
	memcpy(object, ((char*)array->front) + (index * size), size);
	//3. object를 출력한다.
	//4. 끝내다.
}

//Insert
Long Array_Insert(Array* array, Long index, void* object, size_t size)
{
	void(*front);
	Long i = 0;
	Long j = 0;

	//1. 위치와 대상을 입력받는다.
	//2.  새 배열을 만든다.
	front = calloc(array->capacity + 1, size);
	//3. 밀어낸다.
	while (i < index)
	{
		memcpy(((char*)front) + (i * size), ((char*)array->front) + (j * size), size);
		j++;
		i++;
	}
	while (i < array->length)
	{
		memcpy(((char*)front) + ((i + 1) * size), ((char*)array->front) + (j * size), size);
		j++;
		i++;
	}
	//4. 기존배열을 지운다.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//5. 삽입한다.
	array->front = front;
	array->capacity++;
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	//6. 위치를 출력한다.
	return index;
	//7. 끝내다.
}

//AppendFromFront
Long Array_AppendFromFront(Array* array, void* object, size_t size)
{
	Long index = 0;
	void(*front);
	Long i = 1;
	Long j = 0;
	//1. object를 입력받는다.
	//2. 새 배열을 만든다.
	front = calloc(array->capacity + 1, size);
	//3. 밀어낸다.
	while (j < array->length)
	{
		memcpy(((char*)front) + (i * size), ((char*)array->front) + (j * size), size);
		i++;
		j++;
	}
	//4. 할당해제한다.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//5. 삽입한다.
	array->front = front;
	array->capacity++;
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	//6. 위치를 출력한다.
	return index;
	//7. 끝내다.
}

//AppendFromRear
Long Array_AppendFromRear(Array* array, void* object, size_t size)
{
	Long index = 0;
	void(*front);
	Long i = 0;

	//1. object를 입력받는다.
	//2. 새 배열을 만든다.
	front = calloc(array->capacity + 1, size);
	//3. 기존 배열을 옮겨적는다.
	while (i < array->length)
	{
		memcpy(((char*)front) + (i * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	//4. 기존 배열을 지운다.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//5. object를 삽입한다.
	array->front = front;
	array->capacity++;
	index = array->capacity - 1;
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	//6. 위치를 출력한다.
	return index;
	//7. 끝내다.
}

//Delete
Long Array_Delete(Array* array, Long index, size_t size)
{
	void(*front) = NULL;
	Long i = 0;
	Long j = 0;

	//1. 위치를 입력받는다.
	//2. 할당량이 1보다 크면
	if (array->capacity > 1)
	{
		//2.1 새 배열을 만든다.
		front = calloc(array->capacity - 1, size);
	}
	//3. 기존 배열의 내용을 옮겨적는다.
	while (i < index)
	{
		memcpy(((char*)front) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	i = index + 1;
	while (i < array->length)
	{
		memcpy(((char*)front) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	//4. 기존 배열을 지운다.
	if (array->front != NULL)
	{
		free(array->front);
		array->front = NULL;
	}
	//5. 할당량이 1보다 크면
	if (array->capacity > 1)
	{
		//5.1 새배열의 주소를 저장한다.
		array->front = front;
	}
	//6. 할당량을 감소시킨다.
	array->capacity--;
	//7. 사용량을 감소시킨다.
	array->length--;
	//8. 위치를 출력한다.
	index = -1;
	return index;
	//8. 끝내다.
}

//DeleteFromFront
Long Array_DeleteFromFront(Array* array, size_t size)
{
	Long index = 0;
	void(*front) = NULL;
	Long i = 1;
	Long j = 0;

	//1. 할당량이 1보다 크면
	if (array->capacity > 1)
	{
		//1.1 새 배열을 만든다.
		front = calloc(array->capacity - 1, size);
	}
	//2. 기존 배열의 내용을 옮겨적는다.
	while (i < array->length)
	{
		memcpy(((char*)front) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	//3. 기존 배열을 지운다.
	if (array->front != NULL)
	{
		free(array->front);
		array->front = NULL;
	}
	//4. 할당량이 1보다 크면
	if (array->capacity > 1)
	{
		//4.1 새배열의 주소를 저장한다.
		array->front = front;
	}
	//5. 할당량을 감소시킨다.
	array->capacity--;
	//6. 사용량을 감소시킨다.
	array->length--;
	//7. 위치를 출력한다.
	index = -1;
	return index;
	//8. 끝내다.
}

//DeleteFromRear
Long Array_DeleteFromRear(Array* array, size_t size)
{
	Long index = -1;
	void(*front) = NULL;
	Long i = 0;

	//1. 할당량이 1보다 크면
	if (array->capacity > 1)
	{
		//1.1 새 배열을 만든다.
		front = calloc(array->capacity - 1, size);
	}
	//2. 기존 배열의 내용을 옮겨적는다.
	while (i < array->capacity - 1)
	{
		memcpy(((char*)front) + (i * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	//3. 기존 배열을 지운다.
	if (array->front != NULL)
	{
		free(array->front);
		array->front = NULL;
	}
	//4. 할당량이 1보다 크면
	if (array->capacity > 1)
	{
		//4.1 새배열의 주소를 저장한다.
		array->front = front;
	}
	//5. 할당량을 감소시킨다.
	array->capacity--;
	//6. 사용량을 감소시킨다.
	array->length--;
	//7. 위치를 출력한다.
	return index;
	//8. 끝내다.
}

//Clear
void Array_Clear(Array* array)
{
	//1. 배열을 할당해제한다.
	if (array->front != NULL)
	{
		free(array->front);
		array->front = NULL;
	}
	//2. 할당량을 0으로 정한다.
	array->capacity = 0;
	//3. 사용량을 0으로 정한다.
	array->length = 0;
	//4. 끝내다.
}

//Modify
Long Array_Modify(Array* array, Long index, void* object, size_t size)
{
	//1. 위치와 대상을 입력받는다.
	//2. 위치에서 수정한다.
	memcpy(((char*)array->front) + (index * size), object, size);
	//3. 위치를 출력한다.
	return index;
	//4. 끝내다.
}

//LinearSearchUnique
Long Array_LinearSearchUnique(Array* array, void* key, size_t size, int (*compare)(void*, void*))
{
	Long index = -1;
	Long i = 0;

	//1. 찾고자 하는 값을 입력받는다.
	//2. 사용량보다 작거나 같은동안 그리고 찾고자 하는 값과 같지 않은 동안 반복한다.
	while (i < array->length && compare(((char*)array->front) + (i * size), key) != 0)
	{
		//2.1 위치를 센다.
		i++;
	}
	//3. 위치를 저장한다.
	if (i < array->length)
	{
		index = i;
	}
	//4. 위치를 출력한다.
	return index;
	//5. 끝내다.
}

//LinearSearchDuplicate
void Array_LinearSearchDuplicate(Array* array, void* key, Long* (*indexes), Long* count,
	size_t size, int (*compare)(void*, void*))
{
	Long i = 0;
	Long j = 0;

	*count = 0;
	//1. 찾고자 하는 값을 입력받는다.
	//2. 사용량보다 작거나 같은동안 반복한다.
	while (i < array->length)
	{
		//2.1 찾고자 하는 값과 서로 같으면
		if (compare(((char*)array->front) + (i * size), key) == 0)
		{
			//2.1.1 개수를 센다.
			(*count)++;
		}
		i++;
	}
	//3, 개수가 0보다 크면
	if (*count > 0)
	{
		//3.1 위치들 배열을 만든다.
		*indexes = (Long(*))calloc(*count, sizeof(Long));
	}
	i = 0;
	//4. 사용량보다 작거나 같은동안 반복한다.
	while (i < array->length)
	{
		//4.1 찾고자 하는 값과 서로 같으면
		if (compare(((char*)array->front) + (i * size), key) == 0)
		{
			//4.1.1 위치를 저장한다.
			(*indexes)[j] = i;
			j++;
		}
		i++;
	}
	//5. 위치들과 개수를 출력한다.
	//6 끝내다.
}

//BinarySearchUnique
Long Array_BinarySearchUnique(Array* array, void* key, size_t size, int (*compare)(void*, void*))
{
	Long index = -1;
	Long first = 0;
	Long middle;
	Long last;

	//1. 찾고자 하는 값을 입력받는다.
	//2.3 중간 값을 구한다.
	last = array->length - 1;
	middle = (first + last) / 2;
	//2. 처음이 마지막보다 작거나 같은동안 그리고 찾고자 하는 값과 같지 않은동안 반복한다.
	while (first <= last && compare(((char*)array->front) + (middle * size), key) != 0)
	{
		//2.1 찾고자 하는 값이 중간보다 크면
		if (compare(((char*)array->front) + (middle * size), key) < 0)
		{
			//2.1.1 첫 번째 값을 증가시킨다.
			first = middle + 1;
		}
		//2.2 그렇지 않으면
		else
		{
			//2.3.1 마지막 값을 감소시킨다.
			last = middle - 1;
		}
		//2.3 중간값을 구한다.
		middle = (first + last) / 2;
	}
	//3. 위치를 저장한다.
	if (first <= last)
	{
		index = middle;
	}
	//4. 위치를 출력한다.
	return index;
	//5. 끝내다.
}

//BinarySearchDuplicate
void Array_BinarySearchDuplicate(Array* array, void* key, Long* (*indexes), Long* count,
	size_t size, int (*compare)(void*, void*))
{
	Long first = 0;
	Long middle;
	Long last;
	Long i;
	Long j = 0;

	*count = 0;
	//1. 찾고자 하는 값을 입력받는다.
	//2. 위치들 배열을 할당한다.
	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	//3.3 중간 값을 구한다.
	last = array->length - 1;
	middle = (first + last) / 2;
	//3. first가 last보다 작거나 같은동안 그리고 찾고자 하는 값과 같지 않을 동안 반복한다.
	while (first <= last && compare(((char*)array->front) + (middle * size), key) != 0)
	{
		//3.1 중간항보다 찾고자 하는 값이 크면
		if (compare(((char*)array->front) + (middle * size), key) < 0)
		{
			//3.1.1 첫번째를 증가시킨다.
			first = middle + 1;
		}
		//3.2 그렇지 않으면
		else
		{
			//3.2.1 마지막을 감소시킨다.
			last = middle - 1;
		}
		//3.3 중간값을 증가시킨다.
		middle = (first + last) / 2;
	}
	//4. 중복된 수들의 위치를 저장한다.
	i = middle - 1;
	while (i >= 0 && compare(((char*)array->front) + (i * size), key) == 0)
	{
		i--;
	}
	i++;
	while (i < array->length && compare(((char*)array->front) + (i * size), key) == 0)
	{
		(*indexes)[j] = i;
		j++;
		(*count)++;
		i++;
	}
	//5. 위치들과 개수를 출력한다.
	//6. 끝내다.
}

//SelectionSort
void Array_SelectionSort(Array* array, size_t size, int (*compare)(void*, void*))
{
	void* temp;
	void* lowest;
	Long i = 0;
	Long j;
	Long minimum;

	temp = malloc(size);
	lowest = malloc(size);

	//1. 오름차순으로 정렬한다.
	while (i < array->length - 1)
	{
		j = i + 1;
		memcpy(lowest, ((char*)array->front) + (i * size), size);
		minimum = i;
		while (j < array->length)
		{
			if (compare(lowest, ((char*)array->front) + (j * size)) > 0)
			{
				memcpy(lowest, ((char*)array->front) + (j * size), size);
				minimum = j;
			}
			j++;
		}
		if (minimum != i)
		{
			memcpy(temp, ((char*)array->front) + (i * size), size);
			memcpy(((char*)array->front) + (i * size), ((char*)array->front) + (minimum * size), size);
			memcpy(((char*)array->front) + (minimum * size), temp, size);
		}
		i++;
	}
	//2. 끝내다.
	if (lowest != NULL)
	{
		free(lowest);
	}
	if (temp != NULL)
	{
		free(temp);
	}
}

//BubbleSort
void Array_BubbleSort(Array* array, size_t size, int (*compare)(void*, void*))
{
	void* temp;
	Long i;
	Long j;
	Boolean flag = TRUE;

	temp = malloc(size);
	i = array->length - 2;
	//1. 오름차순으로 정렬한다.
	while (i >= 0 && flag == TRUE)
	{
		flag = FALSE;
		j = 0;
		while (j <= i)
		{
			if (compare(((char*)array->front) + (j * size), ((char*)array->front) + ((j + 1) * size)) > 0)
			{
				memcpy(temp, ((char*)array->front) + (j * size), size);
				memcpy(((char*)array->front) + (j * size), ((char*)array->front) + ((j + 1) * size), size);
				memcpy(((char*)array->front) + ((j + 1) * size), temp, size);
				flag = TRUE;
			}
			j++;
		}
		i--;
	}
	//2. 끝내다.
	if (temp != NULL)
	{
		free(temp);
	}
}

//InsertionSort
void Array_InsertionSort(Array* array, size_t size, int (*compare)(void*, void*))
{
	void* temp;
	Long i = 1;
	Long j;

	temp = malloc(size);

	//1. 오름차순으로 정렬한다.
	while (i < array->length)
	{
		memcpy(temp, ((char*)array->front) + (i * size), size);
		j = i - 1;
		while (j >= 0 && compare(((char*)array->front) + (j * size), temp) > 0)
		{
			memcpy(((char*)array->front) + ((j + 1) * size), ((char*)array->front) + (j * size), size);
			j--;
		}
		memcpy(((char*)array->front) + ((j + 1) * size), temp, size);
		i++;
	}
	//2. 끝내다.
	if (temp != NULL)
	{
		free(temp);
	}
}

//Merge
void Array_Merge(Array* array, Array* one, Array* other, size_t size, int (*compare)(void*, void*))
{
	Long i = 0;
	Long j = 0;
	Long k = 0;

	//1. one, other 배열을 입력받는다.
	//2. array 배열을 할당해제한다.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//3. array배열을 새로 만든다.
	array->front = calloc(one->length + other->length, size);
	array->capacity = one->length + other->length;
	array->length = 0;
	//4. legnth 보다 작은동안 반복한다.
	while (i < one->length && j < other->length)
	{
		//4.1 one 배열항목이 other 배열항목보다 크면
		if (compare(((char*)one->front) + (i * size), ((char*)other->front) + (j * size)) > 0)
		{
			//4.1.1 other 배열항목을 저장한다.
			memcpy(((char*)array->front) + (k * size), ((char*)other->front) + (j * size), size);
			k++;
			j++;
		}
		//4.2 그렇지 않으면
		else
		{
			//4.2.1 one 배열 항목을 저장한다.
			memcpy(((char*)array->front) + (k * size), ((char*)one->front) + (i * size), size);
			k++;
			i++;
		}
	}
	//5. length보다 작은동안 반복한다.
	while (i < one->length)
	{
		memcpy(((char*)array->front) + (k * size), ((char*)one->front) + (i * size), size);
		k++;
		i++;
	}
	while (j < other->length)
	{
		memcpy(((char*)array->front) + (k * size), ((char*)other->front) + (j * size), size);
		k++;
		j++;
	}
	//6. 사용량을 증가시킨다.
	array->length = one->length + other->length;
	//7. 끝내다.
}

//Destroy
void Array_Destroy(Array* array)
{
	//1. 배열을 할당해제한다.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//2. 끝내다.
}