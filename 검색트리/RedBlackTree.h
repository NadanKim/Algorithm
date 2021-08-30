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

	RedBlackNode* GetSibling()
	{
		RedBlackNode* sibling{ nullptr };

		if (parent != nullptr)
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

	void SwapColor(RedBlackNode* other)
	{
		NodeColor temp{ other->color };
		other->color = color;
		color = temp;
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
	void AdjustInsertedNode(RedBlackNode* node);

	RedBlackNode* Delete(RedBlackNode* node);
	void AdjustDeletedNode(RedBlackNode* node);

	RedBlackNode* GetNode(int data);

	bool IsLeftNode(RedBlackNode* node);
	bool IsRightNode(RedBlackNode* node);

	void RotateLeft(RedBlackNode* node);
	void RotateRight(RedBlackNode* node);

private:
	RedBlackNode* _root;
	RedBlackNode* _nil;
	RedBlackNodeManager* _nodeManager;
};