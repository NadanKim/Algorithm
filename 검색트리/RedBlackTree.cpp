#include "RedBlackTree.h"

#pragma region 노드 매니저
/// <summary>
/// 레드 블랙 노드의 매니저에 nil 노드 등록
/// </summary>
/// <param name="nil">nil 노드</param>
RedBlackNodeManager::RedBlackNodeManager(RedBlackNode* nil)
	: _nil(nil), _nodes(nullptr)
{
}

/// <summary>
/// 종료 전 생성하 노드 제거
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
/// 사용 완료한 노드를 매니저에 저장
/// </summary>
/// <param name="node">사용후 반환할 노드</param>
void RedBlackNodeManager::Push(RedBlackNode* node)
{
	node->left = _nodes;
	_nodes = node;
}

/// <summary>
/// 노드가 필요한 경우 매니저에서 반환
/// </summary>
/// <returns>사용할 수 있는 노드</returns>
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

#pragma region 레드 블랙 트리
/// <summary>
/// 레드 블랙 트리에 필요한 정보 세팅
/// </summary>
RedBlackTree::RedBlackTree()
	: _root(nullptr)
{
	_nil = new RedBlackNode();
	_nil->color = NodeColor::Black;

	_nodeManager = new RedBlackNodeManager(_nil);
}

/// <summary>
/// 종료 전 남은 노드 제거 처리
/// </summary>
RedBlackTree::~RedBlackTree()
{
	while (_root != nullptr)
	{
		Delete(_root);
	}
}

/// <summary>
/// 레드 블랙 트리에서 특정 값을 가지는 노드가 존재하는지 여부 확인
/// </summary>
/// <param name="data">찾을 값</param>
/// <returns>존재 여부</returns>
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
/// 레드 블랙 트리에서 주어진 값을 가진 노드를 반환
/// </summary>
/// <param name="data">찾을 값</param>
/// <returns>값을 가진 노드, 없으면 nullptr</returns>
const RedBlackNode& RedBlackTree::Search(int data)
{
	return GetNode(data);
}

/// <summary>
/// 레드 블랙 트리에 값을 가지는 노드를 삽입
/// </summary>
/// <param name="data">삽입할 값</param>
void RedBlackTree::Insert(int data)
{
	if (Exists(data))
	{
		return;
	}

	AdjustInsertedNode(Insert(_root, data));
}

/// <summary>
/// 레드 블랙 트리에서 해당 값을 가지는 노드를 제거
/// </summary>
/// <param name="data">제거할 값</param>
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
/// 레드 블랙 트리 삽입 처리
/// </summary>
/// <param name="parent">삽입해야 할 노드의 부모</param>
/// <param name="data">삽입할 값</param>
/// <returns>새로 삽입한 노드</returns>
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
/// 레드 블랙 트리에 삽인한 노드를 규칙에 맞게 정렬한다.
/// </summary>
/// <param name="node">문제가 되는 노드</param>
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
/// 레드 블랙 트리 제거 처리
/// </summary>
/// <param name="node">제거할 노드</param>
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
/// 해당 노드가 부모 노드의 왼쪽 자식인지 여부
/// </summary>
/// <param name="node">확인할 노드</param>
/// <returns>왼쪽 자식인지 여부</returns>
bool RedBlackTree::IsLeftNode(RedBlackNode* node)
{
	return node->parent != nullptr && node->parent->left == node;
}

/// <summary>
/// 해당 노드가 부모 노드의 오른쪽 자식인지 여부
/// </summary>
/// <param name="node">확인할 노드</param>
/// <returns>오른쪽 자식인지 여부</returns>
bool RedBlackTree::IsRightNode(RedBlackNode* node)
{
	return node->parent != nullptr && node->parent->right == node;
}

/// <summary>
/// 주어진 노드를 기준으로 왼쪽으로 회전한다.
/// </summary>
/// <param name="node">기준 노드</param>
void RedBlackTree::RotateLeft(RedBlackNode* node)
{
	RedBlackNode* x{ node->right };
	RedBlackNode* p{ node };
	RedBlackNode* p2{ p->parent };

	p->right = x->left;
	x->left = p;
	p2->left = x;
}

/// <summary>
/// 주어진 노드를 기준으로 오른쪽으로 회전한다.
/// </summary>
/// <param name="node">기준 노드</param>
void RedBlackTree::RotateRight(RedBlackNode* node)
{
	RedBlackNode* x{ node->left };
	RedBlackNode* p{ node };
	RedBlackNode* p2{ p->parent };

	p->left = x->right;
	x->right = p;
	p2->right = x;
}
#pragma endregion