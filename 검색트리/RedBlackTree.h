#pragma once
#include "../Common.h"

enum class NodeColor
{
	Red,
	Black
};

/// <summary>
/// ���� �� Ʈ���� ����� ���
/// </summary>
struct RedBlackNode
{
	RedBlackNode() : data{ 0 }, color{ NodeColor::Red }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}
	RedBlackNode(int data) : data{ data }, color{ NodeColor::Red }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}

	void Clear()
	{
		data = 0;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	bool HasParent()
	{
		return parent != nullptr;
	}

	bool IsRightChild()
	{
		return (parent->right == this);
	}

	RedBlackNode* GetSibling()
	{
		RedBlackNode* sibling{ nullptr };

		if (HasParent())
		{
			if (parent->left == this)
			{
				sibling = parent->right;
			}
			else
			{
				sibling = parent->left;
			}
		}
		return sibling;
	}

	int data;
	NodeColor color;
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
	RedBlackNodeManager(RedBlackNode* nil);
	~RedBlackNodeManager();

	void Push(RedBlackNode* node);
	RedBlackNode* Pop();

private:
	RedBlackNode* _nil;
	RedBlackNode* _nodes;
};

/// <summary>
/// ���� �ڷᱸ���� �̿��� ���� �� Ʈ��
/// </summary>
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	bool Exists(int data);
	const RedBlackNode& Search(int data);
	void Insert(int data);
	void Delete(int data);

private:
	RedBlackNode* Insert(RedBlackNode* parent, int data);

	void Delete(RedBlackNode* node);
	RedBlackNode& GetNode(int data);
	bool IsLeftNode(RedBlackNode* node);
	bool IsRightNode(RedBlackNode* node);

private:
	RedBlackNode* _root;
	RedBlackNode* _nil;
	RedBlackNodeManager* _nodeManager;
};