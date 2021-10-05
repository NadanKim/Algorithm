#include "BTree.h"

#pragma region 노드 매니저
/// <summary>
/// 가지고 있던 노드를 모두 안전하게 제거한다.
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
/// 사용 완료한 노드를 저장한다.
/// </summary>
/// <param name="node">사용 완료한 노드</param>
void BTreeNodeManager::Push(BTreeNode* node)
{
	node->parent = nodes;
	nodes = node;
}

/// <summary>
/// 사용할 노드를 인출한다.
/// </summary>
/// <returns>사용할 노드</returns>
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