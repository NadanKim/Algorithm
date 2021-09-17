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

/// <summary>
/// �־��� ��带 �θ�� �ϴ� ���� ��带 ��ȯ�Ѵ�.
/// </summary>
/// <param name="parent">�θ� ���</param>
/// <returns>���� ���</returns>
BinarySearchNode* BinarySearchNodeManager::GetEmptyNode(BinarySearchNode* parent)
{
	BinarySearchNode* emptyNode = Pop();
	emptyNode->parent = parent;
	emptyNode->isEmpty = true;

	return emptyNode;
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
/// �־��� ��忡 �´� ���븦 ����� ��ȯ�Ѵ�.
/// </summary>
/// <param name="node">ó���� ���</param>
/// <returns>���� ��� ���ڿ�</returns>
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
#pragma endregion