#include "BTree.h"

#pragma region ���
/// <summary>
/// ����� Ű�� �ʱ�ȭ�Ѵ�.
/// </summary>
void BTreeNodeKey::Clear()
{
	prev = nullptr;
	left = nullptr;
	value = 0;
	right = nullptr;
	next = nullptr;
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
/// B Ʈ�� �Ҹ���, �����ߴ� Ű�� �����Ѵ�.
/// </summary>
BTreeNode::~BTreeNode()
{
	Clear();
}

/// <summary>
/// ��带 �ʱ�ȭ�Ѵ�.
/// </summary>
void BTreeNode::Clear()
{
	parent = nullptr;
	size = 0;

	while (keyRoot != nullptr)
	{
		BTreeNodeKey* key{ keyRoot };
		keyRoot = key->next;
		key->Clear();
		keyManager->Push(key);
	}
}
#pragma endregion

#pragma region ��� �Ŵ���
/// <summary>
/// ��� �Ŵ��� �� Ű �Ŵ����� �ʱ�ȭ�Ѵ�.
/// </summary>
BTreeNodeManager::BTreeNodeManager()
{
	BTreeNode::keyManager = new BTreeNodeKeyManager();
}

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

	delete BTreeNode::keyManager;
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

/// <summary>
/// ������ �ִ� Ű�� ��� �����ϰ� �����Ѵ�.
/// </summary>
BTreeNodeKeyManager::~BTreeNodeKeyManager()
{
	while (nodes != nullptr)
	{
		BTreeNodeKey* node{ nodes };
		nodes = nodes->next;
		delete node;
	}
}

/// <summary>
/// ��� �Ϸ��� Ű�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="node">��� �Ϸ��� Ű</param>
void BTreeNodeKeyManager::Push(BTreeNodeKey* node)
{
	node->next = nodes;
	nodes = node;
}

/// <summary>
/// ����� Ű�� �����Ѵ�.
/// </summary>
/// <returns>����� Ű</returns>
BTreeNodeKey* BTreeNodeKeyManager::Pop()
{
	BTreeNodeKey* node{ nodes };

	if (node != nullptr)
	{
		nodes = node->next;
		node->Clear();
	}
	else
	{
		node = new BTreeNodeKey();
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
		BTreeNodeKey* key{ node->keyRoot };
		while (key != nullptr)
		{
			if (key->value == data)
			{
				return true;
			}

			if (data < key->value)
			{
				node = key->left;
				break;
			}
			else if (key->value < data)
			{
				if (key->next == nullptr || data < key->next->value)
				{
					node = key->right;
					break;
				}
			}
			
			key = key->next;
		}
	}
	
	return false;
}

///// <summary>
///// �־��� ���� B Ʈ���� �����Ѵ�.
///// </summary>
///// <param name="data">������ ��</param>
//void BTree::Insert(int data)
//{
//	if (Exists(data))
//	{
//		return;
//	}
//
//	Insert(_root, data);
//}
//
///// <summary>
///// �־��� ���� B Ʈ���� �����Ѵ�.
///// </summary>
///// <param name="parent">������ ���</param>
///// <param name="data">������ ��</param>
//void BTree::Insert(BTreeNode* parent, int data)
//{
//	// ��Ʈ�� �� ���̾��� ���
//	if (parent == nullptr)
//	{
//		BTreeNode* node{ _nodeManager.Pop() };
//		node->Insert(data);
//		_root = node;
//	}
//	// ��忡 Ű ���� ������ ���
//	else if (!parent->Insert(data))
//	{
//		BTreeNode* node = parent->GetProperNodeToInsert(data);
//		if (node != nullptr)
//		{
//			Insert(node, data);
//		}
//		else
//		{
//
//			// ���� ���(parent)�� ���� �����÷ο� ó�� ����
//		}
//	}
//}
//
//void BTree::ClearOverflow(BTreeNode* node, int data)
//{
//
//}
#pragma endregion