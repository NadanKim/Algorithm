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
/// �� Ű�� ���� Ű�� ���ʿ� �����Ѵ�.
/// </summary>
/// <param name="newKey">������ Ű</param>
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
/// �� Ű�� ���� Ű�� �����ʿ� �����Ѵ�.
/// </summary>
/// <param name="newKey">������ Ű</param>
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
/// �ٸ� Ű�� value�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="other">�ٸ� Ű</param>
void BTreeNodeKey::SwapValue(BTreeNodeKey* other)
{
	int temp{ value };
	value = other->value;
	other->value = temp;
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

/// <summary>
/// ��忡 �����͸� �����Ѵ�.
/// </summary>
/// <param name="data">������ ������</param>
/// <returns>���� ����</returns>
bool BTreeNode::Insert(int data)
{
	BTreeNodeKey* newKey{ keyManager->Pop() };
	newKey->Set(data);

	return Insert(newKey);
}

/// <summary>
/// �־��� Ű�� ����� Ű�� �����Ѵ�.
/// </summary>
/// <param name="key">������ Ű</param>
/// <returns>���� ����</returns>
bool BTreeNode::Insert(BTreeNodeKey* newKey)
{
	if (keyRoot == nullptr)
	{
		keyRoot = newKey;
	}
	else
	{
		// �� ���� ��忡�� ���� ���� ���
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

			// �� ���� ��忡�� ���� ū ���
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
/// �־��� �����͸� �����ϴ� Ű�� ��忡�� �����Ѵ�.
/// </summary>
/// <param name="data">������ ��</param>
/// <returns>���� ����</returns>
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
/// �־��� Ű�� ��忡�� �����Ѵ�.
/// </summary>
/// <param name="deleteKey">������ Ű</param>
/// <returns>���� ����</returns>
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
/// ��忡 ������ �ִ��� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <returns>���� �������� ����</returns>
bool BTreeNode::IsAbleToInsert()
{
	return size < TotalKeyCount;
}

/// <summary>
/// ���� ��尡 �־��� ���� �����ϴ��� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">Ȯ���� ��</param>
/// <returns>�� ���� ����</returns>
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
/// �� ��忡�� Ű�� �����ص� ���������� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <returns>Ű�� �����ص� ���������� ����</returns>
bool BTreeNode::IsAbleToWithdraw()
{
	return size > TotalKeyCount / 2;
}

/// <summary>
/// ���� ���� Ű�� ��忡�� ��� ��ȯ�Ѵ�.
/// </summary>
/// <returns>���� ���� Ű</returns>
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
/// ���� ū Ű�� ��忡�� ��� ��ȯ�Ѵ�.
/// </summary>
/// <returns>���� ū Ű</returns>
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
/// ����� Ű �� �߰� ���� ���� Ű�� ��� ��ȯ�Ѵ�.
/// </summary>
/// <returns>�߰� Ű</returns>
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
/// �־��� ���� ������ Ű�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">ã�� ��</param>
/// <returns>���� ������ Ű</returns>
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

#pragma region ��� �Ŵ���
/// <summary>
/// ��� �Ŵ��� �� Ű �Ŵ����� �ʱ�ȭ�Ѵ�.
/// </summary>
BTreeNodeManager::BTreeNodeManager()
	: nodes(nullptr)
{
	keyManager = new BTreeNodeKeyManager();
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

	delete keyManager;
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
	node->keyManager = keyManager;

	return node;
}

/// <summary>
/// ������ �ִ� Ű�� ��� �����ϰ� �����Ѵ�.
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
/// ��� �Ϸ��� Ű�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="node">��� �Ϸ��� Ű</param>
void BTreeNodeKeyManager::Push(BTreeNodeKey* key)
{
	key->next = keys;
	keys = key;
}

/// <summary>
/// ����� Ű�� �����Ѵ�.
/// </summary>
/// <returns>����� Ű</returns>
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
/// �ʿ��� ������ �����Ѵ�.
/// </summary>
BTree::BTree()
	: _root(nullptr)
{
}

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

	BTreeNode* node{ GetProperNodeToInsert(data) };
	if (!node->Insert(data))
	{
		ClearOverflow(node);
	}
}

/// <summary>
/// �־��� ���� ������ Ű�� B Ʈ������ �����Ѵ�.
/// </summary>
/// <param name="data">������ ��</param>
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
/// Ʈ���� �ؽ�Ʈ�� ����Ѵ�.
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
/// �����÷ο� �߻��� ��带 �����Ѵ�.
/// </summary>
/// <param name="node">���� �÷ο찡 �߻��� ���</param>
void BTree::ClearOverflow(BTreeNode* node)
{
	bool isDone{ false };

	BTreeNode* parent{ node->parent };
	// ��Ʈ ��尡 �ƴ� ���
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

		// ���� ������ �����ϰ� ���� ������ ���
		if (lsKey != nullptr && lsKey->left != nullptr
			&& lsKey->left->IsAbleToInsert())
		{
			BTreeNodeKey* key{ node->GetSmallestKey() };
			lsKey->SwapValue(key);
			lsKey->left->Insert(key);
			isDone = true;
		}
		// ������ ������ �����ϰ� ���� ������ ���
		else if (rsKey != nullptr && rsKey->right != nullptr
			&& rsKey->right->IsAbleToInsert())
		{
			BTreeNodeKey* key{ node->GetBiggestKey() };
			rsKey->SwapValue(key);
			rsKey->right->Insert(key);
			isDone = true;
		}
	}

	// ���� ������ ������ ���� ���
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
/// ����÷ο찡 �߻��� ��带 �����Ѵ�.
/// </summary>
/// <param name="node">��� �÷ο찡 �߻��� ���</param>
void BTree::ClearUnderflow(BTreeNode* node)
{
	// ��尡 ��Ʈ�� ���
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

		// ���� ������ �����ϰ� ���� ������ ���
		if (lsKey != nullptr && lsKey->left != nullptr
			&& lsKey->left->IsAbleToWithdraw())
		{
			BTreeNodeKey* key{ lsKey->left->GetBiggestKey() };
			lsKey->SwapValue(key);
			node->Insert(key);
			isDone = true;
		}
		// ������ ������ �����ϰ� ���� ������ ���
		else if (rsKey != nullptr && rsKey->right != nullptr
			&& rsKey->right->IsAbleToWithdraw())
		{
			BTreeNodeKey* key{ rsKey->right->GetSmallestKey() };
			rsKey->SwapValue(key);
			node->Insert(key);
			isDone = true;
		}

		// ���� ������ ������ ���� ���
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
/// ��带 �־��� Ű�� �������� �����ϰ� ���� ������ ��带 ��ȯ�Ѵ�.
/// </summary>
/// <param name="node">������ ���</param>
/// <param name="key">���� Ű</param>
/// <returns>���ҵ� �� ���</returns>
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
/// �־��� Ű�� �������� ��带 �����Ѵ�.
/// </summary>
/// <param name="node">������ ���</param>
/// <param name="lsKey">���� �θ�Ű</param>
/// <param name="rsKey">������ �θ�Ű</param>
/// <returns>���յ� ���</returns>
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
/// �־��� data�� ������ �� �ִ� ������ ��带 ã�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">������ ��</param>
/// <returns>�����͸� ������ �� �ִ� ���</returns>
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
/// �־��� ���� ī�� Ű�� �����ϱ� ���� ������ ��带 ã�� ��ȯ�Ѵ�.
/// </summary>
/// <param name="data">������ ��</param>
/// <returns>������ ���� ���</returns>
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