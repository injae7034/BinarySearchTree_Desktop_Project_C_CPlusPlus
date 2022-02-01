#include "Array.h"
#include<stddef.h>//size_t
#include<stdlib.h>//malloc, calloc, free
#include<memory.h>//memcpy, memcmp

//Create
void Array_Create(Array* array, Long capacity, size_t size)
{
	//1. capacity�� �Է¹޴´�.
	//2. �迭�� �����.
	array->front = calloc(capacity, size);
	//3. �Ҵ緮�� ���Ѵ�.
	array->capacity = capacity;
	//4. ��뷮�� ���Ѵ�.
	array->length = 0;
	//5. ������.
}

//Store
Long Array_Store(Array* array, Long index, void* object, size_t size)
{
	//1. ��ġ�� ����� �Է¹޴´�.
	//2. object�� ��ġ�� �����Ѵ�.
	memcpy(((char*)array->front) + (index * size), object, size);
	//3. ��뷮�� ������Ų��.
	array->length++;
	//4. ��ġ�� ����Ѵ�.
	return index;
	//5. ������.
}

//GetAt
void Array_GetAt(Array* array, Long index, void* object, size_t size)
{
	//1. ��ġ�� �Է¹޴´�.
	//2. object�� �迭��Ҹ� �����Ѵ�.
	memcpy(object, ((char*)array->front) + (index * size), size);
	//3. object�� ����Ѵ�.
	//4. ������.
}

//Insert
Long Array_Insert(Array* array, Long index, void* object, size_t size)
{
	void(*front);
	Long i = 0;
	Long j = 0;

	//1. ��ġ�� ����� �Է¹޴´�.
	//2.  �� �迭�� �����.
	front = calloc(array->capacity + 1, size);
	//3. �о��.
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
	//4. �����迭�� �����.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//5. �����Ѵ�.
	array->front = front;
	array->capacity++;
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	//6. ��ġ�� ����Ѵ�.
	return index;
	//7. ������.
}

//AppendFromFront
Long Array_AppendFromFront(Array* array, void* object, size_t size)
{
	Long index = 0;
	void(*front);
	Long i = 1;
	Long j = 0;
	//1. object�� �Է¹޴´�.
	//2. �� �迭�� �����.
	front = calloc(array->capacity + 1, size);
	//3. �о��.
	while (j < array->length)
	{
		memcpy(((char*)front) + (i * size), ((char*)array->front) + (j * size), size);
		i++;
		j++;
	}
	//4. �Ҵ������Ѵ�.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//5. �����Ѵ�.
	array->front = front;
	array->capacity++;
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	//6. ��ġ�� ����Ѵ�.
	return index;
	//7. ������.
}

//AppendFromRear
Long Array_AppendFromRear(Array* array, void* object, size_t size)
{
	Long index = 0;
	void(*front);
	Long i = 0;

	//1. object�� �Է¹޴´�.
	//2. �� �迭�� �����.
	front = calloc(array->capacity + 1, size);
	//3. ���� �迭�� �Ű����´�.
	while (i < array->length)
	{
		memcpy(((char*)front) + (i * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	//4. ���� �迭�� �����.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//5. object�� �����Ѵ�.
	array->front = front;
	array->capacity++;
	index = array->capacity - 1;
	memcpy(((char*)array->front) + (index * size), object, size);
	array->length++;
	//6. ��ġ�� ����Ѵ�.
	return index;
	//7. ������.
}

//Delete
Long Array_Delete(Array* array, Long index, size_t size)
{
	void(*front) = NULL;
	Long i = 0;
	Long j = 0;

	//1. ��ġ�� �Է¹޴´�.
	//2. �Ҵ緮�� 1���� ũ��
	if (array->capacity > 1)
	{
		//2.1 �� �迭�� �����.
		front = calloc(array->capacity - 1, size);
	}
	//3. ���� �迭�� ������ �Ű����´�.
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
	//4. ���� �迭�� �����.
	if (array->front != NULL)
	{
		free(array->front);
		array->front = NULL;
	}
	//5. �Ҵ緮�� 1���� ũ��
	if (array->capacity > 1)
	{
		//5.1 ���迭�� �ּҸ� �����Ѵ�.
		array->front = front;
	}
	//6. �Ҵ緮�� ���ҽ�Ų��.
	array->capacity--;
	//7. ��뷮�� ���ҽ�Ų��.
	array->length--;
	//8. ��ġ�� ����Ѵ�.
	index = -1;
	return index;
	//8. ������.
}

//DeleteFromFront
Long Array_DeleteFromFront(Array* array, size_t size)
{
	Long index = 0;
	void(*front) = NULL;
	Long i = 1;
	Long j = 0;

	//1. �Ҵ緮�� 1���� ũ��
	if (array->capacity > 1)
	{
		//1.1 �� �迭�� �����.
		front = calloc(array->capacity - 1, size);
	}
	//2. ���� �迭�� ������ �Ű����´�.
	while (i < array->length)
	{
		memcpy(((char*)front) + (j * size), ((char*)array->front) + (i * size), size);
		j++;
		i++;
	}
	//3. ���� �迭�� �����.
	if (array->front != NULL)
	{
		free(array->front);
		array->front = NULL;
	}
	//4. �Ҵ緮�� 1���� ũ��
	if (array->capacity > 1)
	{
		//4.1 ���迭�� �ּҸ� �����Ѵ�.
		array->front = front;
	}
	//5. �Ҵ緮�� ���ҽ�Ų��.
	array->capacity--;
	//6. ��뷮�� ���ҽ�Ų��.
	array->length--;
	//7. ��ġ�� ����Ѵ�.
	index = -1;
	return index;
	//8. ������.
}

//DeleteFromRear
Long Array_DeleteFromRear(Array* array, size_t size)
{
	Long index = -1;
	void(*front) = NULL;
	Long i = 0;

	//1. �Ҵ緮�� 1���� ũ��
	if (array->capacity > 1)
	{
		//1.1 �� �迭�� �����.
		front = calloc(array->capacity - 1, size);
	}
	//2. ���� �迭�� ������ �Ű����´�.
	while (i < array->capacity - 1)
	{
		memcpy(((char*)front) + (i * size), ((char*)array->front) + (i * size), size);
		i++;
	}
	//3. ���� �迭�� �����.
	if (array->front != NULL)
	{
		free(array->front);
		array->front = NULL;
	}
	//4. �Ҵ緮�� 1���� ũ��
	if (array->capacity > 1)
	{
		//4.1 ���迭�� �ּҸ� �����Ѵ�.
		array->front = front;
	}
	//5. �Ҵ緮�� ���ҽ�Ų��.
	array->capacity--;
	//6. ��뷮�� ���ҽ�Ų��.
	array->length--;
	//7. ��ġ�� ����Ѵ�.
	return index;
	//8. ������.
}

//Clear
void Array_Clear(Array* array)
{
	//1. �迭�� �Ҵ������Ѵ�.
	if (array->front != NULL)
	{
		free(array->front);
		array->front = NULL;
	}
	//2. �Ҵ緮�� 0���� ���Ѵ�.
	array->capacity = 0;
	//3. ��뷮�� 0���� ���Ѵ�.
	array->length = 0;
	//4. ������.
}

//Modify
Long Array_Modify(Array* array, Long index, void* object, size_t size)
{
	//1. ��ġ�� ����� �Է¹޴´�.
	//2. ��ġ���� �����Ѵ�.
	memcpy(((char*)array->front) + (index * size), object, size);
	//3. ��ġ�� ����Ѵ�.
	return index;
	//4. ������.
}

//LinearSearchUnique
Long Array_LinearSearchUnique(Array* array, void* key, size_t size, int (*compare)(void*, void*))
{
	Long index = -1;
	Long i = 0;

	//1. ã���� �ϴ� ���� �Է¹޴´�.
	//2. ��뷮���� �۰ų� �������� �׸��� ã���� �ϴ� ���� ���� ���� ���� �ݺ��Ѵ�.
	while (i < array->length && compare(((char*)array->front) + (i * size), key) != 0)
	{
		//2.1 ��ġ�� ����.
		i++;
	}
	//3. ��ġ�� �����Ѵ�.
	if (i < array->length)
	{
		index = i;
	}
	//4. ��ġ�� ����Ѵ�.
	return index;
	//5. ������.
}

//LinearSearchDuplicate
void Array_LinearSearchDuplicate(Array* array, void* key, Long* (*indexes), Long* count,
	size_t size, int (*compare)(void*, void*))
{
	Long i = 0;
	Long j = 0;

	*count = 0;
	//1. ã���� �ϴ� ���� �Է¹޴´�.
	//2. ��뷮���� �۰ų� �������� �ݺ��Ѵ�.
	while (i < array->length)
	{
		//2.1 ã���� �ϴ� ���� ���� ������
		if (compare(((char*)array->front) + (i * size), key) == 0)
		{
			//2.1.1 ������ ����.
			(*count)++;
		}
		i++;
	}
	//3, ������ 0���� ũ��
	if (*count > 0)
	{
		//3.1 ��ġ�� �迭�� �����.
		*indexes = (Long(*))calloc(*count, sizeof(Long));
	}
	i = 0;
	//4. ��뷮���� �۰ų� �������� �ݺ��Ѵ�.
	while (i < array->length)
	{
		//4.1 ã���� �ϴ� ���� ���� ������
		if (compare(((char*)array->front) + (i * size), key) == 0)
		{
			//4.1.1 ��ġ�� �����Ѵ�.
			(*indexes)[j] = i;
			j++;
		}
		i++;
	}
	//5. ��ġ��� ������ ����Ѵ�.
	//6 ������.
}

//BinarySearchUnique
Long Array_BinarySearchUnique(Array* array, void* key, size_t size, int (*compare)(void*, void*))
{
	Long index = -1;
	Long first = 0;
	Long middle;
	Long last;

	//1. ã���� �ϴ� ���� �Է¹޴´�.
	//2.3 �߰� ���� ���Ѵ�.
	last = array->length - 1;
	middle = (first + last) / 2;
	//2. ó���� ���������� �۰ų� �������� �׸��� ã���� �ϴ� ���� ���� �������� �ݺ��Ѵ�.
	while (first <= last && compare(((char*)array->front) + (middle * size), key) != 0)
	{
		//2.1 ã���� �ϴ� ���� �߰����� ũ��
		if (compare(((char*)array->front) + (middle * size), key) < 0)
		{
			//2.1.1 ù ��° ���� ������Ų��.
			first = middle + 1;
		}
		//2.2 �׷��� ������
		else
		{
			//2.3.1 ������ ���� ���ҽ�Ų��.
			last = middle - 1;
		}
		//2.3 �߰����� ���Ѵ�.
		middle = (first + last) / 2;
	}
	//3. ��ġ�� �����Ѵ�.
	if (first <= last)
	{
		index = middle;
	}
	//4. ��ġ�� ����Ѵ�.
	return index;
	//5. ������.
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
	//1. ã���� �ϴ� ���� �Է¹޴´�.
	//2. ��ġ�� �迭�� �Ҵ��Ѵ�.
	*indexes = (Long(*))calloc(array->length, sizeof(Long));
	//3.3 �߰� ���� ���Ѵ�.
	last = array->length - 1;
	middle = (first + last) / 2;
	//3. first�� last���� �۰ų� �������� �׸��� ã���� �ϴ� ���� ���� ���� ���� �ݺ��Ѵ�.
	while (first <= last && compare(((char*)array->front) + (middle * size), key) != 0)
	{
		//3.1 �߰��׺��� ã���� �ϴ� ���� ũ��
		if (compare(((char*)array->front) + (middle * size), key) < 0)
		{
			//3.1.1 ù��°�� ������Ų��.
			first = middle + 1;
		}
		//3.2 �׷��� ������
		else
		{
			//3.2.1 �������� ���ҽ�Ų��.
			last = middle - 1;
		}
		//3.3 �߰����� ������Ų��.
		middle = (first + last) / 2;
	}
	//4. �ߺ��� ������ ��ġ�� �����Ѵ�.
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
	//5. ��ġ��� ������ ����Ѵ�.
	//6. ������.
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

	//1. ������������ �����Ѵ�.
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
	//2. ������.
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
	//1. ������������ �����Ѵ�.
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
	//2. ������.
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

	//1. ������������ �����Ѵ�.
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
	//2. ������.
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

	//1. one, other �迭�� �Է¹޴´�.
	//2. array �迭�� �Ҵ������Ѵ�.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//3. array�迭�� ���� �����.
	array->front = calloc(one->length + other->length, size);
	array->capacity = one->length + other->length;
	array->length = 0;
	//4. legnth ���� �������� �ݺ��Ѵ�.
	while (i < one->length && j < other->length)
	{
		//4.1 one �迭�׸��� other �迭�׸񺸴� ũ��
		if (compare(((char*)one->front) + (i * size), ((char*)other->front) + (j * size)) > 0)
		{
			//4.1.1 other �迭�׸��� �����Ѵ�.
			memcpy(((char*)array->front) + (k * size), ((char*)other->front) + (j * size), size);
			k++;
			j++;
		}
		//4.2 �׷��� ������
		else
		{
			//4.2.1 one �迭 �׸��� �����Ѵ�.
			memcpy(((char*)array->front) + (k * size), ((char*)one->front) + (i * size), size);
			k++;
			i++;
		}
	}
	//5. length���� �������� �ݺ��Ѵ�.
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
	//6. ��뷮�� ������Ų��.
	array->length = one->length + other->length;
	//7. ������.
}

//Destroy
void Array_Destroy(Array* array)
{
	//1. �迭�� �Ҵ������Ѵ�.
	if (array->front != NULL)
	{
		free(array->front);
	}
	//2. ������.
}