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