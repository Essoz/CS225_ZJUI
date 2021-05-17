/*
 * Copyright@Naveen
 * 6:24:49 PM
 * B.cpp
 *
 * Some implementations is not satisfied for what we learnt in class and book.
 * This file is modified by Tianyu Zhang.
 */
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;
/* In BNode class
   We store the primary key (person id) as the value (data) of the node,
   the secondary key (here is age) is used as key in the BNode.
*/

typedef struct
{
	vector<int64_t> primary_key;	// data
	int64_t secondary_key;			// key
} Keys;

class BNode
{
	friend class B;
public:
	Keys* keys;					// List of key structures
	vector<BNode*>* Child;	// Pointer to a list containing ptr of childs
	int64_t num_keys;			// The number of key structures in this node
	int64_t order;				// Mini-degree for the tree, num_keys must be in range (t-1, 2t-1) except for root node
	bool leaf;					// If it is a leaf node
	BNode* parent;			// Point to its parent

	BNode(int64_t order, bool leaf, BNode* parent)
	{
		this->order = order;
		this->leaf = leaf;
		keys = new Keys[2 * order - 1];
		Child = new vector<BNode*> (2 * order);
		num_keys = 0;
		this->parent = parent;
	}

	int64_t findpId(int64_t ids_k, int64_t p_k);// Find the index of primary key with value p_k in the structure
	int64_t findsId(int64_t s_k);				// Find the index of secondary key with value s_k in this node
	void remove(int64_t p_k, int64_t s_k);		// Remove a record (here is just structure) in this node
	//void removeFromLeaf(int64_t id, int64_t p_k);
	//void removeFromNonLeaf(int64_t id, int64_t p_k);
	//void borrowFromPrev(int64_t id, int64_t p_k);
	//void borrowFromSucc(int64_t id, int64_t p_k);
	//int64_t findSucc(int64_t id);
	//int64_t findPrec(int64_t id);
	//void merge(int64_t id);
	//void fill(int64_t id);
	void traverse();							// Print all the elements in this node
	BNode* search(int64_t s_k);				// Get the record with secondary key s_k in this node

	void insertNonFull(int64_t p_k, int64_t s_k);			// Insert a record if the node is not fully filled
	void splitChild(int64_t i, BNode* y);				// 
};

class B
{
public:
	BNode* root;		// Root node pointer
	int64_t order;			// Mini-degree

	B(int64_t order)
	{
		root = new BNode(order, true, NULL);	// Create root node
		this->order = order;
	}

	void insert(int64_t p_k, int64_t s_k);	// Insert a record with both types of keys
	void remove(int64_t p_k, int64_t s_k);	// Remove a record (here is just id) in the tree
	vector<int64_t> getAll(int64_t s_k);	// Give the list of all the primary keys related with the input s_k
	//int64_t find_max();	
	//int64_t find_min();	
	//int64_t findSucc(int64_t k);
	//int64_t findPrec(int64_t k);
	// Find the parent of given node with a certain key:
	//BNode* find_par(BNode* node, int64_t k);

	void traverse()						// Print all the elements in a non-empty tree
	{
		if (root == NULL) return;
		else
			root->traverse();
	}
	BNode* search(int64_t s_k)	// Get the node with secondary key s_k in a non-empty tree
	{
		return (root == NULL) ? NULL : root->search(s_k);
	}
};

// Find the index of primary key with value p_k in the structure:
int64_t BNode::findpId(int64_t ids_k, int64_t p_k) {
    int i;
	for (i = 0; i < int(keys[ids_k].primary_key.size()) - 1; i++)
	{
		if (keys[ids_k].primary_key[i] == p_k)
		{
			return i;
		}
	}
	return -1;	// The primary key is not in the node
}

// Find the index of secondary key with value s_k in this node:
// If the key is not in this node, the result will be the latter one.
int64_t BNode::findsId(int64_t s_k)
{
    int i;
	for (i = 0; i < num_keys && keys[i].secondary_key < s_k; i++);
	return i;
}

// Remove the record with p_k and s_k in this node:
void BNode::remove(int64_t p_k, int64_t s_k)
{
	int64_t id = findsId(s_k);
	// Check if the key is in this node:
	if (id < num_keys && keys[id].secondary_key == s_k)
	{	// The key is in this node:
		// Find the primary key in this structure entry
		int64_t uid = findpId(id, p_k);
		if (-1 == uid)
		{
			cout << "No such record!!" << endl;
			return;
		}
		else
		{
			// Just remove the primary key from that structure.
			keys->primary_key.erase(keys->primary_key.begin() + uid);
			/*
			if (1 == keys->primary_key.empty())
			{
				if (leaf)
					removeFromLeaf(id, p_k);			// NOW THERE !!!!!!!!!!!!!
				else
					removeFromNonLeaf(id, p_k);
			}
			*/
		}
	}
	else
	{	// The key is not in this node, check if this node is a leaf node:
		if (leaf)
		{
			cout << "Element does not exist" << endl;
			return;
		}
		else
		{
			(*Child)[id]->remove(p_k, s_k);
			/*
			bool flag;
			if (num_keys == id)		// The key is in the last child of this node
				flag = true;
			else
				flag = false;

			//if ((*Child)[id]->order < order)	//???
			//	fill(id);

			if (flag && id > num_keys)
				(*Child)[id - 1]->remove(k);
			else
				(*Child)[id]->remove(k);
			*/
		}
	}
}


/*

// Remove a key from leaf node:
void BNode::removeFromLeaf(int64_t id, int64_t p_k)
{
	for (int64_t i = id + 1; i < num_keys; i++)
	{
		keys[i - 1] = keys[i];
	}
	num_keys--;
	// Did not check if num_keys is less than floor(t) ?????
}

// Remove a key from non-leaf node:
void BNode::removeFromNonLeaf(int64_t id)
{
	if ((*Child)[id]->num_keys >= order)
	{	// ????
		keys[id] = findPrec(id);		// Replace by presuccessor
		(*Child)[id]->remove(keys[id]);	// Remove the presuccessor from its node
	}
	else if ((*Child)[id + 1]->num_keys >= order)
	{	// ????
		keys[id] = findSucc(id);		// Replace by successor
		(*Child)[id + 1]->remove(keys[id]);	// Remove the successor from its node
	}
	else
	{
		int64_t d = keys[id];
		merge(id);
		(*Child)[id]->remove(d);
	}
}

// Find the predecessor of a key in a non-leaf node:
int64_t BNode::findPrec(int64_t id)
{
	BNode* curr = (*Child)[id];
	while (!curr->leaf)		// Go to the leaf node
		curr = curr->(*Child)[curr->num_keys];
	return curr->keys[curr->num_keys - 1];
}
// Find the successor of a key in a non-leaf node:
int64_t BNode::findSucc(int64_t id)
{
	BNode* curr = (*Child)[id + 1];
	while (!curr->leaf)
		curr = curr->Child->at(0);
	return curr->keys[0];
}
void BNode::fill(int64_t id)
{
	if (id != 0 && (*Child)[id - 1]->num_keys >= order)
		borrowFromPrev(id);
	else if (id != num_keys && (*Child)[id + 1]->num_keys >= order)
		borrowFromSucc(id);
	else
	{
		if (id != num_keys)
			merge(id);
		else
			merge(id - 1);
	}

}

void BNode::borrowFromPrev(int64_t id)
{
	BNode* child = (*Child)[id];
	BNode* sibling = (*Child)[id - 1];

	for (int64_t i = child->num_keys - 1; i >= 0; i--)
		child->keys[i + 1] = child->keys[i];

	if (!child->leaf)
	{
		for (int64_t i = child->num_keys; i >= 0; i++)
			child->(*Child)[i + 1] = child->Child->at(i);
	}
	child->keys[0] = keys[id - 1];
	if (!child->leaf)
		child->Child->at(0) = sibling->(*Child)[sibling->num_keys];
	keys[id - 1] = sibling->keys[sibling->num_keys - 1];
	(child->num_keys)++;
	(sibling->num_keys)--;

}

void BNode::borrowFromSucc(int64_t id)
{

	BNode* child = (*Child)[id];
	BNode* sibling = (*Child)[id + 1];

	child->keys[child->num_keys] = keys[id];
	keys[id] = sibling->keys[0];

	if (!child->leaf) {
		child->(*Child)[(child->num_keys) + 1] = sibling->Child->at(0);
	}

	for (int64_t i = 1; i < sibling->num_keys; i++)
		sibling->keys[i - 1] = sibling->keys[i];
	if (!child->leaf) {
		for (int64_t i = 1; i <= sibling->num_keys; i++)
			sibling->(*Child)[i - 1] = sibling->Child->at(i);
	}

	(sibling->num_keys)--;
	(child->num_keys)++;
}

// Merge the two childs of given key k in this node:
void BNode::merge(int64_t id)
{
	BNode* child = (*Child)[id];
	BNode* sibling = (*Child)[id + 1];

	child->keys[child->num_keys] = keys[id];

	for (int64_t i = 0; i < sibling->num_keys; i++)
		child->keys[child->num_keys + 1 + i] = sibling->keys[i];

	if (!child->leaf)
	{
		for (int64_t i = 0; i <= sibling->num_keys; i++)
			child->(*Child)[child->num_keys + 1 + i] = sibling->Child->at(i);
	}

	for (int64_t i = id + 1; i < num_keys; i++)
		keys[i - 1] = keys[i];
	for (int64_t i = id + 1; i <= num_keys; i++)
		(*Child)[i - 1] = Child->at(i);
	child->num_keys += sibling->num_keys + 1;
	num_keys--;
	delete(sibling);
	return;
}

*/


// Print all the secondary keys in current subtree with inorder traversal:
void BNode::traverse()
{
	int64_t i;
	// Used for previous num_keys-1 childs:
	for (i = 0; i < num_keys; i++)
	{
		if (leaf == false)
			Child->at(i)->traverse();
		cout << keys[i].secondary_key << " ";
	}
	// Used for the last child:
	if (leaf == false)
		Child->at(i)->traverse();
}

// Find the node containing exactly the secondary key with value s_k:
BNode* BNode::search(int64_t s_k)
{
	int64_t i;
	for (i = 0; i < num_keys && keys[i].secondary_key < s_k; i++);
	if (keys[i].secondary_key == s_k)
		return this;

	if (leaf == true)
		return NULL;	// No such secondary key in the tree

	return Child->at(i)->search(s_k);
}

// Add a record in the tree:
void B::insert(int64_t p_k, int64_t s_k)
{
	if (root == NULL)
	{
		root = new BNode(order, true, NULL);
		Keys strut;
		vector<int64_t> vec;
		vec.push_back(p_k);

		strut.primary_key = vec;
		strut.secondary_key = s_k;

		root->keys[0] = strut;
		root->num_keys = 1;
	}
	else
	{
		// Now check if the s_k is already in the tree:
		BNode* target = search(s_k);
		if (NULL != target)
		{
			int64_t id = target->findsId(s_k);
			int64_t uid = target->findpId(id, p_k);
			if (-1 != uid)
			{	// Record already exists!
				cout << "Record already exists!" << endl;
				return;
			}
			// Add the new p_k into the corresponding structure:
			target->keys[id].primary_key.push_back(p_k);
			return;
		}

		// If reach here, that means no s_k in the tree:
		if (root->num_keys == 2 * order - 1)
		{
			// Split the root since it is already full:
			BNode* new_root = new BNode(order, false, NULL);
			new_root->Child->at(0) = root;
			new_root->Child->at(0)->parent = new_root;
			new_root->splitChild(0, new_root->Child->at(0));

			// Now decide which child to insert:
			int64_t i = 0;
			if (new_root->keys[0].secondary_key < s_k)
				i++;
			new_root->Child->at(i)->insertNonFull(p_k, s_k);
			root = new_root;
		}
		else
			root->insertNonFull(p_k, s_k);
	}
}

// Remove a record with both types of id in the tree:
void B::remove(int64_t p_k, int64_t s_k)
{
	if (!root)
	{
		cout << "The tree is empty\num_keys";
		return;
	}
	root->remove(p_k, s_k);
	// If the root becomes empty after deletion, update the root node:
	if (root->num_keys == 0)
	{
		BNode* r = root;
		if (root->leaf)
			root = NULL;
		else
			root = root->Child->at(0);
		delete r;
	}
	return;
}

// Give the list of all the primary keys related with the input s_k:
vector<int64_t> B::getAll(int64_t s_k) {
	// Find the right node first:
	BNode* r_node = search(s_k);
	// Find the right index next:
	int64_t r_index = r_node->findsId(s_k);
	// Get the right array of primary keys:
	return r_node->keys[r_index].primary_key;
}

// Insert a record if the node is not fully filled:
void BNode::insertNonFull(int64_t p_k, int64_t s_k)
{
	int64_t i = num_keys - 1;
	if (leaf == true)
	{
		while (i >= 0 && s_k < keys[i].secondary_key)
		{
			keys[i + 1] = keys[i];
			i--;
		}
		// Reuse the previous structure for insertion
		keys[i + 1].secondary_key = s_k;
		keys[i + 1].primary_key.clear();
		keys[i + 1].primary_key.push_back(p_k);
		num_keys = num_keys + 1;
	}
	else
	{
		while (i >= 0 && s_k < keys[i].secondary_key)
			i--;
		if ((*Child)[i + 1]->num_keys == 2 * order - 1)
		{
			splitChild(i + 1, (*Child)[i + 1]);
			if (keys[i + 1].secondary_key < s_k)
				i++;
		}
		(*Child)[i + 1]->insertNonFull(p_k, s_k);
	}
}

void BNode::splitChild(int64_t i, BNode* y)
{
	BNode* z = new BNode(y->order, y->leaf, y->parent);
	z->num_keys = order - 1;
	// Move the right half data to the new node
	for (int64_t j = 0; j < order - 1; j++)
		z->keys[j] = y->keys[j + order];
	// Move the right half child to the new node if nonleaf
	if (y->leaf == false)
	{
		for (int64_t j = 0; j < order; j++)
			z->Child->at(j) = y->Child->at(j + order);
	}
	y->num_keys = order - 1;
	// Reorganize childs to the parent:
	for (int64_t j = num_keys; j >= i + 1; j--)
		(*Child)[j + 1] = Child->at(j);
	(*Child)[i + 1] = z;
	// Reorganize keys in the parent:
	for (int64_t j = num_keys - 1; j >= i; j--)
		keys[j + 1] = keys[j];
	keys[i] = y->keys[order - 1];
	num_keys = num_keys + 1;
}

/*
// For HW8:
// (ii):
//find the max key stored in B-tree//
int64_t B::find_max()
{
	//Implement your code here//
	// Start with the root node, always find the last child of the current node,
	// until we reach a leaf node:
	BNode* node = root;
	while (!node->leaf)
	{
		node = node->(*Child)[node->num_keys];
	}
	return node->keys[node->num_keys - 1];
}
//find the min key stored in B-tree//
int64_t B::find_min()
{
	//Implement your code here//
	// Start with the root node, always find the first child of the current node,
	// until we reach a leaf node:
	BNode* node = root;
	while (!node->leaf)
	{
		node = node->Child->at(0);
	}
	return node->keys[0];
}

// (iv):
// Note: the nodes in B-tree do not have a pointer to its parent, so the implementation will
// be somehow complicated......
//find the predecessor of the given key//
int64_t B::findPrec(int64_t k)
{
	// To start with, check if the key is in the tree:
	BNode* pos = search(k);
	if (NULL == pos)
	{
		cout << "The key is not in the tree!!" << endl;
		return k;
	}
	// Now, check if the node is a leaf node:
	int64_t id_0 = pos->findId(k);
	if (!pos->leaf)
	{
		return pos->findPrec(id_0);
	}
	else
	{
		// Check if the key is the first in the key list:
		if (id_0 != 0)
		{
			return pos->keys[id_0 - 1];
		}
	}
	// Now deal with the exceptional case: first key of a leaf node
	// First, check if the key is the smallest key of the tree:
	if (k == find_min())
	{
		cout << "The key has no predecessor!!";
		return k;
	}
	// Second, check if the key is in the root node:
	int64_t id = root->findId(k);
	if (id < root->num_keys && root->keys[id] == k)
	{
		return root->keys[id - 1];
	}
	// Then, find the node where the parent of the key locates:
	BNode* parent = find_par(pos, k);
	// Loop to find a ancestor that the child is not the first child of children list:
	while (parent->Child->at(0) == pos)
	{
		pos = parent;
		parent = find_par(parent, k);
	}
	// Locate the predecessor:
	id = parent->findId(k);
	return parent->keys[id - 1];
}

//find the successor of the given key//
int64_t B::findSucc(int64_t k)
{
	// To start with, check if the key is in the tree:
	BNode* pos = search(k);
	if (NULL == pos)
	{
		cout << "The key is not in the tree!!" << endl;
		return k;
	}
	// Now, check if the node is a leaf node:
	int64_t id_0 = pos->findId(k);
	if (!pos->leaf)
	{
		return pos->findSucc(id_0);
	}
	else
	{
		// Check if the key is the last in the key list:
		if (id_0 != pos->num_keys - 1)
		{
			return pos->keys[id_0 + 1];
		}
	}
	// Now deal with the exceptional case: last key of a leaf node
	// First, check if the key is the largest key of the tree:
	if (k == find_max())
	{
		cout << "The key has no successor!!";
		return k;
	}
	// Second, check if the key is in the root node:
	int64_t id = root->findId(k);
	if (id < root->num_keys && root->keys[id] == k)
	{
		return root->keys[id + 1];
	}
	// Then, find the node where the parent of the key locates:
	BNode* parent = find_par(pos, k);
	// Loop to find a ancestor that the child is not the last child of children list:
	while (parent->(*Child)[parent->num_keys] == pos)
	{
		pos = parent;
		parent = find_par(parent, k);
	}
	// Locate the predecessor:
	id = parent->findId(k);
	return parent->keys[id + 1];
}
// Find the parent of given node with a certain key:
BNode* B::find_par(BNode* node, int64_t k)
{
	BNode* par = root;
	int64_t id = par->findId(k);
	while (par->(*Child)[id] != node)
	{
		par = par->(*Child)[id];
		id = par->findId(k);
	}
	return par;
}
*/
/*
int main()
{
	B t(3);
	t.insert(1,9);
	t.insert(3,20);
	t.insert(7,1);
	t.insert(10,332);
	t.insert(11,43);
	t.insert(13,1);
	t.insert(14,32);
	t.insert(15,55);
	t.insert(18,93);
	t.insert(16,8);
	t.insert(19,12);
	t.insert(24,33);
	t.insert(25,3);
	t.insert(26,987);
	t.insert(4,109);
	t.insert(5,234);
	t.insert(20,77);
	t.insert(22,95);
	t.insert(2,123);
	t.insert(17,68);
	t.insert(12,14);
	t.insert(6,5);
	//write your test here//
	cout << "B:" << endl;
	t.traverse();
	cout << endl;
	
	cout << "Max key is " << t.find_max() << endl;
	cout << "Min key is " << t.find_min() << endl;
	cout << "The predecessor of 1 is " << t.findPrec(1) << endl;
	cout << "The predecessor of 13 is " << t.findPrec(13) << endl;
	cout << "The predecessor of 5 is " << t.findPrec(5) << endl;
	cout << "The successor of 11 is " << t.findSucc(11) << endl;
	cout << "The successor of 24 is " << t.findSucc(24) << endl;
	cout << "The successor of 26 is " << t.findSucc(26) << endl;
	
	return 0;
}
*/
