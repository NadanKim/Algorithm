#include "BTree.h"

#pragma region 노드
/// <summary>
/// 노드의 키를 초기화한다.
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
/// 주어진 값을 키에 저장한다.
/// </summary>
/// <param name="data">저장할 값</param>
void BTreeNodeKey::Set(int data)
{
	value = data;
}

/// <summary>
/// B 트리 소멸자, 생성했던 키를 제거한다.
/// </summary>
BTreeNode::~BTreeNode()
{
	Clear();
}

/// <summary>
/// 노드를 초기화한다.
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

#pragma region 노드 매니저
/// <summary>
/// 노드 매니저 및 키 매니저를 초기화한다.
/// </summary>
BTreeNodeManager::BTreeNodeManager()
{
	BTreeNode::keyManager = new BTreeNodeKeyManager();
}

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

	delete BTreeNode::keyManager;
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

/// <summary>
/// 가지고 있던 키를 모두 안전하게 제거한다.
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
/// 사용 완료한 키를 반환한다.
/// </summary>
/// <param name="node">사용 완료한 키</param>
void BTreeNodeKeyManager::Push(BTreeNodeKey* node)
{
	node->next = nodes;
	nodes = node;
}

/// <summary>
/// 사용할 키를 인출한다.
/// </summary>
/// <returns>사용할 키</returns>
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

#pragma region B 트리
/// <summary>
/// B 트리가 제거될 때 사용한 모든 노드를 반환한다.
/// </summary>
BTree::~BTree()
{
}

/// <summary>
/// B 트리를 확인하여 주어진 값이 트리에 존재하는지 여부를 반환한다.
/// </summary>
/// <param name="data">확인할 값</param>
/// <returns>존재 여부</returns>
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
///// 주어진 값을 B 트리에 삽입한다.
///// </summary>
///// <param name="data">삽입할 값</param>
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
///// 주어진 값을 B 트리에 삽입한다.
///// </summary>
///// <param name="parent">삽입할 노드</param>
///// <param name="data">삽입할 값</param>
//void BTree::Insert(BTreeNode* parent, int data)
//{
//	// 루트가 빈 값이었던 경우
//	if (parent == nullptr)
//	{
//		BTreeNode* node{ _nodeManager.Pop() };
//		node->Insert(data);
//		_root = node;
//	}
//	// 노드에 키 삽입 실패한 경우
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
//			// 기존 노드(parent)에 대해 오버플로우 처리 진행
//		}
//	}
//}
//
//void BTree::ClearOverflow(BTreeNode* node, int data)
//{
//
//}
#pragma endregion