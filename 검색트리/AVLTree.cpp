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

/// <summary>
/// �־��� ��带 �θ�� �ϴ� ���� ��带 ��ȯ�Ѵ�.
/// </summary>
/// <param name="parent">�θ� ���</param>
/// <returns>���� ���</returns>
AVLNode* AVLNodeManager::GetEmptyNode(AVLNode* parent)
{
	AVLNode* emptyNode = Pop();
	emptyNode->parent = parent;
	emptyNode->isEmpty = true;

	return emptyNode;
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

	Insert(_root, data);
	CalculateBalaceFactor(_root);
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

	Delete(GetNode(data));
	CalculateBalaceFactor(_root);
}

/// <summary>
/// ���� �˻� Ʈ���� ����Ѵ�.
/// </summary>
void AVLTree::PrintTree()
{
	if (_root == nullptr)
	{
		std::cout << "EMPTY\n";
		return;
	}

	int maxDepth{ _root->GetMaxDepth() };
	int maxNodeCount{ static_cast<int>(std::pow(2, maxDepth - 1)) };
	int totalCount{ maxNodeCount * 2 + 1 };
	int lineWidth{ totalCount * AVLNode::Width };

	for (int i = 1; i <= maxDepth; i++)
	{
		_numberMap[i] = "";
		_stickMap[i] = "";
	}

	_queue.push(_root);
	while (!_queue.empty())
	{
		AVLNode* node{ _queue.front() };
		_queue.pop();

		PrintTree(node, lineWidth);

		if (!node->isEmpty)
		{
			if (node->left != nullptr)
			{
				_queue.push(node->left);
			}
			else
			{
				AVLNode* emptyNode{ _nodeManager.GetEmptyNode(node) };
				emptyNode->left = node;
				_queue.push(emptyNode);
			}

			if (node->right != nullptr)
			{
				_queue.push(node->right);
			}
			else
			{
				AVLNode* emptyNode{ _nodeManager.GetEmptyNode(node) };
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
/// AVL Ʈ�� ���� ó��
/// </summary>
/// <param name="parent">�����ؾ� �� ����� �θ�</param>
/// <param name="data">������ ��</param>
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
/// AVL Ʈ�� ���� ó��
/// </summary>
/// <param name="node">������ ���</param>
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
/// Ʈ���� ����Ѵ�.
/// </summary>
/// <param name="node">���� ����� ���</param>
void AVLTree::PrintTree(AVLNode* node, int lineWidth)
{
	int curDepth{ node->GetCurDepth() };
	int curNodeCount{ static_cast<int>(std::pow(2, curDepth - 1)) };
	int totalNodeSize{ curNodeCount * AVLNode::Width };
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
string AVLTree::GetNodeStick(AVLNode* node, int blankSize)
{
	if (node == _root)
	{
		return "";
	}

	int halfNodeWidth{ AVLNode::Width / 2 };
	int halfBlankSize{ blankSize / 2 };

	string result;
	if ((node->isEmpty && node->left != nullptr) || IsLeftNode(node))
	{
		int leftSpaceCnt{ blankSize + halfNodeWidth
			- (AVLNode::Width % 2 == 0 ? 1 : 0) };
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

/// <summary>
/// �־��� ��带 �������� �������� ȸ���Ѵ�.
/// </summary>
/// <param name="node">���� ���</param>
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
/// �־��� ��带 �������� ���������� ȸ���Ѵ�.
/// </summary>
/// <param name="node">���� ���</param>
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
/// �־��� ����� BF�� ���Ͽ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="node">Ÿ�� ���</param>
int AVLTree::CalculateBalaceFactor(AVLNode* node)
{
	if (node == nullptr)
	{
		return 0;
	}

	CalculateBalaceFactor(node->left);
	CalculateBalaceFactor(node->right);

	node->bf = GetNodeDepth(node->left) - GetNodeDepth(node->right);

	// �뷱���� ������ ���
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
/// �־��� ����� ���̸� ���Ͽ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="node">���� ���</param>
/// <returns>���� ����� �ִ� ����</returns>
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
/// �־��� ����� ��ġ�� LL���̽����� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="c">���� ����� �ڽ�</param>
/// <param name="c2">c�� �ڽ�</param>
/// <returns>LL���̽����� ����</returns>
bool AVLTree::IsLLCase(AVLNode* c, AVLNode* c2)
{
	if (IsLeftNode(c) && IsLeftNode(c2))
	{
		return true;
	}
	return false;
}

/// <summary>
/// �־��� ����� ��ġ�� RR���̽����� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="c">���� ����� �ڽ�</param>
/// <param name="c2">c�� �ڽ�</param>
/// <returns>RR���̽����� ����</returns>
bool AVLTree::IsRRCase(AVLNode* c, AVLNode* c2)
{
	if (IsRightNode(c) && IsRightNode(c2))
	{
		return true;
	}
	return false;
}

/// <summary>
/// �־��� ����� ��ġ�� LR���̽����� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="c">���� ����� �ڽ�</param>
/// <param name="c2">c�� �ڽ�</param>
/// <returns>LR���̽����� ����</returns>
bool AVLTree::IsLRCase(AVLNode* c, AVLNode* c2)
{
	if (IsLeftNode(c) && IsRightNode(c2))
	{
		return true;
	}
	return false;
}

/// <summary>
/// �־��� ����� ��ġ�� RL���̽����� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="c">���� ����� �ڽ�</param>
/// <param name="c2">c�� �ڽ�</param>
/// <returns>RL���̽����� ����</returns>
bool AVLTree::IsRLCase(AVLNode* c, AVLNode* c2)
{
	if (IsRightNode(c) && IsLeftNode(c2))
	{
		return true;
	}
	return false;
}
#pragma endregion