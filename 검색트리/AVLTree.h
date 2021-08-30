#pragma once
#include "../Common.h"

/// <summary>
/// AVL Ʈ���� ����� ���
/// </summary>
struct AVLNode
{
	AVLNode() : data{ 0 }, bf{ 0 }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}
	AVLNode(int data) : data{ data }, bf{ 0 }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}

	void Clear()
	{
		data = 0;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	bool HasBalanceProblem()
	{
		return bf < -1 || 1 < bf;
	}

	int data;
	int bf;
	AVLNode* parent;
	AVLNode* left;
	AVLNode* right;
};

/// <summary>
/// AVL Ʈ������ ����� ��Ȱ���� ���� �Ŵ���
/// </summary>
class AVLNodeManager
{
public:
	~AVLNodeManager();

	void Push(AVLNode* node);
	AVLNode* Pop();

private:
	AVLNode* nodes;
};

/// <summary>
/// ���� �ڷᱸ���� �̿��� AVL Ʈ��
/// </summary>
class AVLTree
{
public:
	~AVLTree();

	bool Exists(int data);
	const AVLNode& Search(int data);
	void Insert(int data);
	void Delete(int data);

private:
	void Insert(AVLNode* parent, int data);
	void Delete(AVLNode* node);

	AVLNode* GetNode(int data);

	bool IsLeftNode(AVLNode* node);
	bool IsRightNode(AVLNode* node);

	AVLNode* RotateLeft(AVLNode* node);
	AVLNode* RotateRight(AVLNode* node);

	int CalculateBalaceFactor(AVLNode* node);

	int GetNodeDepth(AVLNode* node, int depth = 0);

	bool IsLLCase(AVLNode* c, AVLNode* c2);
	bool IsRRCase(AVLNode* c, AVLNode* c2);
	bool IsLRCase(AVLNode* c, AVLNode* c2);
	bool IsRLCase(AVLNode* c, AVLNode* c2);

private:
	AVLNode* _root;
	AVLNodeManager _nodeManager;
};