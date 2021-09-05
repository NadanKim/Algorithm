#include "BinarySearchTree.h"

#pragma region ��� �Ŵ���
/// <summary>
/// ���� �� ������ ��� ����
/// </summary>
BinarySearchNodeManager::~BinarySearchNodeManager()
{
	while (nodes != nullptr)
	{
		BinarySearchNode* temp{ nodes };
		nodes = nodes->left;
		delete temp;
	}
}

/// <summary>
/// ��� �Ϸ��� ��带 �Ŵ����� ����
/// </summary>
/// <param name="node">����� ��ȯ�� ���</param>
void BinarySearchNodeManager::Push(BinarySearchNode* node)
{
	node->left = nodes;
	nodes = node;
}

/// <summary>
/// ��尡 �ʿ��� ��� �Ŵ������� ��ȯ
/// </summary>
/// <returns>����� �� �ִ� ���</returns>
BinarySearchNode* BinarySearchNodeManager::Pop()
{
	BinarySearchNode* node{ nodes };

	if (node != nullptr)
	{
		nodes = node->left;
		node->Clear();
	}
	else
	{
		node = new BinarySearchNode();
	}

	return node;
}
#pragma endregion

#pragma region ���� �˻� Ʈ��
/// <summary>
/// ���� �� ���� ��� ���� ó��
/// </summary>
BinarySearchTree::~BinarySearchTree()
{
	while (_root != nullptr)
	{
		Delete(_root);
	}
}

/// <summary>
/// ���� �˻� Ʈ������ Ư�� ���� ������ ��尡 �����ϴ��� ���� Ȯ��
/// </summary>
/// <param name="data">ã�� ��</param>
/// <returns>���� ����</returns>
bool BinarySearchTree::Exists(int data)
{
	BinarySearchNode* node{ _root };

	while (node != nullptr)
	{
		if (node->data == data)
		{
			return true;
		}
		else if (node->data > data)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	return false;
}

/// <summary>
/// ���� �˻� Ʈ������ �־��� ���� ���� ��带 ��ȯ
/// </summary>
/// <param name="data">ã�� ��</param>
/// <returns>���� ���� ���, ������ nullptr</returns>
const BinarySearchNode& BinarySearchTree::Search(int data)
{
	return *GetNode(data);
}

/// <summary>
/// ���� �˻� Ʈ���� ���� ������ ��带 ����
/// </summary>
/// <param name="data">������ ��</param>
void BinarySearchTree::Insert(int data)
{
	if (Exists(data))
	{
		return;
	}

	Insert(_root, data);
}

/// <summary>
/// ���� �˻� Ʈ������ �ش� ���� ������ ��带 ����
/// </summary>
/// <param name="data">������ ��</param>
void BinarySearchTree::Delete(int data)
{
	if (!Exists(data))
	{
		return;
	}

	Delete(GetNode(data));
}

/// <summary>
/// ���� �˻� Ʈ���� ����Ѵ�.
/// </summary>
void BinarySearchTree::PrintBinarySearchTree()
{
	if (_root == nullptr)
	{
		std::cout << "EMPTY\n";
		return;
	}

	_queue.push(_root);
	while (!_queue.empty())
	{
		BinarySearchNode* node{ _queue.front() };
		_queue.pop();

		PrintBinarySearchTree(node);

		if (node->left != nullptr)
		{
			_queue.push(node->left);
		}
		if (node->right != nullptr)
		{
			_queue.push(node->right);
		}
	}
	std::cout << "\n\n";
}

/// <summary>
/// ���� �˻� Ʈ�� ���� ó��
/// </summary>
/// <param name="parent">�����ؾ� �� ����� �θ�</param>
/// <param name="data">������ ��</param>
void BinarySearchTree::Insert(BinarySearchNode* parent, int data)
{
	if (parent == nullptr)
	{
		BinarySearchNode* node{ _nodeManager.Pop() };
		node->data = data;
		_root = node;
	}
	else if (parent->data > data)
	{
		if (parent->left == nullptr)
		{
			BinarySearchNode* node{ _nodeManager.Pop() };
			node->data = data;
			node->parent = parent;
			parent->left = node;
		}
		else
		{
			Insert(parent->left, data);
		}
	}
	else
	{
		if (parent->right == nullptr)
		{
			BinarySearchNode* node{ _nodeManager.Pop() };
			node->data = data;
			node->parent = parent;
			parent->right = node;
		}
		else
		{
			Insert(parent->right, data);
		}
	}
}

/// <summary>
/// ���� �˻� Ʈ�� ���� ó��
/// </summary>
/// <param name="node">������ ���</param>
void BinarySearchTree::Delete(BinarySearchNode* node)
{
	BinarySearchNode* parent{ node->parent };

	if (node->left == nullptr && node->right == nullptr)
	{
		if (IsLeftNode(node))
		{
			parent->left = nullptr;
		}
		else if (IsRightNode(node))
		{
			parent->right = nullptr;
		}
		else
		{
			_root = nullptr;
		}

		_nodeManager.Push(node);
	}
	else if (node->left != nullptr && node->right == nullptr ||
		node->left == nullptr && node->right != nullptr)
	{
		BinarySearchNode* child{ node->left };
		if (child == nullptr)
		{
			child = node->right;
		}

		if (IsLeftNode(node))
		{
			parent->left = child;
		}
		else if (IsRightNode(node))
		{
			parent->right = child;
		}
		else
		{
			_root = child;
		}
		child->parent = parent;

		_nodeManager.Push(node);
	}
	else
	{
		BinarySearchNode* child{ node->left };
		while (child->right != nullptr)
		{
			child = child->right;
		}
		node->data = child->data;
		Delete(child);
	}
}

/// <summary>
/// ���� �˻� Ʈ���� ����Ѵ�.
/// </summary>
/// <param name="node">���� ����� ���</param>
void BinarySearchTree::PrintBinarySearchTree(BinarySearchNode* node)
{
	int depth{ node->GetMaxDepth() };
	int center{ (depth - 1) * 5 / 2 };

	bool isNeedReturn{ ((node == _root) || IsRightNode(node) && IsRightNode(node->parent)) };

	for (int i = 0; i < center; i++)
	{
		std::cout << ' ';
	}
	std::cout << node->data;
	for (int i = 0; i < center; i++)
	{
		std::cout << ' ';
	}

	if (isNeedReturn)
	{
		std::cout << '\n';
	}

	if (node->HasLeftChild())
	{
		std::cout << "��";
		for (int i = 1; i < center; i++)
		{
			std::cout << "��";
		}
	}
	else
	{
		for (int i = 0; i < center; i++)
		{
			std::cout << ' ';
		}
	}

	if (node->HasLeftChild() || node->HasRightChild())
	{
		std::cout << "��";
	}

	if (node->HasRightChild())
	{
		for (int i = 1; i < center; i++)
		{
			std::cout << "��";
		}
		std::cout << "��";
	}
	else
	{
		for (int i = 0; i < center + 3; i++)
		{
			std::cout << ' ';
		}
	}

	if (isNeedReturn)
	{
		std::cout << '\n';
	}
}

/// <summary>
/// �־��� ���� ���� ����� �����͸� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">ã������ ��</param>
/// <returns>����� ������</returns>
BinarySearchNode* BinarySearchTree::GetNode(int data)
{
	BinarySearchNode* node{ _root };

	while (node != nullptr)
	{
		if (node->data == data)
		{
			break;
		}
		else if (node->data > data)
		{
			node = node->left;
		}
		else
		{
			node = node->right;
		}
	}

	return node;
}

/// <summary>
/// �ش� ��尡 �θ� ����� ���� �ڽ����� ����
/// </summary>
/// <param name="node">Ȯ���� ���</param>
/// <returns>���� �ڽ����� ����</returns>
bool BinarySearchTree::IsLeftNode(BinarySearchNode* node)
{
	return node->parent != nullptr && node->parent->left == node;
}

/// <summary>
/// �ش� ��尡 �θ� ����� ������ �ڽ����� ����
/// </summary>
/// <param name="node">Ȯ���� ���</param>
/// <returns>������ �ڽ����� ����</returns>
bool BinarySearchTree::IsRightNode(BinarySearchNode* node)
{
	return node->parent != nullptr && node->parent->right == node;
}

/// <summary>
/// Ʈ���� �ִ� ���̸� ��ȯ�Ѵ�.
/// </summary>
/// <returns>Ʈ���� �ִ� ����</returns>
int BinarySearchTree::GetTreeMaxDepth()
{
	return _root != nullptr ? _root->GetMaxDepth() : 0;
}
#pragma endregion