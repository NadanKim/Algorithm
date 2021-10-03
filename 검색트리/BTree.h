#pragma once
#include "../Common.h"

struct BTreeNode;

/// <summary>
/// B Ʈ���� ��忡�� ����� Ű
/// </summary>
class BTreeNodeKey
{
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

	BTreeNode* parent;
	BTreeNodeKey* keys;
};

/// <summary>
/// ���� �ڷᱸ���� �̿��� B Ʈ��
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