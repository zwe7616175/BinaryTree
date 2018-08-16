#pragma once

#include <iostream>
using namespace std;
#include <string.h>

enum PoniterTag
{
	LINK,//表示有孩子结点
	THREAD//表示有线索
};
template <class T>
struct BinNode
{
	BinNode(const T& data = T())
	:data(data)
	, left(NULL)
	, right(NULL)
	, lthread(LINK)
	, rthread(LINK)
	{}

	T data;
	BinNode<T>* left;
	BinNode<T>* right;
	PoniterTag lthread;
	PoniterTag rthread;
};

template <class T>
class BinTreeThreading
{
	typedef BinNode<T> Node;
	typedef BinNode<T>* pNode;

public:
	//构造函数
	BinTreeThreading()
		:_pRoot(NULL)
	{}

	//创建一棵二叉树，前序创建
	BinTreeThreading(const T* arr, size_t size, const T& invalid)
	{
		size_t index = 0;
		_pRoot = _Create(arr, size, index, invalid);
	}

	//拷贝构造函数
	BinTreeThreading(const BinTreeThreading& sm)
	{
		if (this != &sm)
		{
			_pRoot = _Copy(sm._pRoot);
		}
	}

	//赋值运算符重载
	BinTreeThreading& operator=(const BinTreeThreading& sm)
	{
		if (this != &sm)
		{
			_DestoryTree(_pRoot);//销毁当前树
			_pRoot = _Copy(sm._pRoot);
		}
		return *this;
	}

	//析构函数
	~BinTreeThreading()
	{
		_DestoryTree(_pRoot);
		_pRoot = NULL;
	}

	//前序线索化二叉树
	void PreThread()
	{
		pNode pre = NULL;
		_PreThread(_pRoot,pre);
	}

	//前序线索遍历二叉树
	void PreOrderThreadTraversal()
	{
		_PreOrderThreadTraversal(_pRoot);
		cout << endl;
	}

	//中序线索化二叉树
	void InThread()
	{
		pNode pre = NULL;
		_InThread(_pRoot, pre);
	}
	//中序线索遍历二叉树--->循环
	void InOrderThreadTraversal()
	{
		_InOrderThreadTraversal(_pRoot);
		cout << endl;
	}

	//后序线索化二叉树
	void PostThread()
	{
		pNode pre = NULL;
		_PostThread(_pRoot, pre);
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

	//前序线索化二叉树
	void _PreThread(pNode pRoot,pNode& pPre)
	{
		//二叉树为空
		if (pRoot == NULL)
			return;

		//线索化当前结点
		//1.线索化当前结点的左指针域
		if (NULL == pRoot->left)//左孩子为空
		{
			pRoot->left = pPre;//指向前驱
			pRoot->lthread = THREAD;
		}
		//2.线索化当前结点的右指针域
		if (pPre && NULL == pPre->right)//上一个结点没有右子树
		{
			pPre->right = pRoot;
			pPre->rthread = THREAD; 
		}

		pPre = pRoot;//更新pPre

		//线索化左子树
		if (pRoot->lthread == LINK)//pRoot有左孩子
		{
			_PreThread(pRoot->left, pPre);
		}
		
		//线索化右子树
		if (pRoot->rthread == LINK)//pRoot有右孩子
		{
			_PreThread(pRoot->right, pPre);
		}
	}

	//前序线索遍历二叉树---->循环
	void _PreOrderThreadTraversal(pNode pRoot)
	{
		if (pRoot == NULL)
			return;

		pNode pCur = pRoot;

		//找左侧路径中所有结点并访问
		while (pCur->left != NULL && pCur->lthread==LINK)
		{
			cout << pCur->data << " ";
			pCur = pCur->left;
		}

		cout << pCur->data << " ";//访问最左边的结点

		//遇到线索就看右结点
		if (pCur->lthread == THREAD)
		{
			pCur = pCur->right;
			cout << pCur->data << " ";
		}
		
		while (pCur)
		{
			if (pCur->left != NULL&&pCur->lthread == LINK)//遇到左结点，访问
			{
				pCur = pCur->left;
				cout << pCur->data << " ";
				
			}
				pCur = pCur->right;
				if (pCur)
				  cout << pCur->data << " ";
		}
	}

	//中序线索化二叉树
	void _InThread(pNode pRoot, pNode& pPre)
	{
		//二叉树为空
		if (pRoot == NULL)
			return;

		//线索化左子树
		_InThread(pRoot->left, pPre);

		//线索化当前结点
		//1.线索化当前结点的左指针域
		if (NULL == pRoot->left)
		{
			pRoot->left = pPre;
			pRoot->lthread = THREAD;
		}
		//2.线索化当前结点的右指针域
		if (pPre && NULL == pPre->right)
		{
			pPre->right = pRoot;
			pPre->rthread = THREAD;
		}
		pPre = pRoot;//更新pPre

		//线索化右子树
		_InThread(pRoot->right, pPre);
	}

	//中序线索遍历二叉树--->循环
	void _InOrderThreadTraversal(pNode pRoot)
	{
		if (pRoot == NULL)
			return;

		pNode pCur = pRoot;

		while (pCur)
		{
			//找左侧路径中的结点
			while (pCur->left != NULL && pCur->lthread == LINK)
			{
				pCur = pCur->left;
			}
			cout << pCur->data << " ";

			//访问连在一起的后继
			while(pCur->rthread == THREAD)
			{
				pCur = pCur->right;
				cout << pCur->data << " ";
			}

			//继续循环
			pCur = pCur->right;
		}
	}

	//后序线索化二叉树
	void _PostThread(pNode pRoot, pNode& pPre)
	{
		//二叉树为空
		if (pRoot == NULL)
			return;

		//线索化左子树
		_PostThread(pRoot->left, pPre);

		//线索化右子树
		_PostThread(pRoot->right, pPre);

		//线索化当前结点
		//1.线索化当前结点的左指针域
		if (NULL == pRoot->left)
		{
			pRoot->left = pPre;
			pRoot->lthread = THREAD;
		}
		//2.线索化当前结点的右指针域
		if (pPre && NULL == pPre->right)
		{
			pPre->right = pRoot;
			pPre->rthread = THREAD;
		}
		pPre = pRoot;//更新pPre
	}
	/*
	//后序线索遍历二叉树--->循环
	void _PostOrderThreadTraversal(pNode pRoot)
	{
		if (pRoot == NULL)
			return;

		pNode pCur = pRoot;
		pNode pPre = NULL;

		while (pCur)
		{
			//找左侧路径中的结点
			while (pCur->left != NULL && pCur->lthread == LINK)
			{
				pCur = pCur->left;
			}

			//访问连在一起的后继
			while (pCur && pCur->rthread == THREAD)
			{
				cout << pCur->data << " ";
				pPre = pCur;
				pCur = pCur->right;
			}

			//判断是否为根结点
			if (pCur == pRoot)
			{
				cout << pCur->data << endl;
				return;
			}

			while (pCur&&pCur->right == pPre)
			{
				cout << pCur->data << " ";
				pPre = pCur;
				pCur = _ParentNode(pRoot, pCur);
			}
			if (pCur&&pCur->rthread == LINK)
			{
				pCur = pCur->right;
			}
		}
	}
	*/

private:
	pNode _pRoot;
};

void test1()
{
	char arr[] = "ABD###CE##F";
	int len = strlen(arr);
	BinTreeThreading<char> tree1(arr, len, '#');
	//tree1.PreThread();
	//tree1.PreOrderThreadTraversal();

	//tree1.InThread();
	//tree1.InOrderThreadTraversal();



}

