#pragma once
#include "../Common.h"
#include <string>
#include <queue>
#include <map>

using std::string;
using std::queue;
using std::map;

/// <summary>
/// AVL 트리에 사용할 노드
/// </summary>
struct AVLNode
{
	const static int NodeSize = 5;
	const static int BfSize = 4;
	// NodeSize + BfSize
	const static int Width = 9;

	AVLNode() : isEmpty{ false }, data { 0 }, bf{ 0 }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}
	AVLNode(int data) : isEmpty{ false }, data{ data }, bf{ 0 }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}

	void Clear()
	{
		isEmpty = false;
		data = 0;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	bool HasBalanceProblem()
	{
		return bf < -1 || 1 < bf;
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

		string bfStr = bf >= 0 ? "+" + std::to_string(bf) : std::to_string(bf);

		return string(leftSpaceCnt, '_') + dataStr + string(rightSpaceCnt, '_') + "(" + bfStr + ")";
	}

	bool isEmpty;

	int data;
	int bf;
	AVLNode* parent;
	AVLNode* left;
	AVLNode* right;
};

/// <summary>
/// AVL 트리에서 노드의 재활용을 위한 매니저
/// </summary>
class AVLNodeManager
{
public:
	~AVLNodeManager();

	void Push(AVLNode* node);
	AVLNode* Pop();
	AVLNode* GetEmptyNode(AVLNode* parent);

private:
	AVLNode* nodes;
};

/// <summary>
/// 연결 자료구조를 이용한 AVL 트리
/// </summary>
class AVLTree
{
public:
	~AVLTree();

	bool Exists(int data);
	const AVLNode& Search(int data);
	void Insert(int data);
	void Delete(int data);

	void PrintTree();

private:
	void Insert(AVLNode* parent, int data);
	void Delete(AVLNode* node);

	void PrintTree(AVLNode* node, int lineWidth);
	string GetNodeStick(AVLNode* node, int blankSize);

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
	queue<AVLNode*> _queue;
	map<int, string> _numberMap;
	map<int, string> _stickMap;
};