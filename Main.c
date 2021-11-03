#include "BinaryTree.h"
#include<stdio.h>//printf
#pragma warning(disable:4996)

int Compare(void* one, void* other);
void Node_Printf(BinaryNode* node);

int main(int argc, char* argv[])
{
	BinaryTree binaryTree;
	BinaryNode* index;
	Long key;
	Long value;

	//�����׽�Ʈ�ó�����
	//1. �����˻�Ʈ���� �����.(Create)
	Create(&binaryTree);
	//2. 100�� �ִ´�.(Insert)
	key = 100;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//3. 100�� �����.(Delete)
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//4. 100�� �ִ´�.(Insert)
	key = 100;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//5. 30�� �ִ´�.(Insert)
	key = 30;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//6. 60�� �ִ´�.(Insert)
	key = 60;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//7. 90�� �ִ´�.(Insert)
	key = 90;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//8. 150�� �ִ´�.(Insert)
	key = 150;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//9. 120�� �ִ´�.(Insert)
	key = 120;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//10. 180�� �ִ´�.(Insert)
	key = 180;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//11. 100�� �����.(Delete)
	key = 100;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//12. 180�� �����.(Delete)
	key = 180;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//13. 30�� �����.(Delete)
	key = 30;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//14. 120�� �����.(Delete)
	key = 120;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//15. 150�� �����.(Delete)
	key = 150;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//16. 30�� �ִ´�.(Insert)
	key = 30;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//17. 40�� �ִ´�.(Insert)
	key = 40;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//18. 90�� �����.(Delete)
	key = 90;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//19. 60�� �����.(Delete)
	key = 60;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//20. 40�� �����.(Delete)
	key = 40;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//21. 30�� �����.(Delete)
	key = 30;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("���������ϴ�.\n");
	}
	//22. 60�� �ִ´�.(Insert)
	key = 60;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//23. 30�� �ִ´�.(Insert)
	key = 30;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//24. 100�� �ִ´�.(Insert)
	key = 100;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//25.150�� �ִ´�.(Insert)
	key = 150;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//26. 180�� �ִ´�.(Insert)
	key = 180;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//27. 120�� �ִ´�.(Insert)
	key = 120;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//28. 90�� �ִ´�.(Insert)
	key = 90;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//29. 60�� ã�´�.(Search)
	key = 60;
	index = Search(&binaryTree, &key, Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//30. 150�� ã�´�.(Search)
	key = 150;
	index = Search(&binaryTree, &key, Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	printf("����������\n");
	//31. ������ �����.(MakeBalance)
	MakeBalance(&binaryTree, sizeof(Long));
	Node_Printf(binaryTree.root);
	//32. ������.(Destroy)
	Destroy(&binaryTree);

	return 0;
}

//Compare���Լ�
int Compare(void* one, void* other)
{
	Long* one_ = (Long*)one;
	Long* other_ = (Long*)other;
	int ret;

	if (*one_ > *other_)
	{
		ret = 1;
	}
	else if (*one_ == *other_)
	{
		ret = 0;
	}
	else if (*one_ < *other_)
	{
		ret = -1;
	}
	return ret;
}

//��¿� ����Լ�
void Node_Printf(BinaryNode* node)
{
	if (node != NULL)
	{
		printf("%d\n", *((Long*)(node + 1)));
		Node_Printf(node->left);
		Node_Printf(node->right);
	}
}