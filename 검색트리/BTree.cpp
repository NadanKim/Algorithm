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
	}
	newKey->next = this;
	prev = newKey;
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
	}
	newKey->prev = this;
	next = newKey;
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
/// ��忡 ������ �ִ��� ���θ� ��ȯ�Ѵ�.
/// </summary>
/// <returns>���� �������� ����</returns>
bool BTreeNode::IsAbleToInsert()
{
	return size < TotalKeyCount;
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

#pragma region BTree Public Methods
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
#pragma endregion

#pragma region BTree Private Methods
/// <summary>
/// �����÷ο� �߻��� ��带 �����Ѵ�.
/// </summary>
/// <param name="node">���� �÷ο찡 �߻��� ���</param>
void BTree::ClearOverflow(BTreeNode* node)
{
	bool isDone{ false };

	BTreeNode* p{ node->parent };
	// ��Ʈ ��尡 �ƴ� ���
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
		// ��带 ������ key �� �������� �ΰ��� ������.
		// key�� �������� ��, �� ��尡 �ǵ��� �Ѵ�.
		// �θ� ��忡 key�� �����ϰ� ���� Ű�� ��, �� �ڽ��� ������ �ٲ��ش�.
		// �θ��� ����� �Ѿ�� �� ��� �θ� ��忡 ó�� �ݺ�
		// ���� ��尡 ��Ʈ ���� key�� ������ �� ��带 ����� ��Ʈ�� �����
		// ���� �и��ߴ� ��带 key�� ��, �� �ڽ� ���� �����ϰ� ����
	}
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