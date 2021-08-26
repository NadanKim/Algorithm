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

	AdjustInsertedNode(Insert(_root, data));
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
	AdjustDeletedNode(Delete(node));
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
/// ���� �� Ʈ���� ������ ��带 ��Ģ�� �°� �����Ѵ�.
/// </summary>
/// <param name="node">������ �Ǵ� ���</param>
void RedBlackTree::AdjustInsertedNode(RedBlackNode* node)
{
	RedBlackNode* x{ node };
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
		p->color = s->color = NodeColor::Black;
		p2->color = NodeColor::Red;
		if (p2 == _root)
		{
			p2->color = NodeColor::Red;
		}
		else
		{
			AdjustInsertedNode(p2);
		}
	}
	else
	{
		// case 2-1
		if (IsLeftNode(p) && IsRightNode(x))
		{
			RotateLeft(p);
			// case 2-2
			RotateRight(p2);
		}
		else if (IsRightNode(p) && IsLeftNode(x))
		{
			RotateRight(p);
			// case 2-2
			RotateLeft(p2);
		}
		// case 2-2
		p2->SwapColor(p);
	}
}

/// <summary>
/// ���� �� Ʈ�� ���� ó��
/// </summary>
/// <param name="node">������ ���</param>
RedBlackNode* RedBlackTree::Delete(RedBlackNode* node)
{
	RedBlackNode* parent{ node->parent };
	RedBlackNode* x{ nullptr };

	if (node->left == _nil && node->right == _nil)
	{
		if (IsLeftNode(node))
		{
			parent->left = _nil;
			_nil->parent = parent;
		}
		else if (IsRightNode(node))
		{
			parent->right = _nil;
			_nil->parent = parent;
		}
		else
		{
			_root = nullptr;
		}

		if (node->color == NodeColor::Black)
		{
			x = _nil;
		}

		_nodeManager->Push(node);
	}
	else if (node->left != _nil && node->right == _nil ||
		node->left == _nil && node->right != _nil)
	{
		RedBlackNode* child{ node->left };
		if (child == _nil)
		{
			child = node->right;
		}

		if (IsLeftNode(node))
		{
			parent->left = child;
			child->parent = parent;
		}
		else if (IsRightNode(node))
		{
			parent->right = child;
			child->parent = parent;
		}
		else
		{
			_root = child;
			child->parent = nullptr;
		}
		child->parent = parent;

		if (node->color == NodeColor::Black && child->color == NodeColor::Red)
		{
			x = child;
		}

		_nodeManager->Push(node);
	}
	else
	{
		RedBlackNode* child{ node->right };
		while (child->left != _nil)
		{
			child = child->left;
		}
		node->data = child->data;
		Delete(child);
	}

	return x;
}

/// <summary>
/// ���� �� Ʈ������ ��带 ������ �� ��Ģ�� �°� �����Ѵ�.
/// </summary>
/// <param name="node">������ �Ǵ� ���</param>
void RedBlackTree::AdjustDeletedNode(RedBlackNode* node)
{
	if (node == nullptr)
	{
		return;
	}

	RedBlackNode* x{ node };
	RedBlackNode* p{ x->parent };
	RedBlackNode* s{ x->GetSibling() };
	RedBlackNode* l{ s->left };
	RedBlackNode* r{ s->right };

	// case 1-1
	if (p->color == NodeColor::Red && s->color == NodeColor::Black &&
		l->color == NodeColor::Black && r->color == NodeColor::Black)
	{
		p->SwapColor(s);
	}
	// case *-2
	else if (s->color == NodeColor::Black && r->color == NodeColor::Red)
	{
		if (IsLeftNode(x))
		{
			RotateLeft(p);
			r->color = NodeColor::Black;
		}
		else
		{
			RotateRight(p);
			l->color = NodeColor::Black;
		}
		p->SwapColor(s);
	}
	// case *-3
	else if (s->color == NodeColor::Black && 
		l->color == NodeColor::Red && r->color == NodeColor::Black)
	{
		if (IsLeftNode(x))
		{
			RotateRight(s);
			l->SwapColor(s);
		}
		else
		{
			RotateLeft(s);
			r->SwapColor(s);
		}
		AdjustDeletedNode(x);
	}
	// case 2-1
	else if (p->color == NodeColor::Black && s->color == NodeColor::Black &&
		l->color == NodeColor::Black && r->color == NodeColor::Black)
	{
		s->color = NodeColor::Red;
		AdjustDeletedNode(p);
	}
	// case 2-4
	else if (p->color == NodeColor::Black && s->color == NodeColor::Red)
	{
		if (IsLeftNode(x))
		{
			RotateLeft(p);
		}
		else
		{
			RotateRight(p);
		}
		p->SwapColor(s);
		AdjustDeletedNode(x);
	}
	
	_nil->parent = nullptr;
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

/// <summary>
/// �־��� ��带 �������� �������� ȸ���Ѵ�.
/// </summary>
/// <param name="node">���� ���</param>
void RedBlackTree::RotateLeft(RedBlackNode* node)
{
	RedBlackNode* x{ node->right };
	RedBlackNode* p{ node };
	RedBlackNode* p2{ p->parent };

	p->right = x->left;
	x->left->parent = p;
	x->left = p;
	p->parent = x;
	if (p2 != nullptr)
	{
		p2->left = x;
	}
	else
	{
		_root = x;
	}
	x->parent = p2;
}

/// <summary>
/// �־��� ��带 �������� ���������� ȸ���Ѵ�.
/// </summary>
/// <param name="node">���� ���</param>
void RedBlackTree::RotateRight(RedBlackNode* node)
{
	RedBlackNode* x{ node->left };
	RedBlackNode* p{ node };
	RedBlackNode* p2{ p->parent };

	p->left = x->right;
	x->right->parent = p;
	x->right = p;
	p->parent = x;
	if (p2 != nullptr)
	{
		p2->right = x;
	}
	else
	{
		_root = x;
	}
	x->parent = p2;
}
#pragma endregion