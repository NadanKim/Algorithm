#pragma once
#include "../Common.h"

struct BTreeNode;

/// <summary>
/// B Ʈ���� ��忡�� ����� Ű
/// </summary>
struct BTreeNodeKey
{
	BTreeNodeKey() : prev(nullptr), left(nullptr), value(0), right(nullptr), next(nullptr) {}

	void Clear();
	void Set(int data);

	BTreeNodeKey* prev;
	BTreeNode* left;
	int value;
	BTreeNode* right;
	BTreeNodeKey* next;
};

/// <summary>
/// B Ʈ���� ����� ���
/// </summary>
struct BTreeNode
{
	static const size_t TotalKeyCount{ 2 };

	~BTreeNode();

	void Clear();

	BTreeNode* parent;
	BTreeNodeKey* keyRoot;
	size_t size;

	static BTreeNodeKeyManager* keyManager;
};

/// <summary>
/// B Ʈ������ ����� ��Ȱ���� ���� �Ŵ���
/// </summary>
class BTreeNodeManager
{
public:
	BTreeNodeManager();
	~BTreeNodeManager();

	void Push(BTreeNode* node);
	BTreeNode* Pop();

private:
	BTreeNode* nodes;
};

/// <summary>
/// B Ʈ������ ����� Ű�� ��Ȱ�� �ϱ����� �Ŵ���
/// </summary>
class BTreeNodeKeyManager
{
public:
	~BTreeNodeKeyManager();

	void Push(BTreeNodeKey* node);
	BTreeNodeKey* Pop();

private:
	BTreeNodeKey* nodes;
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
	void Insert(BTreeNode* parent, int data);
	void ClearOverflow(BTreeNode* node, int data);
	//void Delete(BinarySearchNode* node);

	//BinarySearchNode* GetNode(int data);

private:
	BTreeNode* _root;
	BTreeNodeManager _nodeManager;
};