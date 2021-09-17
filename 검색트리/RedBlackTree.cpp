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

/// <summary>
/// 주어진 노드를 부모로 하는 공백 노드를 반환한다.
/// </summary>
/// <param name="parent">부모 노드</param>
/// <returns>공백 노드</returns>
RedBlackNode* RedBlackNodeManager ::GetEmptyNode(RedBlackNode* parent)
{
	RedBlackNode* emptyNode = Pop();
	emptyNode->parent = parent;
	emptyNode->isEmpty = true;

	return emptyNode;
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
/// 레드 블랙 트리에서 주어진 값을 가진 노드를 반환
/// </summary>
/// <param name="data">찾을 값</param>
/// <returns>값을 가진 노드, 없으면 nullptr</returns>
const RedBlackNode& RedBlackTree::Search(int data)
{
	return *GetNode(data);
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

	AdjustDeletedNode(Delete(GetNode(data)));
}

/// <summary>
/// 트리를 출력한다.
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
/// 레드 블랙 트리에 삽입한 노드를 규칙에 맞게 정렬한다.
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
/// 레드 블랙 트리에서 노드를 제거한 뒤 규칙에 맞게 정렬한다.
/// </summary>
/// <param name="node">문제가 되는 노드</param>
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
/// 트리를 출력한다.
/// </summary>
/// <param name="node">현재 출력할 노드</param>
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
/// 주어진 노드에 맞는 막대를 만들어 반환한다.
/// </summary>
/// <param name="node">처리할 노드</param>
/// <returns>막대 노드 문자열</returns>
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
		result.append(node->isEmpty ? " " : "┌");
		int rightHypenCnt{ halfBlankSize + halfNodeWidth - 1 };
		for (int i = 0; i < rightHypenCnt; i++)
		{
			result.append(node->isEmpty ? " " : "─");
		}
		result.append(node->isEmpty ? " " : "┘");
	}
	else
	{
		result.append(node->isEmpty ? " " : "└");
		int leftHypenCnt{ halfBlankSize + halfNodeWidth - 1 };
		for (int i = 0; i < leftHypenCnt; i++)
		{
			result.append(node->isEmpty ? " " : "─");
		}
		result.append(node->isEmpty ? " " : "┐");
		result.append(string(halfNodeWidth, ' '));
	}

	return result;
}

/// <summary>
/// 주어진 값을 가진 노드의 포인터를 반환한다.
/// </summary>
/// <param name="data">찾으려는 값</param>
/// <returns>노드의 포인터</returns>
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
/// 주어진 노드를 기준으로 오른쪽으로 회전한다.
/// </summary>
/// <param name="node">기준 노드</param>
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
/// 트리의 최대 깊이를 반환한다.
/// </summary>
/// <returns>트리의 최대 깊이</returns>
int RedBlackTree::GetTreeMaxDepth()
{
	return _root != nullptr ? _root->GetMaxDepth() : 0;
}
#pragma endregion