#include "BTree.h"

#pragma region ���
/// <summary>
/// ����� Ű�� �ʱ�ȭ�Ѵ�.
/// </summary>
void BTreeNodeKey::Clear()
{
	left = nullptr;
	value = 0;
	right = nullptr;
}

/// <summary>
/// �־��� ���� Ű�� �����Ѵ�.
/// </summary>
/// <param name="data">������ ��</param>
void BTreeNodeKey::Set(int data)
{
	value = data;
}

/// <summary>
/// B Ʈ�� ��� ������, key�� ������ ������ŭ �����Ѵ�.
/// </summary>
BTreeNode::BTreeNode()
	: parent(nullptr), size(0)
{
	keys = new BTreeNodeKey[TotalKeyCount];
}

/// <summary>
/// B Ʈ�� �Ҹ���, �����ߴ� Ű�� �����Ѵ�.
/// </summary>
BTreeNode::~BTreeNode()
{
	delete[] keys;
}

/// <summary>
/// ��带 �ʱ�ȭ�Ѵ�.
/// </summary>
void BTreeNode::Clear()
{
	parent = nullptr;
	for (int i = 0; i < TotalKeyCount; i++)
	{
		keys[i].Clear();
	}
}

/// <summary>
/// ��忡 ���� ������ �� ������ �����ϰ� true�� ��ȯ�ϰ� �ƴϸ� false�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data"></param>
/// <returns>���� ����</returns>
bool BTreeNode::Insert(int data)
{
	if (TotalKeyCount <= size)
	{
		return false;
	}

	keys[size++].Set(data);

	return true;
}

/// <summary>
/// ���� ó���� ���� ������ ��带 ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">�߰��� ��</param>
/// <returns>������ ���</returns>
BTreeNode* BTreeNode::GetProperNodeToInsert(int data)
{
	for (int i = 0; i < size; i++)
	{
		if (data < keys[i].value)
		{
			return keys[i].left;
		}

		if (keys[i].value < data)
		{
			if (i == size)
			{
				return keys[i].right;
			}
			else if (data < keys[i + 1].value)
			{
				return keys[i].right;
			}
		}
	}
	return nullptr;
}
#pragma endregion

#pragma region ��� �Ŵ���
/// <summary>
/// ������ �ִ� ��带 ��� �����ϰ� �����Ѵ�.
/// </summary>
BTreeNodeManager::~BTreeNodeManager()
{
	while (nodes != nullptr)
	{
		BTreeNode* node{ nodes };
		nodes = nodes->parent;
		delete node;
	}
}

/// <summary>
/// ��� �Ϸ��� ��带 �����Ѵ�.
/// </summary>
/// <param name="node">��� �Ϸ��� ���</param>
void BTreeNodeManager::Push(BTreeNode* node)
{
	node->parent = nodes;
	nodes = node;
}

/// <summary>
/// ����� ��带 �����Ѵ�.
/// </summary>
/// <returns>����� ���</returns>
BTreeNode* BTreeNodeManager::Pop()
{
	BTreeNode* node{ nodes };

	if (node != nullptr)
	{
		nodes = node->parent;
		node->Clear();
	}
	else
	{
		node = new BTreeNode();
	}

	return node;
}
#pragma endregion

#pragma region B Ʈ��
/// <summary>
/// B Ʈ���� ���ŵ� �� ����� ��� ��带 ��ȯ�Ѵ�.
/// </summary>
BTree::~BTree()
{
}

/// <summary>
/// B Ʈ���� Ȯ���Ͽ� �־��� ���� Ʈ���� �����ϴ��� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">Ȯ���� ��</param>
/// <returns>���� ����</returns>
bool BTree::Exists(int data)
{
	BTreeNode* node{ _root };
	while (node != nullptr)
	{
		for (int i = 0; i < node->size; i++)
		{
			if (node->keys[i].value == data)
			{
				return true;
			}

			if (data < node->keys[i].value)
			{
				node = node->keys[i].left;
				break;
			}

			if (node->keys[i].value < data)
			{
				if (i == node->size)
				{
					node = node->keys[i].right;
					break;
				}
				else if(data < node->keys[i + 1].value)
				{
					node = node->keys[i].right;
					break;
				}
			}
		}
	}
	
	return false;
}

/// <summary>
/// �־��� ���� B Ʈ���� �����Ѵ�.
/// </summary>
/// <param name="data">������ ��</param>
void BTree::Insert(int data)
{
	if (Exists(data))
	{
		return;
	}

	Insert(_root, data);
}

/// <summary>
/// �־��� ���� B Ʈ���� �����Ѵ�.
/// </summary>
/// <param name="parent">������ ���</param>
/// <param name="data">������ ��</param>
void BTree::Insert(BTreeNode* parent, int data)
{
	// ��Ʈ�� �� ���̾��� ���
	if (parent == nullptr)
	{
		BTreeNode* node{ _nodeManager.Pop() };
		node->Insert(data);
		_root = node;
	}
	// ��忡 Ű ���� ������ ���
	else if (!parent->Insert(data))
	{
		BTreeNode* node = parent->GetProperNodeToInsert(data);
		if (node != nullptr)
		{
			Insert(node, data);
		}
		else
		{
			// ���� ���(parent)�� ���� �����÷ο� ó�� ����
		}
	}
}
#pragma endregion