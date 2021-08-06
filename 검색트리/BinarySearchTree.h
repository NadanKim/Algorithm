#pragma once
#include "../Common.h"

/// <summary>
/// 이진 검색 트리에 사용할 노드
/// </summary>
struct BinarySearchNode
{
	BinarySearchNode() : data{ 0 }, parent{ nullptr }, 
		left{ nullptr }, right{ nullptr } {}
	BinarySearchNode(int data) : data{ data }, parent{ nullptr }, 
		left{ nullptr }, right{ nullptr } {}

	void Clear()
	{
		data = 0;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

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

private:
	void Insert(BinarySearchNode* parent, int data);
	void Delete(BinarySearchNode* node);
	BinarySearchNode& GetNode(int data);
	bool IsLeftNode(BinarySearchNode* node);
	bool IsRightNode(BinarySearchNode* node);

private:
	BinarySearchNode* _root;
	BinarySearchNodeManager _nodeManager;
};