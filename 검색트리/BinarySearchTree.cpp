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

/// <summary>
/// 주어진 노드를 부모로 하는 공백 노드를 반환한다.
/// </summary>
/// <param name="parent">부모 노드</param>
/// <returns>공백 노드</returns>
BinarySearchNode* BinarySearchNodeManager::GetEmptyNode(BinarySearchNode* parent)
{
	BinarySearchNode* emptyNode = Pop();
	emptyNode->parent = parent;
	emptyNode->isEmpty = true;

	return emptyNode;
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

	int maxDepth{ _root->GetMaxDepth() };
	int maxNodeCount{ static_cast<int>(std::pow(2, maxDepth - 1)) };
	int totalCount{ maxNodeCount * 2 + 1 };
	int lineWidth{ totalCount * BinarySearchNode::Width };

	for (int i = 1; i <= maxDepth; i++)
	{
		_numberMap[i] = "";
		_stickMap[i] = "";
	}

	_queue.push(_root);
	while (!_queue.empty())
	{
		BinarySearchNode* node{ _queue.front() };
		_queue.pop();

		PrintBinarySearchTree(node, lineWidth);

		if (!node->isEmpty)
		{
			if (node->left != nullptr)
			{
				_queue.push(node->left);
			}
			else
			{
				BinarySearchNode* emptyNode{ _nodeManager.GetEmptyNode(node) };
				emptyNode->left = node;
				_queue.push(emptyNode);
			}

			if (node->right != nullptr)
			{
				_queue.push(node->right);
			}
			else
			{
				BinarySearchNode* emptyNode{ _nodeManager.GetEmptyNode(node) };
				emptyNode->right = node;
				_queue.push(emptyNode);
			}
		}
		
		if (node->isEmpty)
		{
			_nodeManager.Push(node);
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
void BinarySearchTree::PrintBinarySearchTree(BinarySearchNode* node, int lineWidth)
{
	int curDepth{ node->GetCurDepth() };
	int curNodeCount{ static_cast<int>(std::pow(2, curDepth - 1)) };
	int totalNodeSize{ curNodeCount * BinarySearchNode::Width };
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
string BinarySearchTree::GetNodeStick(BinarySearchNode* node, int blankSize)
{
	if (node == _root)
	{
		return "";
	}

	int halfNodeWidth{ BinarySearchNode::Width / 2 };
	int halfBlankSize{ blankSize / 2 };

	string result;
	if ((node->isEmpty && node->left != nullptr) || IsLeftNode(node))
	{
		int leftSpaceCnt{ blankSize + halfNodeWidth
			- (BinarySearchNode::Width % 2 == 0 ? 1 : 0) };
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
#pragma endregion