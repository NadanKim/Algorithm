#pragma once
#include "../Common.h"
#include <string>
#include <queue>
#include <map>

using std::string;
using std::queue;
using std::map;

enum class NodeColor
{
	Red,
	Black
};

/// <summary>
/// 레드 블랙 트리에 사용할 노드
/// </summary>
struct RedBlackNode
{
	const static int NodeSize = 5;
	const static int ColorSize = 3;
	// NodeSize + ColorSize
	const static int Width = 8;

	RedBlackNode() : isEmpty{ false }, data { 0 }, color{ NodeColor::Red }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}
	RedBlackNode(int data) : isEmpty{ false }, data{ data }, color{ NodeColor::Red }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}

	void Clear()
	{
		isEmpty = false;
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

	int GetMaxDepth()
	{
		int leftMaxDepth{ left != nullptr ? left->GetMaxDepth() : 0 };
		int rightMaxDpth{ right != nullptr ? right->GetMaxDepth() : 0 };
		return (leftMaxDepth > rightMaxDpth ? leftMaxDepth : rightMaxDpth) + 1;
	}

	int GetCurDepth()
	{
		return (parent != nullptr ? parent->GetCurDepth() : 0) + 1;
	}

	bool HasLeftChild()
	{
		return left != nullptr;
	}

	bool HasRightChild()
	{
		return right != nullptr;
	}

	string ToString()
	{
		if (isEmpty)
		{
			return string(Width, ' ');
		}

		string dataStr = std::to_string(data);
		size_t spaceCnt = NodeSize - dataStr.size();
		size_t leftSpaceCnt = spaceCnt / 2;
		size_t rightSpaceCnt = spaceCnt / 2 + spaceCnt % 2;

		string colorText = (color == NodeColor::Black ? "R" : "B");

		return string(leftSpaceCnt, '_') + dataStr + string(rightSpaceCnt, '_') + "(" + colorText + ")";
	}

	bool isEmpty;

	int data;
	NodeColor color;
	RedBlackNode* parent;
	RedBlackNode* left;
	RedBlackNode* right;
};

/// <summary>
/// 레드 블랙 트리에서 노드의 재활용을 위한 매니저
/// </summary>
class RedBlackNodeManager
{
public:
	RedBlackNodeManager(RedBlackNode* nil);
	~RedBlackNodeManager();

	void Push(RedBlackNode* node);
	RedBlackNode* Pop();
	RedBlackNode* GetEmptyNode(RedBlackNode* parent);

private:
	RedBlackNode* _nil;
	RedBlackNode* _nodes;
};

/// <summary>
/// 연결 자료구조를 이용한 레드 블랙 트리
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

	void PrintTree();

private:
	RedBlackNode* Insert(RedBlackNode* parent, int data);
	void AdjustInsertedNode(RedBlackNode* node);

	RedBlackNode* Delete(RedBlackNode* node);
	void AdjustDeletedNode(RedBlackNode* node);

	void PrintTree(RedBlackNode* node, int lineWidth);
	string GetNodeStick(RedBlackNode* node, int blankSize);

	RedBlackNode* GetNode(int data);

	bool IsLeftNode(RedBlackNode* node);
	bool IsRightNode(RedBlackNode* node);

	void RotateLeft(RedBlackNode* node);
	void RotateRight(RedBlackNode* node);

	int GetTreeMaxDepth();

private:
	RedBlackNode* _root;
	RedBlackNode* _nil;
	RedBlackNodeManager* _nodeManager;
	queue<RedBlackNode*> _queue;
	map<int, string> _numberMap;
	map<int, string> _stickMap;
};