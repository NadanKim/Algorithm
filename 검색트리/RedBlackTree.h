#pragma once
#include "../Common.h"

/// <summary>
/// ���� �� Ʈ���� ����� ���
/// </summary>
struct RedBlackNode
{
	RedBlackNode() : data{ 0 }, parent{ nullptr }, 
		left{ nullptr }, right{ nullptr } {}
	RedBlackNode(int data) : data{ data }, parent{ nullptr }, 
		left{ nullptr }, right{ nullptr } {}

	void Clear()
	{
		data = 0;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	int data;
	RedBlackNode* parent;
	RedBlackNode* left;
	RedBlackNode* right;
};

/// <summary>
/// ���� �� Ʈ������ ����� ��Ȱ���� ���� �Ŵ���
/// </summary>
class RedBlackNodeManager
{
public:
	~RedBlackNodeManager();

	void Push(RedBlackNode* node);
	RedBlackNode* Pop();

private:
	RedBlackNode* nodes;
};

/// <summary>
/// ���� �ڷᱸ���� �̿��� ���� �� Ʈ��
/// </summary>
class RedBlackTree
{
public:
	~RedBlackTree();

	bool Exists(int data);
	const RedBlackNode& Search(int data);
	void Insert(int data);
	void Delete(int data);

private:
	void Insert(RedBlackNode* parent, int data);
	void Delete(RedBlackNode* node);
	RedBlackNode& GetNode(int data);
	bool IsLeftNode(RedBlackNode* node);
	bool IsRightNode(RedBlackNode* node);

private:
	RedBlackNode* _root;
	RedBlackNodeManager _nodeManager;
};