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
/// 새 키를 기존 키의 왼쪽에 삽입한다.
/// </summary>
/// <param name="newKey">삽입할 키</param>
void BTreeNodeKey::AddKeyToPrev(BTreeNodeKey* newKey)
{
	BTreeNodeKey* prevKey{ prev };
	if (prevKey != nullptr)
	{
		prevKey->next = newKey;
		newKey->prev = prevKey;
	}
	newKey->next = this;
	prev = newKey;
}

/// <summary>
/// 새 키를 기존 키의 오른쪽에 삽입한다.
/// </summary>
/// <param name="newKey">삽입할 키</param>
void BTreeNodeKey::AddKeyToNext(BTreeNodeKey* newKey)
{
	BTreeNodeKey* nextKey{ next };
	if (nextKey != nullptr)
	{
		nextKey->prev = newKey;
		newKey->next = nextKey;
	}
	newKey->prev = this;
	next = newKey;
}

/// <summary>
/// 다른 키와 value를 교환한다.
/// </summary>
/// <param name="other">다른 키</param>
void BTreeNodeKey::SwapValue(BTreeNodeKey* other)
{
	int temp{ value };
	value = other->value;
	other->value = temp;
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

/// <summary>
/// 노드에 데이터를 삽입한다.
/// </summary>
/// <param name="data">삽입할 데이터</param>
/// <returns>성공 여부</returns>
bool BTreeNode::Insert(int data)
{
	BTreeNodeKey* newKey{ keyManager->Pop() };
	newKey->Set(data);

	return Insert(newKey);
}

/// <summary>
/// 주어진 키를 노드의 키에 삽입한다.
/// </summary>
/// <param name="key">삽입할 키</param>
/// <returns>성공 여부</returns>
bool BTreeNode::Insert(BTreeNodeKey* newKey)
{
	if (keyRoot == nullptr)
	{
		keyRoot = newKey;
	}
	else
	{
		// 새 값이 노드에서 가장 작은 경우
		if (newKey->value < keyRoot->value)
		{
			keyRoot->AddKeyToPrev(newKey);
			keyRoot = newKey;
		}
		else
		{
			BTreeNodeKey* key{ keyRoot };
			BTreeNodeKey* prevKey{ nullptr };

			while (key != nullptr)
			{
				if (newKey->value < key->value)
				{
					prevKey = nullptr;
					key->AddKeyToPrev(newKey);
					break;
				}

				prevKey = key;
				key = key->next;
			}

			// 새 값이 노드에서 가장 큰 경우
			if (prevKey != nullptr)
			{
				prevKey->AddKeyToNext(newKey);
			}
		}
	}

	size++;

	return size <= TotalKeyCount;
}

/// <summary>
/// 노드에 여유가 있는지 여부를 반환한다.
/// </summary>
/// <returns>삽입 가능한지 여부</returns>
bool BTreeNode::IsAbleToInsert()
{
	return size < TotalKeyCount;
}

/// <summary>
/// 가장 작은 키를 노드에서 떼어내 반환한다.
/// </summary>
/// <returns>가장 작은 키</returns>
BTreeNodeKey* BTreeNode::GetSmallestKey()
{
	BTreeNodeKey* key{ nullptr };
	if (keyRoot != nullptr)
	{
		key = keyRoot;
		keyRoot = keyRoot->next;
		keyRoot->prev = nullptr;
	}
	size--;
	return key;
}

/// <summary>
/// 가장 큰 키를 노드에서 떼어내 반환한다.
/// </summary>
/// <returns>가장 큰 키</returns>
BTreeNodeKey* BTreeNode::GetBiggestKey()
{
	BTreeNodeKey* key{ nullptr };
	if (keyRoot != nullptr)
	{
		key = keyRoot;
		while (key->next != nullptr)
		{
			key = key->next;
		}

		BTreeNodeKey* prev{ key->prev };
		if (prev != nullptr)
		{
			prev->next = nullptr;
			key->prev = nullptr;
		}
	}
	size--;
	return key;
}

/// <summary>
/// 노드의 키 중 중간 값을 가진 키를 떼어내 반환한다.
/// </summary>
/// <returns>중간 키</returns>
BTreeNodeKey* BTreeNode::GetMiddleKey()
{
	size_t midIdx = TotalKeyCount / 2;

	BTreeNodeKey* key{ nullptr };
	if (keyRoot != nullptr)
	{
		key = keyRoot;
		while (key->next != nullptr && midIdx > 0)
		{
			key = key->next;
			midIdx--;
		}

		BTreeNodeKey* prev{ key->prev };
		BTreeNodeKey* next{ key->next };
		if (prev != nullptr)
		{
			prev->next = next;
			key->prev = nullptr;
		}
		if (next != nullptr)
		{
			next->prev = prev;
			key->next = nullptr;
		}
	}
	size--;
	return key;
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

#pragma region BTree Public Methods
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

/// <summary>
/// 주어진 값을 B 트리에 삽입한다.
/// </summary>
/// <param name="data">삽입할 값</param>
void BTree::Insert(int data)
{
	if (Exists(data))
	{
		return;
	}

	BTreeNode* node{ GetProperNodeToInsert(data) };
	if (!node->Insert(data))
	{
		ClearOverflow(node);
	}
}
#pragma endregion

#pragma region BTree Private Methods
/// <summary>
/// 오버플로우 발생한 노드를 정리한다.
/// </summary>
/// <param name="node">오버 플로우가 발생한 노드</param>
void BTree::ClearOverflow(BTreeNode* node)
{
	bool isDone{ false };

	BTreeNode* p{ node->parent };
	// 루트 노드가 아닌 경우
	if (p != nullptr)
	{
		BTreeNodeKey* lsKey{ nullptr };
		BTreeNodeKey* rsKey{ p->keyRoot };
		while (rsKey != nullptr)
		{
			if (rsKey->left == node)
			{
				break;
			}
			lsKey = rsKey;
			rsKey = rsKey->next;
		}

		// 왼쪽 형제가 존재하고 삽입 가능한 경우
		if (lsKey != nullptr && lsKey->left != nullptr
			&& lsKey->left->IsAbleToInsert())
		{
			BTreeNodeKey* key{ node->GetSmallestKey() };
			lsKey->SwapValue(key);
			lsKey->left->Insert(key);
			isDone = true;
		}
		// 오른쪽 형제가 존재하고 삽입 가능한 경우
		else if (rsKey != nullptr && rsKey->right != nullptr
			&& rsKey->right->IsAbleToInsert())
		{
			BTreeNodeKey* key{ node->GetBiggestKey() };
			rsKey->SwapValue(key);
			rsKey->right->Insert(key);
			isDone = true;
		}
	}

	// 삽입 가능한 형제가 없는 경우
	if (!isDone)
	{
		BTreeNodeKey* key{ node->GetMiddleKey() };
		// 노드를 가져온 key 를 기준으로 두개로 나눈다.
		// key를 기준으로 좌, 우 노드가 되도록 한다.
		// 부모 노드에 key를 삽입하고 형제 키의 좌, 우 자식을 적절히 바꿔준다.
		// 부모의 사이즈가 넘어가게 된 경우 부모 노드에 처리 반복
		// 현재 노드가 루트 노드면 key를 가지는 새 노드를 만들어 루트로 만들고
		// 기존 분리했던 노드를 key의 좌, 우 자식 노드로 적용하고 종료
	}
}
#pragma endregion

#pragma region BTree Util Methods
/// <summary>
/// 주어진 data를 삽입할 수 있는 적절한 노드를 찾아 반환한다.
/// </summary>
/// <param name="data">삽입할 값</param>
/// <returns>데이터를 삽입할 수 있는 노드</returns>
BTreeNode* BTree::GetProperNodeToInsert(int data)
{
	if (_root == nullptr)
	{
		_root = _nodeManager.Pop();
		return _root;
	}

	BTreeNode* node{ _root };
	BTreeNode* prevNode{ nullptr };

	while (node != nullptr)
	{
		if (node->IsAbleToInsert())
		{
			return node;
		}

		BTreeNodeKey* key{ node->keyRoot };
		while (key != nullptr)
		{
			if (data < key->value)
			{
				prevNode = node;
				node = key->left;
				break;
			}
			else if (key->value < data)
			{
				if (key->next == nullptr || data < key->next->value)
				{
					prevNode = node;
					node = key->right;
					break;
				}
			}

			key = key->next;
		}
	}
	
	return prevNode;
}
#pragma endregion