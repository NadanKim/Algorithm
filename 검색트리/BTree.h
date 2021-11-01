#pragma once
#include "../Common.h"
#include <queue>

using std::queue;

struct BTreeNode;
class BTreeNodeKeyManager;

/// <summary>
/// B Ʈ���� ��忡�� ����� Ű
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
/// B Ʈ���� ����� ���
/// </summary>
struct BTreeNode
{
	static const size_t TotalKeyCount{ 3 };

	~BTreeNode();

	void Clear();
	bool Insert(int data);
	bool Insert(BTreeNodeKey* newKey);

	bool Delete(int data);
	bool Delete(BTreeNodeKey* deleteKey);

	bool IsAbleToInsert();
	bool IsContainsData(int data);
	bool IsAbleToWithdraw();

	BTreeNodeKey* GetSmallestKey();
	BTreeNodeKey* GetBiggestKey();
	BTreeNodeKey* GetMiddleKey();

	BTreeNodeKey* GetKey(int data);

	BTreeNode* parent;
	BTreeNodeKey* keyRoot;
	size_t size;

	BTreeNodeKeyManager* keyManager;
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
	BTreeNodeKeyManager* keyManager;
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
	BTreeNodeKey* keys;
};

/// <summary>
/// ���� �ڷᱸ���� �̿��� B Ʈ��
/// </summary>
class BTree
{
public:
	BTree();
	~BTree();

	bool Exists(int data);
	void Insert(int data);
	void Delete(int data);

	void PrintTree();

private:
	void ClearOverflow(BTreeNode* node);
	void ClearUnderflow(BTreeNode* node);

	BTreeNode* SplitNodeWithKey(BTreeNode* node, BTreeNodeKey* key);
	BTreeNode* MergeNodeWithKey(BTreeNode* node, BTreeNodeKey* lsKey, BTreeNodeKey* rsKey);

private: // For Util Methods
	BTreeNode* GetProperNodeToInsert(int data);
	BTreeNode* GetProperNodeToDelete(int data);

private:
	BTreeNode* _root;
	BTreeNodeManager _nodeManager;
	queue<BTreeNode*> _queue;
};