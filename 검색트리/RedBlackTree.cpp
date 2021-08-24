#include "RedBlackTree.h"

#pragma region ��� �Ŵ���
/// <summary>
/// ���� �� ����� �Ŵ����� nil ��� ���
/// </summary>
/// <param name="nil">nil ���</param>
RedBlackNodeManager::RedBlackNodeManager(RedBlackNode* nil)
	: _nil(nil), _nodes(nullptr)
{
}

/// <summary>
/// ���� �� ������ ��� ����
/// </summary>
RedBlackNodeManager::~RedBlackNodeManager()
{
	while (_nodes != nullptr)
	{
		RedBlackNode* temp{ _nodes };
		_nodes = _nodes->left;
		delete temp;
	}
}

/// <summary>
/// ��� �Ϸ��� ��带 �Ŵ����� ����
/// </summary>
/// <param name="node">����� ��ȯ�� ���</param>
void RedBlackNodeManager::Push(RedBlackNode* node)
{
	node->left = _nodes;
	_nodes = node;
}

/// <summary>
/// ��尡 �ʿ��� ��� �Ŵ������� ��ȯ
/// </summary>
/// <returns>����� �� �ִ� ���</returns>
RedBlackNode* RedBlackNodeManager::Pop()
{
	RedBlackNode* node{ _nodes };

	if (node != nullptr)
	{
		_nodes = node->left;
		node->Clear();
	}
	else
	{
		node = new RedBlackNode();
	}

	node->color = NodeColor::Red;
	node->left = node->right = _nil;

	return node;
}
#pragma endregion

#pragma region ���� �� Ʈ��
/// <summary>
/// ���� �� Ʈ���� �ʿ��� ���� ����
/// </summary>
RedBlackTree::RedBlackTree()
	: _root(nullptr)
{
	_nil = new RedBlackNode();
	_nil->color = NodeColor::Black;

	_nodeManager = new RedBlackNodeManager(_nil);
}

/// <summary>
/// ���� �� ���� ��� ���� ó��
/// </summary>
RedBlackTree::~RedBlackTree()
{
	while (_root != nullptr)
	{
		Delete(_root);
	}
}

/// <summary>
/// ���� �� Ʈ������ Ư�� ���� ������ ��尡 �����ϴ��� ���� Ȯ��
/// </summary>
/// <param name="data">ã�� ��</param>
/// <returns>���� ����</returns>
bool RedBlackTree::Exists(int data)
{
	RedBlackNode* node{ _root };

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
/// ���� �� Ʈ������ �־��� ���� ���� ��带 ��ȯ
/// </summary>
/// <param name="data">ã�� ��</param>
/// <returns>���� ���� ���, ������ nullptr</returns>
const RedBlackNode& RedBlackTree::Search(int data)
{
	return GetNode(data);
}

/// <summary>
/// ���� �� Ʈ���� ���� ������ ��带 ����
/// </summary>
/// <param name="data">������ ��</param>
void RedBlackTree::Insert(int data)
{
	if (Exists(data))
	{
		return;
	}

	RedBlackNode* x{ Insert(_root, data) };
	RedBlackNode* p{ x->parent };
	
	if (x == _root || p->color == NodeColor::Black)
	{
		return;
	}

	RedBlackNode* y{ x->GetSibling() };
	RedBlackNode* p2{ p->parent };
	RedBlackNode* s{ p->GetSibling() };

	// case 1
	if (s->color == NodeColor::Red)
	{

	}
	else
	{
		// case 2-1
		if (x->IsRightChild())
		{

		}
		// case 2-2
		else
		{

		}
	}
}

/// <summary>
/// ���� �� Ʈ������ �ش� ���� ������ ��带 ����
/// </summary>
/// <param name="data">������ ��</param>
void RedBlackTree::Delete(int data)
{
	if (!Exists(data))
	{
		return;
	}

	RedBlackNode* node{ &GetNode(data) };
	Delete(node);
}

/// <summary>
/// ���� �� Ʈ�� ���� ó��
/// </summary>
/// <param name="parent">�����ؾ� �� ����� �θ�</param>
/// <param name="data">������ ��</param>
/// <returns>���� ������ ���</returns>
RedBlackNode* RedBlackTree::Insert(RedBlackNode* parent, int data)
{
	if (parent == nullptr)
	{
		RedBlackNode* node{ _nodeManager->Pop() };
		node->data = data;
		_root = node;

		return node;
	}
	else if (parent->data > data)
	{
		if (parent->left == nullptr)
		{
			RedBlackNode* node{ _nodeManager->Pop() };
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
			RedBlackNode* node{ _nodeManager->Pop() };
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
/// ���� �� Ʈ�� ���� ó��
/// </summary>
/// <param name="node">������ ���</param>
void RedBlackTree::Delete(RedBlackNode* node)
{
	RedBlackNode* parent{ node->parent };

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

		_nodeManager->Push(node);
	}
	else if (node->left != nullptr && node->right == nullptr ||
		node->left == nullptr && node->right != nullptr)
	{
		RedBlackNode* child{ node->left };
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

		_nodeManager->Push(node);
	}
	else
	{
		RedBlackNode* child{ node->left };
		while (child->right != nullptr)
		{
			child = child->right;
		}
		node->data = child->data;
		Delete(child);
	}
}

RedBlackNode& RedBlackTree::GetNode(int data)
{
	RedBlackNode* node{ _root };

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

	return *node;
}

/// <summary>
/// �ش� ��尡 �θ� ����� ���� �ڽ����� ����
/// </summary>
/// <param name="node">Ȯ���� ���</param>
/// <returns>���� �ڽ����� ����</returns>
bool RedBlackTree::IsLeftNode(RedBlackNode* node)
{
	return node->parent != nullptr && node->parent->left == node;
}

/// <summary>
/// �ش� ��尡 �θ� ����� ������ �ڽ����� ����
/// </summary>
/// <param name="node">Ȯ���� ���</param>
/// <returns>������ �ڽ����� ����</returns>
bool RedBlackTree::IsRightNode(RedBlackNode* node)
{
	return node->parent != nullptr && node->parent->right == node;
}
#pragma endregion