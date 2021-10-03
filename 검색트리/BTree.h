#pragma once
#include "../Common.h"

struct BTreeNode;

/// <summary>
/// B 트리의 노드에서 사용할 키
/// </summary>
class BTreeNodeKey
{
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

	BTreeNode* parent;
	BTreeNodeKey* keys;
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