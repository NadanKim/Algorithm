#pragma once
#include "../Common.h"
#include <string>
#include <queue>

using std::string;
using std::queue;

/// <summary>
/// ���� �˻� Ʈ���� ����� ���
/// </summary>
struct BinarySearchNode
{
	BinarySearchNode() : data{ 0 }, parent{ nullptr }, 
		left{ nullptr }, right{ nullptr } {}
	BinarySearchNode(int data) : data{ data }, parent{ nullptr }, 
		left{ nullptr }, right{ nullptr } {}

	void Clear()
	{
		data = 0;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	int GetMaxDepth()
	{
		int leftMaxDepth{ left != nullptr ? left->GetMaxDepth() : 0 };
		int rightMaxDpth{ right != nullptr ? right->GetMaxDepth() : 0 };
		return (leftMaxDepth > rightMaxDpth ? leftMaxDepth : rightMaxDpth) + 1;
	}

	bool HasLeftChild()
	{
		return left != nullptr;
	}

	bool HasRightChild()
	{
		return right != nullptr;
	}

	int data;
	BinarySearchNode* parent;
	BinarySearchNode* left;
	BinarySearchNode* right;
};

/// <summary>
/// ���� �˻� Ʈ������ ����� ��Ȱ���� ���� �Ŵ���
/// </summary>
class BinarySearchNodeManager
{
public:
	~BinarySearchNodeManager();

	void Push(BinarySearchNode* node);
	BinarySearchNode* Pop();

private:
	BinarySearchNode* nodes;
};

/// <summary>
/// ���� �ڷᱸ���� �̿��� ���� �˻� Ʈ��
/// </summary>
class BinarySearchTree
{
public:
	~BinarySearchTree();

	bool Exists(int data);
	const BinarySearchNode& Search(int data);
	void Insert(int data);
	void Delete(int data);

	void PrintBinarySearchTree();

private:
	void Insert(BinarySearchNode* parent, int data);
	void Delete(BinarySearchNode* node);

	void PrintBinarySearchTree(BinarySearchNode* node);

	BinarySearchNode* GetNode(int data);

	bool IsLeftNode(BinarySearchNode* node);
	bool IsRightNode(BinarySearchNode* node);

	int GetTreeMaxDepth();

private:
	BinarySearchNode* _root;
	BinarySearchNodeManager _nodeManager;
	queue<BinarySearchNode*> _queue;
};