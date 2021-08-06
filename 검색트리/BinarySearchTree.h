#pragma once
#include "../Common.h"

/// <summary>
/// ���� �˻� Ʈ���� ����� ���
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
/// ���� �˻� Ʈ������ ����� ��Ȱ���� ���� �Ŵ���
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
/// ���� �ڷᱸ���� �̿��� ���� �˻� Ʈ��
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