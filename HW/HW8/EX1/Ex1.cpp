/*
 * Copyright@Naveen
 * 6:24:49 PM
 * Btree.cpp
 *
 * Some implementations is not satisfied for what we learnt in class and book.
 * This file is modified by Tianyu Zhang.
 * Modification is marked with ***
 */
#include <iostream>
#include <stdio.h>

using namespace std;
/* In BtreeNode class 
   We just store the key and we do not store value 
   if you want, you can modify the class definition of Btree Node.
*/
class BtreeNode
{
	int *a;				// Pointer to list of keys
	BtreeNode **C;		// Pointer to a list containing ptr of childs
	int n;				// The number of keys in this node
	int t;				// Mini-degree for the tree, n must be in range (t-1, 2t-1) except for root node
	bool leaf;			// If it is a leaf node
public:
	BtreeNode(int t,bool leaf)
    {
		this->t = t;
		this->leaf = leaf;
		a = new int[2*t-1];
		C = new BtreeNode*[2*t];
		n = 0;
    }
	int findId(int k);
	void remove(int k);
	void removeFromLeaf(int id);
	void removeFromNonLeaf(int id);
	void borrowFromPrev(int id);
	void borrowFromSucc(int id);
	int findSucc(int id);
	int findPrec(int id);
	void merge(int id);
	void fill(int id);
	void traverse();
	BtreeNode *search(int k);
	void insertNonFull(int k);
	void splitChild(int i,BtreeNode *y);

friend class Btree;
};

class Btree
{
	BtreeNode* root;	// Root node pointer
	int t;				// Mini-degree
public:
	Btree(int t)
    {
		root = new BtreeNode(t,true);	// Create root node
		this->t = t;
    }
	void insert(int k);
	void remove(int k);
    int find_max();		// TO DO
    int find_min();		// TO DO
	int findSucc(int k);// TO DO
	int findPrec(int k);// TO DO
	void traverse()		// Print all the elements in the tree
	{
		if(root == NULL) return;
		else
			root->traverse();
	}
	BtreeNode *search(int k)	// Get the node with key k
	{
		return (root==NULL) ? NULL : root->search(k);
	}
};

// Find the index of key with value k in this node:
// If the key is not in this node, the index will be n or the index of the next larger key.
int BtreeNode :: findId(int k)
{
	int i;
	for (i = 0; i < n && a[i] < k; i++);
	return i;
}
// Remove the key with value k in this node:
void BtreeNode :: remove(int k)
{
	int id = findId(k);
	// Check if the key is in this node:
	if(id < n && a[id] == k)
	{	// The key is in this node:
		if(leaf)
			removeFromLeaf(id);			// NOW THERE !!!!!!!!!!!!!
		else
			removeFromNonLeaf(id);
	}
	else
	{	// The key is not in this node, check if this node is a leaf node:
		if(leaf)
		{
		cout<<"Element does not exist"<<endl;
		return;
		}
		else
		{
			bool flag;
			if(n == id)		// The key is in the last child of this node
				flag = true;
			else
				flag = false;

			if(C[id]->t < t)	//???
				fill(id);

			if(flag && id > n)
				C[id-1]->remove(k);
			else
				C[id]->remove(k);
		}
	}
}
// Remove a key from leaf node:
void BtreeNode::removeFromLeaf(int id)
{
	for (int i = id + 1; i < n; i++)
	{
		a[i-1] = a[i];
	}
	n--;
	// Did not check if n is less than floor(t) ?????
}
// Remove a key from non-leaf node:
void BtreeNode :: removeFromNonLeaf(int id)
{
	if(C[id]->n >= t)
	{	// ????
		a[id]=findPrec(id);		// Replace by presuccessor
		C[id]->remove(a[id]);	// Remove the presuccessor from its node
	}
	else if(C[id+1]->n >= t)
	{	// ????
		a[id]=findSucc(id);		// Replace by successor
		C[id+1]->remove(a[id]);	// Remove the successor from its node
	}
	else
	{
		int d = a[id];
		merge(id);				
		C[id]->remove(d);
	}
}

int BtreeNode :: findPrec(int id)
{
	BtreeNode *curr = C[id];
	while(!curr->leaf)		// Go to the leaf node
		curr = curr->C[curr->n];
	return curr->a[curr->n-1];
}

int BtreeNode :: findSucc(int id)
{
	BtreeNode *curr = C[id+1];
	while(!curr->leaf)
		curr = curr->C[0];
	return curr->a[0];
}

void BtreeNode :: fill(int id)
{
	if(id!=0 && C[id-1]->n>=t)
		borrowFromPrev(id);
	else if(id!=n && C[id+1]->n>=t)
		borrowFromSucc(id);
	else
	{
		if(id!=n)
			merge(id);
		else
			merge(id-1);
	}

}

void BtreeNode :: borrowFromPrev(int id)
{
	BtreeNode *child = C[id];
	BtreeNode *sibling = C[id-1];

	for(int i = child->n-1;i >=0 ;i--)
		child->a[i+1] = child->a[i];

	if(!child->leaf)
	{
		for(int i=child->n;i>=0;i++)
			child->C[i+1] = child->C[i];
	}
	child->a[0] = a[id-1];
	if(!child->leaf)
		child->C[0] = sibling->C[sibling->n];
	a[id-1] = sibling->a[sibling->n-1];
	(child->n)++;
	(sibling->n)--;

}

void BtreeNode :: borrowFromSucc(int id)
{

	BtreeNode *child = C[id];
	BtreeNode *sibling = C[id+1];

	child->a[child->n] = a[id];
	a[id] = sibling->a[0];

	if(!child->leaf){
	child->C[(child->n)+1] = sibling->C[0];
	}

	for(int i = 1;i<sibling->n;i++ )
		sibling->a[i-1] = sibling->a[i];
	if(!child->leaf){
	    for(int i = 1;i<=sibling->n;i++ )
		    sibling->C[i-1] = sibling->C[i];
	}

	(sibling->n)--;
	(child->n)++;
}
// Merge the two childs of given key k in this node:
void BtreeNode ::merge(int id)
{
	BtreeNode *child = C[id];
	BtreeNode *sibling = C[id+1];

	child->a[child->n] = a[id];

	for(int i=0;i<sibling->n;i++)
		child->a[child->n+1+i] = sibling->a[i];

	if(!child->leaf)
	{	for(int i=0;i<=sibling->n;i++)
				child->C[child->n+1+i] = sibling->C[i];
	}

	for(int i=id+1;i<n;i++)
		a[i-1] = a[i];
	for(int i=id+1;i<=n;i++)
		C[i-1]=C[i];
	child->n += sibling->n+1;
	n--;
	delete(sibling);
	return ;
}
// Remove a key k in the tree:
void Btree :: remove(int k)
{
	if(!root)
	{
		cout<<"The tree is empty\n";
		return;
	}
	root->remove(k);
	// If the root becomes empty after deletion, update the root node:
	if(root->n == 0)
	{
		BtreeNode *t = root;
		if(root->leaf)
			root = NULL;
		else
			root = root->C[0];
		delete t;
	}
	return;
}
// Print all the keys in current subtree with inorder traversal:
void BtreeNode :: traverse()
{
	int i;
	for(i = 0; i < n; i++)
	{
		if(leaf == false)
			C[i]->traverse();
		cout << a[i] << " ";
	}
}
// Find the node containing exactly the key with value k:
BtreeNode * BtreeNode :: search(int k)
{	
	int i;
	for(i = 0; i < n && a[i] < k; i++);
	if(a[i] == k)
		return this;

	if(leaf == true)
		return NULL;

	return C[i]->search(k);
}
// Add a key k in the tree:
void Btree ::insert(int k)
{
	if(root == NULL)
	{
		root = new BtreeNode(t,true);
		root->a[0] = k;
		root->n = 1;
	}
	else
	{
		if(root->n == 2*t-1)
		{
			BtreeNode *p = new BtreeNode(t,false);
			p->C[0] = root;
			p->splitChild(0,p->C[0]);
			int i=0;
			if(p->a[0] < k)
				i++;
			p->C[i]->insertNonFull(k);
			root = p;
		}
		else
			root->insertNonFull(k);
	}
}

void BtreeNode :: insertNonFull(int k)
{
 int i = n-1;
 if(leaf == true)
 {

	 while(i >=0 && k < a[i])
		 {
		 a[i+1] = a[i];
		 i--;
		 }
	 a[i+1] = k;
	 n = n+1;
}
 else
 {
	 while(i >=0 && k <a[i])
		 i--;
	 if(C[i+1]->n == 2*t-1)
	 {
		 splitChild(i+1,C[i+1]);
		 if(a[i+1] < k)
			 i++;
	 }
	 C[i+1]->insertNonFull(k);

 }
}

void BtreeNode::splitChild(int i,BtreeNode *y)
{
	BtreeNode *z = new BtreeNode(y->t,y->leaf);
	z->n = t-1;

	for(int j=0;j<t-1;j++)
		z->a[j] = y->a[j+t];
	if(y->leaf == false)
	{
		for(int j=0;j<t;j++)
			z->C[j] = y->C[j+t];
	}
	y->n = t-1;
	for(int j=n;j>=i+1;j--)
		C[j+1] = C[j];
	C[i+1] = z;
	for(int j=n-1;j>=i;j--)
		a[j+1] = a[j];
	a[i]=y->a[t-1];
	n = n+1;
}
//find the max key stored in B-tree//
int Btree::find_max()
{
    //Implement your code here//
	// Start with the root node, always find the last child of the current node,
	// until we reach a leaf node:
	BtreeNode* node = root;
	while (!node->leaf)
	{
		node = node->C[node->n];
	}
    return node->a[node->n - 1];
}
//find the min key stored in B-tree//
int Btree::find_min()
{
    //Implement your code here//
	// Start with the root node, always find the first child of the current node,
	// until we reach a leaf node:
	BtreeNode* node = root;
	while (!node->leaf)
	{
		node = node->C[0];
	}
	return node->a[0];
}
//find the predecessor of the given key//
int Btree :: findPrec(int k)
{
	// To start with, check if the key is in the tree:
	BtreeNode* pos = search(k);
	if (NULL == pos)
	{
		cout << "The key is not in the tree!!" << endl;
		return k;
	}
	// Now, check if the node is a leaf node:
	int id_0 = pos->findId(k);
	if (!pos->leaf)
	{
		return pos->findPrec(id_0);
	}
	else
	{
		// Check if the key is the first in the key list:
		if (id_0 != 0)
		{
			return pos->a[id_0 - 1];
		}
	}
	// Now deal with the exceptional case: first key of a leaf node
	// First, check if the key is the smallest key of the tree:
	if (k == find_min())
	{
		cout << "The key has no predecessor!!" << endl;
		return k;
	}
	// Second, check if the key is in the root node:
	int id = root->findId(k);
	if (id < root->n && root->a[id] == k)
	{
		return root->a[id - 1];
	}
	// Then, find the node where the parent of the key locates:
	BtreeNode* node = root;
	while (node->C[id] != pos)
	{
		node = node->C[id];
		id = node->findId(k);
	}
	// Locate the node of predecessor:
	BtreeNode* find = node->C[id - 1];
	return find->a[find->n - 1];
}

//find the successor of the given key//
int Btree :: findSucc(int k)
{
	// To start with, check if the key is in the tree:
	BtreeNode* pos = search(k);
	if (NULL == pos)
	{
		cout << "The key is not in the tree!!" << endl;
		return k;
	}
	// Now, check if the node is a leaf node:
	int id_0 = pos->findId(k);
	if (!pos->leaf)
	{
		return pos->findSucc(id_0);
	}
	else
	{
		// Check if the key is the last in the key list:
		if (id_0 != pos->n)
		{
			return pos->a[id_0 + 1];
		}
	}
	// Now deal with the exceptional case: last key of a leaf node
	// First, check if the key is the largest key of the tree:
	if (k == find_max())
	{
		cout << "The key has no successor!!" << endl;
		return k;
	}
	// Second, check if the key is in the root node:
	int id = root->findId(k);
	if (id < root->n && root->a[id] == k)
	{
		return root->a[id + 1];
	}
	// Then, find the node where the parent of the key locates:
	BtreeNode* node = root;
	while (node->C[id] != pos)
	{
		node = node->C[id];
		id = node->findId(k);
	}
	// Locate the node of successor:
	BtreeNode* find = node->C[id + 1];
	return find->a[0];
}

int main()
{
	Btree t(3);
	t.insert(1);
	t.insert(3);
	t.insert(7);
	t.insert(10);
	t.insert(11);
	t.insert(13);
	t.insert(14);
	t.insert(15);
	t.insert(18);
	t.insert(16);
	t.insert(19);
	t.insert(24);
	t.insert(25);
	t.insert(26);
	t.insert(4);
	t.insert(5);
	t.insert(20);
	t.insert(22);
	t.insert(2);
	t.insert(17);
	t.insert(12);
	t.insert(6);
    //write your test here//
	cout << t.find_max() << endl;
	cout << t.find_min() << endl;
	cout << t.findPrec(13) << endl;
	cout << t.findSucc(24) << endl;
    return 0;
}
