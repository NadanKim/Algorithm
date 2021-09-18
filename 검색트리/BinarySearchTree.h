#pragma once
#include "../Common.h"
#include <string>
#include <queue>
#include <map>

using std::string;
using std::queue;
using std::map;

/// <summary>
/// 이진 검색 트리에 사용할 노드
/// </summary>
struct BinarySearchNode
{
	const static int Width = 8;

	BinarySearchNode() : isEmpty{ false }, data{ 0 }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}
	BinarySearchNode(int data) : isEmpty{ false }, data{ data }, parent{ nullptr },
		left{ nullptr }, right{ nullptr } {}

	void Clear()
	{
		isEmpty = false;
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
		size_t spaceCnt = Width - dataStr.size();
		size_t leftSpaceCnt = spaceCnt / 2;
		size_t rightSpaceCnt = spaceCnt / 2 + spaceCnt % 2;

		return string(leftSpaceCnt, '_') + dataStr + string(rightSpaceCnt, '_');
	}

	bool isEmpty;

	int data;
	BinarySearchNode* parent;
	BinarySearchNode* left;
	BinarySearchNode* right;
};

/// <summary>
/// 이진 검색 트리에서 노드의 재활용을 위한 매니저
/// </summary>
class BinarySearchNodeManager
{
public:
	~BinarySearchNodeManager();

	void Push(BinarySearchNode* node);
	BinarySearchNode* Pop();
	BinarySearchNode* GetEmptyNode(BinarySearchNode* parent);

private:
	BinarySearchNode* nodes;
};

/// <summary>
/// 연결 자료구조를 이용한 이진 검색 트리
/// </summary>
class BinarySearchTree
{
public:
	~BinarySearchTree();

	bool Exists(int data);
	const BinarySearchNode& Search(int data);
	void Insert(int data);
	void Delete(int data);

	void PrintTree();

private:
	void Insert(BinarySearchNode* parent, int data);
	void Delete(BinarySearchNode* node);

	void PrintTree(BinarySearchNode* node, int lineWidth);
	string GetNodeStick(BinarySearchNode* node, int blankSize);

	BinarySearchNode* GetNode(int data);

	bool IsLeftNode(BinarySearchNode* node);
	bool IsRightNode(BinarySearchNode* node);

private:
	BinarySearchNode* _root;
	BinarySearchNodeManager _nodeManager;
	queue<BinarySearchNode*> _queue;
	map<int, string> _numberMap;
	map<int, string> _stickMap;
};