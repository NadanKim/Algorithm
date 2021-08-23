#pragma once
#include "../Common.h"

/// <summary>
/// 레드 블랙 트리에 사용할 노드
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
/// 레드 블랙 트리에서 노드의 재활용을 위한 매니저
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
/// 연결 자료구조를 이용한 레드 블랙 트리
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