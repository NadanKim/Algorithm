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
	AVLNode* Insert(AVLNode* parent, int data);
	AVLNode* Delete(AVLNode* node);

	AVLNode* GetNode(int data);

	bool IsLeftNode(AVLNode* node);
	bool IsRightNode(AVLNode* node);

private:
	AVLNode* _root;
	AVLNodeManager _nodeManager;
};