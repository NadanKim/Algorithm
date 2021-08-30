#include "AVLTree.h"

#pragma region 노드 매니저
/// <summary>
/// 종료 전 생성하 노드 제거
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
/// 사용 완료한 노드를 매니저에 저장
/// </summary>
/// <param name="node">사용후 반환할 노드</param>
void AVLNodeManager::Push(AVLNode* node)
{
	node->left = nodes;
	nodes = node;
}

/// <summary>
/// 노드가 필요한 경우 매니저에서 반환
/// </summary>
/// <returns>사용할 수 있는 노드</returns>
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

#pragma region AVL트리
/// <summary>
/// 종료 전 남은 노드 제거 처리
/// </summary>
AVLTree::~AVLTree()
{
	while (_root != nullptr)
	{
		Delete(_root);
	}
}

/// <summary>
/// AVL 트리에서 특정 값을 가지는 노드가 존재하는지 여부 확인
/// </summary>
/// <param name="data">찾을 값</param>
/// <returns>존재 여부</returns>
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
/// AVL 트리에서 주어진 값을 가진 노드를 반환
/// </summary>
/// <param name="data">찾을 값</param>
/// <returns>값을 가진 노드, 없으면 nullptr</returns>
const AVLNode& AVLTree::Search(int data)
{
	return *GetNode(data);
}

/// <summary>
/// AVL 트리에 값을 가지는 노드를 삽입
/// </summary>
/// <param name="data">삽입할 값</param>
void AVLTree::Insert(int data)
{
	if (Exists(data))
	{
		return;
	}

	Insert(_root, data);
	CalculateBalaceFactor(_root);
}

/// <summary>
/// AVL 트리에서 해당 값을 가지는 노드를 제거
/// </summary>
/// <param name="data">제거할 값</param>
void AVLTree::Delete(int data)
{
	if (!Exists(data))
	{
		return;
	}

	Delete(GetNode(data));
	CalculateBalaceFactor(_root);
}

/// <summary>
/// AVL 트리 삽입 처리
/// </summary>
/// <param name="parent">삽입해야 할 노드의 부모</param>
/// <param name="data">삽입할 값</param>
void AVLTree::Insert(AVLNode* parent, int data)
{
	if (parent == nullptr)
	{
		AVLNode* node{ _nodeManager.Pop() };
		node->data = data;
		_root = node;
	}
	else if (parent->data > data)
	{
		if (parent->left == nullptr)
		{
			AVLNode* node{ _nodeManager.Pop() };
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
			AVLNode* node{ _nodeManager.Pop() };
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
/// AVL 트리 제거 처리
/// </summary>
/// <param name="node">제거할 노드</param>
void AVLTree::Delete(AVLNode* node)
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
}

/// <summary>
/// 주어진 값을 가진 노드의 포인터를 반환한다.
/// </summary>
/// <param name="data">찾으려는 값</param>
/// <returns>노드의 포인터</returns>
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
/// 해당 노드가 부모 노드의 왼쪽 자식인지 여부
/// </summary>
/// <param name="node">확인할 노드</param>
/// <returns>왼쪽 자식인지 여부</returns>
bool AVLTree::IsLeftNode(AVLNode* node)
{
	return node->parent != nullptr && node->parent->left == node;
}

/// <summary>
/// 해당 노드가 부모 노드의 오른쪽 자식인지 여부
/// </summary>
/// <param name="node">확인할 노드</param>
/// <returns>오른쪽 자식인지 여부</returns>
bool AVLTree::IsRightNode(AVLNode* node)
{
	return node->parent != nullptr && node->parent->right == node;
}

/// <summary>
/// 주어진 노드를 기준으로 왼쪽으로 회전한다.
/// </summary>
/// <param name="node">기준 노드</param>
AVLNode* AVLTree::RotateLeft(AVLNode* node)
{
	AVLNode* x{ node };
	AVLNode* c{ x->right };

	c->left = x;
	c->parent = x->parent;
	x->parent = c;
	x->right = nullptr;

	return c;
}

/// <summary>
/// 주어진 노드를 기준으로 오른쪽으로 회전한다.
/// </summary>
/// <param name="node">기준 노드</param>
AVLNode* AVLTree::RotateRight(AVLNode* node)
{
	AVLNode* x{ node };
	AVLNode* c{ x->left };

	c->right = x;
	c->parent = x->parent;
	x->parent = c;
	x->left = nullptr;

	return c;
}

/// <summary>
/// 주어진 노드의 BF를 구하여 반환한다.
/// </summary>
/// <param name="node">타겟 노드</param>
int AVLTree::CalculateBalaceFactor(AVLNode* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	CalculateBalaceFactor(node->left);
	CalculateBalaceFactor(node->right);

	node->bf = GetNodeDepth(node->left) - GetNodeDepth(node->right);

	// 밸런스가 무너진 경우
	if (node->HasBalanceProblem())
	{
		AVLNode* x{ node };
		AVLNode* c{ x->left != nullptr ? x->left : x->right };
		AVLNode* c2{ c->left != nullptr ? c->left : c->right };

		if (IsLLCase(c, c2))
		{
			node = RotateRight(x);
		}
		else if (IsRRCase(c, c2))
		{
			node = RotateLeft(x);
		}
		else if (IsLRCase(c, c2))
		{
			RotateRight(c);
			node = RotateLeft(x);
		}
		else if (IsRLCase(c, c2))
		{
			RotateLeft(c);
			node = RotateRight(x);
		}

		node->bf = GetNodeDepth(node->left) - GetNodeDepth(node->right);
	}

	return node->bf + (node != _root ? 1 : 0);
}

/// <summary>
/// 주어진 노드의 깊이를 구하여 반환한다.
/// </summary>
/// <param name="node">시작 노드</param>
/// <returns>시작 노드의 최대 깊이</returns>
int AVLTree::GetNodeDepth(AVLNode* node, int depth)
{
	if (node == nullptr)
	{
		return depth;
	}

	int leftDepth{ GetNodeDepth(node->left, depth + 1) };
	int rightDepth{ GetNodeDepth(node->right, depth + 1) };

	return (leftDepth > rightDepth ? leftDepth : rightDepth);
}

/// <summary>
/// 주어진 노드의 배치가 LL케이스인지 여부를 반환한다.
/// </summary>
/// <param name="c">문제 노드의 자식</param>
/// <param name="c2">c의 자식</param>
/// <returns>LL케이스인지 여부</returns>
bool AVLTree::IsLLCase(AVLNode* c, AVLNode* c2)
{
	if (IsLeftNode(c) && IsLeftNode(c2))
	{
		return true;
	}
	return false;
}

/// <summary>
/// 주어진 노드의 배치가 RR케이스인지 여부를 반환한다.
/// </summary>
/// <param name="c">문제 노드의 자식</param>
/// <param name="c2">c의 자식</param>
/// <returns>RR케이스인지 여부</returns>
bool AVLTree::IsRRCase(AVLNode* c, AVLNode* c2)
{
	if (IsRightNode(c) && IsRightNode(c2))
	{
		return true;
	}
	return false;
}

/// <summary>
/// 주어진 노드의 배치가 LR케이스인지 여부를 반환한다.
/// </summary>
/// <param name="c">문제 노드의 자식</param>
/// <param name="c2">c의 자식</param>
/// <returns>LR케이스인지 여부</returns>
bool AVLTree::IsLRCase(AVLNode* c, AVLNode* c2)
{
	if (IsLeftNode(c) && IsRightNode(c2))
	{
		return true;
	}
	return false;
}

/// <summary>
/// 주어진 노드의 배치가 RL케이스인지 여부를 반환한다.
/// </summary>
/// <param name="c">문제 노드의 자식</param>
/// <param name="c2">c의 자식</param>
/// <returns>RL케이스인지 여부</returns>
bool AVLTree::IsRLCase(AVLNode* c, AVLNode* c2)
{
	if (IsRightNode(c) && IsLeftNode(c2))
	{
		return true;
	}
	return false;
}
#pragma endregion