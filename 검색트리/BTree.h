#pragma once
#include "../Common.h"

struct BTreeNode;

/// <summary>
/// B 트리의 노드에서 사용할 키
/// </summary>
struct BTreeNodeKey
{
	BTreeNodeKey() : left(nullptr), value(0), right(nullptr) {}

	void Clear()
	{
		left = nullptr;
		value = 0;
		right = nullptr;
	}

	BTreeNode* left;
	int value;
	BTreeNode* right;
};

/// <summary>
/// B 트리에 사용할 노드
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
/// B 트리에서 노드의 재활용을 위한 매니저
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
/// 연결 자료구조를 이용한 B 트리
/// </summary>
class BTree
{
public:
	/*~BTree();

	bool Exists(int data);
	const BinarySearchNode& Search(int data);
	void Insert(int data);
	void Delete(int data);

	void PrintTree();

private:
	void Insert(BinarySearchNode* parent, int data);
	void Delete(BinarySearchNode* node);

	void PrintTree(BinarySearchNode* node, int lineWidth);
	string GetNodeStick(BinarySearchNode* node, int blankSize);

	BinarySearchNode* GetNode(int data);

	bool IsLeftNode(BinarySearchNode* node);
	bool IsRightNode(BinarySearchNode* node);

private:
	BinarySearchNode* _root;
	BinarySearchNodeManager _nodeManager;
	queue<BinarySearchNode*> _queue;
	map<int, string> _numberMap;
	map<int, string> _stickMap;*/
};