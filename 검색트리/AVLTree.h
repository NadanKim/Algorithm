#pragma once
#include "../Common.h"

/// <summary>
/// AVL 트리에 사용할 노드
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
/// AVL 트리에서 노드의 재활용을 위한 매니저
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