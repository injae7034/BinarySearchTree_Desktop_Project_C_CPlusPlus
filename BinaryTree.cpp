#include "BinaryTree.h"
#include<iostream>
using namespace std;

//�Լ������ͼ���
int Compare(void* one, void* other);
//�̺а˻�Ʈ�� ��¿� ����Լ�
void Printf(BinaryTree<int>::Node* node);

//�����׽�Ʈ�ó�����
int main(int argc, char* argv[])
{
	//1. BinaryTree�� �����.
	BinaryTree<int> binaryTree;
	//2. 100�� �ִ´�.
	BinaryTree<int>::Node* index = binaryTree.Insert(100, Compare);
	cout << index->GetKey() << endl;
	//3. 100�� �����.
	index = binaryTree.Delete(100, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//4. 100�� �ִ´�.
	index = binaryTree.Insert(100, Compare);
	cout << index->GetKey() << endl;
	//5. 30�� �ִ´�.
	index = binaryTree.Insert(30, Compare);
	cout << index->GetKey() << endl;
	//6. 60�� �ִ´�.
	index = binaryTree.Insert(60, Compare);
	cout << index->GetKey() << endl;
	//7. 90�� �ִ´�.
	index = binaryTree.Insert(90, Compare);
	cout << index->GetKey() << endl;
	//8. 150�� �ִ´�.
	index = binaryTree.Insert(150, Compare);
	cout << index->GetKey() << endl;
	//9. 120�� �ִ´�.
	index = binaryTree.Insert(120, Compare);
	cout << index->GetKey() << endl;
	//10. 180�� �ִ´�.
	index = binaryTree.Insert(180, Compare);
	cout << index->GetKey() << endl;
	//11. 100�� �����.
	index = binaryTree.Delete(100, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//12. 180�� �����.
	index = binaryTree.Delete(180, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//13. 30�� �����.
	index = binaryTree.Delete(30, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//14. 120�� �����.
	index = binaryTree.Delete(120, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//15. 150�� �����.
	index = binaryTree.Delete(150, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//16. 30�� �ִ´�.
	index = binaryTree.Insert(30, Compare);
	cout << index->GetKey() << endl;
	//17. 40�� �ִ´�.
	index = binaryTree.Insert(40, Compare);
	cout << index->GetKey() << endl;
	//18. 90�� �����.
	index = binaryTree.Delete(90, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//19. 60�� �����.
	index = binaryTree.Delete(60, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//20. 40�� �����.
	index = binaryTree.Delete(40, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//21. 30�� �����.
	index = binaryTree.Delete(30, Compare);
	if (index == 0)
	{
		cout << "���������ϴ�." << endl;
	}
	//22. 60�� �ִ´�.
	index = binaryTree.Insert(60, Compare);
	cout << index->GetKey() << endl;
	//23. 30�� �ִ´�.
	index = binaryTree.Insert(30, Compare);
	cout << index->GetKey() << endl;
	//24. 100�� �ִ´�.
	index = binaryTree.Insert(100, Compare);
	cout << index->GetKey() << endl;
	//25. 150�� �ִ´�.
	index = binaryTree.Insert(150, Compare);
	cout << index->GetKey() << endl;
	//26. 180�� �ִ´�.
	index = binaryTree.Insert(180, Compare);
	cout << index->GetKey() << endl;
	//27. 120�� �ִ´�.
	index = binaryTree.Insert(120, Compare);
	cout << index->GetKey() << endl;
	//28. 90�� �ִ´�.
	index = binaryTree.Insert(90, Compare);
	cout << index->GetKey() << endl;
	//29. 60�� ã�´�.
	index = binaryTree.Search(60, Compare);
	cout << index->GetKey() << endl;
	//30. 150�� ã�´�.
	index = binaryTree.Search(150, Compare);
	cout << index->GetKey() << endl;
	//31. ���������
	cout << "���������" << endl;
	BinaryTree<int> other(binaryTree);
	Printf(other.GetRoot());
	//32. ġȯ������
	cout << "ġȯ������ ���� ��" << endl;
	BinaryTree<int> theOther;
	//32.1 100�� �ִ´�.
	index = theOther.Insert(100, Compare);
	//32.2 30�� �ִ´�.
	index = theOther.Insert(30, Compare);
	//32.3 60�� �ִ´�.
	index = theOther.Insert(60, Compare);
	//32.4 90�� �ִ´�.
	index = theOther.Insert(90, Compare);
	//32.5 150�� �ִ´�.
	index = theOther.Insert(150, Compare);
	//32.6 120�� �ִ´�.
	index = theOther.Insert(120, Compare);
	//32.7 180�� �ִ´�.
	index = theOther.Insert(180, Compare);
	Printf(theOther.GetRoot());
	cout << "ġȯ������ ���� ��" << endl;
	theOther = other;
	Printf(theOther.GetRoot());
	//33. ������ �����.
	cout << "������ ���� ��" << endl;
	theOther.MakeBalance();
	Printf(theOther.GetRoot());
	//34. ������.
	return 0;
}

//�Լ������� ����
int Compare(void* one, void* other)
{
	Long* one_ = (Long*)one;
	Long* other_ = (Long*)other;
	int ret;
	if (*one_ > * other_)
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

//Printf
void Printf(BinaryTree<int>::Node* node)
{
	cout << node->GetKey() << endl;
	if (node->GetLeft() != 0)
	{
		Printf(node->GetLeft());
	}
	if (node->GetRight() != 0)
	{
		Printf(node->GetRight());
	}
}