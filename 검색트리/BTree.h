#pragma once
#include "../Common.h"

struct BTreeNode;

/// <summary>
/// B 트리의 노드에서 사용할 키
/// </summary>
struct BTreeNodeKey
{
	BTreeNodeKey() : prev(nullptr), left(nullptr), value(0), right(nullptr), next(nullptr) {}

	void Clear();
	void Set(int data);

	void AddKeyToPrev(BTreeNodeKey* newKey);
	void AddKeyToNext(BTreeNodeKey* newKey);

	void SwapValue(BTreeNodeKey* other);

	BTreeNodeKey* prev;
	BTreeNode* left;
	int value;
	BTreeNode* right;
	BTreeNodeKey* next;
};

/// <summary>
/// B 트리에 사용할 노드
/// </summary>
struct BTreeNode
{
	static const size_t TotalKeyCount{ 2 };

	~BTreeNode();

	void Clear();
	bool Insert(int data);
	bool Insert(BTreeNodeKey* newKey);

	bool IsAbleToInsert();

	BTreeNodeKey* GetSmallestKey();
	BTreeNodeKey* GetBiggestKey();
	BTreeNodeKey* GetMiddleKey();

	BTreeNode* parent;
	BTreeNodeKey* keyRoot;
	size_t size;

	static BTreeNodeKeyManager* keyManager;
};

/// <summary>
/// B 트리에서 노드의 재활용을 위한 매니저
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
/// B 트리에서 노드의 키를 재활용 하기위한 매니저
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
	void ClearOverflow(BTreeNode* node);

	BTreeNode* SplitNodeWithKey(BTreeNode* node, BTreeNodeKey* key);
	//void Delete(BinarySearchNode* node);

	//BinarySearchNode* GetNode(int data);

private: // For Util Methods
	BTreeNode* GetProperNodeToInsert(int data);

private:
	BTreeNode* _root;
	BTreeNodeManager _nodeManager;
};