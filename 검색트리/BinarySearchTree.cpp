#include "BinarySearchTree.h"

#pragma region 노드 매니저
/// <summary>
/// 종료 전 생성하 노드 제거
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
/// 사용 완료한 노드를 매니저에 저장
/// </summary>
/// <param name="node">사용후 반환할 노드</param>
void BinarySearchNodeManager::Push(BinarySearchNode* node)
{
	node->left = nodes;
	nodes = node;
}

/// <summary>
/// 노드가 필요한 경우 매니저에서 반환
/// </summary>
/// <returns>사용할 수 있는 노드</returns>
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

#pragma region 이진 검색 트리
/// <summary>
/// 종료 전 남은 노드 제거 처리
/// </summary>
BinarySearchTree::~BinarySearchTree()
{
	while (_root != nullptr)
	{
		Delete(_root);
	}
}

/// <summary>
/// 이진 검색 트리에서 특정 값을 가지는 노드가 존재하는지 여부 확인
/// </summary>
/// <param name="data">찾을 값</param>
/// <returns>존재 여부</returns>
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
/// 이진 검색 트리에서 주어진 값을 가진 노드를 반환
/// </summary>
/// <param name="data">찾을 값</param>
/// <returns>값을 가진 노드, 없으면 nullptr</returns>
const BinarySearchNode& BinarySearchTree::Search(int data)
{
	return *GetNode(data);
}

/// <summary>
/// 이진 검색 트리에 값을 가지는 노드를 삽입
/// </summary>
/// <param name="data">삽입할 값</param>
void BinarySearchTree::Insert(int data)
{
	if (Exists(data))
	{
		return;
	}

	Insert(_root, data);
}

/// <summary>
/// 이진 검색 트리에서 해당 값을 가지는 노드를 제거
/// </summary>
/// <param name="data">제거할 값</param>
void BinarySearchTree::Delete(int data)
{
	if (!Exists(data))
	{
		return;
	}

	Delete(GetNode(data));
}

/// <summary>
/// 이진 검색 트리를 출력한다.
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
/// 이진 검색 트리 삽입 처리
/// </summary>
/// <param name="parent">삽입해야 할 노드의 부모</param>
/// <param name="data">삽입할 값</param>
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
/// 이진 검색 트리 제거 처리
/// </summary>
/// <param name="node">제거할 노드</param>
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
/// 이진 검색 트리를 출력한다.
/// </summary>
/// <param name="node">현재 출력할 노드</param>
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
		std::cout << "┌";
		for (int i = 1; i < center; i++)
		{
			std::cout << "─";
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
		std::cout << "┴";
	}

	if (node->HasRightChild())
	{
		for (int i = 1; i < center; i++)
		{
			std::cout << "─";
		}
		std::cout << "┐";
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
/// 주어진 값을 가진 노드의 포인터를 반환한다.
/// </summary>
/// <param name="data">찾으려는 값</param>
/// <returns>노드의 포인터</returns>
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
/// 해당 노드가 부모 노드의 왼쪽 자식인지 여부
/// </summary>
/// <param name="node">확인할 노드</param>
/// <returns>왼쪽 자식인지 여부</returns>
bool BinarySearchTree::IsLeftNode(BinarySearchNode* node)
{
	return node->parent != nullptr && node->parent->left == node;
}

/// <summary>
/// 해당 노드가 부모 노드의 오른쪽 자식인지 여부
/// </summary>
/// <param name="node">확인할 노드</param>
/// <returns>오른쪽 자식인지 여부</returns>
bool BinarySearchTree::IsRightNode(BinarySearchNode* node)
{
	return node->parent != nullptr && node->parent->right == node;
}

/// <summary>
/// 트리의 최대 깊이를 반환한다.
/// </summary>
/// <returns>트리의 최대 깊이</returns>
int BinarySearchTree::GetTreeMaxDepth()
{
	return _root != nullptr ? _root->GetMaxDepth() : 0;
}
#pragma endregion