#pragma once

#include <iostream>
using namespace std;
#include <stack>
#include <string.h>
#include <queue>

template <class T>
struct BinNode
{
	BinNode(const T& data = T())
	:data(data)
	, left(NULL)
	, right(NULL)
	{}

	T data;
	BinNode<T>* left;
	BinNode<T>* right;

};

template <class T>
class BinTree
{
	typedef BinNode<T> Node;
	typedef BinNode<T>* pNode;

public:
	//构造函数
	BinTree()
		:_pRoot(NULL)
	{}

	//创建一棵二叉树，前序创建
	BinTree(const T* arr, size_t size, const T& invalid)
	{
		size_t index = 0;
		_pRoot = _Create(arr, size, index, invalid);
	}

	//拷贝构造函数
	BinTree(const BinTree& sm)
	{
		if (this != &sm)
		{
			_pRoot = _Copy(sm._pRoot);
		}
	}

	//赋值运算符重载
	BinTree& operator=(const BinTree& sm)
	{
		if (this != &sm)
		{
			_DestoryTree(_pRoot);//销毁当前树
			_pRoot = _Copy(sm._pRoot);
		}
		return *this;
	}

	//析构函数
	~BinTree()
	{
		_DestoryTree(_pRoot);
		_pRoot = NULL;
	}

	//前序遍历二叉树
	void PreOrder()
	{
		_PreOrder(_pRoot);
		cout << endl;
	}

	void PreOrderTraversal()
	{
		_PreOrderTraversal(_pRoot);
		cout << endl;
	}

	//中序遍历二叉树
	void InOrder()
	{
		_InOrder(_pRoot);
		cout << endl;
	}
	void InOrderTraversal()
	{
		_InOrderTraversal(_pRoot);
		cout << endl;
	}

	//后序遍历二叉树
	void PostOrder()
	{
		_PostOrder(_pRoot);
		cout << endl;
	}
	void PostOrderTraversal()
	{
		_PostOrderTraversal(_pRoot);
		cout << endl;
	}

	//层序遍历
	void LevelOrder()
	{
		_LevelOrder(_pRoot);
		cout << endl;
	}

	//结点个数
	size_t Node_Count()
	{
		return _Node_Count(_pRoot);
	}

	//叶结点的个数
	size_t LeafNode_Count()
	{
		return _LeafNode_Count(_pRoot);
	}

	//第K层结点的个数
	size_t KNode_Count(size_t K)
	{
		return _KNode_Count(_pRoot, K);
	}

	//二叉树的高度
	size_t Hight()
	{
		return _Hight(_pRoot);
	}

	//值为data的元素的位置
	pNode Find(const T& data)
	{
		return _Find(_pRoot, data);
	}

	//双亲结点
	pNode ParentNode(pNode curNode)
	{
		return _ParentNode(_pRoot, curNode);
	}

	//左孩子结点
	pNode Left_Child(pNode curNode)
	{
		return _Left_Child(_pRoot, curNode);
	}

	//右孩子结点
	pNode Right_Child(pNode curNode)
	{
		return _Right_Child(_pRoot, curNode);
	}

	//二叉树的镜像
	void MirrorBinTree()
	{
		_MirrorBinTree(_pRoot);
	}

	bool IsCompleteBinTree()
	{
		return _IsCompleteBinTree(_pRoot);
	}

private:
	pNode _Create(const T* arr, size_t size, size_t& index, const T& invalid)
	{
		if (NULL == arr)
			return NULL;
		pNode pRoot = NULL;

		if (index < size && arr[index] != invalid)
		{
			//创建根结点
			pRoot = new Node(arr[index]);

			//创建左子树
			pRoot->left = _Create(arr, size, ++index, invalid);

			//创建右子树
			pRoot->right = _Create(arr, size, ++index, invalid);
		}
		return pRoot;
	}

	//拷贝二叉树
	pNode _Copy(pNode pRoot)
	{
		if (pRoot)
		{
			//拷贝根结点
			pNode newpRoot = new Node(pRoot->data);

			//拷贝左子树
			if (pRoot->left)
				newpRoot->left = _Copy(pRoot->left);

			//拷贝右子树
			if (pRoot->right)
				newpRoot->right = _Copy(pRoot->right);
		}
		return pRoot;
	}

	//销毁二叉树,后序销毁
	void _DestoryTree(pNode pRoot)
	{
		if (pRoot)
			return;
		if (pRoot->left == NULL&&pRoot->right == NULL)
		{
			delete pRoot;
			return;
		}
		//销毁左子树
		if (pRoot->left)
		{
			_DestoryTree(pRoot->left);
			pRoot->left = NULL;
		}
		//销毁右子树
		if (pRoot->right)
		{
			_DestoryTree(pRoot->right);
			pRoot->right = NULL;
		}
		//销毁根结点
		delete pRoot;
	}

	//前序遍历二叉树--->递归实现
	void _PreOrder(pNode pRoot)
	{
		if (!pRoot)
			return;
		//访问根结点
		cout << pRoot->data << " ";
		//访问左子树
		_PreOrder(pRoot->left);
		//访问右子树
		_PreOrder(pRoot->right);
	}

	//前序遍历二叉树--->循环实现
	void _PreOrderTraversal(pNode pRoot)
	{
		if (pRoot == NULL)
			return;

		stack<pNode> s;
		pNode pCur = NULL;
		s.push(pRoot);

		while (!s.empty())
		{
			pCur = s.top();
			s.pop();
			while (pCur)
			{
				cout << pCur->data << " ";
				if (pCur->right)//如果右子树存在，先压右子树
					s.push(pCur->right);
				pCur = pCur->left;
			}
		}
	}
	//中序遍历二叉树
	void _InOrder(pNode pRoot)
	{
		if (!pRoot)
			return;
		//访问左子树
		_InOrder(pRoot->left);
		//访问根结点
		cout << pRoot->data << " ";
		//访问右子树
		_InOrder(pRoot->right);
	}

	//中序遍历二叉树---->循环实现
	void _InOrderTraversal(pNode pRoot)
	{
		if (pRoot == NULL)
			return;

		stack<pNode> s;
		pNode pCur = pRoot;

		while (pCur || !s.empty())
		{
			while (pCur)//保存左侧路径的所有结点
			{
				s.push(pCur);
				pCur = pCur->left;
			}
			pCur = s.top();//取栈顶元素
			cout << pCur->data << " ";//访问
			s.pop();//出栈
			pCur = pCur->right;//对当前结点的右子树继续做同样的事情
		}
	}

	//后序遍历二叉树
	void _PostOrder(pNode pRoot)
	{
		if (!pRoot)
			return;
		//访问左子树
		_PostOrder(pRoot->left);
		//访问右子树
		_PostOrder(pRoot->right);
		//访问根结点
		cout << pRoot->data << " ";
	}
	//后序遍历二叉树---->循环实现
	void _PostOrderTraversal(pNode pRoot)
	{
		if (pRoot == NULL)
			return;

		pNode pCur = pRoot;
		pNode pPre = NULL;
		stack<pNode> s;

		while (!s.empty() || pCur)
		{
			while (pCur)//保存左侧路径的所有结点
			{
				s.push(pCur);
				pCur = pCur->left;
			}

			if (s.empty())
				return;

			pNode top = s.top();
			if (top->right == NULL || pPre == top->right)//当前结点的右子树为空
			{
				cout << top->data << " ";//访问
				pPre = top;
				s.pop();
			}
			else
				pCur = top->right;
		}
	}
	//层序遍历
	void _LevelOrder(pNode pRoot)
	{
		if (pRoot == NULL)
			return;
		queue<pNode> q;
		q.push(pRoot);

		while (!q.empty())
		{
			pNode pcur = q.front();
			cout << pcur->data << " ";
			q.pop();

			if (pcur->left)
				q.push(pcur->left);
			if (pcur->right)
				q.push(pcur->right);
		}
	}

	//结点个数
	size_t _Node_Count(pNode pRoot)
	{
		//空树
		if (pRoot == NULL)
			return 0;

		//其他情况
		else
		{
			return _Node_Count(pRoot->left) + _Node_Count(pRoot->right) + 1;
		}
	}

	//叶结点的个数
	size_t _LeafNode_Count(pNode pRoot)
	{
		//空树
		if (pRoot == NULL)
			return 0;

		//只有一个结点
		if (pRoot->left == NULL&&pRoot->right == NULL)
			return 1;

		//多个结点
		else
			return _LeafNode_Count(pRoot->left) + _LeafNode_Count(pRoot->right);
	}

	//二叉树的高度
	size_t _Hight(pNode pRoot)
	{
		if (pRoot == NULL)
			return 0;
		if (pRoot->left == NULL&&pRoot->right == NULL)
			return 1;
		else
		{
			return (_Hight(pRoot->left) > _Hight(pRoot->right)) ? _Hight(pRoot->left) + 1 : _Hight(pRoot->right) + 1;
		}
	}

	//值为data的元素的位置
	pNode _Find(pNode pRoot, const T& data)
	{
		//空树
		if (pRoot == NULL)
			return NULL;

		//寻找的值为根结点的值
		if (pRoot->data == data)
			return pRoot;

		if (pRoot->left)
			_Find(pRoot->left, data);

		if (pRoot->right)
			_Find(pRoot->right, data);
		return pRoot;
	}

	//双亲结点
	pNode _ParentNode(pNode pRoot, pNode curNode)
	{
		//结点为空，树为空，为根结点
		if (pRoot == NULL || curNode == NULL || pRoot = curNode)
			return NULL;

		//根为双亲结点
		if (pRoot->left == curNode || pRoot->right == curNode)
			return pRoot;

		//左子树
		if (pRoot->left)
			_ParentNode(pRoot->left, curNode);

		if (pRoot->right)
			_ParentNode(pRoot->right, curNode);
	}

	//左孩子结点
	pNode _Left_Child(pNode pRoot, pNode curNode)
	{
		if (pRoot == NULL || curNode == NULL)
			return NULL;

		return curNode->left;
	}

	//右孩子结点
	pNode _Right_Child(pNode pRoot, pNode curNode)
	{
		if (pRoot == NULL || curNode == NULL)
			return NULL;

		return curNode->right;
	}

	//二叉树的镜像
	void _MirrorBinTree(pNode pRoot)
	{
		if (pRoot == NULL)
			return;

		//镜像结点
		swap(pRoot->left, pRoot->right);
		//镜像左子树
		_MirrorBinTree(pRoot->left);
		//镜像右子树
		_MirrorBinTree(pRoot->right);
	}

	//第K层结点的个数
	size_t _KNode_Count(pNode pRoot, size_t k)
	{
		if (pRoot == NULL || k == 0)
			return 0;
		if (k == 1)
			return 1;

		return _KNode_Count(pRoot->left, k - 1) + _KNode_Count(pRoot->right, k - 1);
	}
	//判断一棵二叉树是否为完全二叉树
	bool _IsCompleteBinTree(pNode pRoot)
	{
		//空树
		if (pRoot == NULL)
			return true;
		//一个结点
		if (pRoot->left == NULL&&pRoot->right == NULL)
			return true;

		queue<pNode> q;
		pNode pCur = NULL;
		//多个结点
		while (pCur || !q.empty())
		{
			if (pCur->right&&NULL == pCur->left)//右子树存在，左子树不存在
				return false;

			if (pCur->left&&pCur->right)//饱和结点
			{
				q.push(pCur);
			}
		}
	}

private:
	pNode _pRoot;
};
void test1()
{
	char arr[] = "ABCD##E##F##GMN###Q##";
	int len = strlen(arr);
	BinTree<char> tree1(arr, len, '#');
	tree1.PreOrder();//前序
	tree1.InOrder();//中序
	tree1.PostOrder();//后序

	BinTree<char> tree2(tree1);//拷贝
	tree2.PreOrder();

	BinTree<char> tree3 = tree1;//赋值
	tree3.PreOrder();

	int a = tree1.Node_Count();
	cout << "The number of Node is " << a << endl;

	int b = tree1.LeafNode_Count();
	cout << "The number of LeafNode is " << b << endl;

	int c = tree1.Hight();
	cout << "The Hight of Tree is " << c << endl;


	cout << "G的地址为：" << tree1.Find('G') << endl;

	tree1.LevelOrder();//层序遍历
}

void test2()
{
	char arr[] = "AB#MDE##F";
	int len = strlen(arr);
	BinTree<char> tree1(arr, len, '#');
	cout << "前序遍历：  ";
	tree1.PreOrderTraversal();
	cout << "中序遍历：  ";
	tree1.InOrderTraversal();
	cout << "后序遍历：  ";
	tree1.PostOrderTraversal();
	tree1.MirrorBinTree();
	cout << "镜像后前序遍历：  ";
	tree1.PreOrderTraversal();

	size_t b = 3;
	int a = tree1.KNode_Count(b);
	cout << "第<<b<<层结点的个数：" << a << endl;

	if (tree1.IsCompleteBinTree())
		cout << "此树是一棵完全二叉树" << endl;
	else
		cout << "此树不是一棵完全二叉树" << endl;

}
int main()
{
	test2();

	system("pause:");
	return 0;
}
