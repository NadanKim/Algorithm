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

/// <summary>
/// �־��� ��带 �θ�� �ϴ� ���� ��带 ��ȯ�Ѵ�.
/// </summary>
/// <param name="parent">�θ� ���</param>
/// <returns>���� ���</returns>
RedBlackNode* RedBlackNodeManager ::GetEmptyNode(RedBlackNode* parent)
{
	RedBlackNode* emptyNode = Pop();
	emptyNode->parent = parent;
	emptyNode->isEmpty = true;

	return emptyNode;
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
	if (_root == nullptr)
	{
		return false;
	}

	RedBlackNode* node{ _root };

	while (node != _nil)
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
	return *GetNode(data);
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

	AdjustDeletedNode(Delete(GetNode(data)));
}

/// <summary>
/// Ʈ���� ����Ѵ�.
/// </summary>
void RedBlackTree::PrintTree()
{
	if (_root == nullptr)
	{
		std::cout << "EMPTY\n";
		return;
	}

	int maxDepth{ _root->GetMaxDepth() };
	int maxNodeCount{ static_cast<int>(std::pow(2, maxDepth - 1)) };
	int totalCount{ maxNodeCount * 2 + 1 };
	int lineWidth{ totalCount * RedBlackNode::Width };

	for (int i = 1; i <= maxDepth; i++)
	{
		_numberMap[i] = "";
		_stickMap[i] = "";
	}

	_queue.push(_root);
	while (!_queue.empty())
	{
		RedBlackNode* node{ _queue.front() };
		_queue.pop();

		PrintTree(node, lineWidth);

		if (!node->isEmpty)
		{
			if (node->left != _nil)
			{
				_queue.push(node->left);
			}
			else
			{
				RedBlackNode* emptyNode{ _nodeManager->GetEmptyNode(node) };
				emptyNode->left = node;
				_queue.push(emptyNode);
			}

			if (node->right != _nil)
			{
				_queue.push(node->right);
			}
			else
			{
				RedBlackNode* emptyNode{ _nodeManager->GetEmptyNode(node) };
				emptyNode->right = node;
				_queue.push(emptyNode);
			}
		}

		if (node->isEmpty)
		{
			_nodeManager->Push(node);
		}
	}

	for (int i = 1; i <= maxDepth; i++)
	{
		std::cout << _stickMap[i] << '\n';
		std::cout << _numberMap[i] << '\n';
	}
	std::cout << "\n\n";
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
		if (parent->left == _nil)
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
		if (parent->right == _nil)
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

/// <summary>
/// Ʈ���� ����Ѵ�.
/// </summary>
/// <param name="node">���� ����� ���</param>
void RedBlackTree::PrintTree(RedBlackNode* node, int lineWidth)
{
	int curDepth{ node->GetCurDepth() };
	int curNodeCount{ static_cast<int>(std::pow(2, curDepth - 1)) };
	int totalNodeSize{ curNodeCount * RedBlackNode::Width };
	int blankCount{ curNodeCount + 1 };
	int totalBlankSize{ lineWidth - totalNodeSize };
	int blankSize{ totalBlankSize / blankCount };

	string& numberStr{ _numberMap[curDepth] };
	numberStr.append(string(blankSize, ' '));
	numberStr.append(node->ToString());

	string& stickStr{ _stickMap[curDepth] };
	stickStr.append(GetNodeStick(node, blankSize));
}

/// <summary>
/// �־��� ��忡 �´� ���븦 ����� ��ȯ�Ѵ�.
/// </summary>
/// <param name="node">ó���� ���</param>
/// <returns>���� ��� ���ڿ�</returns>
string RedBlackTree::GetNodeStick(RedBlackNode* node, int blankSize)
{
	if (node == _root)
	{
		return "";
	}

	int halfNodeWidth{ RedBlackNode::Width / 2 };
	int halfBlankSize{ blankSize / 2 };

	string result;
	if ((node->isEmpty && node->left != nullptr) || IsLeftNode(node))
	{
		int leftSpaceCnt{ blankSize + halfNodeWidth
			- (RedBlackNode::Width % 2 == 0 ? 1 : 0) };
		result.append(string(leftSpaceCnt, ' '));
		result.append(node->isEmpty ? " " : "��");
		int rightHypenCnt{ halfBlankSize + halfNodeWidth - 1 };
		for (int i = 0; i < rightHypenCnt; i++)
		{
			result.append(node->isEmpty ? " " : "��");
		}
		result.append(node->isEmpty ? " " : "��");
	}
	else
	{
		result.append(node->isEmpty ? " " : "��");
		int leftHypenCnt{ halfBlankSize + halfNodeWidth - 1 };
		for (int i = 0; i < leftHypenCnt; i++)
		{
			result.append(node->isEmpty ? " " : "��");
		}
		result.append(node->isEmpty ? " " : "��");
		result.append(string(halfNodeWidth, ' '));
	}

	return result;
}

/// <summary>
/// �־��� ���� ���� ����� �����͸� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">ã������ ��</param>
/// <returns>����� ������</returns>
RedBlackNode* RedBlackTree::GetNode(int data)
{
	if (_root == nullptr)
	{
		return nullptr;
	}

	RedBlackNode* node{ _root };

	while (node != _nil)
	{
		if (node->data == data)
		{
			return node;
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

	return nullptr;
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

/// <summary>
/// Ʈ���� �ִ� ���̸� ��ȯ�Ѵ�.
/// </summary>
/// <returns>Ʈ���� �ִ� ����</returns>
int RedBlackTree::GetTreeMaxDepth()
{
	return _root != nullptr ? _root->GetMaxDepth() : 0;
}
#pragma endregion