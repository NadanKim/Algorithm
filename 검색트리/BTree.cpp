#include "BTree.h"

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
		for (int i = 0; i < BTreeNode::TotalKeyCount; i++)
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
				int nextKeyIdx{ i + 1 };
				if (nextKeyIdx < BTreeNode::TotalKeyCount && node->keys[i + 1].isSet)
				{
					if (data < node->keys[i + 1].value)
					{
						node = node->keys[i].right;
						break;
					}
				}
				else
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
}
#pragma endregion