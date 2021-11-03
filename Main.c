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

	//메인테스트시나리오
	//1. 이진검색트리를 만든다.(Create)
	Create(&binaryTree);
	//2. 100을 넣는다.(Insert)
	key = 100;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//3. 100을 지운다.(Delete)
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//4. 100을 넣는다.(Insert)
	key = 100;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//5. 30을 넣는다.(Insert)
	key = 30;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//6. 60을 넣는다.(Insert)
	key = 60;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//7. 90을 넣는다.(Insert)
	key = 90;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//8. 150을 넣는다.(Insert)
	key = 150;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//9. 120을 넣는다.(Insert)
	key = 120;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//10. 180을 넣는다.(Insert)
	key = 180;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//11. 100을 지운다.(Delete)
	key = 100;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//12. 180을 지운다.(Delete)
	key = 180;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//13. 30을 지운다.(Delete)
	key = 30;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//14. 120을 지운다.(Delete)
	key = 120;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//15. 150을 지운다.(Delete)
	key = 150;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//16. 30을 넣는다.(Insert)
	key = 30;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//17. 40을 넣는다.(Insert)
	key = 40;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//18. 90을 지운다.(Delete)
	key = 90;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//19. 60을 지운다.(Delete)
	key = 60;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//20. 40을 지운다.(Delete)
	key = 40;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//21. 30을 지운다.(Delete)
	key = 30;
	index = Delete(&binaryTree, &key, sizeof(Long), Compare);
	if (index == NULL)
	{
		printf("지워졌습니다.\n");
	}
	//22. 60을 넣는다.(Insert)
	key = 60;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//23. 30을 넣는다.(Insert)
	key = 30;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//24. 100을 넣는다.(Insert)
	key = 100;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//25.150을 넣는다.(Insert)
	key = 150;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//26. 180을 넣는다.(Insert)
	key = 180;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//27. 120을 넣는다.(Insert)
	key = 120;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//28. 90을 넣는다.(Insert)
	key = 90;
	index = Insert(&binaryTree, &key, sizeof(Long), Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//29. 60을 찾는다.(Search)
	key = 60;
	index = Search(&binaryTree, &key, Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	//30. 150을 찾는다.(Search)
	key = 150;
	index = Search(&binaryTree, &key, Compare);
	GetAt(&binaryTree, index, &value, sizeof(Long));
	printf("%d\n", value);
	printf("균형맞춘후\n");
	//31. 균형을 맞춘다.(MakeBalance)
	MakeBalance(&binaryTree, sizeof(Long));
	Node_Printf(binaryTree.root);
	//32. 끝내다.(Destroy)
	Destroy(&binaryTree);

	return 0;
}

//Compare비교함수
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

//출력용 재귀함수
void Node_Printf(BinaryNode* node)
{
	if (node != NULL)
	{
		printf("%d\n", *((Long*)(node + 1)));
		Node_Printf(node->left);
		Node_Printf(node->right);
	}
}