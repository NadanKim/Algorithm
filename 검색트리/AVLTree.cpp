#include "AVLTree.h"

#pragma region ��� �Ŵ���
/// <summary>
/// ���� �� ������ ��� ����
/// </summary>
AVLNodeManager::~AVLNodeManager()
{
	while (nodes != nullptr)
	{
		AVLNode* temp{ nodes };
		nodes = nodes->left;
		delete temp;
	}
}

/// <summary>
/// ��� �Ϸ��� ��带 �Ŵ����� ����
/// </summary>
/// <param name="node">����� ��ȯ�� ���</param>
void AVLNodeManager::Push(AVLNode* node)
{
	node->left = nodes;
	nodes = node;
}

/// <summary>
/// ��尡 �ʿ��� ��� �Ŵ������� ��ȯ
/// </summary>
/// <returns>����� �� �ִ� ���</returns>
AVLNode* AVLNodeManager::Pop()
{
	AVLNode* node{ nodes };

	if (node != nullptr)
	{
		nodes = node->left;
		node->Clear();
	}
	else
	{
		node = new AVLNode();
	}

	return node;
}
#pragma endregion

#pragma region AVLƮ��
/// <summary>
/// ���� �� ���� ��� ���� ó��
/// </summary>
AVLTree::~AVLTree()
{
	while (_root != nullptr)
	{
		Delete(_root);
	}
}

/// <summary>
/// AVL Ʈ������ Ư�� ���� ������ ��尡 �����ϴ��� ���� Ȯ��
/// </summary>
/// <param name="data">ã�� ��</param>
/// <returns>���� ����</returns>
bool AVLTree::Exists(int data)
{
	AVLNode* node{ _root };

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
/// AVL Ʈ������ �־��� ���� ���� ��带 ��ȯ
/// </summary>
/// <param name="data">ã�� ��</param>
/// <returns>���� ���� ���, ������ nullptr</returns>
const AVLNode& AVLTree::Search(int data)
{
	return *GetNode(data);
}

/// <summary>
/// AVL Ʈ���� ���� ������ ��带 ����
/// </summary>
/// <param name="data">������ ��</param>
void AVLTree::Insert(int data)
{
	if (Exists(data))
	{
		return;
	}

	AVLNode* node{ Insert(_root, data) };
}

/// <summary>
/// AVL Ʈ������ �ش� ���� ������ ��带 ����
/// </summary>
/// <param name="data">������ ��</param>
void AVLTree::Delete(int data)
{
	if (!Exists(data))
	{
		return;
	}

	AVLNode* node{ Delete(GetNode(data)) };
}

/// <summary>
/// AVL Ʈ�� ���� ó��
/// </summary>
/// <param name="parent">�����ؾ� �� ����� �θ�</param>
/// <param name="data">������ ��</param>
AVLNode* AVLTree::Insert(AVLNode* parent, int data)
{
	if (parent == nullptr)
	{
		AVLNode* node{ _nodeManager.Pop() };
		node->data = data;
		_root = node;

		return node;
	}
	else if (parent->data > data)
	{
		if (parent->left == nullptr)
		{
			AVLNode* node{ _nodeManager.Pop() };
			node->data = data;
			node->parent = parent;
			parent->left = node;

			return node;
		}
		else
		{
			return Insert(parent->left, data);
		}
	}
	else
	{
		if (parent->right == nullptr)
		{
			AVLNode* node{ _nodeManager.Pop() };
			node->data = data;
			node->parent = parent;
			parent->right = node;
			
			return node;
		}
		else
		{
			return Insert(parent->right, data);
		}
	}
}

/// <summary>
/// AVL Ʈ�� ���� ó��
/// </summary>
/// <param name="node">������ ���</param>
AVLNode* AVLTree::Delete(AVLNode* node)
{
	AVLNode* parent{ node->parent };

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
		AVLNode* child{ node->left };
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
		AVLNode* child{ node->left };
		while (child->right != nullptr)
		{
			child = child->right;
		}
		node->data = child->data;
		Delete(child);
	}

	return parent;
}

/// <summary>
/// �־��� ���� ���� ����� �����͸� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">ã������ ��</param>
/// <returns>����� ������</returns>
AVLNode* AVLTree::GetNode(int data)
{
	AVLNode* node{ _root };

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
bool AVLTree::IsLeftNode(AVLNode* node)
{
	return node->parent != nullptr && node->parent->left == node;
}

/// <summary>
/// �ش� ��尡 �θ� ����� ������ �ڽ����� ����
/// </summary>
/// <param name="node">Ȯ���� ���</param>
/// <returns>������ �ڽ����� ����</returns>
bool AVLTree::IsRightNode(AVLNode* node)
{
	return node->parent != nullptr && node->parent->right == node;
}
#pragma endregion