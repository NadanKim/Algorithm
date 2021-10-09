#pragma once
#include "../Common.h"

struct BTreeNode;

/// <summary>
/// B 트리의 노드에서 사용할 키
/// </summary>
struct BTreeNodeKey
{
	BTreeNodeKey() : left(nullptr), value(0), right(nullptr) {}

	void Clear();
	void Set(int data);

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

	BTreeNode();
	~BTreeNode();

	void Clear();

	bool Insert(int data);
	BTreeNode* GetProperNodeToInsert(int data);

	BTreeNode* parent;
	BTreeNodeKey* keys;
	size_t size;
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
	~BTree();

	bool Exists(int data);
	void Insert(int data);
	//void Delete(int data);

private:
	void Insert(BTreeNode* parent, int data);
	//void Delete(BinarySearchNode* node);

	//BinarySearchNode* GetNode(int data);

private:
	BTreeNode* _root;
	BTreeNodeManager _nodeManager;
};