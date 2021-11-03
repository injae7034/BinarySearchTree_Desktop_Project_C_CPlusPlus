#include "BinaryTree.h"
#include<iostream>
using namespace std;

//함수포인터선언
int Compare(void* one, void* other);
//이분검색트리 출력용 재귀함수
void Printf(BinaryTree<int>::Node* node);

//메인테스트시나리오
int main(int argc, char* argv[])
{
	//1. BinaryTree를 만든다.
	BinaryTree<int> binaryTree;
	//2. 100을 넣는다.
	BinaryTree<int>::Node* index = binaryTree.Insert(100, Compare);
	cout << index->GetKey() << endl;
	//3. 100을 지운다.
	index = binaryTree.Delete(100, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//4. 100을 넣는다.
	index = binaryTree.Insert(100, Compare);
	cout << index->GetKey() << endl;
	//5. 30을 넣는다.
	index = binaryTree.Insert(30, Compare);
	cout << index->GetKey() << endl;
	//6. 60을 넣는다.
	index = binaryTree.Insert(60, Compare);
	cout << index->GetKey() << endl;
	//7. 90을 넣는다.
	index = binaryTree.Insert(90, Compare);
	cout << index->GetKey() << endl;
	//8. 150을 넣는다.
	index = binaryTree.Insert(150, Compare);
	cout << index->GetKey() << endl;
	//9. 120을 넣는다.
	index = binaryTree.Insert(120, Compare);
	cout << index->GetKey() << endl;
	//10. 180을 넣는다.
	index = binaryTree.Insert(180, Compare);
	cout << index->GetKey() << endl;
	//11. 100을 지운다.
	index = binaryTree.Delete(100, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//12. 180을 지운다.
	index = binaryTree.Delete(180, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//13. 30을 지운다.
	index = binaryTree.Delete(30, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//14. 120을 지운다.
	index = binaryTree.Delete(120, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//15. 150을 지운다.
	index = binaryTree.Delete(150, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//16. 30을 넣는다.
	index = binaryTree.Insert(30, Compare);
	cout << index->GetKey() << endl;
	//17. 40을 넣는다.
	index = binaryTree.Insert(40, Compare);
	cout << index->GetKey() << endl;
	//18. 90을 지운다.
	index = binaryTree.Delete(90, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//19. 60을 지운다.
	index = binaryTree.Delete(60, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//20. 40을 지운다.
	index = binaryTree.Delete(40, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//21. 30을 지운다.
	index = binaryTree.Delete(30, Compare);
	if (index == 0)
	{
		cout << "지워졌습니다." << endl;
	}
	//22. 60을 넣는다.
	index = binaryTree.Insert(60, Compare);
	cout << index->GetKey() << endl;
	//23. 30을 넣는다.
	index = binaryTree.Insert(30, Compare);
	cout << index->GetKey() << endl;
	//24. 100을 넣는다.
	index = binaryTree.Insert(100, Compare);
	cout << index->GetKey() << endl;
	//25. 150을 넣는다.
	index = binaryTree.Insert(150, Compare);
	cout << index->GetKey() << endl;
	//26. 180을 넣는다.
	index = binaryTree.Insert(180, Compare);
	cout << index->GetKey() << endl;
	//27. 120을 넣는다.
	index = binaryTree.Insert(120, Compare);
	cout << index->GetKey() << endl;
	//28. 90을 넣는다.
	index = binaryTree.Insert(90, Compare);
	cout << index->GetKey() << endl;
	//29. 60을 찾는다.
	index = binaryTree.Search(60, Compare);
	cout << index->GetKey() << endl;
	//30. 150을 찾는다.
	index = binaryTree.Search(150, Compare);
	cout << index->GetKey() << endl;
	//31. 복사생성자
	cout << "복사생성자" << endl;
	BinaryTree<int> other(binaryTree);
	Printf(other.GetRoot());
	//32. 치환연산자
	cout << "치환연산자 실행 전" << endl;
	BinaryTree<int> theOther;
	//32.1 100을 넣는다.
	index = theOther.Insert(100, Compare);
	//32.2 30을 넣는다.
	index = theOther.Insert(30, Compare);
	//32.3 60을 넣는다.
	index = theOther.Insert(60, Compare);
	//32.4 90을 넣는다.
	index = theOther.Insert(90, Compare);
	//32.5 150을 넣는다.
	index = theOther.Insert(150, Compare);
	//32.6 120을 넣는다.
	index = theOther.Insert(120, Compare);
	//32.7 180을 넣는다.
	index = theOther.Insert(180, Compare);
	Printf(theOther.GetRoot());
	cout << "치환연산자 실행 후" << endl;
	theOther = other;
	Printf(theOther.GetRoot());
	//33. 균형을 맞춘다.
	cout << "균형을 맞춘 후" << endl;
	theOther.MakeBalance();
	Printf(theOther.GetRoot());
	//34. 끝내다.
	return 0;
}

//함수포인터 정의
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