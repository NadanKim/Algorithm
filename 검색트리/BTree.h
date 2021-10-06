#pragma once
#include "../Common.h"

struct BTreeNode;

/// <summary>
/// B Ʈ���� ��忡�� ����� Ű
/// </summary>
struct BTreeNodeKey
{
	BTreeNodeKey() : isSet(false), left(nullptr), value(0), right(nullptr) {}

	void Clear()
	{
		isSet = false;
		left = nullptr;
		value = 0;
		right = nullptr;
	}

	bool isSet;
	BTreeNode* left;
	int value;
	BTreeNode* right;
};

/// <summary>
/// B Ʈ���� ����� ���
/// </summary>
struct BTreeNode
{
	static const size_t TotalKeyCount{ 4 };

	BTreeNode() : parent(nullptr)
	{
		keys = new BTreeNodeKey[TotalKeyCount];
	}
	~BTreeNode()
	{
		delete[] keys;
	}

	void Clear()
	{
		parent = nullptr;
		for (int i = 0; i < TotalKeyCount; i++)
		{
			keys[i].Clear();
		}
	}

	BTreeNode* parent;
	BTreeNodeKey* keys;
};

/// <summary>
/// B Ʈ������ ����� ��Ȱ���� ���� �Ŵ���
/// </summary>
class BTreeNodeManager
{
public:
	~BTreeNodeManager();

	void Push(BTreeNode* node);
	BTreeNode* Pop();

private:
	BTreeNode* nodes;
};

/// <summary>
/// ���� �ڷᱸ���� �̿��� B Ʈ��
/// </summary>
class BTree
{
public:
	~BTree();

	bool Exists(int data);
	void Insert(int data);
	//void Delete(int data);

private:
	//void Insert(BinarySearchNode* parent, int data);
	//void Delete(BinarySearchNode* node);

	//BinarySearchNode* GetNode(int data);

private:
	BTreeNode* _root;
	BTreeNodeManager _nodeManager;
};