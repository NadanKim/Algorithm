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
		prevKey->right = newKey->left;
	}
	newKey->next = this;
	prev = newKey;

	left = newKey->right;
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
		nextKey->left = newKey->right;
	}
	newKey->prev = this;
	next = newKey;

	right = newKey->left;
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
/// 주어진 데이터를 포함하는 키를 노드에서 제거한다.
/// </summary>
/// <param name="data">제거할 값</param>
/// <returns>성공 여부</returns>
bool BTreeNode::Delete(int data)
{
	BTreeNodeKey* key{ keyRoot };

	while (key != nullptr)
	{
		if (key->value == data)
		{
			return Delete(key);
		}
	}

	return false;
}

/// <summary>
/// 주어진 키를 노드에서 제거한다.
/// </summary>
/// <param name="deleteKey">제거할 키</param>
/// <returns>성공 여부</returns>
bool BTreeNode::Delete(BTreeNodeKey* deleteKey)
{
	BTreeNodeKey* prevKey{ deleteKey->prev };
	BTreeNodeKey* nextKey{ deleteKey->next };

	if (prevKey != nullptr)
	{
		prevKey->next = nextKey;
	}
	if (nextKey != nullptr)
	{
		nextKey->prev = prevKey;
	}

	keyManager->Push(deleteKey);

	size--;

	return size >= TotalKeyCount / 2;
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
/// 현재 노드가 주어진 값을 포함하는지 여부를 반환한다.
/// </summary>
/// <param name="data">확인할 값</param>
/// <returns>값 포함 여부</returns>
bool BTreeNode::IsContainsData(int data)
{
	BTreeNodeKey* key{ keyRoot };
	while (key != nullptr)
	{
		if (key->value == data)
		{
			return true;
		}
		key = key->next;
	}
	return false;
}

/// <summary>
/// 이 노드에서 키를 인출해도 안정적인지 여부를 반환한다.
/// </summary>
/// <returns>키를 인출해도 안정적인지 여부</returns>
bool BTreeNode::IsAbleToWithdraw()
{
	return size > TotalKeyCount / 2;
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
		key->next = nullptr;
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

		if (key == keyRoot)
		{
			keyRoot = nullptr;
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

		if (key == keyRoot)
		{
			keyRoot = keyRoot->next;
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

/// <summary>
/// 주어진 값을 가지는 키를 반환한다.
/// </summary>
/// <param name="data">찾을 값</param>
/// <returns>값을 가지는 키</returns>
BTreeNodeKey* BTreeNode::GetKey(int data)
{
	BTreeNodeKey* key{ keyRoot };
	while (key != nullptr)
	{
		if (key->value == data)
		{
			break;
		}
		key = key->next;
	}
	return key;
}
#pragma endregion

#pragma region 노드 매니저
/// <summary>
/// 노드 매니저 및 키 매니저를 초기화한다.
/// </summary>
BTreeNodeManager::BTreeNodeManager()
	: nodes(nullptr)
{
	keyManager = new BTreeNodeKeyManager();
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

	delete keyManager;
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
	node->keyManager = keyManager;

	return node;
}

/// <summary>
/// 가지고 있던 키를 모두 안전하게 제거한다.
/// </summary>
BTreeNodeKeyManager::~BTreeNodeKeyManager()
{
	while (keys != nullptr)
	{
		BTreeNodeKey* node{ keys };
		keys = keys->next;
		delete node;
	}
}

/// <summary>
/// 사용 완료한 키를 반환한다.
/// </summary>
/// <param name="node">사용 완료한 키</param>
void BTreeNodeKeyManager::Push(BTreeNodeKey* key)
{
	key->next = keys;
	keys = key;
}

/// <summary>
/// 사용할 키를 인출한다.
/// </summary>
/// <returns>사용할 키</returns>
BTreeNodeKey* BTreeNodeKeyManager::Pop()
{
	BTreeNodeKey* node{ keys };

	if (node != nullptr)
	{
		keys = node->next;
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
/// 필요한 값들을 생성한다.
/// </summary>
BTree::BTree()
	: _root(nullptr)
{
}

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

/// <summary>
/// 주어진 값을 가지는 키를 B 트리에서 제거한다.
/// </summary>
/// <param name="data">제거할 값</param>
void BTree::Delete(int data)
{
	if (!Exists(data))
	{
		return;
	}

	BTreeNode* node{ GetProperNodeToDelete(data) };
	if (!node->Delete(data))
	{
		ClearUnderflow(node);
	}
}

/// <summary>
/// 트리를 텍스트로 출력한다.
/// </summary>
void BTree::PrintTree()
{
	std::cout << "\n--------------------\n";

	if (_root == nullptr)
	{
		std::cout << "EMPTY TREE";
	}
	else
	{
		int nodeCount{ 1 };
		int counter{ 0 };

		_queue.push(_root);
		while (!_queue.empty())
		{
			BTreeNode* node{ _queue.front() };
			_queue.pop();

			if (counter == nodeCount)
			{
				counter = 0;
				nodeCount *= BTreeNode::TotalKeyCount;
				std::cout << '\n';
			}

			BTreeNodeKey* key{ node->keyRoot };
			if (key->left != nullptr)
			{
				_queue.push(key->left);
			}

			std::cout << '[';
			while (key != nullptr)
			{
				if (key->right != nullptr)
				{
					_queue.push(key->right);
				}
				std::cout << key->value << (key->next != nullptr ? ", " : "");
				key = key->next;
			}
			std::cout << ']';

			counter++;
		}
	}

	std::cout << "\n--------------------\n";
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

	BTreeNode* parent{ node->parent };
	// 루트 노드가 아닌 경우
	if (parent != nullptr)
	{
		BTreeNodeKey* lsKey{ nullptr };
		BTreeNodeKey* rsKey{ parent->keyRoot };
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
		BTreeNode* newNode{ SplitNodeWithKey(node, key) };
		key->left = node;
		key->right = newNode;

		if (node == _root)
		{
			BTreeNode* newRootNode{ _nodeManager.Pop() };
			newRootNode->Insert(key);
			node->parent = newNode->parent = newRootNode;
			_root = newRootNode;
		}
		else if (!parent->Insert(key))
		{
			ClearOverflow(parent);
		}
	}
}

/// <summary>
/// 언더플로우가 발생한 노드를 정리한다.
/// </summary>
/// <param name="node">언더 플로우가 발생한 노드</param>
void BTree::ClearUnderflow(BTreeNode* node)
{
	// 노드가 루트인 경우
	if (node == _root)
	{
		if (node->size == 0)
		{
			_nodeManager.Push(node);
			_root = nullptr;
		}
	}
	else
	{
		bool isDone{ false };

		BTreeNode* parent{ node->parent };
		BTreeNodeKey* lsKey{ nullptr };
		BTreeNodeKey* rsKey{ parent->keyRoot };
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
			&& lsKey->left->IsAbleToWithdraw())
		{
			BTreeNodeKey* key{ lsKey->left->GetBiggestKey() };
			lsKey->SwapValue(key);
			node->Insert(key);
			isDone = true;
		}
		// 오른쪽 형제가 존재하고 삽입 가능한 경우
		else if (rsKey != nullptr && rsKey->right != nullptr
			&& rsKey->right->IsAbleToWithdraw())
		{
			BTreeNodeKey* key{ rsKey->right->GetSmallestKey() };
			rsKey->SwapValue(key);
			node->Insert(key);
			isDone = true;
		}

		// 인출 가능한 형제가 없는 경우
		if (!isDone)
		{
			BTreeNodeKey* key{ rsKey != nullptr ? rsKey : lsKey };
			BTreeNode* mergeNode{ MergeNodeWithKey(node, lsKey, rsKey) };

			if (key != nullptr)
			{
				if (key->prev != nullptr)
				{
					key->prev->right = mergeNode;
				}
				if (key->next != nullptr)
				{
					key->next->left = mergeNode;
				}

				if (parent == _root)
				{
					parent->Delete(key);
					_nodeManager.Push(parent);
					_root = mergeNode;
				}
				else if (!parent->Delete(key))
				{
					ClearUnderflow(parent);
				}
			}
		}
	}
}

/// <summary>
/// 노드를 주어진 키를 기준으로 분할하고 새로 생성된 노드를 반환한다.
/// </summary>
/// <param name="node">분할할 노드</param>
/// <param name="key">기준 키</param>
/// <returns>분할된 새 노드</returns>
BTreeNode* BTree::SplitNodeWithKey(BTreeNode* node, BTreeNodeKey* key)
{
	BTreeNode* newNode{ _nodeManager.Pop() };
	newNode->parent = node->parent;

	while (true)
	{
		BTreeNodeKey* targetKey{ node->GetBiggestKey() };
		if (targetKey->value < key->value)
		{
			node->Insert(targetKey);
			break;
		}

		newNode->Insert(targetKey);
	}

	return newNode;
}

/// <summary>
/// 주어진 키를 기준으로 노드를 병합한다.
/// </summary>
/// <param name="node">병합할 노드</param>
/// <param name="lsKey">왼쪽 부모키</param>
/// <param name="rsKey">오른쪽 부모키</param>
/// <returns>병합된 노드</returns>
BTreeNode* BTree::MergeNodeWithKey(BTreeNode* node, BTreeNodeKey* lsKey, BTreeNodeKey* rsKey)
{
	BTreeNodeKey* mergeKey{ nullptr };
	BTreeNode* mergeNode{ nullptr };

	if (rsKey != nullptr)
	{
		mergeKey = rsKey;
		mergeNode = rsKey->right;
	}
	else
	{
		mergeKey = lsKey;
		mergeNode = lsKey->left;
	}

	while (node->size > 0)
	{
		BTreeNodeKey* key{ node->GetSmallestKey() };
		mergeNode->Insert(key);
	}
	mergeNode->Insert(mergeKey->value);

	_nodeManager.Push(node);

	return mergeNode;
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
	BTreeNode* prevNode{ node };

	while (node != nullptr)
	{
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

/// <summary>
/// 주어진 값을 카진 키를 제거하기 위해 적절한 노드를 찾아 반환한다.
/// </summary>
/// <param name="data">제거할 값</param>
/// <returns>삭제를 위한 노드</returns>
BTreeNode* BTree::GetProperNodeToDelete(int data)
{
	BTreeNode* node{ _root };
	BTreeNode* leafNode{ nullptr };

	while (node != nullptr)
	{
		if (node->IsContainsData(data))
		{
			BTreeNodeKey* key{ node->GetKey(data) };
			while (key->right != nullptr)
			{
				leafNode = key->right;
				key = leafNode->GetSmallestKey();
			}
			break;
		}
	}

	if (leafNode != nullptr)
	{
		BTreeNodeKey* key{ node->GetKey(data) };
		BTreeNodeKey* leafKey{ leafNode->GetSmallestKey() };
		key->SwapValue(leafKey);
		node = leafNode;
	}

	return leafNode;
}
#pragma endregion